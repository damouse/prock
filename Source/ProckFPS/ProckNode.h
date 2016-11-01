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
     'generators': <NodeList [0, 'value', 1, 'value', 0, 'generators'], " for y in z" 75493048, on ArgumentGeneratorComprehensionNode 75492376>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(x for y in z)" 75492656, on AtomtrailersNode 75497312>,
     'result': <NameNode path=[0, 'value', 1, 'value', 0, 'result'], "x" 75493160, on ArgumentGeneratorComprehensionNode 75492376>,
     'type': 'argument_generator_comprehension'}
    
*/
class PROCKFPS_API PNArgumentGeneratorComprehension : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 75568912, on AssertNode 75569080>,
     'init': False,
     'message': <NameNode path=[0, 'message'], "message" 75568856, on AssertNode 75569080>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "assert test, message" 75568744, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 75569136, on AssertNode 75569080>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 75569192, on AssertNode 75569080>,
     'type': 'assert',
     'value': <NameNode path=[0, 'value'], "test" 75569360, on AssertNode 75569080>}
    
*/
class PROCKFPS_API PNAssert : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 75491144, on AssignmentNode 75490864>,
     'init': False,
     'on_attribute': 'root',
     'operator': '',
     'parent': <RedBaron [], "a = b" 75491368, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 75491256, on AssignmentNode 75490864>,
     'target': <NameNode path=[0, 'target'], "a" 75490192, on AssignmentNode 75490864>,
     'type': 'assignment',
     'value': <NameNode path=[0, 'value'], "b" 75490696, on AssignmentNode 75490864>}
    
*/
class PROCKFPS_API PNAssignment : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 75489856, on AssociativeParenthesisNode 75490024>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 75568352, on AssociativeParenthesisNode 75490024>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 73432200, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 75492880, on AssociativeParenthesisNode 75490024>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 75490976, on AssociativeParenthesisNode 75490024>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 75489968, on AssociativeParenthesisNode 75490024>}
    
*/
class PROCKFPS_API PNAssociativeParenthesis : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 75489856, on AssociativeParenthesisNode 75490024>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 75568352, on AssociativeParenthesisNode 75490024>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 73432200, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 75492880, on AssociativeParenthesisNode 75490024>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 75490976, on AssociativeParenthesisNode 75490024>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 75489968, on AssociativeParenthesisNode 75490024>}
    
*/
class PROCKFPS_API PNAtomtrailers : public ProckNode {
public: 
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
     'parent': <RedBaron [], "0b10101" 78544568, on NoneType 1961454680>,
     'type': 'binary',
     'value': '0b10101'}
    
*/
class PROCKFPS_API PNBinary : public ProckNode {
public: 
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
     'first': <IntNode path=[0, 'first'], "1" 78578296, on BinaryOperatorNode 78544624>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 78578128, on BinaryOperatorNode 78544624>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "1 + 1" 78542328, on NoneType 1961454680>,
     'second': <IntNode path=[0, 'second'], "1" 78578576, on BinaryOperatorNode 78544624>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 78578632, on BinaryOperatorNode 78544624>,
     'type': 'binary_operator',
     'value': '+'}
    
*/
class PROCKFPS_API PNBinaryOperator : public ProckNode {
public: 
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
     'first': <NameNode path=[0, 'first'], "x" 78579920, on BooleanOperatorNode 78578800>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 78579416, on BooleanOperatorNode 78578800>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 78579528, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "y" 78544792, on BooleanOperatorNode 78578800>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 78544736, on BooleanOperatorNode 78578800>,
     'type': 'boolean_operator',
     'value': 'and'}
    
*/
class PROCKFPS_API PNBooleanOperator : public ProckNode {
public: 
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
     'first': <NameNode path=[0, 'first'], "x" 78579920, on BooleanOperatorNode 78578800>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 78579416, on BooleanOperatorNode 78578800>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 78579528, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "y" 78544792, on BooleanOperatorNode 78578800>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 78544736, on BooleanOperatorNode 78578800>,
     'type': 'boolean_operator',
     'value': 'and'}
    
