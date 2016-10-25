// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <list>

// The abstract "type" of this node. May not be the same as the native AST node reports
enum ProckNodeType {
	PNT_Root,
	PNT_Assignment,
	PNT_Addition,
	PNT_Unknown,
	PNT_Unresolved
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

	// Log this object to the console
	virtual void Print() = 0;

	// Dumb getters for internal fields
	bool IsResolved() { return resolved; }
	ProckNodeType Type() { return type; }
	char *Value() { return value; }

	std::list<ProckNode *> children;
	ProckNode* Parent() { return parent; }

protected:
	// Print helper method
	void print(char *subclass);

	bool resolved;
	ProckNodeType type;
	char * value;

	
	ProckNode* parent;
};
