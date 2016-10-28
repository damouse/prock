// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PythonBindings.h"
#include "PythonNode.h"

/**
 * Peter manages editting code: loading and reading, transforming the AST, 
 * saving, and more.
 * 
 * Right now only python is supported so all the nodes are PythonNodes. Notes that the python heavy 
 * lifting is done by PythonBindings, not here. 
 */
class PROCKFPS_API Peter
{
public:
	Peter();
	~Peter();
	
	PythonNode * LoadPython();
	void UnloadPython();

private: 
	PythonBindings *bindPython; // Don't know if this needs to stick around. Thinking the root node is enough

	// The root of the loaded ast
	PythonNode *prockRootNode;
};
