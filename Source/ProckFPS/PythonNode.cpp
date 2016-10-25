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
	if (type != PNT_Root && !pythonNode) {
		UE_LOG(LogProck, Error, TEXT("Native node not set, cannot resolve"));
		resolved = false;
		return;
	}

	// Check to see if we're a root node by querying the "parent" string, which is None or doesnt exist on roots
	//char *isParent = pyGetAttr(pythonNode, "parent");
	//UE_LOG(LogProck, Error, TEXT("Loaded a child"));

	//if (isParent != nullptr && strcmp(isParent, "None") == 0) {
	//	UE_LOG(LogProck, Error, TEXT("Is a parent!"));
	//	type = PNT_Root;

	//	PyObject *pyChildren = PyObject_GetAttrString(pythonNode, "node_list");
	//	printpy(pyChildren);

	//	if (pyChildren == nullptr || !PyList_Check(pyChildren)) {
	//		log_py_error();
	//		UE_LOG(LogProck, Error, TEXT("Not given a list"));
	//		return;
	//	}

	//	// Enqueue all children, but don't resolve them
	//	for (int i = 0; i < PyList_Size(pyChildren); i++) {
	//		PyObject *kid = PyList_GetItem(pyChildren, i);
	//		if (!kid) {
	//			log_py_error();
	//			return;
	//		}

	//		children.push_back(new PythonNode(kid));

	//	}

	//}
	// Not the root node
		////FString name = UTF8_TO_TCHAR(PyString_AsString(PyObject_GetAttrString(item, (char *)"type")));

		//if (name.Equals(TEXT("endl"))) {
		//	UE_LOG(LogProck, Log, TEXT("endl"));

		//} else if (name.Equals(TEXT("comment"))) {
		//	UE_LOG(LogProck, Log, TEXT("comment"));

		//} else if (name.Equals(TEXT("assignment"))) {
		//	UE_LOG(LogProck, Log, TEXT("assignment"));

		////} else if (name.Equals(TEXT("assignment"))) {
		////	UE_LOG(LogProck, Log, TEXT("assignment"));

		//} else {
		//	// This line errs
		//	//UE_LOG(LogProck, Error, TEXT("Unknown node type: %s"), name);
		//}
	

	resolved = true;
}

void PythonNode::Print() {
	print("PythonNode");
}