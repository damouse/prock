// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <list>

// See below
enum ProckNodeType: int;

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

// Helper functions for converting types to and from strings
char *pntToString(ProckNodeType type);
ProckNodeType pntFromPyString(char *native);


// The abstract "type" of this node. May not be the same as the native AST node reports
enum ProckNodeType {
	// Meta node types
	PNT_Root,
	PNT_Unknown,
	PNT_Unresolved,

	PNT_ArgumentGeneratorComprehension,
	PNT_Assert,
	PNT_Assignment,
	PNT_AssociativeParenthesis,
	PNT_Atomtrailers,
	PNT_Binary,
	PNT_BinaryOperator,
	PNT_BinaryRawString,
	PNT_BinaryString,
	PNT_BooleanOperator,
	PNT_Break,
	PNT_CallArgument,
	PNT_Call,
	PNT_Class,
	PNT_CodeBlock,
	PNT_Comma,
	PNT_Comment,
	PNT_Comparison,
	PNT_ComparisonOperator,
	PNT_Complex,
	PNT_ComprehensionIf,
	PNT_ComprehensionLoop,
	PNT_Continue,
	PNT_Decorator,
	PNT_DefArgument,
	PNT_Def,
	PNT_Del,
	PNT_DictArgument,
	PNT_DictComprehension,
	PNT_Dict,
	PNT_Dictitem,
	PNT_Dot,
	PNT_DottedAsName,
	PNT_DottedName,
	PNT_Elif,
	PNT_Ellipsis,
	PNT_ElseAttribute,
	PNT_Else,
	PNT_Endl,
	PNT_Except,
	PNT_Exec,
	PNT_Finally,
	PNT_FloatExponantComplex,
	PNT_FloatExponant,
	PNT_Float,
	PNT_For,
	PNT_FromImport,
	PNT_GeneratorComprehension,
	PNT_Getitem,
	PNT_Global,
	PNT_Hexa,
	PNT_IfElseBlockSibling,
	PNT_If,
	PNT_Ifelseblock,
	PNT_Import,
	PNT_Int,
	PNT_Lambda,
	PNT_LeftParenthesis,
	PNT_ListArgument,
	PNT_ListComprehension,
	PNT_List,
	PNT_Long,
	PNT_NameAsName,
	PNT_Name,
	PNT_Octa,
	PNT_Pass,
	PNT_Print,
	PNT_Raise,
	PNT_RawString,
	PNT_Repr,
	PNT_Return,
	PNT_RightParenthesis,
	PNT_Semicolon,
	PNT_SetComprehension,
	PNT_Set,
	PNT_Slice,
	PNT_Space,
	PNT_Star,
	PNT_StringChain,
	PNT_String,
	PNT_TernaryOperator,
	PNT_Try,
	PNT_Tuple,
	PNT_UnicodeRawString,
	PNT_UnicodeString,
	PNT_UnitaryOperator,
	PNT_While,
	PNT_WithContextItem,
	PNT_With,
	PNT_YieldAtom,
	PNT_Yield,
};
