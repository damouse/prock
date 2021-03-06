/*
 This header holds all the auto-generated ProckNode subclasses (which is implemented in BaseNode.)

 Do not modify this file, your changes will be overriden. 
*/

#pragma once

#include "Nodes/ProckNode.h"
#include <map>
#include <functional>

// Box meshes are resized once spawned. The mesh needs to be redone- remove this then
const float BOX_RESCALE = .2f;

// Start Generated Code

/*
A node representing generator passed as an argument during a function call.

Equivalent python:

    a(x for y in z)

RedBaron .help() text:

    ArgumentGeneratorComprehensionNode()
      result ->
        NameNode()
          value='x'
      generators ->
        * ComprehensionLoopNode()
            iterator ->
              NameNode()
                value='y'
            target ->
              NameNode()
                value='z'
            ifs ->
    
Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['generators'],
     '_str_keys': ['type'],
     'generators': <NodeList [0, 'value', 1, 'value', 0, 'generators'], " for y in z" 63953888, on ArgumentGeneratorComprehensionNode 63953216>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(x for y in z)" 63953496, on AtomtrailersNode 63860352>,
     'result': <NameNode path=[0, 'value', 1, 'value', 0, 'result'], "x" 63954000, on ArgumentGeneratorComprehensionNode 63953216>,
     'type': 'argument_generator_comprehension'}
    
*/
class PROCKFPS_API PNArgumentGeneratorComprehension : public ProckNode {
public: 
    virtual char *Name() { return "ArgumentGeneratorComprehension "; }
    virtual ProckNodeType Type() { return PNT_ArgumentGeneratorComprehension; }

	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
};

/*
A node representing the assert statement.

Equivalent python:

    assert test, message

RedBaron .help() text:

    AssertNode()
      value ->
        NameNode()
          value='test'
      message ->
        NameNode()
          value='message'
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'message'],
     '_list_keys': ['first_formatting', 'second_formatting', 'third_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64042096, on AssertNode 64042264>,
     'init': False,
     'message': <NameNode path=[0, 'message'], "message" 64042040, on AssertNode 64042264>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "assert test, message" 64041928, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 64042320, on AssertNode 64042264>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 64042376, on AssertNode 64042264>,
     'type': 'assert',
     'value': <NameNode path=[0, 'value'], "test" 64042544, on AssertNode 64042264>}
    
*/
class PROCKFPS_API PNAssert : public ProckNode {
public: 
    virtual char *Name() { return "Assert "; }
    virtual ProckNodeType Type() { return PNT_Assert; }

	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Message() { return GetAsNode("message"); } 
};

/*
A node representing the assign operation in python (:file:`foo = bar`) and the"augmented" assign (:file:`foo += bar`).

Equivalent python:

    a = b

RedBaron .help() text:

    AssignmentNode()
      operator=''
      target ->
        NameNode()
          value='a'
      value ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['target', 'value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'operator'],
     'first_formatting': <NodeList [0, 'first_formatting'], " " 63951536, on AssignmentNode 63951928>,
     'init': False,
     'on_attribute': 'root',
     'operator': '',
     'parent': <RedBaron [], "a = b" 63951368, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 63952152, on AssignmentNode 63951928>,
     'target': <NameNode path=[0, 'target'], "a" 63951592, on AssignmentNode 63951928>,
     'type': 'assignment',
     'value': <NameNode path=[0, 'value'], "b" 63951704, on AssignmentNode 63951928>}
    
*/
class PROCKFPS_API PNAssignment : public ProckNode {
public: 
    virtual char *Name() { return "Assignment "; }
    virtual ProckNodeType Type() { return PNT_Assignment; }

