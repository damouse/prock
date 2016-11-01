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

	NodeList *ret = new NodeList();
	ret->astNode = native;

	UE_LOG(LogProck, Error, TEXT("Assigned the root node."));
	return ret;
}

void ProckNode::Spawn() {

}

char *ProckNode::GetAsString(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : PyString_AsString(PyObject_Str(r));
}

std::vector<ProckNode *> *ProckNode::GetAsList(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);

	// Make sure we recieved a list
	if (!PyIter_Check(r)) {
		UE_LOG(LogProck, Error, TEXT("Did not recieve list in node request"));
		return nullptr;
	}

	PyObject *iterator = PyObject_GetIter(r);

	if (iterator == NULL) {
		UE_LOG(LogProck, Error, TEXT("Could not iterate over node list"));
		return nullptr;
	}

	std::vector<ProckNode *> *result = new std::vector<ProckNode*>();
	PyObject *item = PyIter_Next(iterator);

	while (item) {
		ProckNode *a = ProckNode::NewNode(item);

		if (!a) {
			UE_LOG(LogProck, Error, TEXT("Unable to create node for %s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
			delete result;
			Py_DECREF(iterator);
			return nullptr;
		}

		result->push_back(a);
		item = PyIter_Next(iterator);
		// Py_DECREF(item);
	}

	

	//for (int i = 0; i < PyList_Size(r); i++) {
	//	PyObject *item = PyList_GetItem(r, i);

	//	if (!item) {
	//		UE_LOG(LogProck, Error, TEXT("Unable to get item from list: %s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
	//		delete result;
	//		return nullptr;
	//	}

	//	ProckNode *a = ProckNode::NewNode(item);

	//	if (!a) {
	//		UE_LOG(LogProck, Error, TEXT("Unable to create node for %s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
	//		delete result;
	//		return nullptr;
	//	}

	//	result->push_back(a);
	//}

	Py_DECREF(iterator);
	return result;
}

ProckNode *ProckNode::GetAsNode(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : ProckNode::NewNode(r);
}

void ProckNode::PrintRaw() {
	if (astNode) {
		PyObject *dict = PyObject_GetAttrString(astNode, "__dict__");
		if (dict) {
			printpy(dict);
		} else {
			UE_LOG(LogProck, Error, TEXT("Unable to retrieve object __dict__, fallback to str()"));
			printpy(astNode);
		}
	} else {
		UE_LOG(LogProck, Error, TEXT("Native python object not set!"));
	}
}