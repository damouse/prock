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
     'generators': <NodeList [0, 'value', 1, 'value', 0, 'generators'], " for y in z" 76901456, on ArgumentGeneratorComprehensionNode 76901792>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(x for y in z)" 76902072, on AtomtrailersNode 76898992>,
     'result': <NameNode path=[0, 'value', 1, 'value', 0, 'result'], "x" 76901960, on ArgumentGeneratorComprehensionNode 76901792>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 76970136, on AssertNode 76970304>,
     'init': False,
     'message': <NameNode path=[0, 'message'], "message" 76970080, on AssertNode 76970304>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "assert test, message" 76969968, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 76970360, on AssertNode 76970304>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 76970416, on AssertNode 76970304>,
     'type': 'assert',
     'value': <NameNode path=[0, 'value'], "test" 76970584, on AssertNode 76970304>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 76900560, on AssignmentNode 76900280>,
     'init': False,
     'on_attribute': 'root',
     'operator': '',
     'parent': <RedBaron [], "a = b" 76900784, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 76900672, on AssignmentNode 76900280>,
     'target': <NameNode path=[0, 'target'], "a" 76898600, on AssignmentNode 76900280>,
     'type': 'assignment',
     'value': <NameNode path=[0, 'value'], "b" 76900112, on AssignmentNode 76900280>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 76899328, on AssociativeParenthesisNode 76899496>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 76969576, on AssociativeParenthesisNode 76899496>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 76889056, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 76902296, on AssociativeParenthesisNode 76899496>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 76900392, on AssociativeParenthesisNode 76899496>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 76899440, on AssociativeParenthesisNode 76899496>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 76899328, on AssociativeParenthesisNode 76899496>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 76969576, on AssociativeParenthesisNode 76899496>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 76889056, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 76902296, on AssociativeParenthesisNode 76899496>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 76900392, on AssociativeParenthesisNode 76899496>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 76899440, on AssociativeParenthesisNode 76899496>}
    
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
     'parent': <RedBaron [], "0b10101" 77139920, on NoneType 1961454680>,
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
     'first': <IntNode path=[0, 'first'], "1" 77173760, on BinaryOperatorNode 77172920>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 77173592, on BinaryOperatorNode 77172920>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "1 + 1" 77137792, on NoneType 1961454680>,
     'second': <IntNode path=[0, 'second'], "1" 77174040, on BinaryOperatorNode 77172920>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 77174096, on BinaryOperatorNode 77172920>,
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
     'first': <NameNode path=[0, 'first'], "x" 77175384, on BooleanOperatorNode 77174264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 77174880, on BooleanOperatorNode 77174264>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 77174992, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "y" 77139640, on BooleanOperatorNode 77174264>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 77139864, on BooleanOperatorNode 77174264>,
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
     'first': <NameNode path=[0, 'first'], "x" 77175384, on BooleanOperatorNode 77174264>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 77174880, on BooleanOperatorNode 77174264>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 77174992, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "y" 77139640, on BooleanOperatorNode 77174264>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 77139864, on BooleanOperatorNode 77174264>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 77207032, on CallArgumentNode 77176224>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 77206528, on AtomtrailersNode 77172808>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 77207256, on CallArgumentNode 77176224>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 77206696, on CallArgumentNode 77176224>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 77207032, on CallArgumentNode 77176224>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 77206528, on AtomtrailersNode 77172808>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 77207256, on CallArgumentNode 77176224>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 77206696, on CallArgumentNode 77176224>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 77244344, on CommaNode 77245016>,
     'init': False,
     'on_attribute': 'value',
     'parent': <ListNode path=[0], "[1, 2, 3]" 77244624, on RedBaron 77175776>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], " " 77245128, on CommaNode 77245016>,
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
     'first': <IntNode path=[0, 'first'], "42" 77271840, on ComparisonNode 77271392>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 77271616, on ComparisonNode 77271392>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "42 > 30" 77244736, on NoneType 1961454680>,
     'second': <IntNode path=[0, 'second'], "30" 77271952, on ComparisonNode 77271392>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 77271560, on ComparisonNode 77271392>,
     'type': 'comparison',
     'value': <ComparisonOperatorNode path=[0, 'value'], ">" 77246248, on ComparisonNode 77271392>}
    
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
     'first_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'first_formatting'], " " 77243672, on ComprehensionIfNode 77243280>,
     'init': False,
     'on_attribute': 'ifs',
     'parent': <ComprehensionLoopNode path=[0, 'generators', 0], " for x in x if c...n" 77245912, on ListComprehensionNode 77243784>,
     'second_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'second_formatting'], " " 77244288, on ComprehensionIfNode 77243280>,
     'type': 'comprehension_if',
     'value': <NameNode path=[0, 'generators', 0, 'ifs', 0, 'value'], "condition" 77137008, on ComprehensionIfNode 77243280>}
    
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
     'first_formatting': <NodeList [0, 'generators', 0, 'first_formatting'], " " 77274192, on ComprehensionLoopNode 77172864>,
     'fourth_formatting': <NodeList [0, 'generators', 0, 'fourth_formatting'], " " 77274808, on ComprehensionLoopNode 77172864>,
     'ifs': <NodeList [0, 'generators', 0, 'ifs'], "" 77274976, on ComprehensionLoopNode 77172864>,
     'init': False,
     'iterator': <NameNode path=[0, 'generators', 0, 'iterator'], "y" 77271280, on ComprehensionLoopNode 77172864>,
     'on_attribute': 'generators',
     'parent': <ListComprehensionNode path=[0], "[x for y in z]" 77136392, on RedBaron 77246360>,
     'second_formatting': <NodeList [0, 'generators', 0, 'second_formatting'], " " 77274304, on ComprehensionLoopNode 77172864>,
     'target': <NameNode path=[0, 'generators', 0, 'target'], "z" 77274920, on ComprehensionLoopNode 77172864>,
     'third_formatting': <NodeList [0, 'generators', 0, 'third_formatting'], " " 77274696, on ComprehensionLoopNode 77172864>,
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 80780816, on DecoratorNode 80781208>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 80780928, on RedBaron 77274080>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 80781264, on DecoratorNode 80781208>}
    
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 80780816, on DecoratorNode 80781208>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 80780928, on RedBaron 77274080>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 80781264, on DecoratorNode 80781208>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 80847368, on DelNode 80847536>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "del stuff" 77175440, on NoneType 1961454680>,
     'type': 'del',
     'value': <NameNode path=[0, 'value'], "stuff" 80847424, on DelNode 80847536>}
    
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 80850000, on DictArgumentNode 80848096>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 80849608, on AtomtrailersNode 80847648>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 80849888, on DictArgumentNode 80848096>}
    
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 80850000, on DictArgumentNode 80848096>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 80849608, on AtomtrailersNode 80847648>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 80849888, on DictArgumentNode 80848096>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 80885184, on DictComprehensionNode 80780592>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80886472, on DictComprehensionNode 80780592>,
     'generators': <NodeList [0, 'generators'], " for c in d" 80885016, on DictComprehensionNode 80780592>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 80780984, on NoneType 1961454680>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 80885744, on DictComprehensionNode 80780592>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 80885520, on DictComprehensionNode 80780592>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 80885800, on DictComprehensionNode 80780592>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 80885184, on DictComprehensionNode 80780592>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80886472, on DictComprehensionNode 80780592>,
     'generators': <NodeList [0, 'generators'], " for c in d" 80885016, on DictComprehensionNode 80780592>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 80780984, on NoneType 1961454680>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 80885744, on DictComprehensionNode 80780592>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 80885520, on DictComprehensionNode 80780592>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 80885800, on DictComprehensionNode 80780592>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 80884288, on RedBaron 80779080>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 80884288, on RedBaron 80779080>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 80884288, on RedBaron 80779080>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 80884288, on RedBaron 80779080>,
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 80884120, on ExecNode 80849832>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 80886864, on ExecNode 80849832>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80884848, on ExecNode 80849832>,
     'globals': <NameNode path=[0, 'globals'], "a" 80883952, on ExecNode 80849832>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 80883896, on ExecNode 80849832>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 80848320, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 80887648, on ExecNode 80849832>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 80884232, on ExecNode 80849832>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 80884064, on ExecNode 80849832>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 80884120, on ExecNode 80849832>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 80886864, on ExecNode 80849832>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80884848, on ExecNode 80849832>,
     'globals': <NameNode path=[0, 'globals'], "a" 80883952, on ExecNode 80849832>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 80883896, on ExecNode 80849832>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 80848320, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 80887648, on ExecNode 80849832>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 80884232, on ExecNode 80849832>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 80884064, on ExecNode 80849832>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 80884120, on ExecNode 80849832>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 80886864, on ExecNode 80849832>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80884848, on ExecNode 80849832>,
     'globals': <NameNode path=[0, 'globals'], "a" 80883952, on ExecNode 80849832>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 80883896, on ExecNode 80849832>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 80848320, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 80887648, on ExecNode 80849832>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 80884232, on ExecNode 80849832>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 80884064, on ExecNode 80849832>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 80884120, on ExecNode 80849832>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 80886864, on ExecNode 80849832>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80884848, on ExecNode 80849832>,
     'globals': <NameNode path=[0, 'globals'], "a" 80883952, on ExecNode 80849832>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 80883896, on ExecNode 80849832>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 80848320, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 80887648, on ExecNode 80849832>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 80884232, on ExecNode 80849832>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 80884064, on ExecNode 80849832>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 80884120, on ExecNode 80849832>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 80886864, on ExecNode 80849832>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 80884848, on ExecNode 80849832>,
     'globals': <NameNode path=[0, 'globals'], "a" 80883952, on ExecNode 80849832>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 80883896, on ExecNode 80849832>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 80848320, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 80887648, on ExecNode 80849832>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 80884232, on ExecNode 80849832>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 80884064, on ExecNode 80849832>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81025456, on GeneratorComprehensionNode 81025344>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81026576, on GeneratorComprehensionNode 81025344>,
     'generators': <NodeList [0, 'generators'], " for y in z" 81025624, on GeneratorComprehensionNode 81025344>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(x for y in z)" 80780760, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 81025680, on GeneratorComprehensionNode 81025344>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81026240, on GeneratorComprehensionNode 81025344>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81025792, on GeneratorComprehensionNode 81025344>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 81339560, on GetitemNode 81339056>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 81339952, on GetitemNode 81339056>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 81026856, on RedBaron 81026128>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 81339336, on GetitemNode 81339056>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 81339896, on GetitemNode 81339056>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 81339392, on GetitemNode 81339056>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 81339560, on GetitemNode 81339056>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 81339952, on GetitemNode 81339056>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 81026856, on RedBaron 81026128>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 81339336, on GetitemNode 81339056>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 81339896, on GetitemNode 81339056>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 81339392, on GetitemNode 81339056>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 81339560, on GetitemNode 81339056>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 81339952, on GetitemNode 81339056>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 81026856, on RedBaron 81026128>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 81339336, on GetitemNode 81339056>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 81339896, on GetitemNode 81339056>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 81339392, on GetitemNode 81339056>}
    
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 81338944, on NoneType 1961454680>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 81373224, on IfelseblockNode 81371376>}
    
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 81338944, on NoneType 1961454680>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 81373224, on IfelseblockNode 81371376>}
    
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
     'arguments': <CommaProxyList [0, 'arguments'], "x" 81023384, on LambdaNode 81024728>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81024672, on LambdaNode 81024728>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "lambda x: y" 77209496, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81026968, on LambdaNode 81024728>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81023216, on LambdaNode 81024728>,
     'type': 'lambda',
     'value': <NameNode path=[0, 'value'], "y" 81026744, on LambdaNode 81024728>}
    
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
     'formatting': <NodeList [0, 'arguments', 0, 'formatting'], "" 81415976, on ListArgumentNode 81413792>,
     'init': False,
     'on_attribute': 'arguments',
     'parent': <DefNode path=[0], "def a(*b): pass\n" 81415192, on RedBaron 81025008>,
     'type': 'list_argument',
     'value': <NameNode path=[0, 'arguments', 0, 'value'], "b" 81416032, on ListArgumentNode 81413792>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81443920, on ListComprehensionNode 81441960>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81444256, on ListComprehensionNode 81441960>,
     'generators': <NodeList [0, 'generators'], " for y in z" 81443192, on ListComprehensionNode 81441960>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 81415528, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 81443976, on ListComprehensionNode 81441960>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81443416, on ListComprehensionNode 81441960>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81443360, on ListComprehensionNode 81441960>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81443920, on ListComprehensionNode 81441960>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81444256, on ListComprehensionNode 81441960>,
     'generators': <NodeList [0, 'generators'], " for y in z" 81443192, on ListComprehensionNode 81441960>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 81415528, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 81443976, on ListComprehensionNode 81441960>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81443416, on ListComprehensionNode 81441960>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81443360, on ListComprehensionNode 81441960>,
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
     'parent': <FromImportNode path=[0], "from x import a as d" 80919576, on RedBaron 77272344>,
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
     'parent': <FromImportNode path=[0], "from x import a as d" 80919576, on RedBaron 77272344>,
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 81480112, on RaiseNode 81480000>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81481568, on RaiseNode 81480000>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81480056, on RaiseNode 81480000>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 81479888, on RaiseNode 81480000>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 81479552, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81481344, on RaiseNode 81480000>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81481456, on RaiseNode 81480000>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 81477928, on RaiseNode 81480000>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 81480280, on RaiseNode 81480000>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 81480112, on RaiseNode 81480000>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81481568, on RaiseNode 81480000>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81480056, on RaiseNode 81480000>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 81479888, on RaiseNode 81480000>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 81479552, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81481344, on RaiseNode 81480000>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81481456, on RaiseNode 81480000>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 81477928, on RaiseNode 81480000>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 81480280, on RaiseNode 81480000>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 81413008, on ReturnNode 81414632>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 77274360, on NoneType 1961454680>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 81413512, on ReturnNode 81414632>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 81413008, on ReturnNode 81414632>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 77274360, on NoneType 1961454680>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 81413512, on ReturnNode 81414632>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81556368, on SetComprehensionNode 81529712>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81556704, on SetComprehensionNode 81529712>,
     'generators': <NodeList [0, 'generators'], " for y in z" 81555640, on SetComprehensionNode 81529712>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{x for y in z}" 81530832, on NoneType 1961454680>,
     'result': <NameNode path=[0, 'result'], "x" 81556424, on SetComprehensionNode 81529712>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81555864, on SetComprehensionNode 81529712>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81555808, on SetComprehensionNode 81529712>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 'first_formatting'], "" 81414800, on SliceNode 81527640>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'value', 'fourth_formatting'], "" 81413400, on SliceNode 81527640>,
     'has_two_colons': True,
     'init': False,
     'lower': <IntNode path=[0, 'value', 1, 'value', 'lower'], "1" 81527808, on SliceNode 81527640>,
     'on_attribute': 'value',
     'parent': <GetitemNode path=[0, 'value', 1], "[1:-1:2]" 81527192, on AtomtrailersNode 81443024>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 'second_formatting'], "" 81413904, on SliceNode 81527640>,
     'step': <IntNode path=[0, 'value', 1, 'value', 'step'], "2" 81413064, on SliceNode 81527640>,
     'third_formatting': <NodeList [0, 'value', 1, 'value', 'third_formatting'], "" 81414016, on SliceNode 81527640>,
     'type': 'slice',
     'upper': <UnitaryOperatorNode path=[0, 'value', 1, 'value', 'upper'], "-1" 81413120, on SliceNode 81527640>}
    
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
     'parent': <RedBaron [], "'a' r'b' b'c'" 81557936, on NoneType 1961454680>,
     'type': 'string_chain',
     'value': <NodeList [0, 'value'], "'a' r'b' b'c'" 81557600, on StringChainNode 81558720>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 81589248, on TernaryOperatorNode 81559280>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81589416, on TernaryOperatorNode 81559280>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 81589024, on TernaryOperatorNode 81559280>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 81558384, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "c" 81589584, on TernaryOperatorNode 81559280>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81589080, on TernaryOperatorNode 81559280>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81589136, on TernaryOperatorNode 81559280>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 81589472, on TernaryOperatorNode 81559280>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 81589248, on TernaryOperatorNode 81559280>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81589416, on TernaryOperatorNode 81559280>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 81589024, on TernaryOperatorNode 81559280>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 81558384, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "c" 81589584, on TernaryOperatorNode 81559280>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81589080, on TernaryOperatorNode 81559280>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81589136, on TernaryOperatorNode 81559280>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 81589472, on TernaryOperatorNode 81559280>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 81589248, on TernaryOperatorNode 81559280>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81589416, on TernaryOperatorNode 81559280>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 81589024, on TernaryOperatorNode 81559280>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 81558384, on NoneType 1961454680>,
     'second': <NameNode path=[0, 'second'], "c" 81589584, on TernaryOperatorNode 81559280>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81589080, on TernaryOperatorNode 81559280>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81589136, on TernaryOperatorNode 81559280>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 81589472, on TernaryOperatorNode 81559280>}
    
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
     'formatting': <NodeList [0, 'formatting'], "" 81665272, on UnitaryOperatorNode 81664992>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "-1" 81664712, on NoneType 1961454680>,
     'target': <IntNode path=[0, 'target'], "1" 81663592, on UnitaryOperatorNode 81664992>,
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
     'formatting': <NodeList [0, 'formatting'], " " 81632392, on YieldNode 81632840>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "yield 42" 81632672, on NoneType 1961454680>,
     'type': 'yield',
     'value': <IntNode path=[0, 'value'], "42" 81632336, on YieldNode 81632840>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81478320, on YieldAtomNode 81478376>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 81629648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81633120, on YieldAtomNode 81478376>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81557824, on YieldAtomNode 81478376>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 81557488, on YieldAtomNode 81478376>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81478320, on YieldAtomNode 81478376>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 81629648, on NoneType 1961454680>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81633120, on YieldAtomNode 81478376>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81557824, on YieldAtomNode 81478376>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 81557488, on YieldAtomNode 81478376>}
    
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 81697760, on WithContextItemNode 81695352>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 81697144, on WithContextItemNode 81695352>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 81696976, on RedBaron 81665496>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 81697032, on WithContextItemNode 81695352>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 81697256, on WithContextItemNode 81695352>}
    
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 81697760, on WithContextItemNode 81695352>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 81697144, on WithContextItemNode 81695352>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 81696976, on RedBaron 81665496>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 81697032, on WithContextItemNode 81695352>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 81697256, on WithContextItemNode 81695352>}
    