	ProckNode *Target() { return GetAsNode("target"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	char *Operator() { return GetAsString("operator"); } 
};

/*
This node represents a statement prioritised on another by being surrounded by parenthesis. For e.g., the first part of this addition: `(1 + 1) * 2`.

Equivalent python:

    (foo)

RedBaron .help() text:

    AssociativeParenthesisNode()
      value ->
        NameNode()
          value='foo'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 63860296, on AssociativeParenthesisNode 63952040>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 63860688, on AssociativeParenthesisNode 63952040>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 63953720, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 63860184, on AssociativeParenthesisNode 63952040>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 63860408, on AssociativeParenthesisNode 63952040>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 63860632, on AssociativeParenthesisNode 63952040>}
    
*/
class PROCKFPS_API PNAssociativeParenthesis : public ProckNode {
public: 
    virtual char *Name() { return "AssociativeParenthesis "; }
    virtual ProckNodeType Type() { return PNT_AssociativeParenthesis; }

	ProckNode *Value() { return GetAsNode("value"); } 
};

/*
This node represents a combination of :ref:`NameNode`, :ref:`DotNode`,:ref:`CallNode`, :ref:`GetitemNode` sorted in a list. For e.g.::file:`a.b().c[d]`.

Equivalent python:

    a.b().c[d]

RedBaron .help() text:

    AtomtrailersNode()
      value ->
        * NameNode()
            value='a'
        * NameNode()
            value='b'
        * CallNode()
            value ->
        * NameNode()
            value='c'
        * GetitemNode()
            value ->
              NameNode()
                value='d'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 63860296, on AssociativeParenthesisNode 63952040>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 63860688, on AssociativeParenthesisNode 63952040>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 63953720, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 63860184, on AssociativeParenthesisNode 63952040>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 63860408, on AssociativeParenthesisNode 63952040>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 63860632, on AssociativeParenthesisNode 63952040>}
    
*/
class PROCKFPS_API PNAtomtrailers : public ProckNode {
public: 
    virtual char *Name() { return "Atomtrailers "; }
    virtual ProckNodeType Type() { return PNT_Atomtrailers; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
The node represents a binary number value.

Equivalent python:

    0b10101

RedBaron .help() text:

    BinaryNode()
      value='0b10101'
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "0b10101" 64075872, on NoneType 1962241112>,
     'type': 'binary',
     'value': '0b10101'}
    
*/
class PROCKFPS_API PNBinary : public ProckNode {
public: 
    virtual char *Name() { return "Binary "; }
    virtual ProckNodeType Type() { return PNT_Binary; }

	char *Value() { return GetAsString("value"); } 
};

/*
The node represents a binary operator (an operator (e.g: :file:`+` :file:`-` :file:`/`..) applied to 2 values) with its operands. For e.g.: :file:`1 + 1`.

Equivalent python:

    1 + 1

RedBaron .help() text:

    BinaryOperatorNode()
      value='+'
      first ->
        IntNode()
          value='1'
      second ->
        IntNode()
          value='1'
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value'],
     'first': <IntNode path=[0, 'first'], "1" 64076768, on BinaryOperatorNode 64075928>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64076600, on BinaryOperatorNode 64075928>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "1 + 1" 64044896, on NoneType 1962241112>,
     'second': <IntNode path=[0, 'second'], "1" 64077048, on BinaryOperatorNode 64075928>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64077104, on BinaryOperatorNode 64075928>,
     'type': 'binary_operator',
     'value': '+'}
    
*/
class PROCKFPS_API PNBinaryOperator : public ProckNode {
public: 
    virtual char *Name() { return "BinaryOperator "; }
    virtual ProckNodeType Type() { return PNT_BinaryOperator; }

	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
	char *Value() { return GetAsString("value"); } 
};

/*
The node represents a boolean operator (an operator (e.g: :file:`and` :file:`or`) applied to 2 values) with its operands. For e.g.: :file:`x and y`.

Equivalent python:

    x and y

RedBaron .help() text:

    BooleanOperatorNode()
      value='and'
      first ->
        NameNode()
          value='x'
      second ->
        NameNode()
          value='y'
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value'],
     'first': <NameNode path=[0, 'first'], "x" 64107240, on BooleanOperatorNode 64077272>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64106568, on BooleanOperatorNode 64077272>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 64076992, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "y" 64077328, on BooleanOperatorNode 64077272>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64077384, on BooleanOperatorNode 64077272>,
     'type': 'boolean_operator',
     'value': 'and'}
    
*/
class PROCKFPS_API PNBooleanOperator : public ProckNode {
public: 
    virtual char *Name() { return "BooleanOperator "; }
    virtual ProckNodeType Type() { return PNT_BooleanOperator; }

	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
	char *Value() { return GetAsString("value"); } 
};

/*
A node representing a call (eg: :file:`a()`, here :file:`a` is called with noarguments). It is always stored in an :ref:`AtomtrailersNode` or a:ref:`DecoratorNode`.

Equivalent python:

    a(b, c=d)

RedBaron .help() text:

    CallNode()
      value ->
        * CallArgumentNode()
            target ->
              None
            value ->
              NameNode()
                value='b'
        * CallArgumentNode()
            target ->
              NameNode()
                value='c'
            value ->
              NameNode()
                value='d'
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value'],
     'first': <NameNode path=[0, 'first'], "x" 64107240, on BooleanOperatorNode 64077272>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64106568, on BooleanOperatorNode 64077272>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 64076992, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "y" 64077328, on BooleanOperatorNode 64077272>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64077384, on BooleanOperatorNode 64077272>,
     'type': 'boolean_operator',
     'value': 'and'}
    
*/
class PROCKFPS_API PNCall : public ProckNode {
public: 
    virtual char *Name() { return "Call "; }
    virtual ProckNodeType Type() { return PNT_Call; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing an argument or a named argument of a :ref:`CallNode` (othernodes that can be in a CallNode are :ref:`ListArgumentNode` and:ref:`DictArgumentNode`).

Equivalent python:

    a(b, c=d)

RedBaron .help() text:

    CallArgumentNode()
      target ->
        None
      value ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['target', 'value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 64110040, on CallArgumentNode 64107968>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 64109536, on AtomtrailersNode 64106680>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 64110264, on CallArgumentNode 64107968>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 64109704, on CallArgumentNode 64107968>}
    
*/
class PROCKFPS_API PNCallArgument : public ProckNode {
public: 
    virtual char *Name() { return "CallArgument "; }
    virtual ProckNodeType Type() { return PNT_CallArgument; }

	ProckNode *Target() { return GetAsNode("target"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
};

/*
A node representing a class definition.

Equivalent python:

    class SomeAwesomeName(A, B, C): pass

RedBaron .help() text:

    ClassNode()
      name='SomeAwesomeName'
      parenthesis=True
      decorators ->
      inherit_from ->
        * TupleNode()
            with_parenthesis=False
            value ->
              * NameNode()
                  value='A'
              * NameNode()
                  value='B'
              * NameNode()
                  value='C'
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['target', 'value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 64110040, on CallArgumentNode 64107968>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 64109536, on AtomtrailersNode 64106680>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 64110264, on CallArgumentNode 64107968>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 64109704, on CallArgumentNode 64107968>}
    
*/
class PROCKFPS_API PNClass : public ProckNode {
public: 
    virtual char *Name() { return "Class "; }
    virtual ProckNodeType Type() { return PNT_Class; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a comma, this is the kind of formatting node that you mighthave to deal with if not enough high level helpers are available. They aregenerally present in call, function arguments definition and data structuresugar syntactic notation.The comma node is responsible for holding the formatting around it.

Equivalent python:

    [1, 2, 3]

RedBaron .help() text:

    CommaNode()
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 64176424, on CommaNode 64176592>,
     'init': False,
     'on_attribute': 'value',
     'parent': <ListNode path=[0], "[1, 2, 3]" 64147408, on RedBaron 64147352>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], " " 64176872, on CommaNode 64176592>,
     'type': 'comma'}
    
*/
class PROCKFPS_API PNComma : public ProckNode {
public: 
    virtual char *Name() { return "Comma "; }
    virtual ProckNodeType Type() { return PNT_Comma; }

};

/*
The node represents a comparison operation, for e.g.: :file:`42 > 30`.

Equivalent python:

    42 > 30

RedBaron .help() text:

    ComparisonNode()
      first ->
        IntNode()
          value='42'
      value ->
        ComparisonOperatorNode()
          first='>'
          second=''
      second ->
        IntNode()
          value='30'
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first': <IntNode path=[0, 'first'], "42" 64179112, on ComparisonNode 64178888>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 64179000, on ComparisonNode 64178888>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "42 > 30" 64178440, on NoneType 1962241112>,
     'second': <IntNode path=[0, 'second'], "30" 64179056, on ComparisonNode 64178888>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 64178496, on ComparisonNode 64178888>,
     'type': 'comparison',
     'value': <ComparisonOperatorNode path=[0, 'value'], ">" 64177992, on ComparisonNode 64178888>}
    
*/
class PROCKFPS_API PNComparison : public ProckNode {
public: 
    virtual char *Name() { return "Comparison "; }
    virtual ProckNodeType Type() { return PNT_Comparison; }

	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
};

/*
The node represents "if" condition in a comprehension loop. It is always amember of a :ref:`ComprehensionLoopNode`.

Equivalent python:

    [x for x in x if condition]

RedBaron .help() text:

    ComprehensionIfNode()
      value ->
        NameNode()
          value='condition'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'first_formatting'], " " 64146736, on ComprehensionIfNode 64146848>,
     'init': False,
     'on_attribute': 'ifs',
     'parent': <ComprehensionLoopNode path=[0, 'generators', 0], " for x in x if c...n" 64177936, on ListComprehensionNode 64179336>,
     'second_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'second_formatting'], " " 64146512, on ComprehensionIfNode 64146848>,
     'type': 'comprehension_if',
     'value': <NameNode path=[0, 'generators', 0, 'ifs', 0, 'value'], "condition" 64143992, on ComprehensionIfNode 64146848>}
    
*/
class PROCKFPS_API PNComprehensionIf : public ProckNode {
public: 
    virtual char *Name() { return "ComprehensionIf "; }
    virtual ProckNodeType Type() { return PNT_ComprehensionIf; }

	ProckNode *Value() { return GetAsNode("value"); } 
};

/*
The node represents the loop part of a comprehension structure.

Equivalent python:

    [x for y in z]

RedBaron .help() text:

    ComprehensionLoopNode()
      iterator ->
        NameNode()
          value='y'
      target ->
        NameNode()
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
     'first_formatting': <NodeList [0, 'generators', 0, 'first_formatting'], " " 67612912, on ComprehensionLoopNode 64144048>,
     'fourth_formatting': <NodeList [0, 'generators', 0, 'fourth_formatting'], " " 67614424, on ComprehensionLoopNode 64144048>,
     'ifs': <NodeList [0, 'generators', 0, 'ifs'], "" 67614592, on ComprehensionLoopNode 64144048>,
     'init': False,
     'iterator': <NameNode path=[0, 'generators', 0, 'iterator'], "y" 67614032, on ComprehensionLoopNode 64144048>,
     'on_attribute': 'generators',
     'parent': <ListComprehensionNode path=[0], "[x for y in z]" 64146456, on RedBaron 64178384>,
     'second_formatting': <NodeList [0, 'generators', 0, 'second_formatting'], " " 67613472, on ComprehensionLoopNode 64144048>,
     'target': <NameNode path=[0, 'generators', 0, 'target'], "z" 67614536, on ComprehensionLoopNode 64144048>,
     'third_formatting': <NodeList [0, 'generators', 0, 'third_formatting'], " " 67614312, on ComprehensionLoopNode 64144048>,
     'type': 'comprehension_loop'}
    
*/
class PROCKFPS_API PNComprehensionLoop : public ProckNode {
public: 
    virtual char *Name() { return "ComprehensionLoop "; }
    virtual ProckNodeType Type() { return PNT_ComprehensionLoop; }

	ProckNode *Iterator() { return GetAsNode("iterator"); } 
	ProckNode *Target() { return GetAsNode("target"); } 
	std::vector<ProckNode *> *Ifs() { return GetAsList("ifs"); } 
};

/*
A node representing an individual decorator (of a function or a class).

Equivalent python:

    @stuff.plop(*a)\ndef b(): pass

RedBaron .help() text:

    DecoratorNode()
      value ->
        DottedNameNode()
          value ->
            * NameNode()
                value='stuff'
            * DotNode()
            * NameNode()
                value='plop'
      call ->
        CallNode()
          value ->
            * ListArgumentNode()
                value ->
                  NameNode()
                    value='a'
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'call'],
     '_list_keys': [],
     '_str_keys': ['type'],
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 67647416, on DecoratorNode 67647696>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 67647136, on RedBaron 67614088>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 67647584, on DecoratorNode 67647696>}
    
*/
class PROCKFPS_API PNDecorator : public ProckNode {
public: 
    virtual char *Name() { return "Decorator "; }
    virtual ProckNodeType Type() { return PNT_Decorator; }

	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Call() { return GetAsNode("call"); } 
};

/*
A node representing an argument in a function definition.

Equivalent python:

    def a(b, c=d): pass

RedBaron .help() text:

    0 -----------------------------------------------------
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'call'],
     '_list_keys': [],
     '_str_keys': ['type'],
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 67647416, on DecoratorNode 67647696>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 67647136, on RedBaron 67614088>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 67647584, on DecoratorNode 67647696>}
    
*/
class PROCKFPS_API PNDefArgument : public ProckNode {
public: 
    virtual char *Name() { return "DefArgument "; }
    virtual ProckNodeType Type() { return PNT_DefArgument; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a :file:`del` statement.

Equivalent python:

    del stuff

RedBaron .help() text:

    DelNode()
      value ->
        NameNode()
          value='stuff'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 67684840, on DelNode 67685008>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "del stuff" 67615488, on NoneType 1962241112>,
     'type': 'del',
     'value': <NameNode path=[0, 'value'], "stuff" 67684896, on DelNode 67685008>}
    
*/
class PROCKFPS_API PNDel : public ProckNode {
public: 
    virtual char *Name() { return "Del "; }
    virtual ProckNodeType Type() { return PNT_Del; }

	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
};

/*
A node representing a 'kwargs' defined in a function definition argument orused in a :ref:`CallNode`.

Equivalent python:

    a(**b)

RedBaron .help() text:

    DictArgumentNode()
      value ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 67716208, on DictArgumentNode 67685568>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 67715816, on AtomtrailersNode 67685120>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 67716096, on DictArgumentNode 67685568>}
    
*/
class PROCKFPS_API PNDictArgument : public ProckNode {
public: 
    virtual char *Name() { return "DictArgument "; }
    virtual ProckNodeType Type() { return PNT_DictArgument; }

	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
};

/*
A node representing python sugar syntactic notation for dict.

Equivalent python:

    {'a': 1, 'b': 2, 'c': 3}

RedBaron .help() text:

    DictNode()
      value ->
        * DictitemNode()
            key ->
              StringNode()
                value="'a'"
            value ->
              IntNode()
                value='1'
        * DictitemNode()
            key ->
              StringNode()
                value="'b'"
            value ->
              IntNode()
                value='2'
        * DictitemNode()
            key ->
              StringNode()
                value="'c'"
            value ->
              IntNode()
                value='3'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 67716208, on DictArgumentNode 67685568>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 67715816, on AtomtrailersNode 67685120>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 67716096, on DictArgumentNode 67685568>}
    
*/
class PROCKFPS_API PNDict : public ProckNode {
public: 
    virtual char *Name() { return "Dict "; }
    virtual ProckNodeType Type() { return PNT_Dict; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing dictionary comprehension node.

Equivalent python:

    {a: b for c in d}

RedBaron .help() text:

    DictComprehensionNode()
      result ->
        DictitemNode()
          key ->
            NameNode()
              value='a'
          value ->
            NameNode()
              value='b'
      generators ->
        * ComprehensionLoopNode()
            iterator ->
              NameNode()
                value='c'
            target ->
              NameNode()
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 67718896, on DictComprehensionNode 67717384>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67756776, on DictComprehensionNode 67717384>,
     'generators': <NodeList [0, 'generators'], " for c in d" 67718392, on DictComprehensionNode 67717384>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 67717104, on NoneType 1962241112>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 67718952, on DictComprehensionNode 67717384>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67719120, on DictComprehensionNode 67717384>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 67756160, on DictComprehensionNode 67717384>,
     'type': 'dict_comprehension'}
    
*/
class PROCKFPS_API PNDictComprehension : public ProckNode {
public: 
    virtual char *Name() { return "DictComprehension "; }
    virtual ProckNodeType Type() { return PNT_DictComprehension; }

	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
};

/*
A node representing an argument to the import node.

Equivalent python:

    import a.b.c as d

RedBaron .help() text:

    DottedAsNameNode()
      target='d'
      value ->
        * NameNode()
            value='a'
        * NameNode()
            value='b'
        * NameNode()
            value='c'
    
Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 67718896, on DictComprehensionNode 67717384>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67756776, on DictComprehensionNode 67717384>,
     'generators': <NodeList [0, 'generators'], " for c in d" 67718392, on DictComprehensionNode 67717384>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 67717104, on NoneType 1962241112>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 67718952, on DictComprehensionNode 67717384>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67719120, on DictComprehensionNode 67717384>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 67756160, on DictComprehensionNode 67717384>,
     'type': 'dict_comprehension'}
    
*/
class PROCKFPS_API PNDottedAsName : public ProckNode {
public: 
    virtual char *Name() { return "DottedAsName "; }
    virtual ProckNodeType Type() { return PNT_DottedAsName; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a dot '.', generally found in atom trailers (this kind of structure: 'variable.another_variable(call)[getitem]').This is the kind of formatting node that you might have to deal with if not enough high level helpers are available.The dot node is responsible for holding the formatting around it.

Equivalent python:

    a.b

RedBaron .help() text:

    NameNode()
      value='b'
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67759296, on RedBaron 67757560>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNDot : public ProckNode {
public: 
    virtual char *Name() { return "Dot "; }
    virtual ProckNodeType Type() { return PNT_Dot; }

	char *Value() { return GetAsString("value"); } 
};

/*
A node representing an elif statement.The ElifNode, like the :ref:`IfNode` or the :ref:`ElseNode` are stored in a :ref:`IfelseblockNode`.

Equivalent python:

    if a: pass\nelif b: pass

RedBaron .help() text:

    ElifNode()
      test ->
        NameNode()
          value='b'
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67759296, on RedBaron 67757560>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNElif : public ProckNode {
public: 
    virtual char *Name() { return "Elif "; }
    virtual ProckNodeType Type() { return PNT_Elif; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing an else statement.The ElseNode, like the :ref:`IfNode` or the :ref:`ElifNode`, is stored in a :ref:`IfelseblockNode`.

Equivalent python:

    if a: pass\nelse: pass

RedBaron .help() text:

    ElseNode()
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67759296, on RedBaron 67757560>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNElse : public ProckNode {
public: 
    virtual char *Name() { return "Else "; }
    virtual ProckNodeType Type() { return PNT_Else; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing an except statement (member of a :ref:`TryNode`).

Equivalent python:

    try: pass\nexcept FooBar: pass\nexcept Exception: pass\nelse: pass\nfinally: pass\n

RedBaron .help() text:

    EndlNode()
      value='\n'
      indent=''
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': [],
     '_str_keys': ['type', 'value'],
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a.b" 67759296, on RedBaron 67757560>,
     'type': 'name',
     'value': 'b'}
    
*/
class PROCKFPS_API PNExcept : public ProckNode {
public: 
    virtual char *Name() { return "Except "; }
    virtual ProckNodeType Type() { return PNT_Except; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a exec statement.

Equivalent python:

    exec '1 + 1' in a, b

RedBaron .help() text:

    ExecNode()
      value ->
        StringNode()
          value="'1 + 1'"
      globals ->
        NameNode()
          value='a'
      locals ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67758624, on ExecNode 67683888>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67685624, on ExecNode 67683888>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67758568, on ExecNode 67683888>,
     'globals': <NameNode path=[0, 'globals'], "a" 67716040, on ExecNode 67683888>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67757280, on ExecNode 67683888>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67648760, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67715368, on ExecNode 67683888>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67717608, on ExecNode 67683888>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67685848, on ExecNode 67683888>}
    
*/
class PROCKFPS_API PNExec : public ProckNode {
public: 
    virtual char *Name() { return "Exec "; }
    virtual ProckNodeType Type() { return PNT_Exec; }

	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Globals() { return GetAsNode("globals"); } 
	ProckNode *Locals() { return GetAsNode("locals"); } 
};

/*
A node representing a finally statement (member of a :ref:`TryNode`).

Equivalent python:

    try: pass\nexcept FooBar: pass\nexcept Exception: pass\nelse: pass\nfinally: pass\n").finally_.help(deep=True)

RedBaron .help() text:

    FinallyNode()
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67758624, on ExecNode 67683888>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67685624, on ExecNode 67683888>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67758568, on ExecNode 67683888>,
     'globals': <NameNode path=[0, 'globals'], "a" 67716040, on ExecNode 67683888>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67757280, on ExecNode 67683888>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67648760, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67715368, on ExecNode 67683888>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67717608, on ExecNode 67683888>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67685848, on ExecNode 67683888>}
    
*/
class PROCKFPS_API PNFinally : public ProckNode {
public: 
    virtual char *Name() { return "Finally "; }
    virtual ProckNodeType Type() { return PNT_Finally; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a for loop.

Equivalent python:

    for i in b:\n    pass

RedBaron .help() text:

    ForNode()
      iterator ->
        NameNode()
          value='i'
      target ->
        NameNode()
          value='b'
      else ->
        None
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67758624, on ExecNode 67683888>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67685624, on ExecNode 67683888>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67758568, on ExecNode 67683888>,
     'globals': <NameNode path=[0, 'globals'], "a" 67716040, on ExecNode 67683888>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67757280, on ExecNode 67683888>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67648760, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67715368, on ExecNode 67683888>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67717608, on ExecNode 67683888>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67685848, on ExecNode 67683888>}
    
*/
class PROCKFPS_API PNFor : public ProckNode {
public: 
    virtual char *Name() { return "For "; }
    virtual ProckNodeType Type() { return PNT_For; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a "from import" statement.

Equivalent python:

    from a import b

RedBaron .help() text:

    FromImportNode()
      value ->
        * NameNode()
            value='a'
      targets ->
        * NameAsNameNode()
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67758624, on ExecNode 67683888>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67685624, on ExecNode 67683888>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67758568, on ExecNode 67683888>,
     'globals': <NameNode path=[0, 'globals'], "a" 67716040, on ExecNode 67683888>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67757280, on ExecNode 67683888>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67648760, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67715368, on ExecNode 67683888>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67717608, on ExecNode 67683888>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67685848, on ExecNode 67683888>}
    
*/
class PROCKFPS_API PNFromImport : public ProckNode {
public: 
    virtual char *Name() { return "FromImport "; }
    virtual ProckNodeType Type() { return PNT_FromImport; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a function definition.

Equivalent python:

    def stuff():\n    pass\n

RedBaron .help() text:

    DefNode()
      name='stuff'
      decorators ->
      arguments ->
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'globals', 'locals'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67758624, on ExecNode 67683888>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67685624, on ExecNode 67683888>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67758568, on ExecNode 67683888>,
     'globals': <NameNode path=[0, 'globals'], "a" 67716040, on ExecNode 67683888>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 67757280, on ExecNode 67683888>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 67648760, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 67715368, on ExecNode 67683888>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67717608, on ExecNode 67683888>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 67685848, on ExecNode 67683888>}
    
*/
class PROCKFPS_API PNFuncdef : public ProckNode {
public: 
    virtual char *Name() { return "Funcdef "; }
    virtual ProckNodeType Type() { return PNT_Funcdef; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a generator comprehension node.

Equivalent python:

    (x for y in z)

RedBaron .help() text:

    GeneratorComprehensionNode()
      result ->
        NameNode()
          value='x'
      generators ->
        * ComprehensionLoopNode()
            iterator ->
              NameNode()
                value='y'
            target ->
              NameNode()
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 67908104, on GeneratorComprehensionNode 67907992>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67909224, on GeneratorComprehensionNode 67907992>,
     'generators': <NodeList [0, 'generators'], " for y in z" 67908272, on GeneratorComprehensionNode 67907992>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(x for y in z)" 67824552, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 67908328, on GeneratorComprehensionNode 67907992>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67908888, on GeneratorComprehensionNode 67907992>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 67908440, on GeneratorComprehensionNode 67907992>,
     'type': 'generator_comprehension'}
    
*/
class PROCKFPS_API PNGeneratorComprehension : public ProckNode {
public: 
    virtual char *Name() { return "GeneratorComprehension "; }
    virtual ProckNodeType Type() { return PNT_GeneratorComprehension; }

	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
};

/*
A node representing a 'get item' access on a python object, in other words the'[stuff]' in 'some_object[stuff]'.

Equivalent python:

    a[b]

RedBaron .help() text:

    GetitemNode()
      value ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 67910904, on GetitemNode 67910960>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 67911240, on GetitemNode 67910960>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 67909504, on RedBaron 67910344>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 67910624, on GetitemNode 67910960>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 67911184, on GetitemNode 67910960>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 67910680, on GetitemNode 67910960>}
    
*/
class PROCKFPS_API PNGetitem : public ProckNode {
public: 
    virtual char *Name() { return "Getitem "; }
    virtual ProckNodeType Type() { return PNT_Getitem; }

	ProckNode *Value() { return GetAsNode("value"); } 
};

/*
A node representing a global statement.

Equivalent python:

    global a

RedBaron .help() text:

    GlobalNode()
      value ->
        * NameNode()
            value='a'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 67910904, on GetitemNode 67910960>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 67911240, on GetitemNode 67910960>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 67909504, on RedBaron 67910344>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 67910624, on GetitemNode 67910960>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 67911184, on GetitemNode 67910960>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 67910680, on GetitemNode 67910960>}
    
*/
class PROCKFPS_API PNGlobal : public ProckNode {
public: 
    virtual char *Name() { return "Global "; }
    virtual ProckNodeType Type() { return PNT_Global; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing an if statement.The IfNode, like the :ref:`ElifNode` or the :ref:`ElseNode`, is stored in an :ref:`IfelseblockNode`.

Equivalent python:

    if a: pass

RedBaron .help() text:

    IfNode()
      test ->
        NameNode()
          value='a'
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 67910904, on GetitemNode 67910960>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 67911240, on GetitemNode 67910960>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 67909504, on RedBaron 67910344>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 67910624, on GetitemNode 67910960>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 67911184, on GetitemNode 67910960>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 67910680, on GetitemNode 67910960>}
    
*/
class PROCKFPS_API PNIf : public ProckNode {
public: 
    virtual char *Name() { return "If "; }
    virtual ProckNodeType Type() { return PNT_If; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing the conditional block composed of at least one if statement,zero or more elif statements and, at the end, an optional else statement. Allthose statements are stored in a list.

Equivalent python:

    if a: pass\nelif b: pass\nelse: pass\n

RedBaron .help() text:

    IfelseblockNode()
      value ->
        * IfNode()
            test ->
              NameNode()
                value='a'
            value ->
              * PassNode()
        * ElifNode()
            test ->
              NameNode()
                value='b'
            value ->
              * PassNode()
        * ElseNode()
            value ->
              * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['value'],
     '_str_keys': ['type'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "if a: pass\nelif...n" 67909448, on NoneType 1962241112>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 67944064, on IfelseblockNode 67943952>}
    
*/
class PROCKFPS_API PNIfelseblock : public ProckNode {
public: 
    virtual char *Name() { return "Ifelseblock "; }
    virtual ProckNodeType Type() { return PNT_Ifelseblock; }

	std::vector<ProckNode *> *Value() { return GetAsList("value"); } 
};

/*
A node representing the import statement of the python language.*Be careful, this node and its subnodes are way more complex than what you canexpect*.

Equivalent python:

    import foo

RedBaron .help() text:

    ImportNode()
      value ->
        * DottedAsNameNode()
            target=''
            value ->
              * NameNode()
                  value='foo'
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['value'],
     '_str_keys': ['type'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "if a: pass\nelif...n" 67909448, on NoneType 1962241112>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 67944064, on IfelseblockNode 67943952>}
    
*/
class PROCKFPS_API PNImport : public ProckNode {
public: 
    virtual char *Name() { return "Import "; }
    virtual ProckNodeType Type() { return PNT_Import; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a lambda statement.

Equivalent python:

    lambda x: y

RedBaron .help() text:

    IntNode()
      value='42'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting',
                    'arguments',
                    'second_formatting',
                    'third_formatting'],
     '_str_keys': ['type'],
     'arguments': <CommaProxyList [0, 'arguments'], "x" 67942664, on LambdaNode 67940704>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 67941040, on LambdaNode 67940704>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "lambda x: y" 67943112, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 67941096, on LambdaNode 67940704>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67940928, on LambdaNode 67940704>,
     'type': 'lambda',
     'value': <NameNode path=[0, 'value'], "y" 67940592, on LambdaNode 67940704>}
    
*/
class PROCKFPS_API PNLambda : public ProckNode {
public: 
    virtual char *Name() { return "Lambda "; }
    virtual ProckNodeType Type() { return PNT_Lambda; }

	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Arguments() { return GetAsList("arguments"); } 
};

/*
A node representing a "start argument" in a function call **or** definition.

Equivalent python:

    def a(*b): pass

RedBaron .help() text:

    ListArgumentNode()
      value ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'arguments', 0, 'formatting'], "" 68012016, on ListArgumentNode 67859288>,
     'init': False,
     'on_attribute': 'arguments',
     'parent': <DefNode path=[0], "def a(*b): pass\n" 68011232, on RedBaron 67942888>,
     'type': 'list_argument',
     'value': <NameNode path=[0, 'arguments', 0, 'value'], "b" 68012072, on ListArgumentNode 67859288>}
    
*/
class PROCKFPS_API PNListArgument : public ProckNode {
public: 
    virtual char *Name() { return "ListArgument "; }
    virtual ProckNodeType Type() { return PNT_ListArgument; }

	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
};

/*
A node representing a list comprehension node.

Equivalent python:

    [x for y in z]

RedBaron .help() text:

    ListComprehensionNode()
      result ->
        NameNode()
          value='x'
      generators ->
        * ComprehensionLoopNode()
            iterator ->
              NameNode()
                value='y'
            target ->
              NameNode()
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68048152, on ListComprehensionNode 68013360>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68048488, on ListComprehensionNode 68013360>,
     'generators': <NodeList [0, 'generators'], " for y in z" 68047424, on ListComprehensionNode 68013360>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 68011568, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 68048208, on ListComprehensionNode 68013360>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68047648, on ListComprehensionNode 68013360>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68047592, on ListComprehensionNode 68013360>,
     'type': 'list_comprehension'}
    
*/
class PROCKFPS_API PNListComprehension : public ProckNode {
public: 
    virtual char *Name() { return "ListComprehension "; }
    virtual ProckNodeType Type() { return PNT_ListComprehension; }

	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
};

/*
A node representing python sugar syntactic notation for list.

Equivalent python:

    [1, 2, 3]

RedBaron .help() text:

    ListNode()
      value ->
        * IntNode()
            value='1'
        * IntNode()
            value='2'
        * IntNode()
            value='3'
    
Python __dict__ dump:

    {'_dict_keys': ['result'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'generators',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68048152, on ListComprehensionNode 68013360>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68048488, on ListComprehensionNode 68013360>,
     'generators': <NodeList [0, 'generators'], " for y in z" 68047424, on ListComprehensionNode 68013360>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 68011568, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 68048208, on ListComprehensionNode 68013360>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68047648, on ListComprehensionNode 68013360>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68047592, on ListComprehensionNode 68013360>,
     'type': 'list_comprehension'}
    
*/
class PROCKFPS_API PNList : public ProckNode {
public: 
    virtual char *Name() { return "List "; }
    virtual ProckNodeType Type() { return PNT_List; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing an argument to the from import statement.

Equivalent python:

    from x import a as d

RedBaron .help() text:

    NameAsNameNode()
      value='a'
      target='d'
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value', 'target'],
     'first_formatting': [' '],
     'init': False,
     'on_attribute': 'targets',
     'parent': <FromImportNode path=[0], "from x import a as d" 67988840, on RedBaron 68010168>,
     'second_formatting': [' '],
     'target': 'd',
     'type': 'name_as_name',
     'value': 'a'}
    
*/
class PROCKFPS_API PNNameAsName : public ProckNode {
public: 
    virtual char *Name() { return "NameAsName "; }
    virtual ProckNodeType Type() { return PNT_NameAsName; }

	char *Value() { return GetAsString("value"); } 
	char *Target() { return GetAsString("target"); } 
};

/*
A node representing a print statement.

Equivalent python:

    print(stuff)

RedBaron .help() text:

    PrintNode()
      destination ->
        None
      value ->
        * AssociativeParenthesisNode()
            value ->
              NameNode()
                value='stuff'
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type', 'value', 'target'],
     'first_formatting': [' '],
     'init': False,
     'on_attribute': 'targets',
     'parent': <FromImportNode path=[0], "from x import a as d" 67988840, on RedBaron 68010168>,
     'second_formatting': [' '],
     'target': 'd',
     'type': 'name_as_name',
     'value': 'a'}
    
*/
class PROCKFPS_API PNPrint : public ProckNode {
public: 
    virtual char *Name() { return "Print "; }
    virtual ProckNodeType Type() { return PNT_Print; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a raise statement.

Equivalent python:

    raise Exception(), foo, bar

RedBaron .help() text:

    RaiseNode()
      value ->
        AtomtrailersNode()
          value ->
            * NameNode()
                value='Exception'
            * CallNode()
                value ->
      instance ->
        NameNode()
          value='foo'
      traceback ->
        NameNode()
          value='bar'
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'instance', 'traceback'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67941320, on RaiseNode 68049328>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68049944, on RaiseNode 68049328>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67986712, on RaiseNode 68049328>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 67986880, on RaiseNode 68049328>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 68050840, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68049552, on RaiseNode 68049328>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67988168, on RaiseNode 68049328>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 67943280, on RaiseNode 68049328>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 68050056, on RaiseNode 68049328>}
    
*/
class PROCKFPS_API PNRaise : public ProckNode {
public: 
    virtual char *Name() { return "Raise "; }
    virtual ProckNodeType Type() { return PNT_Raise; }

	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Instance() { return GetAsNode("instance"); } 
	ProckNode *Traceback() { return GetAsNode("traceback"); } 
};

/*
A node representing python sugar syntactic notation for repr.

Equivalent python:

    `pouet`

RedBaron .help() text:

    ReprNode()
      value ->
        * NameNode()
            value='pouet'
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'instance', 'traceback'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting',
                    'fifth_formatting'],
     '_str_keys': ['type'],
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 67941320, on RaiseNode 68049328>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68049944, on RaiseNode 68049328>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 67986712, on RaiseNode 68049328>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 67986880, on RaiseNode 68049328>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 68050840, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68049552, on RaiseNode 68049328>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 67988168, on RaiseNode 68049328>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 67943280, on RaiseNode 68049328>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 68050056, on RaiseNode 68049328>}
    
*/
class PROCKFPS_API PNRepr : public ProckNode {
public: 
    virtual char *Name() { return "Repr "; }
    virtual ProckNodeType Type() { return PNT_Repr; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a return statement.

Equivalent python:

    return stuff

RedBaron .help() text:

    ReturnNode()
      value ->
        NameNode()
          value='stuff'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 68080640, on ReturnNode 68081816>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 68080920, on NoneType 1962241112>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 68080360, on ReturnNode 68081816>}
    
*/
class PROCKFPS_API PNReturn : public ProckNode {
public: 
    virtual char *Name() { return "Return "; }
    virtual ProckNodeType Type() { return PNT_Return; }

	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
};

/*
A node representing python sugar syntactic notation for set.

Equivalent python:

    {1, 2, 3}

RedBaron .help() text:

    SetNode()
      value ->
        * IntNode()
            value='1'
        * IntNode()
            value='2'
        * IntNode()
            value='3'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 68080640, on ReturnNode 68081816>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 68080920, on NoneType 1962241112>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 68080360, on ReturnNode 68081816>}
    
*/
class PROCKFPS_API PNSet : public ProckNode {
public: 
    virtual char *Name() { return "Set "; }
    virtual ProckNodeType Type() { return PNT_Set; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a set comprehension node.

Equivalent python:

    {x for y in z}

RedBaron .help() text:

    SetComprehensionNode()
      result ->
        NameNode()
          value='x'
      generators ->
        * ComprehensionLoopNode()
            iterator ->
              NameNode()
                value='y'
            target ->
              NameNode()
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68123672, on SetComprehensionNode 68121656>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 68124008, on SetComprehensionNode 68121656>,
     'generators': <NodeList [0, 'generators'], " for y in z" 68122944, on SetComprehensionNode 68121656>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{x for y in z}" 68081760, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 68123728, on SetComprehensionNode 68121656>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 68123168, on SetComprehensionNode 68121656>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68123112, on SetComprehensionNode 68121656>,
     'type': 'set_comprehension'}
    
*/
class PROCKFPS_API PNSetComprehension : public ProckNode {
public: 
    virtual char *Name() { return "SetComprehension "; }
    virtual ProckNodeType Type() { return PNT_SetComprehension; }

	ProckNode *Result() { return GetAsNode("result"); } 
	std::vector<ProckNode *> *Generators() { return GetAsList("generators"); } 
};

/*
A node representing a slice, the "1:2:3" that can be found in a:ref:`GetitemNode`.

Equivalent python:

    a[1:-1:2]

RedBaron .help() text:

    SliceNode()
      has_two_colons=True
      lower ->
        IntNode()
          value='1'
      upper ->
        UnitaryOperatorNode()
          value='-'
          target ->
            IntNode()
              value='1'
      step ->
        IntNode()
          value='2'
    
Python __dict__ dump:

    {'_dict_keys': ['lower', 'upper', 'step'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type', 'has_two_colons'],
     'first_formatting': <NodeList [0, 'value', 1, 'value', 'first_formatting'], "" 68082768, on SliceNode 68082712>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'value', 'fourth_formatting'], "" 68082992, on SliceNode 68082712>,
     'has_two_colons': True,
     'init': False,
     'lower': <IntNode path=[0, 'value', 1, 'value', 'lower'], "1" 68082432, on SliceNode 68082712>,
     'on_attribute': 'value',
     'parent': <GetitemNode path=[0, 'value', 1], "[1:-1:2]" 68081872, on AtomtrailersNode 68050168>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 'second_formatting'], "" 68082824, on SliceNode 68082712>,
     'step': <IntNode path=[0, 'value', 1, 'value', 'step'], "2" 68081984, on SliceNode 68082712>,
     'third_formatting': <NodeList [0, 'value', 1, 'value', 'third_formatting'], "" 68082544, on SliceNode 68082712>,
     'type': 'slice',
     'upper': <UnitaryOperatorNode path=[0, 'value', 1, 'value', 'upper'], "-1" 68080304, on SliceNode 68082712>}
    
*/
class PROCKFPS_API PNSlice : public ProckNode {
public: 
    virtual char *Name() { return "Slice "; }
    virtual ProckNodeType Type() { return PNT_Slice; }

	ProckNode *Lower() { return GetAsNode("lower"); } 
	ProckNode *Upper() { return GetAsNode("upper"); } 
	ProckNode *Step() { return GetAsNode("step"); } 
	char *HasTwoColons() { return GetAsString("has_two_colons"); } 
};

/*
This is a special node that handle a particular way of writing a single string inpython by putting several strings one after the other while only separated byspaces or endls.

Equivalent python:

    'a' r'b' b'c'

RedBaron .help() text:

    SpaceNode()
      value=' '
    
Python __dict__ dump:

    {'_dict_keys': [],
     '_list_keys': ['value'],
     '_str_keys': ['type'],
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "'a' r'b' b'c'" 67943448, on NoneType 1962241112>,
     'type': 'string_chain',
     'value': <NodeList [0, 'value'], "'a' r'b' b'c'" 68428016, on StringChainNode 68429192>}
    
*/
class PROCKFPS_API PNStringChain : public ProckNode {
public: 
    virtual char *Name() { return "StringChain "; }
    virtual ProckNodeType Type() { return PNT_StringChain; }

	std::vector<ProckNode *> *Value() { return GetAsList("value"); } 
};

/*
A node representing the ternary operator expression.

Equivalent python:

    a if b else c

RedBaron .help() text:

    TernaryOperatorNode()
      first ->
        NameNode()
          value='a'
      value ->
        NameNode()
          value='b'
      second ->
        NameNode()
          value='c'
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first': <NameNode path=[0, 'first'], "a" 68431152, on TernaryOperatorNode 68429752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68430928, on TernaryOperatorNode 68429752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 68430592, on TernaryOperatorNode 68429752>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 68430480, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 68431320, on TernaryOperatorNode 68429752>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68430648, on TernaryOperatorNode 68429752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68431096, on TernaryOperatorNode 68429752>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 68431208, on TernaryOperatorNode 68429752>}
    
*/
class PROCKFPS_API PNTernaryOperator : public ProckNode {
public: 
    virtual char *Name() { return "TernaryOperator "; }
    virtual ProckNodeType Type() { return PNT_TernaryOperator; }

	ProckNode *First() { return GetAsNode("first"); } 
	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *Second() { return GetAsNode("second"); } 
};

/*
A node representing a try statement. This node is responsible for holding the:ref:`ExceptNode`, :ref:`FinallyNode` and :ref:`ElseNode`.

Equivalent python:

    try: pass\nexcept FooBar: pass\nexcept Exception: pass\nelse: pass\nfinally: pass\n

RedBaron .help() text:

    TryNode()
      else ->
        ElseNode()
          value ->
            * PassNode()
      finally ->
        FinallyNode()
          value ->
            * PassNode()
      value ->
        * PassNode()
      excepts ->
        * ExceptNode()
            delimiter=''
            exception ->
              NameNode()
                value='FooBar'
            target ->
              None
            value ->
              * PassNode()
        * ExceptNode()
            delimiter=''
            exception ->
              NameNode()
                value='Exception'
            target ->
              None
            value ->
              * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first': <NameNode path=[0, 'first'], "a" 68431152, on TernaryOperatorNode 68429752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68430928, on TernaryOperatorNode 68429752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 68430592, on TernaryOperatorNode 68429752>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 68430480, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 68431320, on TernaryOperatorNode 68429752>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68430648, on TernaryOperatorNode 68429752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68431096, on TernaryOperatorNode 68429752>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 68431208, on TernaryOperatorNode 68429752>}
    
*/
class PROCKFPS_API PNTry : public ProckNode {
public: 
    virtual char *Name() { return "Try "; }
    virtual ProckNodeType Type() { return PNT_Try; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing python sugar syntactic notation for tuple.

Equivalent python:

    (1, 2, 3)

RedBaron .help() text:

    TupleNode()
      with_parenthesis=True
      value ->
        * IntNode()
            value='1'
        * IntNode()
            value='2'
        * IntNode()
            value='3'
    
Python __dict__ dump:

    {'_dict_keys': ['first', 'value', 'second'],
     '_list_keys': ['first_formatting',
                    'second_formatting',
                    'third_formatting',
                    'fourth_formatting'],
     '_str_keys': ['type'],
     'first': <NameNode path=[0, 'first'], "a" 68431152, on TernaryOperatorNode 68429752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 68430928, on TernaryOperatorNode 68429752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 68430592, on TernaryOperatorNode 68429752>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 68430480, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 68431320, on TernaryOperatorNode 68429752>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68430648, on TernaryOperatorNode 68429752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 68431096, on TernaryOperatorNode 68429752>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 68431208, on TernaryOperatorNode 68429752>}
    
*/
class PROCKFPS_API PNTuple : public ProckNode {
public: 
    virtual char *Name() { return "Tuple "; }
    virtual ProckNodeType Type() { return PNT_Tuple; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a number sign modification operator like :file:`-2` or :file:`+42`.

Equivalent python:

    -1

RedBaron .help() text:

    UnitaryOperatorNode()
      value='-'
      target ->
        IntNode()
          value='1'
    
Python __dict__ dump:

    {'_dict_keys': ['target'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type', 'value'],
     'formatting': <NodeList [0, 'formatting'], "" 68539392, on UnitaryOperatorNode 68539784>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "-1" 68539056, on NoneType 1962241112>,
     'target': <IntNode path=[0, 'target'], "1" 68539616, on UnitaryOperatorNode 68539784>,
     'type': 'unitary_operator',
     'value': '-'}
    
*/
class PROCKFPS_API PNUnitaryOperator : public ProckNode {
public: 
    virtual char *Name() { return "UnitaryOperator "; }
    virtual ProckNodeType Type() { return PNT_UnitaryOperator; }

	ProckNode *Target() { return GetAsNode("target"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
	char *Value() { return GetAsString("value"); } 
};

/*
A node representing a yield statement.

Equivalent python:

    yield 42

RedBaron .help() text:

    YieldNode()
      value ->
        IntNode()
          value='42'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['formatting'],
     '_str_keys': ['type'],
     'formatting': <NodeList [0, 'formatting'], " " 68507184, on YieldNode 68507632>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "yield 42" 68507744, on NoneType 1962241112>,
     'type': 'yield',
     'value': <IntNode path=[0, 'value'], "42" 68507464, on YieldNode 68507632>}
    
*/
class PROCKFPS_API PNYield : public ProckNode {
public: 
    virtual char *Name() { return "Yield "; }
    virtual ProckNodeType Type() { return PNT_Yield; }

	ProckNode *Value() { return GetAsNode("value"); } 
	std::vector<ProckNode *> *Formatting() { return GetAsList("formatting"); } 
};

/*
A node representing a yield statement surrounded by parenthesis.

Equivalent python:

    (yield 42)

RedBaron .help() text:

    YieldAtomNode()
      value ->
        IntNode()
          value='42'
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting', 'second_formatting', 'third_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68506904, on YieldAtomNode 68506176>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 68506960, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68508080, on YieldAtomNode 68506176>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68468184, on YieldAtomNode 68506176>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 68468352, on YieldAtomNode 68506176>}
    
*/
class PROCKFPS_API PNYieldAtom : public ProckNode {
public: 
    virtual char *Name() { return "YieldAtom "; }
    virtual ProckNodeType Type() { return PNT_YieldAtom; }

	ProckNode *Value() { return GetAsNode("value"); } 
};

/*
A node representing a while loop.

Equivalent python:

    while condition:\n    pass

RedBaron .help() text:

    WhileNode()
      test ->
        NameNode()
          value='condition'
      else ->
        None
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['value'],
     '_list_keys': ['first_formatting', 'second_formatting', 'third_formatting'],
     '_str_keys': ['type'],
     'first_formatting': <NodeList [0, 'first_formatting'], "" 68506904, on YieldAtomNode 68506176>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 68506960, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 68508080, on YieldAtomNode 68506176>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 68468184, on YieldAtomNode 68506176>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 68468352, on YieldAtomNode 68506176>}
    
*/
class PROCKFPS_API PNWhile : public ProckNode {
public: 
    virtual char *Name() { return "While "; }
    virtual ProckNodeType Type() { return PNT_While; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};

/*
A node representing a while loop.

Equivalent python:

    with a as b: pass

RedBaron .help() text:

    WithContextItemNode()
      value ->
        NameNode()
          value='a'
      as ->
        NameNode()
          value='b'
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'as'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 68576424, on WithContextItemNode 68541184>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 68575808, on WithContextItemNode 68541184>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 68575640, on RedBaron 68540064>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 68575696, on WithContextItemNode 68541184>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 68575920, on WithContextItemNode 68541184>}
    
*/
class PROCKFPS_API PNWithContextItem : public ProckNode {
public: 
    virtual char *Name() { return "WithContextItem "; }
    virtual ProckNodeType Type() { return PNT_WithContextItem; }

	ProckNode *Value() { return GetAsNode("value"); } 
	ProckNode *As() { return GetAsNode("as"); } 
};

/*
A node representing a with statement.

Equivalent python:

    with a as b, c: pass

RedBaron .help() text:

    WithNode()
      contexts ->
        * WithContextItemNode()
            value ->
              NameNode()
                value='a'
            as ->
              NameNode()
                value='b'
        * WithContextItemNode()
            value ->
              NameNode()
                value='c'
            as ->
              None
      value ->
        * PassNode()
    
Python __dict__ dump:

    {'_dict_keys': ['value', 'as'],
     '_list_keys': ['first_formatting', 'second_formatting'],
     '_str_keys': ['type'],
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 68576424, on WithContextItemNode 68541184>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 68575808, on WithContextItemNode 68541184>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 68575640, on RedBaron 68540064>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 68575696, on WithContextItemNode 68541184>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 68575920, on WithContextItemNode 68541184>}
    
*/
class PROCKFPS_API PNWith : public ProckNode {
public: 
    virtual char *Name() { return "With "; }
    virtual ProckNodeType Type() { return PNT_With; }

	std::vector<ProckNode *> *NodeList() { return GetAsList("node_list"); } 
};


//
// Generalized, "primitive" nodes
class PROCKFPS_API PNBinaryRawString : public ProckNode {
public: 
    virtual char *Name() { return "BinaryRawString "; }
    virtual ProckNodeType Type() { return PNT_BinaryRawString; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNBinaryString : public ProckNode {
public: 
    virtual char *Name() { return "BinaryString "; }
    virtual ProckNodeType Type() { return PNT_BinaryString; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNBreak : public ProckNode {
public: 
    virtual char *Name() { return "Break "; }
    virtual ProckNodeType Type() { return PNT_Break; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNCodeBlock : public ProckNode {
public: 
    virtual char *Name() { return "CodeBlock "; }
    virtual ProckNodeType Type() { return PNT_CodeBlock; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNCommaProxyList : public ProckNode {
public: 
    virtual char *Name() { return "CommaProxyList "; }
    virtual ProckNodeType Type() { return PNT_CommaProxyList; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNComment : public ProckNode {
public: 
    virtual char *Name() { return "Comment "; }
    virtual ProckNodeType Type() { return PNT_Comment; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNComparisonOperator : public ProckNode {
public: 
    virtual char *Name() { return "ComparisonOperator "; }
    virtual ProckNodeType Type() { return PNT_ComparisonOperator; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNComplex : public ProckNode {
public: 
    virtual char *Name() { return "Complex "; }
    virtual ProckNodeType Type() { return PNT_Complex; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNContinue : public ProckNode {
public: 
    virtual char *Name() { return "Continue "; }
    virtual ProckNodeType Type() { return PNT_Continue; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDef : public ProckNode {
public: 
    virtual char *Name() { return "Def "; }
    virtual ProckNodeType Type() { return PNT_Def; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDictitem : public ProckNode {
public: 
    virtual char *Name() { return "Dictitem "; }
    virtual ProckNodeType Type() { return PNT_Dictitem; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDotProxyList : public ProckNode {
public: 
    virtual char *Name() { return "DotProxyList "; }
    virtual ProckNodeType Type() { return PNT_DotProxyList; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNDottedName : public ProckNode {
public: 
    virtual char *Name() { return "DottedName "; }
    virtual ProckNodeType Type() { return PNT_DottedName; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNEllipsis : public ProckNode {
public: 
    virtual char *Name() { return "Ellipsis "; }
    virtual ProckNodeType Type() { return PNT_Ellipsis; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNElseAttribute : public ProckNode {
public: 
    virtual char *Name() { return "ElseAttribute "; }
    virtual ProckNodeType Type() { return PNT_ElseAttribute; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNEndl : public ProckNode {
public: 
    virtual char *Name() { return "Endl "; }
    virtual ProckNodeType Type() { return PNT_Endl; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNFloatExponantComplex : public ProckNode {
public: 
    virtual char *Name() { return "FloatExponantComplex "; }
    virtual ProckNodeType Type() { return PNT_FloatExponantComplex; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNFloatExponant : public ProckNode {
public: 
    virtual char *Name() { return "FloatExponant "; }
    virtual ProckNodeType Type() { return PNT_FloatExponant; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNFloat : public ProckNode {
public: 
    virtual char *Name() { return "Float "; }
    virtual ProckNodeType Type() { return PNT_Float; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNHexa : public ProckNode {
public: 
    virtual char *Name() { return "Hexa "; }
    virtual ProckNodeType Type() { return PNT_Hexa; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNIfElseBlockSibling : public ProckNode {
public: 
    virtual char *Name() { return "IfElseBlockSibling "; }
    virtual ProckNodeType Type() { return PNT_IfElseBlockSibling; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNInt : public ProckNode {
public: 
    virtual char *Name() { return "Int "; }
    virtual ProckNodeType Type() { return PNT_Int; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNLeftParenthesis : public ProckNode {
public: 
    virtual char *Name() { return "LeftParenthesis "; }
    virtual ProckNodeType Type() { return PNT_LeftParenthesis; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNLineProxyList : public ProckNode {
public: 
    virtual char *Name() { return "LineProxyList "; }
    virtual ProckNodeType Type() { return PNT_LineProxyList; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNLong : public ProckNode {
public: 
    virtual char *Name() { return "Long "; }
    virtual ProckNodeType Type() { return PNT_Long; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNName : public ProckNode {
public: 
    virtual char *Name() { return "Name "; }
    virtual ProckNodeType Type() { return PNT_Name; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNOcta : public ProckNode {
public: 
    virtual char *Name() { return "Octa "; }
    virtual ProckNodeType Type() { return PNT_Octa; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNPass : public ProckNode {
public: 
    virtual char *Name() { return "Pass "; }
    virtual ProckNodeType Type() { return PNT_Pass; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNRawString : public ProckNode {
public: 
    virtual char *Name() { return "RawString "; }
    virtual ProckNodeType Type() { return PNT_RawString; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNRightParenthesis : public ProckNode {
public: 
    virtual char *Name() { return "RightParenthesis "; }
    virtual ProckNodeType Type() { return PNT_RightParenthesis; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNSemicolon : public ProckNode {
public: 
    virtual char *Name() { return "Semicolon "; }
    virtual ProckNodeType Type() { return PNT_Semicolon; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNSpace : public ProckNode {
public: 
    virtual char *Name() { return "Space "; }
    virtual ProckNodeType Type() { return PNT_Space; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNStar : public ProckNode {
public: 
    virtual char *Name() { return "Star "; }
    virtual ProckNodeType Type() { return PNT_Star; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNString : public ProckNode {
public: 
    virtual char *Name() { return "String "; }
    virtual ProckNodeType Type() { return PNT_String; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNUnicodeRawString : public ProckNode {
public: 
    virtual char *Name() { return "UnicodeRawString "; }
    virtual ProckNodeType Type() { return PNT_UnicodeRawString; }

    char *Value() { return GetAsString("value"); }
};


class PROCKFPS_API PNUnicodeString : public ProckNode {
public: 
    virtual char *Name() { return "UnicodeString "; }
    virtual ProckNodeType Type() { return PNT_UnicodeString; }

    char *Value() { return GetAsString("value"); }
};
// End Generated Code
