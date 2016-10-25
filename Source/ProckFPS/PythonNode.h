// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProckFPS.h"
#include "PythonBindings.h" // Don't really need to import this seperately, it just has the python headers
#include "ProckNode.h"

/**
 * A C++ wrapper around a python AST node.  
 */
class PROCKFPS_API PythonNode: public ProckNode
{
public:
	PythonNode(PyObject *native);
	~PythonNode();

	// Called only once by PythonBindings when initializing the root of the AST.
	void InitRoot(PyObject *astList);

	virtual void Resolve() override;
	virtual void Print() override;

private: 
	PyObject *pythonNode;
};
