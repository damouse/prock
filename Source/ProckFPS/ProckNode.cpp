// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

ProckNode::ProckNode(PyObject *native) {
	astNode = native;
}

ProckNode::~ProckNode() {}

void ProckNode::Spawn() {

}

char *ProckNode::GetAsString(char *name) {
	return nullptr;
}

std::vector<ProckNode *> ProckNode::GetAsList(char *name) {
	return {};
}

ProckNode *ProckNode::GetAsNode(char *name) {
	return nullptr;
}
