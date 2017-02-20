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


/*
Misc TODO
	- Setup the table: spawn a bunch of boxes in the middle of the world
	- Keep track of the current ProckNode and code line
		- Get the prock nodes to report their line numbers
	- Matches nodes to values in locals by searching nameNodes
	- Basic anup and andown animations
*/
void URuntime::Step() {
	// Tock- wind down animations from last runner step if the line number is not 0
	// Step the native runner. Get the line numbers and locals for this step 
	// Find ProckNode that matches line number
	// Tick- windup animations
	// Turnover- compare new locals with contents of table, and create new boxes as needed. Search whole tree and table for name matches to local and upate values

	PyObject *locals = PyObject_CallMethod(runner, (char *)"tick_locals", NULL);

	if (!locals) {
		log_py_error();
		return;
	}
	
	printpy(locals);

	// Go through the tree and animate the changes?
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
	if (!UConfig::world->GetTimerManager().IsTimerPaused(runnerTimerHandler)) {
		UConfig::world->GetTimerManager().SetTimer(runnerTimerHandler, this, &URuntime::Step, t, true);
	} else {
		UE_LOG(LogProck, Error, TEXT("Runner asked to start a timer thats already running"));
	}
}


void URuntime::StopTimed() {
	if (UConfig::world->GetTimerManager().IsTimerPaused(runnerTimerHandler)) {
		UConfig::world->GetTimerManager().PauseTimer(runnerTimerHandler);
	} else {
		UE_LOG(LogProck, Error, TEXT("Runner asked to stop a timer thats not running"));
	}
}
