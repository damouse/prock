// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter/Peter.h"

#include "Peter/Runtime.h"


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


//Runtime* Peter::RunPython() {
//	PyObject *pyRunner = pyBindings->LoadRunner();
//
//	if (!pyRunner) {
//		UE_LOG(LogProck, Error, TEXT("Peter could not load native runner"));
//		return nullptr;
//	}
//
//	Runtime *runner = new Runtime(prockRootNode, pyRunner);
//	return runner;
//}