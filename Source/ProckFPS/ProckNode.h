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
	//virtual ~ProckNode();
	// Factory Method: creates the appropriate ProckNode subclass based on the given PyObject. 
	// Don't use the default constructor to create new ProckNodes!
	static ProckNode* NewNode(PyObject* astNode);

	// Spawn box for this node at the given position and spawn children recursively
	void Spawn(UWorld *world, FVector pos);

	// Dump the underlying python object
	void PrintRaw();

	// Return this class name without the leading 'PN'
	virtual char *Name();

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

// Start Generated Code


/*
A node representing generator passed as an argument during a function call.

Equivalent python:

    a(x for y in z)

RedBaron .help() text:

    ArgumentGeneratorComprehensionNode()
      # identifiers: argument_generator_comprehension, argument_generator_comprehension_, argumentgeneratorcomprehension, argumentgeneratorcomprehensionnode
      result ->
        NameNode()
          # identifiers: name, name_, namenode
          value='x'
      generators ->
        * ComprehensionLoopNode()
            # identifiers: comprehension_loop, comprehension_loop_, comprehensionloop, comprehensionloopnode
            iterator ->
              NameNode()
                # identifiers: name, name_, namenode
                value='y'
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='z'
            ifs ->
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['generators'],
     '_str_keys': ['type'],
     'generators': <NodeList [0, 'value', 1, 'value', 0, 'generators'], " for y in z" 63835328, on ArgumentGeneratorComprehensionNode 63835496>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(x for y in z)" 63835944, on AtomtrailersNode 63832864>,
     'result': <NameNode path=[0, 'value', 1, 'value', 0, 'result'], "x" 63835888, on ArgumentGeneratorComprehensionNode 63835496>,
     'type': 'argument_generator_comprehension'}
    
*/
class PROCKFPS_API PNArgumentGeneratorComprehension : public ProckNode {
public: 
    virtual char *Name() { return "ArgumentGeneratorComprehension "; }
	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing the assert statement.

Equivalent python:

    assert test, message

RedBaron .help() text:

    AssertNode()
      # identifiers: assert, assert_, assertnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='test'
      message ->
        NameNode()
          # identifiers: name, name_, namenode
          value='message'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'message'],
     '_list_keys': ['first_formatting', 'second_formatting', 'third_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], " " 63904008, on AssertNode 63904176>,
     'init': False,
     'message': <NameNode path=[0, 'message'], "message" 63903952, on AssertNode 63904176>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "assert test, message" 63903840, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 63904232, on AssertNode 63904176>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 63904288, on AssertNode 63904176>,
     'type': 'assert',
     'value': <NameNode path=[0, 'value'], "test" 63904456, on AssertNode 63904176>}
    
