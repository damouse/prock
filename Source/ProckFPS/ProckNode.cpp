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

// Specific to python and redbaron
ProckNodeType pntFromPyString(char *native) {
	if (strcmp(native, "argument_generator_comprehension")) {
		return PNT_ArgumentGeneratorComprehension;
	} else if (strcmp(native, "assert")) {
		return PNT_Assert;
	} else if (strcmp(native, "assign")) {
		return PNT_Assignment;
	} else if (strcmp(native, "associative_parenthesis")) {
		return PNT_AssociativeParenthesis;
	} else if (strcmp(native, "atomtrailers")) {
		return PNT_Atomtrailers;
	} else if (strcmp(native, "binary")) {
		return PNT_Binary;
	} else if (strcmp(native, "binary_operator")) {
		return PNT_BinaryOperator;
	} else if (strcmp(native, "binary_raw_string")) {
		return PNT_BinaryRawString;
	} else if (strcmp(native, "binary_string")) {
		return PNT_BinaryString;
	} else if (strcmp(native, "boolean_operator")) {
		return PNT_BooleanOperator;
	} else if (strcmp(native, "break")) {
		return PNT_Break;
	} else if (strcmp(native, "call_argument")) {
		return PNT_CallArgument;
	} else if (strcmp(native, "call")) {
		return PNT_Call;
	} else if (strcmp(native, "class")) {
		return PNT_Class;
	} else if (strcmp(native, "code_block")) {
		return PNT_CodeBlock;
	} else if (strcmp(native, "comma")) {
		return PNT_Comma;
	} else if (strcmp(native, "comment")) {
		return PNT_Comment;
	} else if (strcmp(native, "comparison")) {
		return PNT_Comparison;
	} else if (strcmp(native, "comparison_operator")) {
		return PNT_ComparisonOperator;
	} else if (strcmp(native, "complex")) {
		return PNT_Complex;
	} else if (strcmp(native, "comprehension_if")) {
		return PNT_ComprehensionIf;
	} else if (strcmp(native, "comprehension_loop")) {
		return PNT_ComprehensionLoop;
	} else if (strcmp(native, "continue")) {
		return PNT_Continue;
	} else if (strcmp(native, "decorator")) {
		return PNT_Decorator;
	} else if (strcmp(native, "def_argument")) {
		return PNT_DefArgument;
	} else if (strcmp(native, "def")) {
		return PNT_Def;
	} else if (strcmp(native, "del")) {
		return PNT_Del;
	} else if (strcmp(native, "dict_argument")) {
		return PNT_DictArgument;
	} else if (strcmp(native, "dict_comprehension")) {
		return PNT_DictComprehension;
	} else if (strcmp(native, "dict")) {
		return PNT_Dict;
	} else if (strcmp(native, "dictitem")) {
		return PNT_Dictitem;
	} else if (strcmp(native, "dot")) {
		return PNT_Dot;
	} else if (strcmp(native, "dotted_as_name")) {
		return PNT_DottedAsName;
	} else if (strcmp(native, "dotted_name")) {
		return PNT_DottedName;
	} else if (strcmp(native, "elif")) {
		return PNT_Elif;
	} else if (strcmp(native, "ellipsis")) {
		return PNT_Ellipsis;
	} else if (strcmp(native, "else_attribute")) {
		return PNT_ElseAttribute;
	} else if (strcmp(native, "else")) {
		return PNT_Else;
	} else if (strcmp(native, "endl")) {
		return PNT_Endl;
	} else if (strcmp(native, "except")) {
		return PNT_Except;
	} else if (strcmp(native, "exec")) {
		return PNT_Exec;
	} else if (strcmp(native, "finally")) {
		return PNT_Finally;
	} else if (strcmp(native, "float_exponant_complex")) {
		return PNT_FloatExponantComplex;
	} else if (strcmp(native, "float_exponant")) {
		return PNT_FloatExponant;
	} else if (strcmp(native, "float")) {
		return PNT_Float;
	} else if (strcmp(native, "for")) {
		return PNT_For;
	} else if (strcmp(native, "from_import")) {
		return PNT_FromImport;
	} else if (strcmp(native, "generator_comprehension")) {
		return PNT_GeneratorComprehension;
	} else if (strcmp(native, "getitem")) {
		return PNT_Getitem;
	} else if (strcmp(native, "global")) {
		return PNT_Global;
	} else if (strcmp(native, "hexa")) {
		return PNT_Hexa;
	} else if (strcmp(native, "if_else_block_sibling")) {
		return PNT_IfElseBlockSibling;
	} else if (strcmp(native, "if")) {
		return PNT_If;
	} else if (strcmp(native, "ifelseblock")) {
		return PNT_Ifelseblock;
	} else if (strcmp(native, "import")) {
		return PNT_Import;
	} else if (strcmp(native, "int")) {
		return PNT_Int;
	} else if (strcmp(native, "lambda")) {
		return PNT_Lambda;
	} else if (strcmp(native, "left_parenthesis")) {
		return PNT_LeftParenthesis;
	} else if (strcmp(native, "list_argument")) {
		return PNT_ListArgument;
	} else if (strcmp(native, "list_comprehension")) {
		return PNT_ListComprehension;
	} else if (strcmp(native, "list")) {
		return PNT_List;
	} else if (strcmp(native, "long")) {
		return PNT_Long;
	} else if (strcmp(native, "name_as_name")) {
		return PNT_NameAsName;
	} else if (strcmp(native, "name")) {
		return PNT_Name;
	} else if (strcmp(native, "octa")) {
		return PNT_Octa;
	} else if (strcmp(native, "pass")) {
		return PNT_Pass;
	} else if (strcmp(native, "print")) {
		return PNT_Print;
	} else if (strcmp(native, "raise")) {
		return PNT_Raise;
	} else if (strcmp(native, "raw_string")) {
		return PNT_RawString;
	} else if (strcmp(native, "repr")) {
		return PNT_Repr;
	} else if (strcmp(native, "return")) {
		return PNT_Return;
	} else if (strcmp(native, "right_parenthesis")) {
		return PNT_RightParenthesis;
	} else if (strcmp(native, "semicolon")) {
		return PNT_Semicolon;
	} else if (strcmp(native, "set_comprehension")) {
		return PNT_SetComprehension;
	} else if (strcmp(native, "set")) {
		return PNT_Set;
	} else if (strcmp(native, "slice")) {
		return PNT_Slice;
	} else if (strcmp(native, "space")) {
		return PNT_Space;
	} else if (strcmp(native, "star")) {
		return PNT_Star;
	} else if (strcmp(native, "string_chain")) {
		return PNT_StringChain;
	} else if (strcmp(native, "string")) {
		return PNT_String;
	} else if (strcmp(native, "ternary_operator")) {
		return PNT_TernaryOperator;
	} else if (strcmp(native, "try")) {
		return PNT_Try;
	} else if (strcmp(native, "tuple")) {
		return PNT_Tuple;
	} else if (strcmp(native, "unicode_raw_string")) {
		return PNT_UnicodeRawString;
	} else if (strcmp(native, "unicode_string")) {
		return PNT_UnicodeString;
	} else if (strcmp(native, "unitary_operator")) {
		return PNT_UnitaryOperator;
	} else if (strcmp(native, "while")) {
		return PNT_While;
	} else if (strcmp(native, "with_context_item")) {
		return PNT_WithContextItem;
	} else if (strcmp(native, "with")) {
		return PNT_With;
	} else if (strcmp(native, "yield_atom")) {
		return PNT_YieldAtom;
	} else if (strcmp(native, "yield")) {
		return PNT_Yield;
	} else {
		return PNT_Unknown;
	}
}