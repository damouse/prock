// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Nodes/ProckNodeSubclasses.h"
#include "Actors/GhostActor.h"
#include <set>

/**
 * A variable in scope. Ghosts have references to each place in which the variable
 * is used within a code block. This class is an abstract collection of all those references. 
 */
class PROCKFPS_API Ghost
{
public:
	// Create a new ghost instance. Returns nul
	Ghost(PNName *n);

	// Add the node to our set iff it doesn't exist. Return true if the add succeeded
	bool AddReference(PNName *n);

//private:
	char *name;
	std::set<PNName *> nodes;

	// In engine representation for this ghost
	AGhostActor *ghostActor;
};
