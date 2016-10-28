// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

#include <list>


/**
 * Interfaces with the native python components
 */
class PROCKFPS_API PythonBindings {
public:
	PythonBindings();
	~PythonBindings();

	// Load the environment  then load the root node
	PyObject * ImportCode();

private: 
	void PythonGILAcquire();
	void PythonGILRelease();
	void *ue_python_gil;
	PyObject *pypeter;
};

void printpy(PyObject *obj);
void log_py_error();

// Returns the attribute as a string if the attribute exists. Equivalent to "a.b" where "a" is the object and "b" is the attribute
char *pyGetAttr(PyObject* obj, char *attrName);