*/
class PROCKFPS_API PNCall : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 78611568, on CallArgumentNode 78580760>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 78611064, on AtomtrailersNode 78577792>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 78611792, on CallArgumentNode 78580760>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 78611232, on CallArgumentNode 78580760>}
    
*/
class PROCKFPS_API PNCallArgument : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 78611568, on CallArgumentNode 78580760>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 78611064, on AtomtrailersNode 78577792>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 78611792, on CallArgumentNode 78580760>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 78611232, on CallArgumentNode 78580760>}
    
*/
class PROCKFPS_API PNClass : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 78644784, on CommaNode 78645456>,
     'init': False,
     'on_attribute': 'value',
     'parent': <ListNode path=[0], "[1, 2, 3]" 78645064, on RedBaron 78577904>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], " " 78645568, on CommaNode 78645456>,
     'type': 'comma'}
    
*/
class PROCKFPS_API PNComma : public ProckNode {
public: 
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
     'first': <IntNode path=[0, 'first'], "42" 78676432, on ComparisonNode 78645176>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 78676264, on ComparisonNode 78645176>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "42 > 30" 78647136, on NoneType 1961454680>,
     'second': <IntNode path=[0, 'second'], "30" 78676488, on ComparisonNode 78645176>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 78676040, on ComparisonNode 78645176>,
     'type': 'comparison',
     'value': <ComparisonOperatorNode path=[0, 'value'], ">" 78646688, on ComparisonNode 78645176>}
    
*/
class PROCKFPS_API PNComparison : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'first_formatting'], " " 78643608, on ComprehensionIfNode 78643888>,
     'init': False,
     'on_attribute': 'ifs',
     'parent': <ComprehensionLoopNode path=[0, 'generators', 0], " for x in x if c...n" 78646912, on ListComprehensionNode 78644560>,
     'second_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'second_formatting'], " " 78643720, on ComprehensionIfNode 78643888>,
     'type': 'comprehension_if',
     'value': <NameNode path=[0, 'generators', 0, 'ifs', 0, 'value'], "condition" 78644112, on ComprehensionIfNode 78643888>}
    
*/
class PROCKFPS_API PNComprehensionIf : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'generators', 0, 'first_formatting'], " " 78678560, on ComprehensionLoopNode 78646968>,
     'fourth_formatting': <NodeList [0, 'generators', 0, 'fourth_formatting'], " " 78679344, on ComprehensionLoopNode 78646968>,
     'ifs': <NodeList [0, 'generators', 0, 'ifs'], "" 78679512, on ComprehensionLoopNode 78646968>,
     'init': False,
     'iterator': <NameNode path=[0, 'generators', 0, 'iterator'], "y" 78676152, on ComprehensionLoopNode 78646968>,
     'on_attribute': 'generators',
     'parent': <ListComprehensionNode path=[0], "[x for y in z]" 78544176, on RedBaron 78646576>,
     'second_formatting': <NodeList [0, 'generators', 0, 'second_formatting'], " " 78678672, on ComprehensionLoopNode 78646968>,
     'target': <NameNode path=[0, 'generators', 0, 'target'], "z" 78679456, on ComprehensionLoopNode 78646968>,
     'third_formatting': <NodeList [0, 'generators', 0, 'third_formatting'], " " 78679232, on ComprehensionLoopNode 78646968>,
     'type': 'comprehension_loop'}
    
*/
class PROCKFPS_API PNComprehensionLoop : public ProckNode {
public: 
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 78716432, on DecoratorNode 78716712>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 78716768, on RedBaron 78679008>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 78716600, on DecoratorNode 78716712>}
    
*/
class PROCKFPS_API PNDecorator : public ProckNode {
public: 
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 78716432, on DecoratorNode 78716712>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 78716768, on RedBaron 78679008>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 78716600, on DecoratorNode 78716712>}
    
