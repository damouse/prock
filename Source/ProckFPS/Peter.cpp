// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"


Peter::Peter() {}
Peter::~Peter() {}

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