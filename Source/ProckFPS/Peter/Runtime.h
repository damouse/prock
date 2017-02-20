#pragma once
#include "Object.h"

#include "PythonBindings.h"
#include "Nodes/ProckNodeSubclasses.h"
#include "Actors/BoxActor.h"

#include "Runtime.generated.h"


// Loads the code, loads the debugger shim, and then executes the code by stepping through it. 
// Assume that LoadPython has already been called in BeginPlay
/*
Running:

Scope			collection of variables. Can be created during a run cycle
Run Cycle		one step of the runner, corresponding to the execution of a single line of code

Tick:			windup animation
Turnover:		step debugger and update values instantaneously
Tock:			winddown animation

Progress	pick the next node to run
Anup		run initial animations
Tick		tick the debugger
Andown		run teardown animations

Its not clear what the biggest value of the program is yet. Do basic running and riting and then move forward.
*/
UCLASS()
class PROCKFPS_API URuntime: public UObject
{
public:
	GENERATED_BODY()

	// Init with the root ProckNode, the native debugger, and the "table"-- or the collection of scope variables
	//URuntime();

	// Tick the debugger once. This involves updating the table, finding the right ProckNodes to act on, 
	// ticking the native debugger, and updating the values in the world
	void Tick();

	// Run the runner on a timer that ticks with the given interval
	void StartTimed(float t);
	void StopTimed();

	// Kill the native debugger and stop. 
	bool Shutdown();

//private:
	ProckNode *root;
	PyObject *runner;
	ABoxActor *table;

	FTimerHandle runnerTimerHandler;
};
