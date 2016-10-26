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

	// Version 2. Always-dynamic getters
	char *GetType();

	PythonNode *GetTarget();
	PythonNode *GetValue();
	PythonNode *GetFirst();
	PythonNode *GetSecond();

	// ifelse, operator, etc
	//PythonNode *Get();
	
	// Next, previous, parent

private: 
	PyObject *pythonNode;
};

/*
Example values based on node type: 

a = 1

AssignmentNode()
	operator=''
	target ->
		NameNode()
			value='a'
	value ->
		IntNode()
			value='1'


1 + a

BinaryOperatorNode()
    value='+'
    first ->
		IntNode()
			value='1'
    second ->
		NameNode()
			value='a'
*/
