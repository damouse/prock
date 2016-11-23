// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Glue/Ghost.h"
#include "Actors/LineActor.h"
#include "Nodes/ProckNode.h"

#include <vector>

/**
 * Collection of references visible within a certain scope, usually attached to a Node.
 * Belongs to some node; all nodes contained within the scope hold a reference to it. 
 *
 * Think of this class as a representation of the nested content within a node and not the node itself.
 */
class PROCKFPS_API Scope {
public:
	Scope(ProckNode *root);

    // Try to register a new variable with the scope. Does nothing if the node is not type PNT_Name
	// Returns true if the variable was added as a new ghost or to an existing one. If the variable
	// was added successfully then a new GhostActor is spawned and attached to the Root
    bool NewVariable(ProckNode *n);

	// Connect the two logical nodes with a line with ALineActor
	// The real connection (ALineActor) could either be between two boxes or a box and a ghost
	// This isn't part of the programming scope, its part of the scope of things drawn within a box
	void Connect(ProckNode *from, ProckNode *to);

	// The root prock node this scope is bound to
	ProckNode *Root;

//private: 
    std::vector<Ghost *> ghosts;
	std::set<ALineActor *> lines;

	// Very sloppy way of tracking where to spawn new Ghosts on the root
	float spawnOffset;
};
