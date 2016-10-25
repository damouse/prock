// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <list>

// The abstract "type" of this node. May not be the same as the native AST node reports
enum ProckNodeType {
	PNTAssignment,
	PNTAddition,
	PNTUnknown,
	PNTUnresolved
};

/**
* An abstract node subclassed by native specific implementations.
*/
class PROCKFPS_API ProckNode {
public:
	ProckNode();
	~ProckNode();

	// Resolve the native node to prock style data structures
	virtual void Resolve() = 0;

	// Dumb getters for internal fields
	bool IsResolved() { return resolved; }
	ProckNodeType Type() { return type; }
	char *Value() { return value; }

	std::list<ProckNode *> Children() { return children; }
	ProckNode* Parent() { return parent; }

protected:
	bool resolved;
	ProckNodeType type;
	char * value;

	std::list<ProckNode *> children;
	ProckNode* parent;
};