*/
class PROCKFPS_API PNDefArgument : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'formatting'], " " 78644448, on DelNode 79040408>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "del stuff" 78679960, on NoneType 1961454680>,
     'type': 'del',
     'value': <NameNode path=[0, 'value'], "stuff" 79069256, on DelNode 79040408>}
    
*/
class PROCKFPS_API PNDel : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 79071944, on DictArgumentNode 79070040>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 79071552, on AtomtrailersNode 79069592>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 79071832, on DictArgumentNode 79070040>}
    
*/
class PROCKFPS_API PNDictArgument : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 79071944, on DictArgumentNode 79070040>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 79071552, on AtomtrailersNode 79069592>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 79071832, on DictArgumentNode 79070040>}
    
*/
class PROCKFPS_API PNDict : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79107128, on DictComprehensionNode 78713968>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79108416, on DictComprehensionNode 78713968>,
     'generators': <NodeList [0, 'generators'], " for c in d" 79106960, on DictComprehensionNode 78713968>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 79039512, on NoneType 1961454680>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 79107688, on DictComprehensionNode 78713968>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79107464, on DictComprehensionNode 78713968>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79107744, on DictComprehensionNode 78713968>,
     'type': 'dict_comprehension'}
    
*/
class PROCKFPS_API PNDictComprehension : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79107128, on DictComprehensionNode 78713968>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79108416, on DictComprehensionNode 78713968>,
     'generators': <NodeList [0, 'generators'], " for c in d" 79106960, on DictComprehensionNode 78713968>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 79039512, on NoneType 1961454680>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 79107688, on DictComprehensionNode 78713968>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79107464, on DictComprehensionNode 78713968>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79107744, on DictComprehensionNode 78713968>,
     'type': 'dict_comprehension'}
    
*/
class PROCKFPS_API PNDottedAsName : public ProckNode {
public: 
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
     'parent': <AtomtrailersNode path=[0], "a.b" 79106512, on RedBaron 78713800>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNDot : public ProckNode {
public: 
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
     'parent': <AtomtrailersNode path=[0], "a.b" 79106512, on RedBaron 78713800>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNElif : public ProckNode {
public: 
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
     'parent': <AtomtrailersNode path=[0], "a.b" 79106512, on RedBaron 78713800>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNElse : public ProckNode {
public: 
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
     'parent': <AtomtrailersNode path=[0], "a.b" 79106512, on RedBaron 78713800>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNExcept : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79073232, on ExecNode 79070264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79070768, on ExecNode 79070264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79070320, on ExecNode 79070264>,
     'globals': <NameNode path=[0, 'globals'], "a" 79070712, on ExecNode 79070264>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 79069928, on ExecNode 79070264>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 79069648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79070824, on ExecNode 79070264>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79071104, on ExecNode 79070264>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 79070992, on ExecNode 79070264>}
    
*/
class PROCKFPS_API PNExec : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79073232, on ExecNode 79070264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79070768, on ExecNode 79070264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79070320, on ExecNode 79070264>,
     'globals': <NameNode path=[0, 'globals'], "a" 79070712, on ExecNode 79070264>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 79069928, on ExecNode 79070264>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 79069648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79070824, on ExecNode 79070264>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79071104, on ExecNode 79070264>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 79070992, on ExecNode 79070264>}
    
*/
class PROCKFPS_API PNFinally : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79073232, on ExecNode 79070264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79070768, on ExecNode 79070264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79070320, on ExecNode 79070264>,
     'globals': <NameNode path=[0, 'globals'], "a" 79070712, on ExecNode 79070264>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 79069928, on ExecNode 79070264>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 79069648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79070824, on ExecNode 79070264>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79071104, on ExecNode 79070264>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 79070992, on ExecNode 79070264>}
    
*/
class PROCKFPS_API PNFor : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79073232, on ExecNode 79070264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79070768, on ExecNode 79070264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79070320, on ExecNode 79070264>,
     'globals': <NameNode path=[0, 'globals'], "a" 79070712, on ExecNode 79070264>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 79069928, on ExecNode 79070264>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 79069648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79070824, on ExecNode 79070264>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79071104, on ExecNode 79070264>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 79070992, on ExecNode 79070264>}
    
