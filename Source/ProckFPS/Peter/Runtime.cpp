//// Fill out your copyright notice in the Description page of Project Settings.

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

Note that theres a problem with this logic: values are not updated in the currently paused node until 
the next step of the debugger. 
*/

/*
Misc TODO
	- Setup the table: spawn a bunch of boxes in the middle of the world
	- Keep track of the current ProckNode and code line
		- Get the prock nodes to report their line numbers
	- Matches nodes to values in locals by searching nameNodes
	- Basic anup and andown animations
*/
void URuntime::Step() {
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

	// Tock- wind down animations from last runner step and clear the animating boxes
	// Problem: values are not updates until the next step. Have to check the locals for updates here, at the start of the next step
	for (auto& n : activeNodes) {
		n->Assign(locals, false);
		n->Activate(false);
	}

	activeNodes.Empty();

	PNList *list = (PNList *)root;
	int debuggerLineNumber = atoi(PyString_AsString(PyObject_Str(lineno)));
	//UE_LOG(LogProck, Log, TEXT("Debugger line Number: %d"), debuggerLineNumber);
	
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
			//UE_LOG(LogProck, Log, TEXT("Found node: %s"), ANSI_TO_TCHAR(child->Name()));
			current = child;
			break;
		}
	};

	if (current == nullptr) {
		UE_LOG(LogProck, Error, TEXT("Could not find ProckNode to match debugger line number: %d"), debuggerLineNumber);
		return;
	}

	// Tick- windup animations
	activeNodes.Add(current);

	for (auto& n : activeNodes) {
		n->Activate(true);
	}

	// Turnover- visualize the changes reported by the native debugger

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
