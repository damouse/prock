// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

ProckNode::ProckNode() {
	resolved = false;
	children = {};
	type = PNT_Unresolved;
}

ProckNode::~ProckNode() {
	children = {};
	type = PNT_Unresolved;
	parent = nullptr;
}

void ProckNode::print(char *subclass) {
	char *val = "null\0";
	char *typ = pntToString(type);

	//if (value != nullptr) {
	//	val = value;
	//}

	// Note that you must have null terminated strings here
	UE_LOG(LogProck, Log, TEXT("%s: Type: %s, Value: %s, Children: %d"), UTF8_TO_TCHAR(subclass), UTF8_TO_TCHAR(typ), UTF8_TO_TCHAR(val), children.size());
}

char *pntToString(ProckNodeType type) {
	switch (type) {
	case PNT_Root: 
		return "Root\0";
	case PNT_Unresolved:
		return "Unresolved\0";
	case PNT_ArgumentGeneratorComprehension:
		return "ArgumentGeneratorComprehension\0";
	case PNT_Assert:
		return "Assert\0";
	case PNT_Assignment:
		return "Assignment\0";
	case PNT_AssociativeParenthesis:
		return "AssociativeParenthesis\0";
	case PNT_Atomtrailers:
		return "Atomtrailers\0";
	case PNT_Binary:
		return "Binary\0";
	case PNT_BinaryOperator:
		return "BinaryOperator\0";
	case PNT_BinaryRawString:
		return "BinaryRawString\0";
	case PNT_BinaryString:
		return "BinaryString\0";
	case PNT_BooleanOperator:
		return "BooleanOperator\0";
	case PNT_Break:
		return "Break\0";
	case PNT_CallArgument:
		return "CallArgument\0";
	case PNT_Call:
		return "Call\0";
	case PNT_Class:
		return "Class\0";
	case PNT_CodeBlock:
		return "CodeBlock\0";
	case PNT_Comma:
		return "Comma\0";
	case PNT_Comment:
		return "Comment\0";
	case PNT_Comparison:
		return "Comparison\0";
	case PNT_ComparisonOperator:
		return "ComparisonOperator\0";
	case PNT_Complex:
		return "Complex\0";
	case PNT_ComprehensionIf:
		return "ComprehensionIf\0";
	case PNT_ComprehensionLoop:
		return "ComprehensionLoop\0";
	case PNT_Continue:
		return "Continue\0";
	case PNT_Decorator:
		return "Decorator\0";
	case PNT_DefArgument:
		return "DefArgument\0";
	case PNT_Def:
		return "Def\0";
	case PNT_Del:
		return "Del\0";
	case PNT_DictArgument:
		return "DictArgument\0";
	case PNT_DictComprehension:
		return "DictComprehension\0";
	case PNT_Dict:
		return "Dict\0";
	case PNT_Dictitem:
		return "Dictitem\0";
	case PNT_Dot:
		return "Dot\0";
	case PNT_DottedAsName:
		return "DottedAsName\0";
	case PNT_DottedName:
		return "DottedName\0";
	case PNT_Elif:
		return "Elif\0";
	case PNT_Ellipsis:
		return "Ellipsis\0";
	case PNT_ElseAttribute:
		return "ElseAttribute\0";
	case PNT_Else:
		return "Else\0";
	case PNT_Endl:
		return "Endl\0";
	case PNT_Except:
		return "Except\0";
	case PNT_Exec:
		return "Exec\0";
	case PNT_Finally:
		return "Finally\0";
	case PNT_FloatExponantComplex:
		return "FloatExponantComplex\0";
	case PNT_FloatExponant:
		return "FloatExponant\0";
	case PNT_Float:
		return "Float\0";
	case PNT_For:
		return "For\0";
	case PNT_FromImport:
		return "FromImport\0";
	case PNT_GeneratorComprehension:
		return "GeneratorComprehension\0";
	case PNT_Getitem:
		return "Getitem\0";
	case PNT_Global:
		return "Global\0";
	case PNT_Hexa:
		return "Hexa\0";
	case PNT_IfElseBlockSibling:
		return "IfElseBlockSibling\0";
	case PNT_If:
		return "If\0";
	case PNT_Ifelseblock:
		return "Ifelseblock\0";
	case PNT_Import:
		return "Import\0";
	case PNT_Int:
		return "Int\0";
	case PNT_Lambda:
		return "Lambda\0";
	case PNT_LeftParenthesis:
		return "LeftParenthesis\0";
	case PNT_ListArgument:
		return "ListArgument\0";
	case PNT_ListComprehension:
		return "ListComprehension\0";
	case PNT_List:
		return "List\0";
	case PNT_Long:
		return "Long\0";
	case PNT_NameAsName:
		return "NameAsName\0";
	case PNT_Name:
		return "Name\0";
	case PNT_Octa:
		return "Octa\0";
	case PNT_Pass:
		return "Pass\0";
	case PNT_Print:
		return "Print\0";
	case PNT_Raise:
		return "Raise\0";
	case PNT_RawString:
		return "RawString\0";
	case PNT_Repr:
		return "Repr\0";
	case PNT_Return:
		return "Return\0";
	case PNT_RightParenthesis:
		return "RightParenthesis\0";
	case PNT_Semicolon:
		return "Semicolon\0";
	case PNT_SetComprehension:
		return "SetComprehension\0";
	case PNT_Set:
		return "Set\0";
	case PNT_Slice:
		return "Slice\0";
	case PNT_Space:
		return "Space\0";
	case PNT_Star:
		return "Star\0";
	case PNT_StringChain:
		return "StringChain\0";
	case PNT_String:
		return "String\0";
	case PNT_TernaryOperator:
		return "TernaryOperator\0";
	case PNT_Try:
		return "Try\0";
	case PNT_Tuple:
		return "Tuple\0";
	case PNT_UnicodeRawString:
		return "UnicodeRawString\0";
	case PNT_UnicodeString:
		return "UnicodeString\0";
	case PNT_UnitaryOperator:
		return "UnitaryOperator\0";
	case PNT_While:
		return "While\0";
	case PNT_WithContextItem:
		return "WithContextItem\0";
	case PNT_With:
		return "With\0";
	case PNT_YieldAtom:
		return "YieldAtom\0";
	case PNT_Yield:
		return "Yield\0";
	default:
		return "Unknown\0";
	}
}