*/
class PROCKFPS_API PNFromImport : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79073232, on ExecNode 79070264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79070768, on ExecNode 79070264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79070320, on ExecNode 79070264>,
     'globals': <NameNode path=[0, 'globals'], "a" 79070712, on ExecNode 79070264>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 79069928, on ExecNode 79070264>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 79069648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79070824, on ExecNode 79070264>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79071104, on ExecNode 79070264>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 79070992, on ExecNode 79070264>}
    
*/
class PROCKFPS_API PNFuncdef : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79251496, on GeneratorComprehensionNode 79251384>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79252616, on GeneratorComprehensionNode 79251384>,
     'generators': <NodeList [0, 'generators'], " for y in z" 79251664, on GeneratorComprehensionNode 79251384>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(x for y in z)" 79069760, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 79251720, on GeneratorComprehensionNode 79251384>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79252280, on GeneratorComprehensionNode 79251384>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79251832, on GeneratorComprehensionNode 79251384>,
     'type': 'generator_comprehension'}
    
*/
class PROCKFPS_API PNGeneratorComprehension : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 79565600, on GetitemNode 79565096>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 79565992, on GetitemNode 79565096>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 79252896, on RedBaron 79252168>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 79565376, on GetitemNode 79565096>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 79565936, on GetitemNode 79565096>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 79565432, on GetitemNode 79565096>}
    
*/
class PROCKFPS_API PNGetitem : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 79565600, on GetitemNode 79565096>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 79565992, on GetitemNode 79565096>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 79252896, on RedBaron 79252168>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 79565376, on GetitemNode 79565096>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 79565936, on GetitemNode 79565096>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 79565432, on GetitemNode 79565096>}
    
*/
class PROCKFPS_API PNGlobal : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 79565600, on GetitemNode 79565096>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 79565992, on GetitemNode 79565096>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 79252896, on RedBaron 79252168>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 79565376, on GetitemNode 79565096>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 79565936, on GetitemNode 79565096>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 79565432, on GetitemNode 79565096>}
    
*/
class PROCKFPS_API PNIf : public ProckNode {
public: 
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 79565040, on NoneType 1961454680>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 79607456, on IfelseblockNode 79250656>}
    
*/
class PROCKFPS_API PNIfelseblock : public ProckNode {
public: 
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 79565040, on NoneType 1961454680>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 79607456, on IfelseblockNode 79250656>}
    
*/
class PROCKFPS_API PNImport : public ProckNode {
public: 
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
     'arguments': <CommaProxyList [0, 'arguments'], "x" 79568288, on LambdaNode 79568176>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79566944, on LambdaNode 79568176>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "lambda x: y" 79566552, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79223776, on LambdaNode 79568176>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79224224, on LambdaNode 79568176>,
     'type': 'lambda',
     'value': <NameNode path=[0, 'value'], "y" 79223944, on LambdaNode 79568176>}
    
*/
class PROCKFPS_API PNLambda : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'arguments', 0, 'formatting'], "" 79642016, on ListArgumentNode 79638600>,
     'init': False,
     'on_attribute': 'arguments',
     'parent': <DefNode path=[0], "def a(*b): pass\n" 79641232, on RedBaron 79567056>,
     'type': 'list_argument',
     'value': <NameNode path=[0, 'arguments', 0, 'value'], "b" 79642072, on ListArgumentNode 79638600>}
    
*/
class PROCKFPS_API PNListArgument : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79674056, on ListComprehensionNode 79672096>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79674392, on ListComprehensionNode 79672096>,
     'generators': <NodeList [0, 'generators'], " for y in z" 79673328, on ListComprehensionNode 79672096>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 79641568, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 79674112, on ListComprehensionNode 79672096>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79673552, on ListComprehensionNode 79672096>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79673496, on ListComprehensionNode 79672096>,
     'type': 'list_comprehension'}
    
