// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter/Peter.h"

Peter::Peter() {}
Peter::~Peter() {}

// Instantiate python bindings, import the code, and set the root ProckNode to the top level node returned by the import
ProckNode *Peter::LoadPython() {
	pyBindings = new PythonBindings();
	PyObject *ast = pyBindings->ImportCode();
	
	if (!ast) {
		UE_LOG(LogProck, Error, TEXT("Peter could not load python"));
		return nullptr;
	}

	prockRootNode = ProckNode::NewNode(ast);
	return prockRootNode;
}

void Peter::UnloadPython() {
	delete pyBindings;
	delete prockRootNode;
}

void Peter::RunPython() {
	PyObject *runner = pyBindings->LoadRunner();

	if (!runner) {
		UE_LOG(LogProck, Error, TEXT("Peter could not load the runner"));
		return;
	}

	for (int i = 0; i < 10; i++) {
		// Runner.tick() returns the list of local variables after a debugger step 
		PyObject *locals = PyObject_CallMethod(runner, (char *)"tick", NULL);

		if (!locals) {
			log_py_error();
		} else {
			printpy(locals);
		}
	}
}