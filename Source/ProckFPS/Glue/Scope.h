// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Glue/Ghost.h"
#include "Nodes/ProckNode.h"

#include <vector>

/**
 * Collection of references visible within a certain scope, usually attached to a Node.
 * Belongs to some node; all nodes contained within the scope hold a reference to it. 
 */
class PROCKFPS_API Scope {
public:
    // Try to register a new variable with the scope. Does nothing if the node is not type PNT_Name
	// Returns true if the variable was added or exists
    bool NewVariable(ProckNode *n);

	// Spawn AGhostActors into the game world as a child of the passed node's box
	void Spawn(ProckNode *root);

//private: 
    std::vector<Ghost *> ghosts;
};
