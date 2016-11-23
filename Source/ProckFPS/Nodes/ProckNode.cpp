// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "Nodes/ProckNode.h" 
#include "Nodes/ProckNodeSubclasses.h"
#include "Utils/Config.h"

using namespace std;

// Returns a constructed subclass of ProckNode that matches the given name. Caller owns the reference to the object
ProckNode *nodeSubclassFromString(char *t);

ProckNode *ProckNode::NewNode(PyObject *native) {
	PyObject *klass = PyObject_GetAttrString(native, "__class__");
	if (!klass) {
		log_py_error();
		return nullptr;
	}

	PyObject *name = PyObject_GetAttrString(klass, "__name__");
	if (!name) {
		log_py_error();
		return nullptr;
	}

	ProckNode *newNode = nodeSubclassFromString(PyString_AsString(name));
	if (newNode) {
		newNode->astNode = native;
		return newNode;
	}

	UE_LOG(LogProck, Error, TEXT("Could not find PN node type for class: %s"), UTF8_TO_TCHAR(PyString_AsString(name)));
	return nullptr;
}

char *ProckNode::GetAsString(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : PyString_AsString(PyObject_Str(r));
}

char *ProckNode::Name() {
	return "Base\0";
}

ProckNodeType ProckNode::Type() {
	return PNT_Base;
}

