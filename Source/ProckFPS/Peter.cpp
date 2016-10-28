// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"

Peter::Peter() {}
Peter::~Peter() {}

// Instantiate python bindings, import the code, and set the root ProckNode to the top level node returned by the import
PythonNode * Peter::LoadPython() {
	bindPython = new PythonBindings();
	PyObject *ast = bindPython->ImportCode();
	
	if (!ast) {
		UE_LOG(LogProck, Error, TEXT("Peter could not load python"));
		return nullptr;
	}

	prockRootNode = new PythonNode(nullptr);
	prockRootNode->InitRoot(ast);

	//prockRootNode->Resolve();
	//prockRootNode->Print();

	//for (ProckNode *node : prockRootNode->Children()) {
	//	PythonNode *pyNode = (PythonNode *)node;

	//	PythonNode *target = pyNode->GetTarget();
	//	if (target) {
	//		//target->Resolve();
	//		UE_LOG(LogProck, Log, TEXT("Target: %s"), UTF8_TO_TCHAR(target->GetType()));
	//	}

	//	//UE_LOG(LogProck, Log, TEXT("%s"), UTF8_TO_TCHAR(pyNode->GetType()));'
	//	//if (node->Type() != PNT_Endl)
	//	//	UE_LOG(LogProck, Error, TEXT("Type exists"));

	//	//if (node->Type() != PNT_Endl && node->Type() != PNT_Comment) {
	//	//	node->Print();
	//	//}
	//}

	return prockRootNode;
}

void Peter::UnloadPython() {
	delete bindPython;
	delete prockRootNode;
}