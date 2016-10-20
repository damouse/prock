// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"


Peter::Peter() {}
Peter::~Peter() {}

void Peter::LoadPython() {
	bindPython = new PythonBindings();
	//Using the unrealenginepythonmodule only as a means of bootstrapping the python environment
	// Once loaded we just cast the main dict and operate on it (mostly) directly
	//python = new FUnrealEnginePythonModule();
	//python->StartupModule();
	//python->RunString("import peter");

	//PyObject *dict = (PyObject *)python->main_dict;

	//UE_LOG(LogAndroid, Log, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(dict))));
}

void Peter::UnloadPython() {
	//python->ShutdownModule();
}