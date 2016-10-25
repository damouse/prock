// Fill out your copyright notice in the Description page of Project Settings.
#include "ProckFPS.h"
#include "PythonNode.h"
#include "ProckNode.h"

PythonNode::PythonNode(PyObject *native): ProckNode() {
	this->native_node = native;
}

// TODO: cleanup python objects as needed
PythonNode::~PythonNode() {
	this->native_node = nullptr;
}

void PythonNode::Resolve() {
	if (!this->resolved) {

	}
}
