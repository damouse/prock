// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"

Peter::Peter() {}
Peter::~Peter() {}

void Peter::LoadRoom() {
	// Need to specify which room to load. Assuming that null means to load the root
	// Note: not testing if the root node exists

	for (ProckNode *node : prockRootNode->Children()) {
		node->Resolve();
		node->Print();
	}
}

// Instantiate python bindings, import the code, and set the root ProckNode to the top level node returned by the import
void Peter::LoadPython() {
	bindPython = new PythonBindings();
	prockRootNode = bindPython->ImportCode();

	prockRootNode->Resolve();
	prockRootNode->Print();
}

void Peter::UnloadPython() {
	delete bindPython;
	delete prockRootNode;
}