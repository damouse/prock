// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Nodes/ProckNodeSubclasses.h"

// Ignore this class. Currently implemented in NodeSubclasses

/**
 * Create BoxActors from ProckNodes. Each have refernces to the other.
 * Also constructs Scopes, Ghosts, and Lines-- all the things that fully flesh out a 
 * box representation in the world.
 *
 * Note that nothing is returned from this factory. The created objects are directly attached to the appropriate ProckNode.
 */
class PROCKFPS_API BoxFactory {
public:
	BoxFactory(ProckNode *node);
	~BoxFactory();

	// Trigger the factory. Nothing is returned. 
	void Build();

private:
	ProckNode *root;
};
