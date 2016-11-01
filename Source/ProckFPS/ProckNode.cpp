// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

ProckNode *ProckNode::NewNode(PyObject *native) {
	// Type will resolve for everything Except 
	PyObject *klass = PyObject_GetAttrString(native, "__class__");
	
	if (!klass) {
		log_py_error();
		return nullptr;
	}	

	PyObject *name = PyObject_GetAttrString(klass, "__name__");

	if (!name) {
		log_py_error();
		return nullptr;
	}

	// Switch on the class. If the class name cannot be found fallthrough here
	// in the case of name == RedBaron

	ProckNode *ret = new ProckNode();
	ret.

	UE_LOG(LogProck, Error, TEXT("%s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(name))));
	return nullptr;
}

void ProckNode::Spawn() {

}

char *ProckNode::GetAsString(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : PyString_AsString(PyObject_Str(r));
}

std::vector<ProckNode *> ProckNode::GetAsList(char *name) {
	return {};
}

ProckNode *ProckNode::GetAsNode(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : ProckNode::NewNode(r);
}
