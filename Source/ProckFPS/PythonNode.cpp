// Fill out your copyright notice in the Description page of Project Settings.
#include "ProckFPS.h"
#include "PythonNode.h"
#include "ProckNode.h"
#include "PythonBindings.h"

#include <cstring>

PythonNode::PythonNode(PyObject *native): ProckNode() {
	pythonNode = native;
}

// TODO: cleanup python objects as needed
PythonNode::~PythonNode() {
	pythonNode = nullptr;
}

// Called from the bindings when initializing the graph. Immediately resolve us and set our children
// astList is assuemd to be a python list.
void PythonNode::InitRoot(PyObject *astList) {
	for (int i = 0; i < PyList_Size(astList); i++) {
		PyObject *item = PyList_GetItem(astList, i);
		if (!item) {
			log_py_error();
			return;
		}

		children.push_back(new PythonNode(item));
	}

	type = PNT_Root;
	resolved = true;
}

// Resolve the fields for this node by querying the native nodes. Will run even if "resolved" is true.
void PythonNode::Resolve() {
	// the root is always resolved if it exists
	if (type == PNT_Root) {
		resolved = true;
		return;
	}

	// Reset the resolved state. In the case of an error this node remains unresolved
	resolved = false;

	// Set our type
	char *name = pyGetAttr(pythonNode, "type");
	if (!name) {
		UE_LOG(LogProck, Error, TEXT("Native node has no type field"));
		return;
	} else {
		type = pntFromPyString(name);
	}

	// Play around with what we got
	//PyObject *keys = PyObject_GetAttrString(pythonNode, "_dict_keys");
	//if (!keys) {
	//	log_py_error();
	//} else {
	//	printpy(keys);
	//}

	resolved = true;
}

// Return this node's type as a string. TODO: change this to the enum directly
char *PythonNode::GetType() {
	char *name = pyGetAttr(pythonNode, "type");
	if (!name) {
		UE_LOG(LogProck, Error, TEXT("Native node has no type field"));
		return nullptr;
	} else {
		return pntToString(pntFromPyString(name));
	}
}

PythonNode *PythonNode::GetTarget() {
	PyObject *keys = PyObject_GetAttrString(pythonNode, "target");
	if (!keys) {
		UE_LOG(LogProck, Error, TEXT("Native node has no field target"));
		return nullptr;
	} else {
		return new PythonNode(keys);
	}
}

PythonNode *PythonNode::GetValue() {
	PyObject *keys = PyObject_GetAttrString(pythonNode, "value");
	if (!keys) {
		UE_LOG(LogProck, Error, TEXT("Native node has no field value"));
		return nullptr;
	} else {
		return new PythonNode(keys);
	}
}

PythonNode *PythonNode::GetFirst() {
	PyObject *keys = PyObject_GetAttrString(pythonNode, "first");
	if (!keys) {
		UE_LOG(LogProck, Error, TEXT("Native node has no field first"));
		return nullptr;
	} else {
		return new PythonNode(keys);
	}
}

PythonNode *PythonNode::GetSecond() {
	PyObject *keys = PyObject_GetAttrString(pythonNode, "second");
	if (!keys) {
		UE_LOG(LogProck, Error, TEXT("Native node has no field second"));
		return nullptr;
	} else {
		return new PythonNode(keys);
	}
}

void PythonNode::Print() {
	print("PythonNode");
}
