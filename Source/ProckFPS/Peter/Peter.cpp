// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter/Peter.h"

Peter::Peter() {}
Peter::~Peter() {}

// Instantiate python bindings, import the code, and set the root ProckNode to the top level node returned by the import
ProckNode *Peter::LoadPython() {
	bindPython = new PythonBindings();
	PyObject *ast = bindPython->ImportCode();
	
	if (!ast) {
		UE_LOG(LogProck, Error, TEXT("Peter could not load python"));
		return nullptr;
	}

	prockRootNode = ProckNode::NewNode(ast);
	return prockRootNode;
}

void Peter::UnloadPython() {
	delete bindPython;
	delete prockRootNode;
}