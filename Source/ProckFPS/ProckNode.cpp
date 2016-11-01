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

	// Switch on the class. If the class name cannot be found fallthrough here
	// in the case of name == RedBaron

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
	/*
	if (strcmp(t, "ArgumentGeneratorComprehensionNode") == 0) {
        return new ArgumentGeneratorComprehensionNode();
    } else if (strcmp(t, "AssertNode") == 0) {
        return new AssertNode();
    } else if (strcmp(t, "AssignmentNode") == 0) {
        return new AssignmentNode();
    } else if (strcmp(t, "AssociativeParenthesisNode") == 0) {
        return new AssociativeParenthesisNode();
    } else if (strcmp(t, "AtomtrailersNode") == 0) {
        return new AtomtrailersNode();
    } else if (strcmp(t, "BinaryNode") == 0) {
        return new BinaryNode();
    } else if (strcmp(t, "BinaryOperatorNode") == 0) {
        return new BinaryOperatorNode();
    } else if (strcmp(t, "BinaryRawStringNode") == 0) {
        return new BinaryRawStringNode();
    } else if (strcmp(t, "BinaryStringNode") == 0) {
        return new BinaryStringNode();
    } else if (strcmp(t, "BooleanOperatorNode") == 0) {
        return new BooleanOperatorNode();
    } else if (strcmp(t, "BreakNode") == 0) {
        return new BreakNode();
    } else if (strcmp(t, "CallArgumentNode") == 0) {
        return new CallArgumentNode();
    } else if (strcmp(t, "CallNode") == 0) {
        return new CallNode();
    } else if (strcmp(t, "ClassNode") == 0) {
        return new ClassNode();
    } else if (strcmp(t, "CodeBlockNode") == 0) {
        return new CodeBlockNode();
    } else if (strcmp(t, "CommaNode") == 0) {
        return new CommaNode();
    } else if (strcmp(t, "CommaProxyList") == 0) {
        return new CommaProxyList();
    } else if (strcmp(t, "CommentNode") == 0) {
        return new CommentNode();
    } else if (strcmp(t, "ComparisonNode") == 0) {
        return new ComparisonNode();
    } else if (strcmp(t, "ComparisonOperatorNode") == 0) {
        return new ComparisonOperatorNode();
    } else if (strcmp(t, "ComplexNode") == 0) {
        return new ComplexNode();
    } else if (strcmp(t, "ComprehensionIfNode") == 0) {
        return new ComprehensionIfNode();
    } else if (strcmp(t, "ComprehensionLoopNode") == 0) {
        return new ComprehensionLoopNode();
    } else if (strcmp(t, "ContinueNode") == 0) {
        return new ContinueNode();
    } else if (strcmp(t, "DecoratorNode") == 0) {
        return new DecoratorNode();
    } else if (strcmp(t, "DefArgumentNode") == 0) {
        return new DefArgumentNode();
    } else if (strcmp(t, "DefNode") == 0) {
        return new DefNode();
    } else if (strcmp(t, "DelNode") == 0) {
        return new DelNode();
    } else if (strcmp(t, "DictArgumentNode") == 0) {
        return new DictArgumentNode();
    } else if (strcmp(t, "DictComprehensionNode") == 0) {
        return new DictComprehensionNode();
    } else if (strcmp(t, "DictNode") == 0) {
        return new DictNode();
    } else if (strcmp(t, "DictitemNode") == 0) {
        return new DictitemNode();
    } else if (strcmp(t, "DotNode") == 0) {
        return new DotNode();
    } else if (strcmp(t, "DotProxyList") == 0) {
        return new DotProxyList();
    } else if (strcmp(t, "DottedAsNameNode") == 0) {
        return new DottedAsNameNode();
    } else if (strcmp(t, "DottedNameNode") == 0) {
        return new DottedNameNode();
    } else if (strcmp(t, "ElifNode") == 0) {
        return new ElifNode();
    } else if (strcmp(t, "EllipsisNode") == 0) {
        return new EllipsisNode();
    } else if (strcmp(t, "ElseAttributeNode") == 0) {
        return new ElseAttributeNode();
    } else if (strcmp(t, "ElseNode") == 0) {
        return new ElseNode();
    } else if (strcmp(t, "EndlNode") == 0) {
        return new EndlNode();
    } else if (strcmp(t, "ExceptNode") == 0) {
        return new ExceptNode();
    } else if (strcmp(t, "ExecNode") == 0) {
        return new ExecNode();
    } else if (strcmp(t, "FinallyNode") == 0) {
        return new FinallyNode();
    } else if (strcmp(t, "FloatExponantComplexNode") == 0) {
        return new FloatExponantComplexNode();
    } else if (strcmp(t, "FloatExponantNode") == 0) {
        return new FloatExponantNode();
    } else if (strcmp(t, "FloatNode") == 0) {
        return new FloatNode();
    } else if (strcmp(t, "ForNode") == 0) {
        return new ForNode();
    } else if (strcmp(t, "FromImportNode") == 0) {
        return new FromImportNode();
    } else if (strcmp(t, "GeneratorComprehensionNode") == 0) {
        return new GeneratorComprehensionNode();
    } else if (strcmp(t, "GetitemNode") == 0) {
        return new GetitemNode();
    } else if (strcmp(t, "GlobalNode") == 0) {
        return new GlobalNode();
    } else if (strcmp(t, "HexaNode") == 0) {
        return new HexaNode();
    } else if (strcmp(t, "IfElseBlockSiblingNode") == 0) {
        return new IfElseBlockSiblingNode();
    } else if (strcmp(t, "IfNode") == 0) {
        return new IfNode();
    } else if (strcmp(t, "IfelseblockNode") == 0) {
        return new IfelseblockNode();
    } else if (strcmp(t, "ImportNode") == 0) {
        return new ImportNode();
    } else if (strcmp(t, "IntNode") == 0) {
        return new IntNode();
    } else if (strcmp(t, "LambdaNode") == 0) {
        return new LambdaNode();
    } else if (strcmp(t, "LeftParenthesisNode") == 0) {
        return new LeftParenthesisNode();
    } else if (strcmp(t, "LineProxyList") == 0) {
        return new LineProxyList();
    } else if (strcmp(t, "ListArgumentNode") == 0) {
        return new ListArgumentNode();
    } else if (strcmp(t, "ListComprehensionNode") == 0) {
        return new ListComprehensionNode();
    } else if (strcmp(t, "ListNode") == 0) {
        return new ListNode();
    } else if (strcmp(t, "LongNode") == 0) {
        return new LongNode();
    } else if (strcmp(t, "NameAsNameNode") == 0) {
        return new NameAsNameNode();
    } else if (strcmp(t, "NameNode") == 0) {
        return new NameNode();
    } else if (strcmp(t, "Node") == 0) {
        return new Node();
    } else if (strcmp(t, "NodeList") == 0) {
        return new NodeList();
    } else if (strcmp(t, "OctaNode") == 0) {
        return new OctaNode();
    } else if (strcmp(t, "PassNode") == 0) {
        return new PassNode();
    } else if (strcmp(t, "PrintNode") == 0) {
        return new PrintNode();
    } else if (strcmp(t, "RaiseNode") == 0) {
        return new RaiseNode();
    } else if (strcmp(t, "RawStringNode") == 0) {
        return new RawStringNode();
    } else if (strcmp(t, "ReprNode") == 0) {
        return new ReprNode();
    } else if (strcmp(t, "ReturnNode") == 0) {
        return new ReturnNode();
    } else if (strcmp(t, "RightParenthesisNode") == 0) {
        return new RightParenthesisNode();
    } else if (strcmp(t, "SemicolonNode") == 0) {
        return new SemicolonNode();
    } else if (strcmp(t, "SetComprehensionNode") == 0) {
        return new SetComprehensionNode();
    } else if (strcmp(t, "SetNode") == 0) {
        return new SetNode();
    } else if (strcmp(t, "SliceNode") == 0) {
        return new SliceNode();
    } else if (strcmp(t, "SpaceNode") == 0) {
        return new SpaceNode();
    } else if (strcmp(t, "StarNode") == 0) {
        return new StarNode();
    } else if (strcmp(t, "StringChainNode") == 0) {
        return new StringChainNode();
    } else if (strcmp(t, "StringNode") == 0) {
        return new StringNode();
    } else if (strcmp(t, "TernaryOperatorNode") == 0) {
        return new TernaryOperatorNode();
    } else if (strcmp(t, "TryNode") == 0) {
        return new TryNode();
    } else if (strcmp(t, "TupleNode") == 0) {
        return new TupleNode();
    } else if (strcmp(t, "UnicodeRawStringNode") == 0) {
        return new UnicodeRawStringNode();
    } else if (strcmp(t, "UnicodeStringNode") == 0) {
        return new UnicodeStringNode();
    } else if (strcmp(t, "UnitaryOperatorNode") == 0) {
        return new UnitaryOperatorNode();
    } else if (strcmp(t, "WhileNode") == 0) {
        return new WhileNode();
    } else if (strcmp(t, "WithContextItemNode") == 0) {
        return new WithContextItemNode();
    } else if (strcmp(t, "WithNode") == 0) {
        return new WithNode();
    } else if (strcmp(t, "YieldAtomNode") == 0) {
        return new YieldAtomNode();
	} else if (strcmp(t, "YieldNode") == 0) {
		return new YieldNode();
	} else {
		UE_LOG(LogProck, Error, TEXT("Unknown node type: %s"), ANSI_TO_TCHAR(t));
		return nullptr;
	}
	*/

	return nullptr;
}