*/
class PROCKFPS_API PNListComprehension : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79674056, on ListComprehensionNode 79672096>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79674392, on ListComprehensionNode 79672096>,
     'generators': <NodeList [0, 'generators'], " for y in z" 79673328, on ListComprehensionNode 79672096>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 79641568, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 79674112, on ListComprehensionNode 79672096>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79673552, on ListComprehensionNode 79672096>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79673496, on ListComprehensionNode 79672096>,
     'type': 'list_comprehension'}
    
*/
class PROCKFPS_API PNList : public ProckNode {
public: 
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
     'parent': <FromImportNode path=[0], "from x import a as d" 79672656, on RedBaron 79640672>,
     'second_formatting': [' '],
     'target': 'd',
     'type': 'name_as_name',
     'value': 'a'}
    
*/
class PROCKFPS_API PNNameAsName : public ProckNode {
public: 
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
     'parent': <FromImportNode path=[0], "from x import a as d" 79672656, on RedBaron 79640672>,
     'second_formatting': [' '],
     'target': 'd',
     'type': 'name_as_name',
     'value': 'a'}
    
*/
class PROCKFPS_API PNPrint : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79711928, on RaiseNode 79709576>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79712152, on RaiseNode 79709576>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79710528, on RaiseNode 79709576>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 79711816, on RaiseNode 79709576>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 79712096, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79711648, on RaiseNode 79709576>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79710640, on RaiseNode 79709576>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 79712040, on RaiseNode 79709576>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 79710416, on RaiseNode 79709576>}
    
*/
class PROCKFPS_API PNRaise : public ProckNode {
public: 
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 79711928, on RaiseNode 79709576>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79712152, on RaiseNode 79709576>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79710528, on RaiseNode 79709576>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 79711816, on RaiseNode 79709576>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 79712096, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79711648, on RaiseNode 79709576>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79710640, on RaiseNode 79709576>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 79712040, on RaiseNode 79709576>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 79710416, on RaiseNode 79709576>}
    
*/
class PROCKFPS_API PNRepr : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'formatting'], " " 79672992, on ReturnNode 79605832>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 79673048, on NoneType 1961454680>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 79564984, on ReturnNode 79605832>}
    
*/
class PROCKFPS_API PNReturn : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'formatting'], " " 79672992, on ReturnNode 79605832>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 79673048, on NoneType 1961454680>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 79564984, on ReturnNode 79605832>}
    
*/
class PROCKFPS_API PNSet : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79757264, on SetComprehensionNode 79755752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 79782744, on SetComprehensionNode 79755752>,
     'generators': <NodeList [0, 'generators'], " for y in z" 79757208, on SetComprehensionNode 79755752>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{x for y in z}" 79756872, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 79754744, on SetComprehensionNode 79755752>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 79757152, on SetComprehensionNode 79755752>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79782240, on SetComprehensionNode 79755752>,
     'type': 'set_comprehension'}
    
*/
class PROCKFPS_API PNSetComprehension : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 'first_formatting'], "" 79566048, on SliceNode 79567168>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'value', 'fourth_formatting'], "" 79673160, on SliceNode 79567168>,
     'has_two_colons': True,
     'init': False,
     'lower': <IntNode path=[0, 'value', 1, 'value', 'lower'], "1" 79564872, on SliceNode 79567168>,
     'on_attribute': 'value',
     'parent': <GetitemNode path=[0, 'value', 1], "[1:-1:2]" 79753400, on AtomtrailersNode 79756928>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 'second_formatting'], "" 79566160, on SliceNode 79567168>,
     'step': <IntNode path=[0, 'value', 1, 'value', 'step'], "2" 79606280, on SliceNode 79567168>,
     'third_formatting': <NodeList [0, 'value', 1, 'value', 'third_formatting'], "" 79565880, on SliceNode 79567168>,
     'type': 'slice',
     'upper': <UnitaryOperatorNode path=[0, 'value', 1, 'value', 'upper'], "-1" 79673664, on SliceNode 79567168>}
    