// Specific to python and redbaron. Switch this to an array index, eh?
ProckNodeType pntFromPyString(char *t) {
	if (strcmp(t, "argument_generator_comprehension") == 0) {
		return PNT_ArgumentGeneratorComprehension;
	} else if (strcmp(t, "assert") == 0) {
		return PNT_Assert;
	} else if (strcmp(t, "assignment") == 0) {
		return PNT_Assignment;
	} else if (strcmp(t, "associative_parenthesis") == 0) {
		return PNT_AssociativeParenthesis;
	} else if (strcmp(t, "atomtrailers") == 0) {
		return PNT_Atomtrailers;
	} else if (strcmp(t, "binary") == 0) {
		return PNT_Binary;
	} else if (strcmp(t, "binary_operator") == 0) {
		return PNT_BinaryOperator;
	} else if (strcmp(t, "binary_raw_string") == 0) {
		return PNT_BinaryRawString;
	} else if (strcmp(t, "binary_string") == 0) {
		return PNT_BinaryString;
	} else if (strcmp(t, "boolean_operator") == 0) {
		return PNT_BooleanOperator;
	} else if (strcmp(t, "break") == 0) {
		return PNT_Break;
	} else if (strcmp(t, "call_argument") == 0) {
		return PNT_CallArgument;
	} else if (strcmp(t, "call") == 0) {
		return PNT_Call;
	} else if (strcmp(t, "class") == 0) {
		return PNT_Class;
	} else if (strcmp(t, "code_block") == 0) {
		return PNT_CodeBlock;
	} else if (strcmp(t, "comma") == 0) {
		return PNT_Comma;
	} else if (strcmp(t, "comment") == 0) {
		return PNT_Comment;
	} else if (strcmp(t, "comparison") == 0) {
		return PNT_Comparison;
	} else if (strcmp(t, "comparison_operator") == 0) {
		return PNT_ComparisonOperator;
	} else if (strcmp(t, "complex") == 0) {
		return PNT_Complex;
	} else if (strcmp(t, "comprehension_if") == 0) {
		return PNT_ComprehensionIf;
	} else if (strcmp(t, "comprehension_loop") == 0) {
		return PNT_ComprehensionLoop;
	} else if (strcmp(t, "continue") == 0) {
		return PNT_Continue;
	} else if (strcmp(t, "decorator") == 0) {
		return PNT_Decorator;
	} else if (strcmp(t, "def_argument") == 0) {
		return PNT_DefArgument;
	} else if (strcmp(t, "def") == 0) {
		return PNT_Def;
	} else if (strcmp(t, "del") == 0) {
		return PNT_Del;
	} else if (strcmp(t, "dict_argument") == 0) {
		return PNT_DictArgument;
	} else if (strcmp(t, "dict_comprehension") == 0) {
		return PNT_DictComprehension;
	} else if (strcmp(t, "dict") == 0) {
		return PNT_Dict;
	} else if (strcmp(t, "dictitem") == 0) {
		return PNT_Dictitem;
	} else if (strcmp(t, "dot") == 0) {
		return PNT_Dot;
	} else if (strcmp(t, "dotted_as_name") == 0) {
		return PNT_DottedAsName;
	} else if (strcmp(t, "dotted_name") == 0) {
		return PNT_DottedName;
	} else if (strcmp(t, "elif") == 0) {
		return PNT_Elif;
	} else if (strcmp(t, "ellipsis") == 0) {
		return PNT_Ellipsis;
	} else if (strcmp(t, "else_attribute") == 0) {
		return PNT_ElseAttribute;
	} else if (strcmp(t, "else") == 0) {
		return PNT_Else;
	} else if (strcmp(t, "endl") == 0) {
		return PNT_Endl;
	} else if (strcmp(t, "except") == 0) {
		return PNT_Except;
	} else if (strcmp(t, "exec") == 0) {
		return PNT_Exec;
	} else if (strcmp(t, "finally") == 0) {
		return PNT_Finally;
	} else if (strcmp(t, "float_exponant_complex") == 0) {
		return PNT_FloatExponantComplex;
	} else if (strcmp(t, "float_exponant") == 0) {
		return PNT_FloatExponant;
	} else if (strcmp(t, "float") == 0) {
		return PNT_Float;
	} else if (strcmp(t, "for") == 0) {
		return PNT_For;
	} else if (strcmp(t, "from_import") == 0) {
		return PNT_FromImport;
	} else if (strcmp(t, "generator_comprehension") == 0) {
		return PNT_GeneratorComprehension;
	} else if (strcmp(t, "getitem") == 0) {
		return PNT_Getitem;
	} else if (strcmp(t, "global") == 0) {
		return PNT_Global;
	} else if (strcmp(t, "hexa") == 0) {
		return PNT_Hexa;
	} else if (strcmp(t, "if_else_block_sibling") == 0) {
		return PNT_IfElseBlockSibling;
	} else if (strcmp(t, "if") == 0) {
		return PNT_If;
	} else if (strcmp(t, "ifelseblock") == 0) {
		return PNT_Ifelseblock;
	} else if (strcmp(t, "import") == 0) {
		return PNT_Import;
	} else if (strcmp(t, "int") == 0) {
		return PNT_Int;
	} else if (strcmp(t, "lambda") == 0) {
		return PNT_Lambda;
	} else if (strcmp(t, "left_parenthesis") == 0) {
		return PNT_LeftParenthesis;
	} else if (strcmp(t, "list_argument") == 0) {
		return PNT_ListArgument;
	} else if (strcmp(t, "list_comprehension") == 0) {
		return PNT_ListComprehension;
	} else if (strcmp(t, "list") == 0) {
		return PNT_List;
	} else if (strcmp(t, "long") == 0) {
		return PNT_Long;
	} else if (strcmp(t, "name_as_name") == 0) {
		return PNT_NameAsName;
	} else if (strcmp(t, "name") == 0) {
		return PNT_Name;
	} else if (strcmp(t, "octa") == 0) {
		return PNT_Octa;
	} else if (strcmp(t, "pass") == 0) {
		return PNT_Pass;
	} else if (strcmp(t, "print") == 0) {
		return PNT_Print;
	} else if (strcmp(t, "raise") == 0) {
		return PNT_Raise;
	} else if (strcmp(t, "raw_string") == 0) {
		return PNT_RawString;
	} else if (strcmp(t, "repr") == 0) {
		return PNT_Repr;
	} else if (strcmp(t, "return") == 0) {
		return PNT_Return;
	} else if (strcmp(t, "right_parenthesis") == 0) {
		return PNT_RightParenthesis;
	} else if (strcmp(t, "semicolon") == 0) {
		return PNT_Semicolon;
	} else if (strcmp(t, "set_comprehension") == 0) {
		return PNT_SetComprehension;
	} else if (strcmp(t, "set") == 0) {
		return PNT_Set;
	} else if (strcmp(t, "slice") == 0) {
		return PNT_Slice;
	} else if (strcmp(t, "space") == 0) {
		return PNT_Space;
	} else if (strcmp(t, "star") == 0) {
		return PNT_Star;
	} else if (strcmp(t, "string_chain") == 0) {
		return PNT_StringChain;
	} else if (strcmp(t, "string") == 0) {
		return PNT_String;
	} else if (strcmp(t, "ternary_operator") == 0) {
		return PNT_TernaryOperator;
	} else if (strcmp(t, "try") == 0) {
		return PNT_Try;
	} else if (strcmp(t, "tuple") == 0) {
		return PNT_Tuple;
	} else if (strcmp(t, "unicode_raw_string") == 0) {
		return PNT_UnicodeRawString;
	} else if (strcmp(t, "unicode_string") == 0) {
		return PNT_UnicodeString;
	} else if (strcmp(t, "unitary_operator") == 0) {
		return PNT_UnitaryOperator;
	} else if (strcmp(t, "while") == 0) {
		return PNT_While;
	} else if (strcmp(t, "with_context_item") == 0) {
		return PNT_WithContextItem;
	} else if (strcmp(t, "with") == 0) {
		return PNT_With;
	} else if (strcmp(t, "yield_atom") == 0) {
		return PNT_YieldAtom;
	} else if (strcmp(t, "yield") == 0) {
		return PNT_Yield;
	} else {
		UE_LOG(LogProck, Error, TEXT("Unknown node type: %s"), ANSI_TO_TCHAR(t));
		return PNT_Unknown;
	}
}