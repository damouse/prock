#pragma once

#include "BoxActor.h"
#include "PythonBindings.h"

/**
 * Abstract base class for all ProckNodes. A ProckNode "glues" a BoxActor to a native
 * Python AST Node as returned by RedBaron: it is neither an actor or an AST node, 
 * but it wraps AST nodes and spawns Boxes to represent them as needed
 */
class PROCKFPS_API ProckNode {
public:
	// Factory Method. Do not use the default constructor
	static ProckNode* NewNode(PyObject* astNode);

	// Spawn the box for this node
	void Spawn();

protected:
	// Generalized getters
	char *GetAsString(char *name);
	std::vector<ProckNode *> GetAsList(char *name);
	ProckNode *GetAsNode(char *name);

	ABoxActor *box;
	PyObject *astNode;
};

class PROCKFPS_API NodeList: public ProckNode
{
//public:
//	std::vector<ProckNode *> List() {
//		return GetAsList("node_list");
//	}
};