*/
class PROCKFPS_API PNSlice : public ProckNode {
public: 
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
     'parent': <RedBaron [], "'a' r'b' b'c'" 79710752, on NoneType 1961454680>,
     'type': 'string_chain',
     'value': <NodeList [0, 'value'], "'a' r'b' b'c'" 79783584, on StringChainNode 79784760>}
    
*/
class PROCKFPS_API PNStringChain : public ProckNode {
public: 
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
     'first': <NameNode path=[0, 'first'], "a" 79823480, on TernaryOperatorNode 79785320>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79823648, on TernaryOperatorNode 79785320>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 79823256, on TernaryOperatorNode 79785320>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 79784424, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "c" 79823816, on TernaryOperatorNode 79785320>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79823312, on TernaryOperatorNode 79785320>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79823368, on TernaryOperatorNode 79785320>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 79823704, on TernaryOperatorNode 79785320>}
    
*/
class PROCKFPS_API PNTernaryOperator : public ProckNode {
public: 
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
     'first': <NameNode path=[0, 'first'], "a" 79823480, on TernaryOperatorNode 79785320>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79823648, on TernaryOperatorNode 79785320>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 79823256, on TernaryOperatorNode 79785320>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 79784424, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "c" 79823816, on TernaryOperatorNode 79785320>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79823312, on TernaryOperatorNode 79785320>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79823368, on TernaryOperatorNode 79785320>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 79823704, on TernaryOperatorNode 79785320>}
    
*/
class PROCKFPS_API PNTry : public ProckNode {
public: 
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
     'first': <NameNode path=[0, 'first'], "a" 79823480, on TernaryOperatorNode 79785320>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 79823648, on TernaryOperatorNode 79785320>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 79823256, on TernaryOperatorNode 79785320>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 79784424, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "c" 79823816, on TernaryOperatorNode 79785320>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79823312, on TernaryOperatorNode 79785320>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 79823368, on TernaryOperatorNode 79785320>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 79823704, on TernaryOperatorNode 79785320>}
    
*/
class PROCKFPS_API PNTuple : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'formatting'], "" 79895408, on UnitaryOperatorNode 79895128>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "-1" 79894848, on NoneType 1961454680>,
     'target': <IntNode path=[0, 'target'], "1" 79893728, on UnitaryOperatorNode 79895128>,
     'type': 'unitary_operator',
     'value': '-'}
    
*/
class PROCKFPS_API PNUnitaryOperator : public ProckNode {
public: 
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
     'formatting': <NodeList [0, 'formatting'], " " 79867352, on YieldNode 79867128>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "yield 42" 79867800, on NoneType 1961454680>,
     'type': 'yield',
     'value': <IntNode path=[0, 'value'], "42" 79867184, on YieldNode 79867128>}
    
*/
class PROCKFPS_API PNYield : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79606168, on YieldAtomNode 79826840>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 78578072, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79864944, on YieldAtomNode 79826840>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79867408, on YieldAtomNode 79826840>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 79864888, on YieldAtomNode 79826840>}
    
*/
class PROCKFPS_API PNYieldAtom : public ProckNode {
public: 
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 79606168, on YieldAtomNode 79826840>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 78578072, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 79864944, on YieldAtomNode 79826840>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 79867408, on YieldAtomNode 79826840>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 79864888, on YieldAtomNode 79826840>}
    
*/
class PROCKFPS_API PNWhile : public ProckNode {
public: 
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 79940184, on WithContextItemNode 79937720>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 79939568, on WithContextItemNode 79937720>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 79939400, on RedBaron 79895632>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 79939456, on WithContextItemNode 79937720>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 79939680, on WithContextItemNode 79937720>}
    
*/
class PROCKFPS_API PNWithContextItem : public ProckNode {
public: 
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 79940184, on WithContextItemNode 79937720>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 79939568, on WithContextItemNode 79937720>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 79939400, on RedBaron 79895632>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 79939456, on WithContextItemNode 79937720>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 79939680, on WithContextItemNode 79937720>}
    
*/
class PROCKFPS_API PNWith : public ProckNode {
public: 
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};
// End Generated Code
