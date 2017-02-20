#pragma once
#include "Object.h"

#include "PythonBindings.h"
#include "Nodes/ProckNodeSubclasses.h"
#include "Actors/BoxActor.h"

#include "Runtime.generated.h"


// Loads the code, loads the debugger shim, and then executes the code by stepping through it. 
// Assume that LoadPython has already been called in BeginPlay

UCLASS()
class PROCKFPS_API URuntime: public UObject
{
public:
	GENERATED_BODY()

	// Init with the root ProckNode, the native debugger, and the "table"-- or the collection of scope variables
	//URuntime();

	// Tick the debugger once. This involves updating the table, finding the right ProckNodes to act on, 
	// ticking the native debugger, and updating the values in the world
	void Step();

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
