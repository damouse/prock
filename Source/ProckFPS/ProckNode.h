#pragma once

#include "BoxActor.h"
#include "PythonBindings.h"
#include <map>

/**
 * Abstract base class for all ProckNodes. A ProckNode "glues" a BoxActor to a native
 * Python AST Node as returned by RedBaron: it is neither an actor or an AST node, 
 * but it wraps AST nodes and spawns Boxes to represent them as needed
 */
class PROCKFPS_API ProckNode {
public:
	// Factory Method: creates the appropriate ProckNode subclass based on the given PyObject. 
	// Don't use the default constructor to create new ProckNodes!
	static ProckNode* NewNode(PyObject* astNode);

	// Spawn the box for this node
	void Spawn();

	// Dump the underlying python object
	void PrintRaw();

protected:
	// Generalized getters
	char *GetAsString(char *name);

	// Note: this allocates a new list! Every time its called it will leak memory-- have to 
	// cache the results on this node! 
	std::vector<ProckNode *> *GetAsList(char *name); 
	ProckNode *GetAsNode(char *name);

	ABoxActor *box;
	PyObject *astNode;
};

// Returns a constructed subclass of ProckNode that matches the given name
ProckNode *nodeSubclassFromString(char *t);

class PROCKFPS_API NodeList: public ProckNode {
public:
	std::vector<ProckNode *> *List() { return GetAsList("node_list"); }
};