*/
class PROCKFPS_API PNWith : public ProckNode {
public: 
	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


//
// Generalized, "primitive" nodes
class PROCKFPS_API PNBinaryRawString : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNBinaryString : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNBreak : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNCodeBlock : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNCommaProxyList : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNComment : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNComparisonOperator : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNComplex : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNContinue : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNDef : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNDictitem : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNDotProxyList : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNDottedName : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNEllipsis : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNElseAttribute : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNEndl : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNFloatExponantComplex : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNFloatExponant : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNFloat : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNHexa : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNIfElseBlockSibling : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNInt : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNLeftParenthesis : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNLineProxyList : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNLong : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNName : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


// class PROCKFPS_API PN : public ProckNode {
// public: 
//     ProckNode *Value() { return GetAsNode("value"); }
// };


// class PROCKFPS_API PNList : public ProckNode {
// public: 
//     ProckNode *Value() { return GetAsNode("value"); }
// };


class PROCKFPS_API PNOcta : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNPass : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNRawString : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNRightParenthesis : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNSemicolon : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNSpace : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNStar : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNString : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNUnicodeRawString : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};


class PROCKFPS_API PNUnicodeString : public ProckNode {
public: 
    ProckNode *Value() { return GetAsNode("value"); }
};
// End Generated Code
