// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PythonBindings.h"
#include "ProckNode.h"

/**
 * 
 */
class PROCKFPS_API Peter
{
public:
	Peter();
	~Peter();

	void LoadPython();
	void UnloadPython();

private: 
	PythonBindings *bindPython; // Don't know if this needs to stick around. Thinking the root node is enough

	// The root of the loaded ast
	ProckNode *prockRootNode;
};
