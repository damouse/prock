// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Peter.h"
#include "UnrealEnginePython.h"

#if UNREAL_ENGINE_PYTHON_ON_MAC == 3
#include <python3.5m/Python.h>
#include <python3.5m/structmember.h>
#elif UNREAL_ENGINE_PYTHON_ON_MAC == 2
#include <python2.7/Python.h>
#include <python2.7/structmember.h>
#elif UNREAL_ENGINE_PYTHON_ON_LINUX
#include <Python.h>
#include <structmember.h>
#else
#include <include/Python.h>
#include <include/structmember.h>
#endif

Peter::Peter() {
	//Using the unrealenginepythonmodule only as a means of bootstrapping the python environment
	// Once loaded we just cast the main dict and operate on it (mostly) directly
	FUnrealEnginePythonModule python = FUnrealEnginePythonModule();
	python.StartupModule();
	python.RunString("import peter");
	PyObject *dict = (PyObject *)python.main_dict;

	UE_LOG(LogAndroid, Log, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(dict))));

	python.ShutdownModule();
}

Peter::~Peter() {
}
