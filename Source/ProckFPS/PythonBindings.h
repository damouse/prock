// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
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


/**
 * 
 */
class PROCKFPS_API PythonBindings {
public:
	PythonBindings();
	~PythonBindings();

	PyObject *RunString(char *str);

private: 
	FUnrealEnginePythonModule *python;
};