std::vector<ProckNode *> *ProckNode::GetAsList(char *name) {
	// Check if we have a cached response for this access
	string s(name);
	if (nodeCache.count(s)) {
		return (vector<ProckNode *> *) nodeCache[s];
	}

	PyObject *r = PyObject_GetAttrString(astNode, name);

	if (!r || !PyIter_Check(r)) {
		UE_LOG(LogProck, Error, TEXT("Did not recieve list in node request"));
		return nullptr;
	}

	PyObject *iterator = PyObject_GetIter(r);
	if (iterator == NULL) {
		UE_LOG(LogProck, Error, TEXT("Could not iterate over node list"));
		return nullptr;
	}

	std::vector<ProckNode *> *result = new std::vector<ProckNode*>();
	PyObject *item = PyIter_Next(iterator);

	while (item) {
		ProckNode *a = ProckNode::NewNode(item);
		if (!a) {
			UE_LOG(LogProck, Error, TEXT("Unable to create node for %s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
			delete result;
			Py_DECREF(iterator);
			return nullptr;
		}

		result->push_back(a);
		item = PyIter_Next(iterator);
		// Py_DECREF(item);
	}

	Py_DECREF(iterator);
	nodeCache[s] = result;
	return result;
}

ProckNode *ProckNode::GetAsNode(char *name) {
	// Check if we have a cached response for this access
	string s(name);
	if (nodeCache.count(s)) {
		return (ProckNode *) nodeCache[s];
	}

	PyObject *r = PyObject_GetAttrString(astNode, name);

	if (r) {
		ProckNode *ret = ProckNode::NewNode(r);
		nodeCache[s] = ret;
		return ret;
	}

	return nullptr;
}

void ProckNode::PrintRaw() {
	if (astNode) {
		PyObject *dict = PyObject_GetAttrString(astNode, "__dict__");
		if (dict) {
			printpy(dict);
		} else {
			UE_LOG(LogProck, Error, TEXT("Unable to retrieve object __dict__, fallback to str()"));
			printpy(astNode);
		}
	} else {
		UE_LOG(LogProck, Error, TEXT("Native python object not set!"));
	}
}

// Factory constructor method. Creates appropriate subclasses from node names
ProckNode *nodeSubclassFromString(char *t) {
	// These top ones are manually added conversions
	if (strcmp(t, "RedBaron") == 0) {
		return new PNList();
	} else if (strcmp(t, "NodeList") == 0) {
		return new PNList();
	} else if (strcmp(t, "str") == 0) {
		return new PNName();

// Start Generated Code
	} else if (strcmp(t, "BinaryRawStringNode") == 0) {
		return new PNBinaryRawString();
	} else if (strcmp(t, "BinaryStringNode") == 0) {
		return new PNBinaryString();
	} else if (strcmp(t, "BreakNode") == 0) {
		return new PNBreak();
	} else if (strcmp(t, "CodeBlockNode") == 0) {
		return new PNCodeBlock();
	} else if (strcmp(t, "CommaProxyList") == 0) {
		return new PNCommaProxyList();
	} else if (strcmp(t, "CommentNode") == 0) {
		return new PNComment();
	} else if (strcmp(t, "ComparisonOperatorNode") == 0) {
		return new PNComparisonOperator();
	} else if (strcmp(t, "ComplexNode") == 0) {
		return new PNComplex();
	} else if (strcmp(t, "ContinueNode") == 0) {
		return new PNContinue();
	} else if (strcmp(t, "DefNode") == 0) {
		return new PNDef();
	} else if (strcmp(t, "DictitemNode") == 0) {
		return new PNDictitem();
	} else if (strcmp(t, "DotProxyList") == 0) {
		return new PNDotProxyList();
	} else if (strcmp(t, "DottedNameNode") == 0) {
		return new PNDottedName();
	} else if (strcmp(t, "EllipsisNode") == 0) {
		return new PNEllipsis();
	} else if (strcmp(t, "ElseAttributeNode") == 0) {
		return new PNElseAttribute();
	} else if (strcmp(t, "EndlNode") == 0) {
		return new PNEndl();
	} else if (strcmp(t, "FloatExponantComplexNode") == 0) {
		return new PNFloatExponantComplex();
	} else if (strcmp(t, "FloatExponantNode") == 0) {
		return new PNFloatExponant();
	} else if (strcmp(t, "FloatNode") == 0) {
		return new PNFloat();
	} else if (strcmp(t, "HexaNode") == 0) {
		return new PNHexa();
	} else if (strcmp(t, "IfElseBlockSiblingNode") == 0) {
		return new PNIfElseBlockSibling();
	} else if (strcmp(t, "IntNode") == 0) {
		return new PNInt();
	} else if (strcmp(t, "LeftParenthesisNode") == 0) {
		return new PNLeftParenthesis();
	} else if (strcmp(t, "LineProxyList") == 0) {
		return new PNLineProxyList();
	} else if (strcmp(t, "LongNode") == 0) {
		return new PNLong();
	} else if (strcmp(t, "NameNode") == 0) {
		return new PNName();
	} else if (strcmp(t, "OctaNode") == 0) {
		return new PNOcta();
	} else if (strcmp(t, "PassNode") == 0) {
		return new PNPass();
	} else if (strcmp(t, "RawStringNode") == 0) {
		return new PNRawString();
	} else if (strcmp(t, "RightParenthesisNode") == 0) {
		return new PNRightParenthesis();
	} else if (strcmp(t, "SemicolonNode") == 0) {
		return new PNSemicolon();
	} else if (strcmp(t, "SpaceNode") == 0) {
		return new PNSpace();
	} else if (strcmp(t, "StarNode") == 0) {
		return new PNStar();
	} else if (strcmp(t, "StringNode") == 0) {
		return new PNString();
	} else if (strcmp(t, "UnicodeRawStringNode") == 0) {
		return new PNUnicodeRawString();
	} else if (strcmp(t, "UnicodeStringNode") == 0) {
		return new PNUnicodeString();
	} else if (strcmp(t, "ArgumentGeneratorComprehensionNode") == 0) {
		return new PNArgumentGeneratorComprehension();
	} else if (strcmp(t, "AssertNode") == 0) {
		return new PNAssert();
	} else if (strcmp(t, "AssignmentNode") == 0) {
		return new PNAssignment();
	} else if (strcmp(t, "AssociativeParenthesisNode") == 0) {
		return new PNAssociativeParenthesis();
	} else if (strcmp(t, "AtomtrailersNode") == 0) {
		return new PNAtomtrailers();
	} else if (strcmp(t, "BinaryNode") == 0) {
		return new PNBinary();
	} else if (strcmp(t, "BinaryOperatorNode") == 0) {
		return new PNBinaryOperator();
	} else if (strcmp(t, "BooleanOperatorNode") == 0) {
		return new PNBooleanOperator();
	} else if (strcmp(t, "CallNode") == 0) {
		return new PNCall();
	} else if (strcmp(t, "CallArgumentNode") == 0) {
		return new PNCallArgument();
	} else if (strcmp(t, "ClassNode") == 0) {
		return new PNClass();
	} else if (strcmp(t, "CommaNode") == 0) {
		return new PNComma();
	} else if (strcmp(t, "ComparisonNode") == 0) {
		return new PNComparison();
	} else if (strcmp(t, "ComprehensionIfNode") == 0) {
		return new PNComprehensionIf();
	} else if (strcmp(t, "ComprehensionLoopNode") == 0) {
		return new PNComprehensionLoop();
	} else if (strcmp(t, "DecoratorNode") == 0) {
		return new PNDecorator();
	} else if (strcmp(t, "DefArgumentNode") == 0) {
		return new PNDefArgument();
	} else if (strcmp(t, "DelNode") == 0) {
		return new PNDel();
	} else if (strcmp(t, "DictArgumentNode") == 0) {
		return new PNDictArgument();
	} else if (strcmp(t, "DictNode") == 0) {
		return new PNDict();
	} else if (strcmp(t, "DictComprehensionNode") == 0) {
		return new PNDictComprehension();
	} else if (strcmp(t, "DottedAsNameNode") == 0) {
		return new PNDottedAsName();
	} else if (strcmp(t, "DotNode") == 0) {
		return new PNDot();
	} else if (strcmp(t, "ElifNode") == 0) {
		return new PNElif();
	} else if (strcmp(t, "ElseNode") == 0) {
		return new PNElse();
	} else if (strcmp(t, "ExceptNode") == 0) {
		return new PNExcept();
	} else if (strcmp(t, "ExecNode") == 0) {
		return new PNExec();
	} else if (strcmp(t, "FinallyNode") == 0) {
		return new PNFinally();
	} else if (strcmp(t, "ForNode") == 0) {
		return new PNFor();
	} else if (strcmp(t, "FromImportNode") == 0) {
		return new PNFromImport();
	} else if (strcmp(t, "FuncdefNode") == 0) {
		return new PNFuncdef();
	} else if (strcmp(t, "GeneratorComprehensionNode") == 0) {
		return new PNGeneratorComprehension();
	} else if (strcmp(t, "GetitemNode") == 0) {
		return new PNGetitem();
	} else if (strcmp(t, "GlobalNode") == 0) {
		return new PNGlobal();
	} else if (strcmp(t, "IfNode") == 0) {
		return new PNIf();
	} else if (strcmp(t, "IfelseblockNode") == 0) {
		return new PNIfelseblock();
	} else if (strcmp(t, "ImportNode") == 0) {
		return new PNImport();
	} else if (strcmp(t, "LambdaNode") == 0) {
		return new PNLambda();
	} else if (strcmp(t, "ListArgumentNode") == 0) {
		return new PNListArgument();
	} else if (strcmp(t, "ListComprehensionNode") == 0) {
		return new PNListComprehension();
	} else if (strcmp(t, "ListNode") == 0) {
		return new PNList();
	} else if (strcmp(t, "NameAsNameNode") == 0) {
		return new PNNameAsName();
	} else if (strcmp(t, "PrintNode") == 0) {
		return new PNPrint();
	} else if (strcmp(t, "RaiseNode") == 0) {
		return new PNRaise();
	} else if (strcmp(t, "ReprNode") == 0) {
		return new PNRepr();
	} else if (strcmp(t, "ReturnNode") == 0) {
		return new PNReturn();
	} else if (strcmp(t, "SetNode") == 0) {
		return new PNSet();
	} else if (strcmp(t, "SetComprehensionNode") == 0) {
		return new PNSetComprehension();
	} else if (strcmp(t, "SliceNode") == 0) {
		return new PNSlice();
	} else if (strcmp(t, "StringChainNode") == 0) {
		return new PNStringChain();
	} else if (strcmp(t, "TernaryOperatorNode") == 0) {
		return new PNTernaryOperator();
	} else if (strcmp(t, "TryNode") == 0) {
		return new PNTry();
	} else if (strcmp(t, "TupleNode") == 0) {
		return new PNTuple();
	} else if (strcmp(t, "UnitaryOperatorNode") == 0) {
		return new PNUnitaryOperator();
	} else if (strcmp(t, "YieldNode") == 0) {
		return new PNYield();
	} else if (strcmp(t, "YieldAtomNode") == 0) {
		return new PNYieldAtom();
	} else if (strcmp(t, "WhileNode") == 0) {
		return new PNWhile();
	} else if (strcmp(t, "WithContextItemNode") == 0) {
		return new PNWithContextItem();
	} else if (strcmp(t, "WithNode") == 0) {
		return new PNWith();
// End Generated Code

	} else {
		UE_LOG(LogProck, Error, TEXT("Unknown node type: %s"), ANSI_TO_TCHAR(t));
		return nullptr;
	}
}