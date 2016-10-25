// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"


Peter::Peter() {}
Peter::~Peter() {}

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