*/
class PROCKFPS_API PNAssert : public ProckNode {
public: 
    virtual char *Name() { return "Assert "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Message() { return GetAsNode("message"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing the assign operation in python (:file:`foo = bar`) and the"augmented" assign (:file:`foo += bar`).

Equivalent python:

    a = b

RedBaron .help() text:

    AssignmentNode()
      # identifiers: assign, assignment, assignment_, assignmentnode
      operator=''
      target ->
        NameNode()
          # identifiers: name, name_, namenode
          value='a'
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['target', 'value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'operator'],
     'first_formatting': <NodeList [0, 'first_formatting'], " " 63834432, on AssignmentNode 63834152>,
     'init': False,
     'on_attribute': 'root',
     'operator': '',
     'parent': <RedBaron [], "a = b" 63834656, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 63834544, on AssignmentNode 63834152>,
     'target': <NameNode path=[0, 'target'], "a" 63832472, on AssignmentNode 63834152>,
     'type': 'assignment',
     'value': <NameNode path=[0, 'value'], "b" 63833984, on AssignmentNode 63834152>}
    
*/
class PROCKFPS_API PNAssignment : public ProckNode {
public: 
    virtual char *Name() { return "Assignment "; }
	ProckNode *Target() { return GetAsNode("target"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Type() { return GetAsString("type"); } 
	char *Operator() { return GetAsString("operator"); } 
};


/*
This node represents a statement prioritised on another by being surrounded byparenthesis. For e.g., the first part of this addition: :file:`(1 + 1) * 2`.

Equivalent python:

    (foo)

RedBaron .help() text:

    AssociativeParenthesisNode()
      # identifiers: associative_parenthesis, associative_parenthesis_, associativeparenthesis, associativeparenthesisnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='foo'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 63833200, on AssociativeParenthesisNode 63833368>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 63903448, on AssociativeParenthesisNode 63833368>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 63822928, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 63836112, on AssociativeParenthesisNode 63833368>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 63834264, on AssociativeParenthesisNode 63833368>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 63833312, on AssociativeParenthesisNode 63833368>}
    
*/
class PROCKFPS_API PNAssociativeParenthesis : public ProckNode {
public: 
    virtual char *Name() { return "AssociativeParenthesis "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
This node represents a combination of :ref:`NameNode`, :ref:`DotNode`,:ref:`CallNode`, :ref:`GetitemNode` sorted in a list. For e.g.::file:`a.b().c[d]`.

Equivalent python:

    a.b().c[d]

RedBaron .help() text:

    AtomtrailersNode()
      # identifiers: atomtrailers, atomtrailers_, atomtrailersnode
      value ->
        * NameNode()
            # identifiers: name, name_, namenode
            value='a'
        * NameNode()
            # identifiers: name, name_, namenode
            value='b'
        * CallNode()
            # identifiers: call, call_, callnode
            value ->
        * NameNode()
            # identifiers: name, name_, namenode
            value='c'
        * GetitemNode()
            # identifiers: getitem, getitem_, getitemnode
            value ->
              NameNode()
                # identifiers: name, name_, namenode
                value='d'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 63833200, on AssociativeParenthesisNode 63833368>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 63903448, on AssociativeParenthesisNode 63833368>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 63822928, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 63836112, on AssociativeParenthesisNode 63833368>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 63834264, on AssociativeParenthesisNode 63833368>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 63833312, on AssociativeParenthesisNode 63833368>}
    
*/
class PROCKFPS_API PNAtomtrailers : public ProckNode {
public: 
    virtual char *Name() { return "Atomtrailers "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
The node represents a binary number value.

Equivalent python:

    0b10101

RedBaron .help() text:

    BinaryNode()
      # identifiers: binary, binary_, binarynode
      value='0b10101'
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "0b10101" 64073624, on NoneType 1962241112>,
     'type': 'binary',
     'value': '0b10101'}
    
*/
class PROCKFPS_API PNBinary : public ProckNode {
public: 
    virtual char *Name() { return "Binary "; }
	char *Type() { return GetAsString("type"); } 
	char *Value() { return GetAsString("value"); } 
};


/*
The node represents a binary operator (an operator (e.g: :file:`+` :file:`-` :file:`/`..) applied to 2 values) with its operands. For e.g.: :file:`1 + 1`.

Equivalent python:

    1 + 1

RedBaron .help() text:

    BinaryOperatorNode()
      # identifiers: binary_operator, binary_operator_, binaryoperator, binaryoperatornode
      value='+'
      first ->
        IntNode()
          # identifiers: int, int_, intnode
          value='1'
      second ->
        IntNode()
          # identifiers: int, int_, intnode
          value='1'
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value'],
     'first': <IntNode path=[0, 'first'], "1" 64103536, on BinaryOperatorNode 64102696>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64103368, on BinaryOperatorNode 64102696>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "1 + 1" 64071664, on NoneType 1962241112>,
     'second': <IntNode path=[0, 'second'], "1" 64103816, on BinaryOperatorNode 64102696>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64103872, on BinaryOperatorNode 64102696>,
     'type': 'binary_operator',
     'value': '+'}
    
*/
class PROCKFPS_API PNBinaryOperator : public ProckNode {
public: 
    virtual char *Name() { return "BinaryOperator "; }
	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
	char *Type() { return GetAsString("type"); } 
	char *Value() { return GetAsString("value"); } 
};


/*
The node represents a boolean operator (an operator (e.g: :file:`and` :file:`or`) applied to 2 values) with its operands. For e.g.: :file:`x and y`.

Equivalent python:

    x and y

RedBaron .help() text:

    BooleanOperatorNode()
      # identifiers: boolean_operator, boolean_operator_, booleanoperator, booleanoperatornode
      value='and'
      first ->
        NameNode()
          # identifiers: name, name_, namenode
          value='x'
      second ->
        NameNode()
          # identifiers: name, name_, namenode
          value='y'
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value'],
     'first': <NameNode path=[0, 'first'], "x" 64105160, on BooleanOperatorNode 64104040>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64104656, on BooleanOperatorNode 64104040>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 64104768, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "y" 64073008, on BooleanOperatorNode 64104040>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64073400, on BooleanOperatorNode 64104040>,
     'type': 'boolean_operator',
     'value': 'and'}
    
*/
class PROCKFPS_API PNBooleanOperator : public ProckNode {
public: 
    virtual char *Name() { return "BooleanOperator "; }
	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
	char *Type() { return GetAsString("type"); } 
	char *Value() { return GetAsString("value"); } 
};


/*
A node representing a call (eg: :file:`a()`, here :file:`a` is called with noarguments). It is always stored in an :ref:`AtomtrailersNode` or a:ref:`DecoratorNode`.

Equivalent python:

    a(b, c=d)

RedBaron .help() text:

    CallNode()
      # identifiers: call, call_, callnode
      value ->
        * CallArgumentNode()
            # identifiers: call_argument, call_argument_, callargument, callargumentnode
            target ->
              None
            value ->
              NameNode()
                # identifiers: name, name_, namenode
                value='b'
        * CallArgumentNode()
            # identifiers: call_argument, call_argument_, callargument, callargumentnode
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='c'
            value ->
              NameNode()
                # identifiers: name, name_, namenode
                value='d'
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value'],
     'first': <NameNode path=[0, 'first'], "x" 64105160, on BooleanOperatorNode 64104040>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64104656, on BooleanOperatorNode 64104040>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 64104768, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "y" 64073008, on BooleanOperatorNode 64104040>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64073400, on BooleanOperatorNode 64104040>,
     'type': 'boolean_operator',
     'value': 'and'}
    
*/
class PROCKFPS_API PNCall : public ProckNode {
public: 
    virtual char *Name() { return "Call "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing an argument or a named argument of a :ref:`CallNode` (othernodes that can be in a CallNode are :ref:`ListArgumentNode` and:ref:`DictArgumentNode`).

Equivalent python:

    a(b, c=d)

RedBaron .help() text:

    CallArgumentNode()
      # identifiers: call_argument, call_argument_, callargument, callargumentnode
      target ->
        None
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['target', 'value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 64140904, on CallArgumentNode 64106000>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 64140400, on AtomtrailersNode 64102472>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 64141128, on CallArgumentNode 64106000>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 64140568, on CallArgumentNode 64106000>}
    
*/
class PROCKFPS_API PNCallArgument : public ProckNode {
public: 
    virtual char *Name() { return "CallArgument "; }
	ProckNode *Target() { return GetAsNode("target"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a class definition.

Equivalent python:

    class SomeAwesomeName(A, B, C): pass

RedBaron .help() text:

    ClassNode()
      # identifiers: class, class_, classnode
      # default test value: name
      name='SomeAwesomeName'
      parenthesis=True
      decorators ->
      inherit_from ->
        * TupleNode()
            # identifiers: tuple, tuple_, tuplenode
            with_parenthesis=False
            value ->
              * NameNode()
                  # identifiers: name, name_, namenode
                  value='A'
              * NameNode()
                  # identifiers: name, name_, namenode
                  value='B'
              * NameNode()
                  # identifiers: name, name_, namenode
                  value='C'
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['target', 'value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 64140904, on CallArgumentNode 64106000>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 64140400, on AtomtrailersNode 64102472>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 64141128, on CallArgumentNode 64106000>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 64140568, on CallArgumentNode 64106000>}
    
*/
class PROCKFPS_API PNClass : public ProckNode {
public: 
    virtual char *Name() { return "Class "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a comma, this is the kind of formatting node that you mighthave to deal with if not enough high level helpers are available. They aregenerally present in call, function arguments definition and data structuresugar syntactic notation.The comma node is responsible for holding the formatting around it.

Equivalent python:

    [1, 2, 3]

RedBaron .help() text:

    CommaNode()
      # identifiers: comma, comma_, commanode
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 64174120, on CommaNode 64174792>,
     'init': False,
     'on_attribute': 'value',
     'parent': <ListNode path=[0], "[1, 2, 3]" 64174400, on RedBaron 64105552>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], " " 64174904, on CommaNode 64174792>,
     'type': 'comma'}
    
*/
class PROCKFPS_API PNComma : public ProckNode {
public: 
    virtual char *Name() { return "Comma "; }
	char *Type() { return GetAsString("type"); } 
};


/*
The node represents a comparison operation, for e.g.: :file:`42 > 30`.

Equivalent python:

    42 > 30

RedBaron .help() text:

    ComparisonNode()
      # identifiers: comparison, comparison_, comparisonnode
      first ->
        IntNode()
          # identifiers: int, int_, intnode
          value='42'
      value ->
        ComparisonOperatorNode()
          # identifiers: comparison_operator, comparison_operator_, comparisonoperator, comparisonoperatornode
          first='>'
          second=''
      second ->
        IntNode()
          # identifiers: int, int_, intnode
          value='30'
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first': <IntNode path=[0, 'first'], "42" 64205712, on ComparisonNode 64205264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64205488, on ComparisonNode 64205264>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "42 > 30" 64174512, on NoneType 1962241112>,
     'second': <IntNode path=[0, 'second'], "30" 64205824, on ComparisonNode 64205264>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64205432, on ComparisonNode 64205264>,
     'type': 'comparison',
     'value': <ComparisonOperatorNode path=[0, 'value'], ">" 64176024, on ComparisonNode 64205264>}
    
*/
class PROCKFPS_API PNComparison : public ProckNode {
public: 
    virtual char *Name() { return "Comparison "; }
	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
The node represents "if" condition in a comprehension loop. It is always amember of a :ref:`ComprehensionLoopNode`.

Equivalent python:

    [x for x in x if condition]

RedBaron .help() text:

    ComprehensionIfNode()
      # identifiers: comprehension_if, comprehension_if_, comprehensionif, comprehensionifnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='condition'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'first_formatting'], " " 64174064, on ComprehensionIfNode 64173448>,
     'init': False,
     'on_attribute': 'ifs',
     'parent': <ComprehensionLoopNode path=[0, 'generators', 0], " for x in x if c...n" 64173784, on ListComprehensionNode 64173504>,
     'second_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'second_formatting'], " " 64070824, on ComprehensionIfNode 64173448>,
     'type': 'comprehension_if',
     'value': <NameNode path=[0, 'generators', 0, 'ifs', 0, 'value'], "condition" 64070712, on ComprehensionIfNode 64173448>}
    
*/
class PROCKFPS_API PNComprehensionIf : public ProckNode {
public: 
    virtual char *Name() { return "ComprehensionIf "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
The node represents the loop part of a comprehension structure.

Equivalent python:

    [x for y in z]

RedBaron .help() text:

    ComprehensionLoopNode()
      # identifiers: comprehension_loop, comprehension_loop_, comprehensionloop, comprehensionloopnode
      iterator ->
        NameNode()
          # identifiers: name, name_, namenode
          value='y'
      target ->
        NameNode()
          # identifiers: name, name_, namenode
          value='z'
      ifs ->
    

Python __dict__ dump:

    {'_dict_keys': ['iterator', 'target'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'ifs'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'generators', 0, 'first_formatting'], " " 64205656, on ComprehensionLoopNode 64070096>,
     'fourth_formatting': <NodeList [0, 'generators', 0, 'fourth_formatting'], " " 64208680, on ComprehensionLoopNode 64070096>,
     'ifs': <NodeList [0, 'generators', 0, 'ifs'], "" 64208848, on ComprehensionLoopNode 64070096>,
     'init': False,
     'iterator': <NameNode path=[0, 'generators', 0, 'iterator'], "y" 64204872, on ComprehensionLoopNode 64070096>,
     'on_attribute': 'generators',
     'parent': <ListComprehensionNode path=[0], "[x for y in z]" 64102528, on RedBaron 64175968>,
     'second_formatting': <NodeList [0, 'generators', 0, 'second_formatting'], " " 64207784, on ComprehensionLoopNode 64070096>,
     'target': <NameNode path=[0, 'generators', 0, 'target'], "z" 64208792, on ComprehensionLoopNode 64070096>,
     'third_formatting': <NodeList [0, 'generators', 0, 'third_formatting'], " " 64208568, on ComprehensionLoopNode 64070096>,
     'type': 'comprehension_loop'}
    
*/
class PROCKFPS_API PNComprehensionLoop : public ProckNode {
public: 
    virtual char *Name() { return "ComprehensionLoop "; }
	ProckNode *Iterator() { return GetAsNode("iterator"); } 
	ProckNode *Target() { return GetAsNode("target"); } 
	std::vector<ProckNode *> *Ifs() { return GetAsList("ifs"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing an individual decorator (of a function or a class).

Equivalent python:

    @stuff.plop(*a)\ndef b(): pass

RedBaron .help() text:

    DecoratorNode()
      # identifiers: decorator, decorator_, decoratornode
      value ->
        DottedNameNode()
          # identifiers: dotted_name, dotted_name_, dottedname, dottednamenode
          value ->
            * NameNode()
                # identifiers: name, name_, namenode
                value='stuff'
            * DotNode()
                # identifiers: dot, dot_, dotnode
            * NameNode()
                # identifiers: name, name_, namenode
                value='plop'
      call ->
        CallNode()
          # identifiers: call, call_, callnode
          value ->
            * ListArgumentNode()
                # identifiers: list_argument, list_argument_, listargument, listargumentnode
                value ->
                  NameNode()
                    # identifiers: name, name_, namenode
                    value='a'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'call'],
     '_list_keys': [],
     '_str_keys': ['type'],
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 67747288, on DecoratorNode 67747792>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 67747568, on RedBaron 64208288>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 67747624, on DecoratorNode 67747792>}
    
*/
class PROCKFPS_API PNDecorator : public ProckNode {
public: 
    virtual char *Name() { return "Decorator "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Call() { return GetAsNode("call"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing an argument in a function definition.

Equivalent python:

    def a(b, c=d): pass

RedBaron .help() text:

    0 -----------------------------------------------------
    DefArgumentNode()
      # identifiers: def_argument, def_argument_, defargument, defargumentnode
      target ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
      value ->
        None
    1 -----------------------------------------------------
    CommaNode()
      # identifiers: comma, comma_, commanode
    2 -----------------------------------------------------
    DefArgumentNode()
      # identifiers: def_argument, def_argument_, defargument, defargumentnode
      target ->
        NameNode()
          # identifiers: name, name_, namenode
          value='c'
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='d'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'call'],
     '_list_keys': [],
     '_str_keys': ['type'],
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 67747288, on DecoratorNode 67747792>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 67747568, on RedBaron 64208288>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 67747624, on DecoratorNode 67747792>}
    
*/
class PROCKFPS_API PNDefArgument : public ProckNode {
public: 
    virtual char *Name() { return "DefArgument "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a :file:`del` statement.

Equivalent python:

    del stuff

RedBaron .help() text:

    DelNode()
      # identifiers: del, del_, delnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='stuff'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 67814008, on DelNode 67814176>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "del stuff" 64139560, on NoneType 1962241112>,
     'type': 'del',
     'value': <NameNode path=[0, 'value'], "stuff" 67814064, on DelNode 67814176>}
    
*/
class PROCKFPS_API PNDel : public ProckNode {
public: 
    virtual char *Name() { return "Del "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a 'kwargs' defined in a function definition argument orused in a :ref:`CallNode`.

Equivalent python:

    a(**b)

RedBaron .help() text:

    DictArgumentNode()
      # identifiers: dict_argument, dict_argument_, dictargument, dictargumentnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 67816640, on DictArgumentNode 67814736>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 67816248, on AtomtrailersNode 67814288>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 67816528, on DictArgumentNode 67814736>}
    
*/
class PROCKFPS_API PNDictArgument : public ProckNode {
public: 
    virtual char *Name() { return "DictArgument "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing python sugar syntactic notation for dict.

Equivalent python:

    {'a': 1, 'b': 2, 'c': 3}

RedBaron .help() text:

    DictNode()
      # identifiers: dict, dict_, dictnode
      value ->
        * DictitemNode()
            # identifiers: dictitem, dictitem_, dictitemnode
            key ->
              StringNode()
                # identifiers: string, string_, stringnode
                value="'a'"
            value ->
              IntNode()
                # identifiers: int, int_, intnode
                value='1'
        * DictitemNode()
            # identifiers: dictitem, dictitem_, dictitemnode
            key ->
              StringNode()
                # identifiers: string, string_, stringnode
                value="'b'"
            value ->
              IntNode()
                # identifiers: int, int_, intnode
                value='2'
        * DictitemNode()
            # identifiers: dictitem, dictitem_, dictitemnode
            key ->
              StringNode()
                # identifiers: string, string_, stringnode
                value="'c'"
            value ->
              IntNode()
                # identifiers: int, int_, intnode
                value='3'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 67816640, on DictArgumentNode 67814736>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 67816248, on AtomtrailersNode 67814288>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 67816528, on DictArgumentNode 67814736>}
    
*/
class PROCKFPS_API PNDict : public ProckNode {
public: 
    virtual char *Name() { return "Dict "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing dictionary comprehension node.

Equivalent python:

    {a: b for c in d}

RedBaron .help() text:

    DictComprehensionNode()
      # identifiers: dict_comprehension, dict_comprehension_, dictcomprehension, dictcomprehensionnode
      result ->
        DictitemNode()
          # identifiers: dictitem, dictitem_, dictitemnode
          key ->
            NameNode()
              # identifiers: name, name_, namenode
              value='a'
          value ->
            NameNode()
              # identifiers: name, name_, namenode
              value='b'
      generators ->
        * ComprehensionLoopNode()
            # identifiers: comprehension_loop, comprehension_loop_, comprehensionloop, comprehensionloopnode
            iterator ->
              NameNode()
                # identifiers: name, name_, namenode
                value='c'
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='d'
            ifs ->
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 67851824, on DictComprehensionNode 67745776>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67853112, on DictComprehensionNode 67745776>,
     'generators': <NodeList [0, 'generators'], " for c in d" 67851656, on DictComprehensionNode 67745776>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 67744040, on NoneType 1962241112>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 67852384, on DictComprehensionNode 67745776>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67852160, on DictComprehensionNode 67745776>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 67852440, on DictComprehensionNode 67745776>,
     'type': 'dict_comprehension'}
    
*/
class PROCKFPS_API PNDictComprehension : public ProckNode {
public: 
    virtual char *Name() { return "DictComprehension "; }
	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing an argument to the import node.

Equivalent python:

    import a.b.c as d

RedBaron .help() text:

    DottedAsNameNode()
      # identifiers: dotted_as_name, dotted_as_name_, dottedasname, dottedasnamenode
      target='d'
      value ->
        * NameNode()
            # identifiers: name, name_, namenode
            value='a'
        * NameNode()
            # identifiers: name, name_, namenode
            value='b'
        * NameNode()
            # identifiers: name, name_, namenode
            value='c'
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 67851824, on DictComprehensionNode 67745776>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67853112, on DictComprehensionNode 67745776>,
     'generators': <NodeList [0, 'generators'], " for c in d" 67851656, on DictComprehensionNode 67745776>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 67744040, on NoneType 1962241112>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 67852384, on DictComprehensionNode 67745776>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67852160, on DictComprehensionNode 67745776>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 67852440, on DictComprehensionNode 67745776>,
     'type': 'dict_comprehension'}
    
*/
class PROCKFPS_API PNDottedAsName : public ProckNode {
public: 
    virtual char *Name() { return "DottedAsName "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a dot '.', generally found in atom trailers (this kind of structure: 'variable.another_variable(call)[getitem]').This is the kind of formatting node that you might have to deal with if not enough high level helpers are available.The dot node is responsible for holding the formatting around it.

Equivalent python:

    a.b

RedBaron .help() text:

    NameNode()
      # identifiers: name, name_, namenode
      value='b'
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67850648, on RedBaron 67883976>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNDot : public ProckNode {
public: 
    virtual char *Name() { return "Dot "; }
	char *Type() { return GetAsString("type"); } 
	char *Value() { return GetAsString("value"); } 
};


/*
A node representing an elif statement.The ElifNode, like the :ref:`IfNode` or the :ref:`ElseNode` are stored in a :ref:`IfelseblockNode`.

Equivalent python:

    if a: pass\nelif b: pass

RedBaron .help() text:

    ElifNode()
      # identifiers: elif, elif_, elifnode
      test ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67850648, on RedBaron 67883976>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNElif : public ProckNode {
public: 
    virtual char *Name() { return "Elif "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing an else statement.The ElseNode, like the :ref:`IfNode` or the :ref:`ElifNode`, is stored in a :ref:`IfelseblockNode`.

Equivalent python:

    if a: pass\nelse: pass

RedBaron .help() text:

    ElseNode()
      # identifiers: else, else_, elsenode
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67850648, on RedBaron 67883976>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNElse : public ProckNode {
public: 
    virtual char *Name() { return "Else "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing an except statement (member of a :ref:`TryNode`).

Equivalent python:

    try: pass\nexcept FooBar: pass\nexcept Exception: pass\nelse: pass\nfinally: pass\n

RedBaron .help() text:

    EndlNode()
      # identifiers: endl, endl_, endlnode
      value='\n'
      indent=''
    ExceptNode()
      # identifiers: except, except_, exceptnode
      delimiter=''
      exception ->
        NameNode()
          # identifiers: name, name_, namenode
          value='FooBar'
      target ->
        None
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67850648, on RedBaron 67883976>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNExcept : public ProckNode {
public: 
    virtual char *Name() { return "Except "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a exec statement.

Equivalent python:

    exec '1 + 1' in a, b

RedBaron .help() text:

    ExecNode()
      # identifiers: exec, exec_, execnode
      value ->
        StringNode()
          # identifiers: string, string_, stringnode
          value="'1 + 1'"
      globals ->
        NameNode()
          # identifiers: name, name_, namenode
          value='a'
      locals ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67850592, on ExecNode 67815520>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67815352, on ExecNode 67815520>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67850536, on ExecNode 67815520>,
     'globals': <NameNode path=[0, 'globals'], "a" 67853504, on ExecNode 67815520>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67850760, on ExecNode 67815520>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67814120, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67851600, on ExecNode 67815520>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67850424, on ExecNode 67815520>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67854008, on ExecNode 67815520>}
    
*/
class PROCKFPS_API PNExec : public ProckNode {
public: 
    virtual char *Name() { return "Exec "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Globals() { return GetAsNode("globals"); } 
	ProckNode *Locals() { return GetAsNode("locals"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a finally statement (member of a :ref:`TryNode`).

Equivalent python:

    try: pass\nexcept FooBar: pass\nexcept Exception: pass\nelse: pass\nfinally: pass\n").finally_.help(deep=True)

RedBaron .help() text:

    FinallyNode()
      # identifiers: finally, finally_, finallynode
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67850592, on ExecNode 67815520>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67815352, on ExecNode 67815520>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67850536, on ExecNode 67815520>,
     'globals': <NameNode path=[0, 'globals'], "a" 67853504, on ExecNode 67815520>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67850760, on ExecNode 67815520>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67814120, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67851600, on ExecNode 67815520>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67850424, on ExecNode 67815520>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67854008, on ExecNode 67815520>}
    
*/
class PROCKFPS_API PNFinally : public ProckNode {
public: 
    virtual char *Name() { return "Finally "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a for loop.

Equivalent python:

    for i in b:\n    pass

RedBaron .help() text:

    ForNode()
      # identifiers: for, for_, fornode
      iterator ->
        NameNode()
          # identifiers: name, name_, namenode
          value='i'
      target ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
      else ->
        None
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67850592, on ExecNode 67815520>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67815352, on ExecNode 67815520>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67850536, on ExecNode 67815520>,
     'globals': <NameNode path=[0, 'globals'], "a" 67853504, on ExecNode 67815520>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67850760, on ExecNode 67815520>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67814120, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67851600, on ExecNode 67815520>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67850424, on ExecNode 67815520>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67854008, on ExecNode 67815520>}
    
*/
class PROCKFPS_API PNFor : public ProckNode {
public: 
    virtual char *Name() { return "For "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a "from import" statement.

Equivalent python:

    from a import b

RedBaron .help() text:

    FromImportNode()
      # identifiers: from_import, from_import_, fromimport, fromimportnode
      # helpers: full_path_modules, full_path_names, modules, names
      value ->
        * NameNode()
            # identifiers: name, name_, namenode
            value='a'
      targets ->
        * NameAsNameNode()
            # identifiers: name_as_name, name_as_name_, nameasname, nameasnamenode
            value='b'
            target=''
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67850592, on ExecNode 67815520>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67815352, on ExecNode 67815520>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67850536, on ExecNode 67815520>,
     'globals': <NameNode path=[0, 'globals'], "a" 67853504, on ExecNode 67815520>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67850760, on ExecNode 67815520>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67814120, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67851600, on ExecNode 67815520>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67850424, on ExecNode 67815520>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67854008, on ExecNode 67815520>}
    
*/
class PROCKFPS_API PNFromImport : public ProckNode {
public: 
    virtual char *Name() { return "FromImport "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a function definition.

Equivalent python:

    def stuff():\n    pass\n

RedBaron .help() text:

    DefNode()
      # identifiers: def, def_, defnode, funcdef, funcdef_
      # default test value: name
      name='stuff'
      decorators ->
      arguments ->
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67850592, on ExecNode 67815520>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67815352, on ExecNode 67815520>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67850536, on ExecNode 67815520>,
     'globals': <NameNode path=[0, 'globals'], "a" 67853504, on ExecNode 67815520>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67850760, on ExecNode 67815520>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67814120, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67851600, on ExecNode 67815520>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67850424, on ExecNode 67815520>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67854008, on ExecNode 67815520>}
    
*/
class PROCKFPS_API PNFuncdef : public ProckNode {
public: 
    virtual char *Name() { return "Funcdef "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a generator comprehension node.

Equivalent python:

    (x for y in z)

RedBaron .help() text:

    GeneratorComprehensionNode()
      # identifiers: generator_comprehension, generator_comprehension_, generatorcomprehension, generatorcomprehensionnode
      result ->
        NameNode()
          # identifiers: name, name_, namenode
          value='x'
      generators ->
        * ComprehensionLoopNode()
            # identifiers: comprehension_loop, comprehension_loop_, comprehensionloop, comprehensionloopnode
            iterator ->
              NameNode()
                # identifiers: name, name_, namenode
                value='y'
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='z'
            ifs ->
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 67992096, on GeneratorComprehensionNode 67991984>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67993216, on GeneratorComprehensionNode 67991984>,
     'generators': <NodeList [0, 'generators'], " for y in z" 67992264, on GeneratorComprehensionNode 67991984>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(x for y in z)" 67957760, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 67992320, on GeneratorComprehensionNode 67991984>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67992880, on GeneratorComprehensionNode 67991984>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 67992432, on GeneratorComprehensionNode 67991984>,
     'type': 'generator_comprehension'}
    
*/
class PROCKFPS_API PNGeneratorComprehension : public ProckNode {
public: 
    virtual char *Name() { return "GeneratorComprehension "; }
	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a 'get item' access on a python object, in other words the'[stuff]' in 'some_object[stuff]'.

Equivalent python:

    a[b]

RedBaron .help() text:

    GetitemNode()
      # identifiers: getitem, getitem_, getitemnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 68302104, on GetitemNode 68301600>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 68302496, on GetitemNode 68301600>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 67993496, on RedBaron 67992768>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 68301880, on GetitemNode 68301600>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 68302440, on GetitemNode 68301600>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 68301936, on GetitemNode 68301600>}
    
*/
class PROCKFPS_API PNGetitem : public ProckNode {
public: 
    virtual char *Name() { return "Getitem "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a global statement.

Equivalent python:

    global a

RedBaron .help() text:

    GlobalNode()
      # identifiers: global, global_, globalnode
      value ->
        * NameNode()
            # identifiers: name, name_, namenode
            value='a'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 68302104, on GetitemNode 68301600>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 68302496, on GetitemNode 68301600>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 67993496, on RedBaron 67992768>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 68301880, on GetitemNode 68301600>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 68302440, on GetitemNode 68301600>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 68301936, on GetitemNode 68301600>}
    
*/
class PROCKFPS_API PNGlobal : public ProckNode {
public: 
    virtual char *Name() { return "Global "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing an if statement.The IfNode, like the :ref:`ElifNode` or the :ref:`ElseNode`, is stored in an :ref:`IfelseblockNode`.

Equivalent python:

    if a: pass

RedBaron .help() text:

    IfNode()
      # identifiers: if, if_, ifnode
      test ->
        NameNode()
          # identifiers: name, name_, namenode
          value='a'
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 68302104, on GetitemNode 68301600>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 68302496, on GetitemNode 68301600>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 67993496, on RedBaron 67992768>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 68301880, on GetitemNode 68301600>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 68302440, on GetitemNode 68301600>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 68301936, on GetitemNode 68301600>}
    
*/
class PROCKFPS_API PNIf : public ProckNode {
public: 
    virtual char *Name() { return "If "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing the conditional block composed of at least one if statement,zero or more elif statements and, at the end, an optional else statement. Allthose statements are stored in a list.

Equivalent python:

    if a: pass\nelif b: pass\nelse: pass\n

RedBaron .help() text:

    IfelseblockNode()
      # identifiers: ifelseblock, ifelseblock_, ifelseblocknode
      value ->
        * IfNode()
            # identifiers: if, if_, ifnode
            test ->
              NameNode()
                # identifiers: name, name_, namenode
                value='a'
            value ->
              * PassNode()
                  # identifiers: pass, pass_, passnode
        * ElifNode()
            # identifiers: elif, elif_, elifnode
            test ->
              NameNode()
                # identifiers: name, name_, namenode
                value='b'
            value ->
              * PassNode()
                  # identifiers: pass, pass_, passnode
        * ElseNode()
            # identifiers: else, else_, elsenode
            value ->
              * PassNode()
                  # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['value'],
     '_str_keys': ['type'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "if a: pass\nelif...n" 68301544, on NoneType 1962241112>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 68339864, on IfelseblockNode 68338016>}
    
*/
class PROCKFPS_API PNIfelseblock : public ProckNode {
public: 
    virtual char *Name() { return "Ifelseblock "; }
	std::vector<ProckNode *> *Value() { return GetAsList("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing the import statement of the python language.*Be careful, this node and its subnodes are way more complex than what you canexpect*.

Equivalent python:

    import foo

RedBaron .help() text:

    ImportNode()
      # identifiers: import, import_, importnode
      # helpers: modules, names
      value ->
        * DottedAsNameNode()
            # identifiers: dotted_as_name, dotted_as_name_, dottedasname, dottedasnamenode
            target=''
            value ->
              * NameNode()
                  # identifiers: name, name_, namenode
                  value='foo'
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['value'],
     '_str_keys': ['type'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "if a: pass\nelif...n" 68301544, on NoneType 1962241112>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 68339864, on IfelseblockNode 68338016>}
    
*/
class PROCKFPS_API PNImport : public ProckNode {
public: 
    virtual char *Name() { return "Import "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a lambda statement.

Equivalent python:

    lambda x: y

RedBaron .help() text:

    IntNode()
      # identifiers: int, int_, intnode
      value='42'
    LambdaNode()
      # identifiers: lambda, lambda_, lambdanode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='y'
      arguments ->
        * DefArgumentNode()
            # identifiers: def_argument, def_argument_, defargument, defargumentnode
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='x'
            value ->
              None
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'arguments',
                    'second_formatting',
                    'third_formatting'],
     '_str_keys': ['type'],
     'arguments': <CommaProxyList [0, 'arguments'], "x" 67989632, on LambdaNode 67991256>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67991648, on LambdaNode 67991256>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "lambda x: y" 64142976, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67993272, on LambdaNode 67991256>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67991592, on LambdaNode 67991256>,
     'type': 'lambda',
     'value': <NameNode path=[0, 'value'], "y" 68302384, on LambdaNode 67991256>}
    
*/
class PROCKFPS_API PNLambda : public ProckNode {
public: 
    virtual char *Name() { return "Lambda "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Arguments() { return GetAsList("arguments"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a "start argument" in a function call **or** definition.

Equivalent python:

    def a(*b): pass

RedBaron .help() text:

    ListArgumentNode()
      # identifiers: list_argument, list_argument_, listargument, listargumentnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'arguments', 0, 'formatting'], "" 68378520, on ListArgumentNode 68375776>,
     'init': False,
     'on_attribute': 'arguments',
     'parent': <DefNode path=[0], "def a(*b): pass\n" 68377736, on RedBaron 67991816>,
     'type': 'list_argument',
     'value': <NameNode path=[0, 'arguments', 0, 'value'], "b" 68378576, on ListArgumentNode 68375776>}
    
*/
class PROCKFPS_API PNListArgument : public ProckNode {
public: 
    virtual char *Name() { return "ListArgument "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a list comprehension node.

Equivalent python:

    [x for y in z]

RedBaron .help() text:

    ListComprehensionNode()
      # identifiers: list_comprehension, list_comprehension_, listcomprehension, listcomprehensionnode
      result ->
        NameNode()
          # identifiers: name, name_, namenode
          value='x'
      generators ->
        * ComprehensionLoopNode()
            # identifiers: comprehension_loop, comprehension_loop_, comprehensionloop, comprehensionloopnode
            iterator ->
              NameNode()
                # identifiers: name, name_, namenode
                value='y'
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='z'
            ifs ->
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68406464, on ListComprehensionNode 68404504>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68406800, on ListComprehensionNode 68404504>,
     'generators': <NodeList [0, 'generators'], " for y in z" 68405736, on ListComprehensionNode 68404504>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 68378072, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 68406520, on ListComprehensionNode 68404504>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68405960, on ListComprehensionNode 68404504>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68405904, on ListComprehensionNode 68404504>,
     'type': 'list_comprehension'}
    
*/
class PROCKFPS_API PNListComprehension : public ProckNode {
public: 
    virtual char *Name() { return "ListComprehension "; }
	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing python sugar syntactic notation for list.

Equivalent python:

    [1, 2, 3]

RedBaron .help() text:

    ListNode()
      # identifiers: list, list_, listnode
      value ->
        * IntNode()
            # identifiers: int, int_, intnode
            value='1'
        * IntNode()
            # identifiers: int, int_, intnode
            value='2'
        * IntNode()
            # identifiers: int, int_, intnode
            value='3'
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68406464, on ListComprehensionNode 68404504>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68406800, on ListComprehensionNode 68404504>,
     'generators': <NodeList [0, 'generators'], " for y in z" 68405736, on ListComprehensionNode 68404504>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 68378072, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 68406520, on ListComprehensionNode 68404504>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68405960, on ListComprehensionNode 68404504>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68405904, on ListComprehensionNode 68404504>,
     'type': 'list_comprehension'}
    
*/
class PROCKFPS_API PNList : public ProckNode {
public: 
    virtual char *Name() { return "List "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing an argument to the from import statement.

Equivalent python:

    from x import a as d

RedBaron .help() text:

    NameAsNameNode()
      # identifiers: name_as_name, name_as_name_, nameasname, nameasnamenode
      value='a'
      target='d'
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value', 'target'],
     'first_formatting': [' '],
     'init': False,
     'on_attribute': 'targets',
     'parent': <FromImportNode path=[0], "from x import a as d" 67960616, on RedBaron 64142864>,
     'second_formatting': [' '],
     'target': 'd',
     'type': 'name_as_name',
     'value': 'a'}
    
*/
class PROCKFPS_API PNNameAsName : public ProckNode {
public: 
    virtual char *Name() { return "NameAsName "; }
	char *Type() { return GetAsString("type"); } 
	char *Value() { return GetAsString("value"); } 
	char *Target() { return GetAsString("target"); } 
};


/*
A node representing a print statement.

Equivalent python:

    print(stuff)

RedBaron .help() text:

    PrintNode()
      # identifiers: print, print_, printnode
      destination ->
        None
      value ->
        * AssociativeParenthesisNode()
            # identifiers: associative_parenthesis, associative_parenthesis_, associativeparenthesis, associativeparenthesisnode
            value ->
              NameNode()
                # identifiers: name, name_, namenode
                value='stuff'
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value', 'target'],
     'first_formatting': [' '],
     'init': False,
     'on_attribute': 'targets',
     'parent': <FromImportNode path=[0], "from x import a as d" 67960616, on RedBaron 64142864>,
     'second_formatting': [' '],
     'target': 'd',
     'type': 'name_as_name',
     'value': 'a'}
    
*/
class PROCKFPS_API PNPrint : public ProckNode {
public: 
    virtual char *Name() { return "Print "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a raise statement.

Equivalent python:

    raise Exception(), foo, bar

RedBaron .help() text:

    RaiseNode()
      # identifiers: raise, raise_, raisenode
      value ->
        AtomtrailersNode()
          # identifiers: atomtrailers, atomtrailers_, atomtrailersnode
          value ->
            * NameNode()
                # identifiers: name, name_, namenode
                value='Exception'
            * CallNode()
                # identifiers: call, call_, callnode
                value ->
      instance ->
        NameNode()
          # identifiers: name, name_, namenode
          value='foo'
      traceback ->
        NameNode()
          # identifiers: name, name_, namenode
          value='bar'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'instance', 'traceback'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 68441144, on RaiseNode 68443776>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68444056, on RaiseNode 68443776>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68440472, on RaiseNode 68443776>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 68442712, on RaiseNode 68443776>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 68442096, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68443944, on RaiseNode 68443776>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68442936, on RaiseNode 68443776>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 68441256, on RaiseNode 68443776>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 68442824, on RaiseNode 68443776>}
    
*/
class PROCKFPS_API PNRaise : public ProckNode {
public: 
    virtual char *Name() { return "Raise "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Instance() { return GetAsNode("instance"); } 
	ProckNode *Traceback() { return GetAsNode("traceback"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing python sugar syntactic notation for repr.

Equivalent python:

    `pouet`

RedBaron .help() text:

    ReprNode()
      # identifiers: repr, repr_, reprnode
      value ->
        * NameNode()
            # identifiers: name, name_, namenode
            value='pouet'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'instance', 'traceback'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 68441144, on RaiseNode 68443776>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68444056, on RaiseNode 68443776>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68440472, on RaiseNode 68443776>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 68442712, on RaiseNode 68443776>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 68442096, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68443944, on RaiseNode 68443776>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68442936, on RaiseNode 68443776>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 68441256, on RaiseNode 68443776>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 68442824, on RaiseNode 68443776>}
    
*/
class PROCKFPS_API PNRepr : public ProckNode {
public: 
    virtual char *Name() { return "Repr "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a return statement.

Equivalent python:

    return stuff

RedBaron .help() text:

    ReturnNode()
      # identifiers: return, return_, returnnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='stuff'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 68376000, on ReturnNode 68375608>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 67884760, on NoneType 1962241112>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 68377344, on ReturnNode 68375608>}
    
*/
class PROCKFPS_API PNReturn : public ProckNode {
public: 
    virtual char *Name() { return "Return "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing python sugar syntactic notation for set.

Equivalent python:

    {1, 2, 3}

RedBaron .help() text:

    SetNode()
      # identifiers: set, set_, setnode
      value ->
        * IntNode()
            # identifiers: int, int_, intnode
            value='1'
        * IntNode()
            # identifiers: int, int_, intnode
            value='2'
        * IntNode()
            # identifiers: int, int_, intnode
            value='3'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 68376000, on ReturnNode 68375608>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 67884760, on NoneType 1962241112>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 68377344, on ReturnNode 68375608>}
    
*/
class PROCKFPS_API PNSet : public ProckNode {
public: 
    virtual char *Name() { return "Set "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a set comprehension node.

Equivalent python:

    {x for y in z}

RedBaron .help() text:

    SetComprehensionNode()
      # identifiers: set_comprehension, set_comprehension_, setcomprehension, setcomprehensionnode
      result ->
        NameNode()
          # identifiers: name, name_, namenode
          value='x'
      generators ->
        * ComprehensionLoopNode()
            # identifiers: comprehension_loop, comprehension_loop_, comprehensionloop, comprehensionloopnode
            iterator ->
              NameNode()
                # identifiers: name, name_, namenode
                value='y'
            target ->
              NameNode()
                # identifiers: name, name_, namenode
                value='z'
            ifs ->
    

Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68518912, on SetComprehensionNode 68475872>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68519248, on SetComprehensionNode 68475872>,
     'generators': <NodeList [0, 'generators'], " for y in z" 68518184, on SetComprehensionNode 68475872>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{x for y in z}" 68474864, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 68518968, on SetComprehensionNode 68475872>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68518408, on SetComprehensionNode 68475872>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68518352, on SetComprehensionNode 68475872>,
     'type': 'set_comprehension'}
    
*/
class PROCKFPS_API PNSetComprehension : public ProckNode {
public: 
    virtual char *Name() { return "SetComprehension "; }
	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a slice, the "1:2:3" that can be found in a:ref:`GetitemNode`.

Equivalent python:

    a[1:-1:2]

RedBaron .help() text:

    SliceNode()
      # identifiers: slice, slice_, slicenode
      has_two_colons=True
      lower ->
        IntNode()
          # identifiers: int, int_, intnode
          value='1'
      upper ->
        UnitaryOperatorNode()
          # identifiers: unitary_operator, unitary_operator_, unitaryoperator, unitaryoperatornode
          value='-'
          target ->
            IntNode()
              # identifiers: int, int_, intnode
              value='1'
      step ->
        IntNode()
          # identifiers: int, int_, intnode
          value='2'
    

Python __dict__ dump:

    {'_dict_keys': ['lower', 'upper', 'step'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type', 'has_two_colons'],
     'first_formatting': <NodeList [0, 'value', 1, 'value', 'first_formatting'], "" 68474080, on SliceNode 68472960>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'value', 'fourth_formatting'], "" 68376560, on SliceNode 68472960>,
     'has_two_colons': True,
     'init': False,
     'lower': <IntNode path=[0, 'value', 1, 'value', 'lower'], "1" 68473128, on SliceNode 68472960>,
     'on_attribute': 'value',
     'parent': <GetitemNode path=[0, 'value', 1], "[1:-1:2]" 68473912, on AtomtrailersNode 68476824>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 'second_formatting'], "" 68374992, on SliceNode 68472960>,
     'step': <IntNode path=[0, 'value', 1, 'value', 'step'], "2" 68375160, on SliceNode 68472960>,
     'third_formatting': <NodeList [0, 'value', 1, 'value', 'third_formatting'], "" 68375104, on SliceNode 68472960>,
     'type': 'slice',
     'upper': <UnitaryOperatorNode path=[0, 'value', 1, 'value', 'upper'], "-1" 68376224, on SliceNode 68472960>}
    
*/
class PROCKFPS_API PNSlice : public ProckNode {
public: 
    virtual char *Name() { return "Slice "; }
	ProckNode *Lower() { return GetAsNode("lower"); } 
	ProckNode *Upper() { return GetAsNode("upper"); } 
	ProckNode *Step() { return GetAsNode("step"); } 
	char *Type() { return GetAsString("type"); } 
	char *HasTwoColons() { return GetAsString("has_two_colons"); } 
};


/*
This is a special node that handle a particular way of writing a single string inpython by putting several strings one after the other while only separated byspaces or endls.

Equivalent python:

    'a' r'b' b'c'

RedBaron .help() text:

    SpaceNode()
      # identifiers: space, space_, spacenode
      value=' '
    StringChainNode()
      # identifiers: string_chain, string_chain_, stringchain, stringchainnode
      value ->
        * StringNode()
            # identifiers: string, string_, stringnode
            value="'a'"
        * RawStringNode()
            # identifiers: raw_string, raw_string_, rawstring, rawstringnode
            value="r'b'"
        * BinaryStringNode()
            # identifiers: binary_string, binary_string_, binarystring, binarystringnode
            value="b'c'"
    

Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['value'],
     '_str_keys': ['type'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "'a' r'b' b'c'" 68520480, on NoneType 1962241112>,
     'type': 'string_chain',
     'value': <NodeList [0, 'value'], "'a' r'b' b'c'" 68520200, on StringChainNode 68521264>}
    
*/
class PROCKFPS_API PNStringChain : public ProckNode {
public: 
    virtual char *Name() { return "StringChain "; }
	std::vector<ProckNode *> *Value() { return GetAsList("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing the ternary operator expression.

Equivalent python:

    a if b else c

RedBaron .help() text:

    TernaryOperatorNode()
      # identifiers: ternary_operator, ternary_operator_, ternaryoperator, ternaryoperatornode
      first ->
        NameNode()
          # identifiers: name, name_, namenode
          value='a'
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
      second ->
        NameNode()
          # identifiers: name, name_, namenode
          value='c'
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first': <NameNode path=[0, 'first'], "a" 68551792, on TernaryOperatorNode 68521824>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68551960, on TernaryOperatorNode 68521824>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 68551568, on TernaryOperatorNode 68521824>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 68520928, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 68552128, on TernaryOperatorNode 68521824>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68551624, on TernaryOperatorNode 68521824>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68551680, on TernaryOperatorNode 68521824>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 68552016, on TernaryOperatorNode 68521824>}
    
*/
class PROCKFPS_API PNTernaryOperator : public ProckNode {
public: 
    virtual char *Name() { return "TernaryOperator "; }
	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a try statement. This node is responsible for holding the:ref:`ExceptNode`, :ref:`FinallyNode` and :ref:`ElseNode`.

Equivalent python:

    try: pass\nexcept FooBar: pass\nexcept Exception: pass\nelse: pass\nfinally: pass\n

RedBaron .help() text:

    TryNode()
      # identifiers: try, try_, trynode
      else ->
        ElseNode()
          # identifiers: else, else_, elsenode
          value ->
            * PassNode()
                # identifiers: pass, pass_, passnode
      finally ->
        FinallyNode()
          # identifiers: finally, finally_, finallynode
          value ->
            * PassNode()
                # identifiers: pass, pass_, passnode
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
      excepts ->
        * ExceptNode()
            # identifiers: except, except_, exceptnode
            delimiter=''
            exception ->
              NameNode()
                # identifiers: name, name_, namenode
                value='FooBar'
            target ->
              None
            value ->
              * PassNode()
                  # identifiers: pass, pass_, passnode
        * ExceptNode()
            # identifiers: except, except_, exceptnode
            delimiter=''
            exception ->
              NameNode()
                # identifiers: name, name_, namenode
                value='Exception'
            target ->
              None
            value ->
              * PassNode()
                  # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first': <NameNode path=[0, 'first'], "a" 68551792, on TernaryOperatorNode 68521824>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68551960, on TernaryOperatorNode 68521824>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 68551568, on TernaryOperatorNode 68521824>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 68520928, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 68552128, on TernaryOperatorNode 68521824>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68551624, on TernaryOperatorNode 68521824>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68551680, on TernaryOperatorNode 68521824>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 68552016, on TernaryOperatorNode 68521824>}
    
*/
class PROCKFPS_API PNTry : public ProckNode {
public: 
    virtual char *Name() { return "Try "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing python sugar syntactic notation for tuple.

Equivalent python:

    (1, 2, 3)

RedBaron .help() text:

    TupleNode()
      # identifiers: tuple, tuple_, tuplenode
      with_parenthesis=True
      value ->
        * IntNode()
            # identifiers: int, int_, intnode
            value='1'
        * IntNode()
            # identifiers: int, int_, intnode
            value='2'
        * IntNode()
            # identifiers: int, int_, intnode
            value='3'
    

Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first': <NameNode path=[0, 'first'], "a" 68551792, on TernaryOperatorNode 68521824>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68551960, on TernaryOperatorNode 68521824>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 68551568, on TernaryOperatorNode 68521824>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 68520928, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 68552128, on TernaryOperatorNode 68521824>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68551624, on TernaryOperatorNode 68521824>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68551680, on TernaryOperatorNode 68521824>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 68552016, on TernaryOperatorNode 68521824>}
    
*/
class PROCKFPS_API PNTuple : public ProckNode {
public: 
    virtual char *Name() { return "Tuple "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a number sign modification operator like :file:`-2` or :file:`+42`.

Equivalent python:

    -1

RedBaron .help() text:

    UnitaryOperatorNode()
      # identifiers: unitary_operator, unitary_operator_, unitaryoperator, unitaryoperatornode
      value='-'
      target ->
        IntNode()
          # identifiers: int, int_, intnode
          value='1'
    

Python __dict__ dump:

    {'_dict_keys': ['target'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type', 'value'],
     'formatting': <NodeList [0, 'formatting'], "" 68627816, on UnitaryOperatorNode 68627536>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "-1" 68627256, on NoneType 1962241112>,
     'target': <IntNode path=[0, 'target'], "1" 68626136, on UnitaryOperatorNode 68627536>,
     'type': 'unitary_operator',
     'value': '-'}
    
*/
class PROCKFPS_API PNUnitaryOperator : public ProckNode {
public: 
    virtual char *Name() { return "UnitaryOperator "; }
	ProckNode *Target() { return GetAsNode("target"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Type() { return GetAsString("type"); } 
	char *Value() { return GetAsString("value"); } 
};


/*
A node representing a yield statement.

Equivalent python:

    yield 42

RedBaron .help() text:

    YieldNode()
      # identifiers: yield, yield_, yieldnode
      value ->
        IntNode()
          # identifiers: int, int_, intnode
          value='42'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 68594880, on YieldNode 68594768>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "yield 42" 68594936, on NoneType 1962241112>,
     'type': 'yield',
     'value': <IntNode path=[0, 'value'], "42" 68594096, on YieldNode 68594768>}
    
*/
class PROCKFPS_API PNYield : public ProckNode {
public: 
    virtual char *Name() { return "Yield "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a yield statement surrounded by parenthesis.

Equivalent python:

    (yield 42)

RedBaron .help() text:

    YieldAtomNode()
      # identifiers: yield_atom, yield_atom_, yieldatom, yieldatomnode
      value ->
        IntNode()
          # identifiers: int, int_, intnode
          value='42'
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting', 'second_formatting', 'third_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68521712, on YieldAtomNode 68441312>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 68405568, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68518072, on YieldAtomNode 68441312>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68521208, on YieldAtomNode 68441312>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 68518856, on YieldAtomNode 68441312>}
    
*/
class PROCKFPS_API PNYieldAtom : public ProckNode {
public: 
    virtual char *Name() { return "YieldAtom "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a while loop.

Equivalent python:

    while condition:\n    pass

RedBaron .help() text:

    WhileNode()
      # identifiers: while, while_, whilenode
      test ->
        NameNode()
          # identifiers: name, name_, namenode
          value='condition'
      else ->
        None
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting', 'second_formatting', 'third_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68521712, on YieldAtomNode 68441312>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 68405568, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68518072, on YieldAtomNode 68441312>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68521208, on YieldAtomNode 68441312>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 68518856, on YieldAtomNode 68441312>}
    
*/
class PROCKFPS_API PNWhile : public ProckNode {
public: 
    virtual char *Name() { return "While "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


/*
A node representing a while loop.

Equivalent python:

    with a as b: pass

RedBaron .help() text:

    WithContextItemNode()
      # identifiers: with_context_item, with_context_item_, withcontextitem, withcontextitemnode
      value ->
        NameNode()
          # identifiers: name, name_, namenode
          value='a'
      as ->
        NameNode()
          # identifiers: name, name_, namenode
          value='b'
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'as'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 68660304, on WithContextItemNode 68657896>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 68659688, on WithContextItemNode 68657896>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 68659520, on RedBaron 68657280>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 68659576, on WithContextItemNode 68657896>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 68659800, on WithContextItemNode 68657896>}
    
*/
class PROCKFPS_API PNWithContextItem : public ProckNode {
public: 
    virtual char *Name() { return "WithContextItem "; }
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *As() { return GetAsNode("as"); } 
	char *Type() { return GetAsString("type"); } 
};


/*
A node representing a with statement.

Equivalent python:

    with a as b, c: pass

RedBaron .help() text:

    WithNode()
      # identifiers: with, with_, withnode
      contexts ->
        * WithContextItemNode()
            # identifiers: with_context_item, with_context_item_, withcontextitem, withcontextitemnode
            value ->
              NameNode()
                # identifiers: name, name_, namenode
                value='a'
            as ->
              NameNode()
                # identifiers: name, name_, namenode
                value='b'
        * WithContextItemNode()
            # identifiers: with_context_item, with_context_item_, withcontextitem, withcontextitemnode
            value ->
              NameNode()
                # identifiers: name, name_, namenode
                value='c'
            as ->
              None
      value ->
        * PassNode()
            # identifiers: pass, pass_, passnode
    

Python __dict__ dump:

    {'_dict_keys': ['value', 'as'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 68660304, on WithContextItemNode 68657896>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 68659688, on WithContextItemNode 68657896>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 68659520, on RedBaron 68657280>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 68659576, on WithContextItemNode 68657896>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 68659800, on WithContextItemNode 68657896>}
    
*/
class PROCKFPS_API PNWith : public ProckNode {
public: 
    virtual char *Name() { return "With "; }
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


//
// Generalized, "primitive" nodes
class PROCKFPS_API PNBinaryRawString : public ProckNode {
public: 
    virtual char *Name() { return "BinaryRawString "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNBinaryString : public ProckNode {
public: 
    virtual char *Name() { return "BinaryString "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNBreak : public ProckNode {
public: 
    virtual char *Name() { return "Break "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNCodeBlock : public ProckNode {
public: 
    virtual char *Name() { return "CodeBlock "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNCommaProxyList : public ProckNode {
public: 
    virtual char *Name() { return "CommaProxyList "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNComment : public ProckNode {
public: 
    virtual char *Name() { return "Comment "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNComparisonOperator : public ProckNode {
public: 
    virtual char *Name() { return "ComparisonOperator "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNComplex : public ProckNode {
public: 
    virtual char *Name() { return "Complex "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNContinue : public ProckNode {
public: 
    virtual char *Name() { return "Continue "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDef : public ProckNode {
public: 
    virtual char *Name() { return "Def "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDictitem : public ProckNode {
public: 
    virtual char *Name() { return "Dictitem "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDotProxyList : public ProckNode {
public: 
    virtual char *Name() { return "DotProxyList "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDottedName : public ProckNode {
public: 
    virtual char *Name() { return "DottedName "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNEllipsis : public ProckNode {
public: 
    virtual char *Name() { return "Ellipsis "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNElseAttribute : public ProckNode {
public: 
    virtual char *Name() { return "ElseAttribute "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNEndl : public ProckNode {
public: 
    virtual char *Name() { return "Endl "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNFloatExponantComplex : public ProckNode {
public: 
    virtual char *Name() { return "FloatExponantComplex "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNFloatExponant : public ProckNode {
public: 
    virtual char *Name() { return "FloatExponant "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNFloat : public ProckNode {
public: 
    virtual char *Name() { return "Float "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNHexa : public ProckNode {
public: 
    virtual char *Name() { return "Hexa "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNIfElseBlockSibling : public ProckNode {
public: 
    virtual char *Name() { return "IfElseBlockSibling "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNInt : public ProckNode {
public: 
    virtual char *Name() { return "Int "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNLeftParenthesis : public ProckNode {
public: 
    virtual char *Name() { return "LeftParenthesis "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNLineProxyList : public ProckNode {
public: 
    virtual char *Name() { return "LineProxyList "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNLong : public ProckNode {
public: 
    virtual char *Name() { return "Long "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNName : public ProckNode {
public: 
    virtual char *Name() { return "Name "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNOcta : public ProckNode {
public: 
    virtual char *Name() { return "Octa "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNPass : public ProckNode {
public: 
    virtual char *Name() { return "Pass "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNRawString : public ProckNode {
public: 
    virtual char *Name() { return "RawString "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNRightParenthesis : public ProckNode {
public: 
    virtual char *Name() { return "RightParenthesis "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNSemicolon : public ProckNode {
public: 
    virtual char *Name() { return "Semicolon "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNSpace : public ProckNode {
public: 
    virtual char *Name() { return "Space "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNStar : public ProckNode {
public: 
    virtual char *Name() { return "Star "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNString : public ProckNode {
public: 
    virtual char *Name() { return "String "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNUnicodeRawString : public ProckNode {
public: 
    virtual char *Name() { return "UnicodeRawString "; }
    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNUnicodeString : public ProckNode {
public: 
    virtual char *Name() { return "UnicodeString "; }
    char *Value() { return GetAsString("value"); }
};
// End Generated Code
