// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// The different kinds of abstract types this node can be. 
enum ProckNodeType {
	Assignment,
	Addition,
	Unknown
};

/**
 * An abstract node subclassed by native specific implementations. 
 */
class PROCKFPS_API ProckNode
{
public:
	// Resolve this node if not already resolved. Equivalent to if (!resolved) { resolve() }
	// Though this is likely to change to something less magical
	virtual void Resolve() = 0;

	//virtual ProckNodeType Type();
	//virtual void Value(); // Not sure what this is going to return just yet

	//virtual ProckNode* Children();
	//virtual ProckNode* Parent();

protected:
	bool resolved;

	ProckNodeType type;

	ProckNode* children;
	ProckNode* parent;
};
