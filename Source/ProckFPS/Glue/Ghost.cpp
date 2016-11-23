// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Ghost.h"

Ghost::Ghost(PNName *n) {
	name = n->Value();
	nodes.insert(n);
}

bool Ghost::AddReference(PNName *n) {
	// Check to make sure the names match
	if (strcmp(name, n->Value()) != 0) {
		return false;
	}
	
	nodes.insert(n);
	n->ghost = this;
	return true;
}