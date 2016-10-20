// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PythonBindings.h"

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
	PythonBindings *bindPython;
};
