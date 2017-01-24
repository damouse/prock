// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PythonBindings.h"
#include "Nodes/ProckNodeSubclasses.h"

/**
 * Peter manages editting code: loading and reading, transforming the AST, 
 * saving, and more.
 *
 * Until we get a better idea of what "node transformations" actually mean this 
 * class is going to be pretty light. 
 * 
 * Right now only python is supported so all the nodes are PythonNodes. Notes that the python heavy 
 * lifting is done by PythonBindings, not here. 
 */
class PROCKFPS_API Peter
{
public:
	Peter();
	~Peter();
	
	// Load a python filename into peter, return the root node for the loaded code
	ProckNode * LoadPython();
	void UnloadPython();

	// Run a previously loaded python file using the native python debugger wrapper
	void RunPython();

private: 
	PythonBindings *bindPython; // Don't know if this needs to stick around. Thinking the root node is enough

	// The root of the loaded ast
	ProckNode *prockRootNode;
};
