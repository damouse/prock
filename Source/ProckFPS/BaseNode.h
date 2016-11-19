#pragma once

#include "BoxActor.h"
#include "PythonBindings.h"
#include <map>
#include <functional>

// The type of each node, used to test for type before casts. This is instead of using dynaic_cast, 
// which requires RTTI and incurs a performance overhead
enum ProckNodeType : int;

/**
* Abstract base class for all ProckNodes. A ProckNode "glues" a BoxActor to a native
* Python AST Node as returned by RedBaron: it is neither an actor or an AST node,
* but it wraps AST nodes and spawns Boxes to represent them as needed.
*
* Note that the rendering heavy lifting is managed in the Spawn method in ProckNode.cpp
*/
class PROCKFPS_API ProckNode {
public:
	//ProckNode();

	// Factory Method: creates the appropriate ProckNode subclass based on the given PyObject. 
	// Don't use the default constructor to create new ProckNodes!
	static ProckNode* NewNode(PyObject* astNode);

	// Spawn this node in the game world.
	// NOTE: this method is the ProckNode.cpp. Its basically a glorified switch statement for the anonymous functions there
	void Spawn(ProckNode *node, FVector pos);

	// Dump the underlying python object. Equivalent to python: str(obj)
	void PrintRaw();

	// Return this class name without the leading 'PN'. The class PNCallArgument returns CallArgument, for example
	virtual char *Name();

	// Return the enumerated type for this node. Use this to check type instead of c++ casts
	virtual ProckNodeType Type();

	// Attach the root component of the given node to our root component and set its relative positioning
	void Attach(ProckNode *node, FVector pos);

//protected:
	// Generalized getters
	char *GetAsString(char *name);

	// Note: this allocates a new list! Every time its called it will leak memory-- have to 
	// cache the results on this node! 
	std::vector<ProckNode *> *GetAsList(char *name);
	ProckNode *GetAsNode(char *name);

	ABoxActor *box;
	PyObject *astNode;

	// Passed in from BaseGameMode within its constructor. This might be incorrect, 
	// but I'm scared to make ProckNode a UClass-- totally hypothetical concerns about performance
	static TSubclassOf<ABoxActor> boxBPClass;
	static UWorld *world;
};

// Returns a constructed subclass of ProckNode that matches the given name. Caller owns the reference to the object
ProckNode *nodeSubclassFromString(char *t);

// Start Generated Code

enum ProckNodeType {
    PNT_Base,
	PNT_ArgumentGeneratorComprehension,
	PNT_Assert,
	PNT_Assignment,
	PNT_AssociativeParenthesis,
	PNT_Atomtrailers,
	PNT_Binary,
	PNT_BinaryOperator,
	PNT_BooleanOperator,
	PNT_Call,
	PNT_CallArgument,
	PNT_Class,
	PNT_Comma,
	PNT_Comparison,
	PNT_ComprehensionIf,
	PNT_ComprehensionLoop,
	PNT_Decorator,
	PNT_DefArgument,
	PNT_Del,
	PNT_DictArgument,
	PNT_Dict,
	PNT_DictComprehension,
	PNT_DottedAsName,
	PNT_Dot,
	PNT_Elif,
	PNT_Else,
	PNT_Except,
	PNT_Exec,
	PNT_Finally,
	PNT_For,
	PNT_FromImport,
	PNT_Funcdef,
	PNT_GeneratorComprehension,
	PNT_Getitem,
	PNT_Global,
	PNT_If,
	PNT_Ifelseblock,
	PNT_Import,
	PNT_Lambda,
	PNT_ListArgument,
	PNT_ListComprehension,
	PNT_List,
	PNT_NameAsName,
	PNT_Print,
	PNT_Raise,
	PNT_Repr,
	PNT_Return,
	PNT_Set,
	PNT_SetComprehension,
	PNT_Slice,
	PNT_StringChain,
	PNT_TernaryOperator,
	PNT_Try,
	PNT_Tuple,
	PNT_UnitaryOperator,
	PNT_Yield,
	PNT_YieldAtom,
	PNT_While,
	PNT_WithContextItem,
	PNT_With,
	PNT_BinaryRawString,
	PNT_BinaryString,
	PNT_Break,
	PNT_CodeBlock,
	PNT_CommaProxyList,
	PNT_Comment,
	PNT_ComparisonOperator,
	PNT_Complex,
	PNT_Continue,
	PNT_Def,
	PNT_Dictitem,
	PNT_DotProxyList,
	PNT_DottedName,
	PNT_Ellipsis,
	PNT_ElseAttribute,
	PNT_Endl,
	PNT_FloatExponantComplex,
	PNT_FloatExponant,
	PNT_Float,
	PNT_Hexa,
	PNT_IfElseBlockSibling,
	PNT_Int,
	PNT_LeftParenthesis,
	PNT_LineProxyList,
	PNT_Long,
	PNT_Name,
	PNT_Octa,
	PNT_Pass,
	PNT_RawString,
	PNT_RightParenthesis,
	PNT_Semicolon,
	PNT_Space,
	PNT_Star,
	PNT_String,
	PNT_UnicodeRawString,
	PNT_UnicodeString,
};
// End Generated Code
