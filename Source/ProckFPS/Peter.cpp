// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"

Peter::Peter() {}
Peter::~Peter() {}

void Peter::LoadRoom() {
	// Need to specify which room to load. Assuming that null means to load the root
	if (!prockRootNode) {
		UE_LOG(LogProck, Error, TEXT("Root node not initialized"));
		return;
	}

	for (ProckNode *node : prockRootNode->Children()) {
		node->Resolve();

		//if (node->Type() != PNT_Endl)
		//	UE_LOG(LogProck, Error, TEXT("Type exists"));

		if (node->Type() != PNT_Endl && node->Type() != PNT_Comment) {
			node->Print();
		}
	}
}

// Instantiate python bindings, import the code, and set the root ProckNode to the top level node returned by the import
void Peter::LoadPython() {
	bindPython = new PythonBindings();
	prockRootNode = bindPython->ImportCode();

	if (!prockRootNode) {
		UE_LOG(LogProck, Error, TEXT("An error occured loading the root ProckNode"));
		return;
	}

	prockRootNode->Resolve();
	prockRootNode->Print();
}

void Peter::UnloadPython() {
	delete bindPython;
	delete prockRootNode;
}