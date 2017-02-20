// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Runtime.h"

#include "Utils/Config.h"

/*
Have to:
- Setup the table: spawn a bunch of boxes in the middle of the world
- Keep track of the current ProckNode and code line
- Matches nodes to values in locals
- Use a timeout to space out steps (BaseGameMode is going to handle this)
- Make some visual indication of progress


Keep the BaseGameMode slim, just a glue for the components of the app. Don't put view logic for this in there.
*/

void URuntime::StartTimed(float t) {
	if (!UConfig::world->GetTimerManager().IsTimerPaused(runnerTimerHandler)) {
		UConfig::world->GetTimerManager().SetTimer(runnerTimerHandler, this, &URuntime::Tick, t, true);
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

void URuntime::Tick() {
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
