// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Runtime.h"

#include "Utils/Config.h"
/*
Some terms:

Scope			collection of variables. Can be created during a run cycle
Run Cycle		one step of the runner, corresponding to the execution of a single line of code

Tick:			windup animation
Turnover:		step debugger and update values instantaneously
Tock:			winddown animation

Progress	pick the next node to run
Anup		run initial animations
Tick		tick the debugger
Andown		run teardown animations
*/

// Node-specific runtime operations- find the locals that match our names and fill our values with them
void Assignment_Run(PNAssignment *n, PyObject* locals) {
	PyObject *target = PyDict_GetItemString(locals, n->Target()->Name());
	PyObject *value = PyDict_GetItemString(locals, n->Value()->Name());

	if (!target || !value) {
		log_py_error();
		return;
	}

	n->Target()->box->SetRunValue(PyString_AsString(PyObject_Str(target)));
	n->Value()->box->SetRunValue(PyString_AsString(PyObject_Str(value)));
}

void BinaryOperator_Run(PNBinaryOperator *n, PyObject* locals) {

}



/*
Misc TODO
	- Setup the table: spawn a bunch of boxes in the middle of the world
	- Keep track of the current ProckNode and code line
		- Get the prock nodes to report their line numbers
	- Matches nodes to values in locals by searching nameNodes
	- Basic anup and andown animations
*/
void URuntime::Step() {
	// Tock- wind down animations from last runner step and clear the animating boxes
	for (auto& box : activeBoxes) {
		box->SetRunstate(false);
	}

	activeBoxes.Empty();

	// Step the native runner. Get the line numbers and locals for this step 
	PyObject *res = PyObject_CallMethod(runner, (char *)"step", NULL);
	if (!res) {
		UE_LOG(LogProck, Error, TEXT("Unable to call step"));
		log_py_error();
		return;
	}

	PyObject *lineno = PyObject_GetAttrString(runner, "lineno");
	PyObject *locals = PyObject_GetAttrString(runner, "locals");

	if (!lineno || !locals) {
		UE_LOG(LogProck, Log, TEXT("Couldnt get information from the runner"));
		log_py_error();
		return;
	}

	PNList *list = (PNList *)root;
	int debuggerLineNumber = atoi(PyString_AsString(PyObject_Str(lineno)));
	UE_LOG(LogProck, Log, TEXT("Debugger line Number: %d"), debuggerLineNumber);
	
	if (debuggerLineNumber > list->NodeList()->size()) {
		UE_LOG(LogProck, Error, TEXT("Looking for a debugger line number out of codelist range"));
		StopTimed();
		return;
	}

	PyObject *at = PyObject_CallMethod(list->astNode, (char *)"at", (char *)"i", debuggerLineNumber);
	if (!res) {
		UE_LOG(LogProck, Error, TEXT("Calling at failed"));
		log_py_error();
		return;
	}

	// The target node's parent index
	PyObject *atNodeParentIndex = PyObject_GetAttrString(at, "index_on_parent");
	ProckNode *current = nullptr;

	for (auto& child : *list->NodeList()) {
		// index_on_parent crashes badly with endline nodes
		if (child->Type() == PNT_Endl) {
			continue;
		}

		PyObject *parentIndex = PyObject_GetAttrString(child->astNode, "index_on_parent");
		if (!parentIndex) {
			UE_LOG(LogProck, Error, TEXT("Calling index_on_parent failed on child node"));
			log_py_error();
			return;
		}

		// Check if the parent indicies match
		if (PyObject_Compare(parentIndex, atNodeParentIndex) == 0) {
			current = child;
			break;
		}
	};

	if (current == nullptr) {
		UE_LOG(LogProck, Error, TEXT("Could not find ProckNode to match debugger line number: %d"), debuggerLineNumber);
		return;
	}

	// Tick- windup animations
	// Child nodes should be "animated" too, but skipping for now
	// Ok, so there's a dumb mistake here: not all nodes have boxes. There may also be too many boxes in play, but 
	// deal with that after with solving the obvious problem. Immediate issue is storing relevant nodes in arrays

	activeBoxes.Add(current->box);

	for (auto& box : activeBoxes) {
		if (box) {
			box->SetRunstate(true);
		} else {
			UE_LOG(LogProck, Error, TEXT("No node found for node"));
		}
	}

	// Turnover- visualize the changes reported by the native debugger

	// There must be a generalizable way to collect the target nodes, but this will do for now 
	// This mirrors the design of the Spawn function. In other words: icky.
	char *name = current->Name();
	switch (current->Type()) {
	case PNT_Endl: 
	case PNT_Comment:
		UE_LOG(LogProck, Log, TEXT("Comment or endline"));
		break;

	case PNT_Assignment:		Assignment_Run((PNAssignment *) current, locals); break;
	case PNT_BinaryOperator:	BinaryOperator_Run((PNBinaryOperator *) current, locals); break;

	default:
		UE_LOG(LogProck, Error, TEXT("Unknown node %s at line %d, not sure how to update values"), ANSI_TO_TCHAR(name), current->GetLineNumber());
	}

	// Update the table	
}

bool URuntime::Shutdown() {
	PyObject *end = PyObject_CallMethod(runner, (char *)"reset_env", NULL);
	if (!end) {
		log_py_error();
		return false;
	} else {
		printpy(end);
		return true;
	}
}

void URuntime::StartTimed(float t) {
	// Debugging 
	PNList *list = (PNList *)root;

	if (!UConfig::world->GetTimerManager().IsTimerPaused(runnerTimerHandler)) {
		UConfig::world->GetTimerManager().SetTimer(runnerTimerHandler, this, &URuntime::Step, t, true);
	} else {
		UE_LOG(LogProck, Error, TEXT("Runner asked to start a timer thats already running"));
	}
}


void URuntime::StopTimed() {
	if (!UConfig::world->GetTimerManager().IsTimerPaused(runnerTimerHandler)) {
		UConfig::world->GetTimerManager().PauseTimer(runnerTimerHandler);
	} else {
		UE_LOG(LogProck, Error, TEXT("Runner asked to stop a timer thats not running"));
	}
}
