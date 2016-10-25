// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

ProckNode::ProckNode() {
	this->resolved = false;
	this->children = {};
	this->type = PNTUnresolved;
}

ProckNode::~ProckNode() {
	this->children = {};
	this->type = PNTUnresolved;
	this->parent = nullptr;
}
