// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

ProckNode *ProckNode::NewNode(PyObject *native) {
	// Type will resolve for everything Except 
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

	// Certain node types (like the root and certain NodeLists) are not well represented by names
	// Check for these now
	
	// In progress
	NodeList *ret = new NodeList();
	ret->astNode = native;

	UE_LOG(LogProck, Error, TEXT("Assigned the root node."));
	return ret;
}

void ProckNode::Spawn() {

}

char *ProckNode::GetAsString(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : PyString_AsString(PyObject_Str(r));
}

std::vector<ProckNode *> *ProckNode::GetAsList(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);

	// Make sure we recieved a list
	if (!PyIter_Check(r)) {
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

	//for (int i = 0; i < PyList_Size(r); i++) {
	//	PyObject *item = PyList_GetItem(r, i);

	//	if (!item) {
	//		UE_LOG(LogProck, Error, TEXT("Unable to get item from list: %s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
	//		delete result;
	//		return nullptr;
	//	}

	//	ProckNode *a = ProckNode::NewNode(item);

	//	if (!a) {
	//		UE_LOG(LogProck, Error, TEXT("Unable to create node for %s"), UTF8_TO_TCHAR(PyString_AsString(PyObject_Str(item))));
	//		delete result;
	//		return nullptr;
	//	}

	//	result->push_back(a);
	//}

	Py_DECREF(iterator);
	return result;
}

ProckNode *ProckNode::GetAsNode(char *name) {
	PyObject *r = PyObject_GetAttrString(astNode, name);
	return (r == nullptr) ? nullptr : ProckNode::NewNode(r);
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

ProckNode *nodeSubclassFromString(char *t) {
    if (strcmp(t, "ArgumentGeneratorComprehensionNode") == 0) {
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
	} else {
		UE_LOG(LogProck, Error, TEXT("Unknown node type: %s"), ANSI_TO_TCHAR(t));
		return nullptr;
	}
}