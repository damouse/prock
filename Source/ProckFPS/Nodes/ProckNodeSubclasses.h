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
     'generators': <NodeList [0, 'value', 1, 'value', 0, 'generators'], " for y in z" 81372664, on ArgumentGeneratorComprehensionNode 81371992>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(x for y in z)" 81372272, on AtomtrailersNode 81275032>,
     'result': <NameNode path=[0, 'value', 1, 'value', 0, 'result'], "x" 81371320, on ArgumentGeneratorComprehensionNode 81371992>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81374848, on AssertNode 81374736>,
     'init': False,
     'message': <NameNode path=[0, 'message'], "message" 81374792, on AssertNode 81374736>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "assert test, message" 81374960, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81374512, on AssertNode 81374736>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 81374680, on AssertNode 81374736>,
     'type': 'assert',
     'value': <NameNode path=[0, 'value'], "test" 81375016, on AssertNode 81374736>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81466032, on AssignmentNode 81466144>,
     'init': False,
     'on_attribute': 'root',
     'operator': '',
     'parent': <RedBaron [], "a = b" 81374904, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81466200, on AssignmentNode 81466144>,
     'target': <NameNode path=[0, 'target'], "a" 81466256, on AssignmentNode 81466144>,
     'type': 'assignment',
     'value': <NameNode path=[0, 'value'], "b" 81466368, on AssignmentNode 81466144>}
    
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
This node represents a statement prioritised on another by being surrounded byparenthesis. For e.g., the first part of this addition: :file:`(1 + 1) * 2`.

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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81467208, on AssociativeParenthesisNode 81467264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81467432, on AssociativeParenthesisNode 81467264>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 81467096, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81466312, on AssociativeParenthesisNode 81467264>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81467488, on AssociativeParenthesisNode 81467264>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 81466480, on AssociativeParenthesisNode 81467264>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81467208, on AssociativeParenthesisNode 81467264>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81467432, on AssociativeParenthesisNode 81467264>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 81467096, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81466312, on AssociativeParenthesisNode 81467264>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81467488, on AssociativeParenthesisNode 81467264>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 81466480, on AssociativeParenthesisNode 81467264>}
    
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
     'parent': <RedBaron [], "0b10101" 81468216, on NoneType 1353870424>,
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
The node represents a binary operator (an operator (e.g.: :file:`+` :file:`-` :file:`/`..) applied to 2 values) with its operands. For e.g.: :file:`1 + 1`.

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
     'first': <IntNode path=[0, 'first'], "1" 81465752, on BinaryOperatorNode 81465808>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81466872, on BinaryOperatorNode 81465808>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "1 + 1" 81465472, on NoneType 1353870424>,
     'second': <IntNode path=[0, 'second'], "1" 81465920, on BinaryOperatorNode 81465808>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81465528, on BinaryOperatorNode 81465808>,
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
The node represents a boolean operator (an operator (e.g.: :file:`and` :file:`or`) applied to 2 values) with its operands. For e.g.: :file:`x and y`.

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
     'first': <NameNode path=[0, 'first'], "x" 81373448, on BooleanOperatorNode 81374456>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81373280, on BooleanOperatorNode 81374456>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 81465640, on NoneType 1353870424>,
     'second': <NameNode path=[0, 'second'], "y" 81777328, on BooleanOperatorNode 81374456>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81778728, on BooleanOperatorNode 81374456>,
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
     'first': <NameNode path=[0, 'first'], "x" 81373448, on BooleanOperatorNode 81374456>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81373280, on BooleanOperatorNode 81374456>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 81465640, on NoneType 1353870424>,
     'second': <NameNode path=[0, 'second'], "y" 81777328, on BooleanOperatorNode 81374456>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81778728, on BooleanOperatorNode 81374456>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 81816096, on CallArgumentNode 81816600>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 81817272, on AtomtrailersNode 81815872>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 81816936, on CallArgumentNode 81816600>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 81816376, on CallArgumentNode 81816600>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 81816096, on CallArgumentNode 81816600>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 81817272, on AtomtrailersNode 81815872>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 81816936, on CallArgumentNode 81816600>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 81816376, on CallArgumentNode 81816600>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 81469056, on CommaNode 81468608>,
     'init': False,
     'on_attribute': 'value',
     'parent': <ListNode path=[0], "[1, 2, 3]" 81374176, on RedBaron 81371432>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], " " 81469392, on CommaNode 81468608>,
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
     'first': <IntNode path=[0, 'first'], "42" 81779288, on ComparisonNode 81779624>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 81779904, on ComparisonNode 81779624>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "42 > 30" 81780184, on NoneType 1353870424>,
     'second': <IntNode path=[0, 'second'], "30" 81780128, on ComparisonNode 81779624>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81776712, on ComparisonNode 81779624>,
     'type': 'comparison',
     'value': <ComparisonOperatorNode path=[0, 'value'], ">" 81777104, on ComparisonNode 81779624>}
    
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
     'first_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'first_formatting'], " " 81859024, on ComprehensionIfNode 81861488>,
     'init': False,
     'on_attribute': 'ifs',
     'parent': <ComprehensionLoopNode path=[0, 'generators', 0], " for x in x if c...n" 81815536, on ListComprehensionNode 81860704>,
     'second_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'second_formatting'], " " 81859248, on ComprehensionIfNode 81861488>,
     'type': 'comprehension_if',
     'value': <NameNode path=[0, 'generators', 0, 'ifs', 0, 'value'], "condition" 81861656, on ComprehensionIfNode 81861488>}
    
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
     'first_formatting': <NodeList [0, 'generators', 0, 'first_formatting'], " " 81891736, on ComprehensionLoopNode 81862272>,
     'fourth_formatting': <NodeList [0, 'generators', 0, 'fourth_formatting'], " " 81892800, on ComprehensionLoopNode 81862272>,
     'ifs': <NodeList [0, 'generators', 0, 'ifs'], "" 81892968, on ComprehensionLoopNode 81862272>,
     'init': False,
     'iterator': <NameNode path=[0, 'generators', 0, 'iterator'], "y" 81892296, on ComprehensionLoopNode 81862272>,
     'on_attribute': 'generators',
     'parent': <ListComprehensionNode path=[0], "[x for y in z]" 81861880, on RedBaron 81860592>,
     'second_formatting': <NodeList [0, 'generators', 0, 'second_formatting'], " " 81891904, on ComprehensionLoopNode 81862272>,
     'target': <NameNode path=[0, 'generators', 0, 'target'], "z" 81892912, on ComprehensionLoopNode 81862272>,
     'third_formatting': <NodeList [0, 'generators', 0, 'third_formatting'], " " 81892688, on ComprehensionLoopNode 81862272>,
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 81862216, on DecoratorNode 81861824>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 81862496, on RedBaron 81892464>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 81860144, on DecoratorNode 81861824>}
    
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 81862216, on DecoratorNode 81861824>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 81862496, on RedBaron 81892464>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 81860144, on DecoratorNode 81861824>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 81960128, on DelNode 81960352>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "del stuff" 81959736, on NoneType 1353870424>,
     'type': 'del',
     'value': <NameNode path=[0, 'value'], "stuff" 81960184, on DelNode 81960352>}
    
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 81926968, on DictArgumentNode 81927192>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 81926688, on AtomtrailersNode 81927640>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 81927136, on DictArgumentNode 81927192>}
    
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 81926968, on DictArgumentNode 81927192>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 81926688, on AtomtrailersNode 81927640>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 81927136, on DictArgumentNode 81927192>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81960744, on DictComprehensionNode 81959680>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81779736, on DictComprehensionNode 81959680>,
     'generators': <NodeList [0, 'generators'], " for c in d" 81959176, on DictComprehensionNode 81959680>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 81994696, on NoneType 1353870424>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 81959064, on DictComprehensionNode 81959680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81960688, on DictComprehensionNode 81959680>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81959568, on DictComprehensionNode 81959680>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81960744, on DictComprehensionNode 81959680>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 81779736, on DictComprehensionNode 81959680>,
     'generators': <NodeList [0, 'generators'], " for c in d" 81959176, on DictComprehensionNode 81959680>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 81994696, on NoneType 1353870424>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 81959064, on DictComprehensionNode 81959680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 81960688, on DictComprehensionNode 81959680>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81959568, on DictComprehensionNode 81959680>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 82032736, on RedBaron 82034304>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 82032736, on RedBaron 82034304>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 82032736, on RedBaron 82034304>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 82032736, on RedBaron 82034304>,
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
A node representing an exec statement.

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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 82153200, on ExecNode 82152752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82152584, on ExecNode 82152752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82153144, on ExecNode 82152752>,
     'globals': <NameNode path=[0, 'globals'], "a" 82153088, on ExecNode 82152752>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 82153312, on ExecNode 82152752>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 81994080, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82152360, on ExecNode 82152752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82153032, on ExecNode 82152752>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 82152472, on ExecNode 82152752>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 82153200, on ExecNode 82152752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82152584, on ExecNode 82152752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82153144, on ExecNode 82152752>,
     'globals': <NameNode path=[0, 'globals'], "a" 82153088, on ExecNode 82152752>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 82153312, on ExecNode 82152752>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 81994080, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82152360, on ExecNode 82152752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82153032, on ExecNode 82152752>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 82152472, on ExecNode 82152752>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 82153200, on ExecNode 82152752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82152584, on ExecNode 82152752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82153144, on ExecNode 82152752>,
     'globals': <NameNode path=[0, 'globals'], "a" 82153088, on ExecNode 82152752>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 82153312, on ExecNode 82152752>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 81994080, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82152360, on ExecNode 82152752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82153032, on ExecNode 82152752>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 82152472, on ExecNode 82152752>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 82153200, on ExecNode 82152752>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82152584, on ExecNode 82152752>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82153144, on ExecNode 82152752>,
     'globals': <NameNode path=[0, 'globals'], "a" 82153088, on ExecNode 82152752>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 82153312, on ExecNode 82152752>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 81994080, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82152360, on ExecNode 82152752>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82153032, on ExecNode 82152752>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 82152472, on ExecNode 82152752>}
    
*/
class PROCKFPS_API PNFromImport : public ProckNode {
public: 
    virtual char *Name() { return "FromImport "; }
    virtual ProckNodeType Type() { return PNT_FromImport; }

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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 82584800, on GeneratorComprehensionNode 81993800>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82583736, on GeneratorComprehensionNode 81993800>,
     'generators': <NodeList [0, 'generators'], " for y in z" 82587600, on GeneratorComprehensionNode 81993800>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(x for y in z)" 81859696, on NoneType 1353870424>,
     'result': <NameNode path=[0, 'result'], "x" 82587488, on GeneratorComprehensionNode 81993800>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82585080, on GeneratorComprehensionNode 81993800>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 82584576, on GeneratorComprehensionNode 81993800>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 82258520, on GetitemNode 82257848>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 82259528, on GetitemNode 82257848>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 82583792, on RedBaron 82256280>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 82256336, on GetitemNode 82257848>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 82259024, on GetitemNode 82257848>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 82257792, on GetitemNode 82257848>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 82258520, on GetitemNode 82257848>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 82259528, on GetitemNode 82257848>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 82583792, on RedBaron 82256280>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 82256336, on GetitemNode 82257848>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 82259024, on GetitemNode 82257848>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 82257792, on GetitemNode 82257848>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 82258520, on GetitemNode 82257848>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 82259528, on GetitemNode 82257848>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 82583792, on RedBaron 82256280>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 82256336, on GetitemNode 82257848>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 82259024, on GetitemNode 82257848>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 82257792, on GetitemNode 82257848>}
    
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 82624128, on NoneType 1353870424>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 82622952, on IfelseblockNode 82624296>}
    
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 82624128, on NoneType 1353870424>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 82622952, on IfelseblockNode 82624296>}
    
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
     'arguments': <CommaProxyList [0, 'arguments'], "x" 82688992, on LambdaNode 82689384>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82689216, on LambdaNode 82689384>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "lambda x: y" 82688600, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82689664, on LambdaNode 82689384>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82689496, on LambdaNode 82689384>,
     'type': 'lambda',
     'value': <NameNode path=[0, 'value'], "y" 82689776, on LambdaNode 82689384>}
    
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
     'formatting': <NodeList [0, 'arguments', 0, 'formatting'], "" 82687200, on ListArgumentNode 82687536>,
     'init': False,
     'on_attribute': 'arguments',
     'parent': <DefNode path=[0], "def a(*b): pass\n" 82687368, on RedBaron 82688376>,
     'type': 'list_argument',
     'value': <NameNode path=[0, 'arguments', 0, 'value'], "b" 82686920, on ListArgumentNode 82687536>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 82621272, on ListComprehensionNode 82583680>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82725464, on ListComprehensionNode 82583680>,
     'generators': <NodeList [0, 'generators'], " for y in z" 82725184, on ListComprehensionNode 82583680>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 82620936, on NoneType 1353870424>,
     'result': <NameNode path=[0, 'result'], "x" 82724680, on ListComprehensionNode 82583680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82725128, on ListComprehensionNode 82583680>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 82723280, on ListComprehensionNode 82583680>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 82621272, on ListComprehensionNode 82583680>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82725464, on ListComprehensionNode 82583680>,
     'generators': <NodeList [0, 'generators'], " for y in z" 82725184, on ListComprehensionNode 82583680>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 82620936, on NoneType 1353870424>,
     'result': <NameNode path=[0, 'result'], "x" 82724680, on ListComprehensionNode 82583680>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82725128, on ListComprehensionNode 82583680>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 82723280, on ListComprehensionNode 82583680>,
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
     'parent': <FromImportNode path=[0], "from x import a as d" 82763336, on RedBaron 82763112>,
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
     'parent': <FromImportNode path=[0], "from x import a as d" 82763336, on RedBaron 82763112>,
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 82649888, on RaiseNode 82722944>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82724512, on RaiseNode 82722944>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82651064, on RaiseNode 82722944>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 82652072, on RaiseNode 82722944>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 82584072, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82724344, on RaiseNode 82722944>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82652296, on RaiseNode 82722944>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 82649328, on RaiseNode 82722944>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 82726080, on RaiseNode 82722944>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 82649888, on RaiseNode 82722944>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82724512, on RaiseNode 82722944>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82651064, on RaiseNode 82722944>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 82652072, on RaiseNode 82722944>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 82584072, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82724344, on RaiseNode 82722944>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82652296, on RaiseNode 82722944>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 82649328, on RaiseNode 82722944>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 82726080, on RaiseNode 82722944>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 82651624, on ReturnNode 82649272>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 82623848, on NoneType 1353870424>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 82259136, on ReturnNode 82649272>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 82651624, on ReturnNode 82649272>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 82623848, on NoneType 1353870424>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 82259136, on ReturnNode 82649272>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 82723392, on SetComprehensionNode 82650392>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 82726864, on SetComprehensionNode 82650392>,
     'generators': <NodeList [0, 'generators'], " for y in z" 82726360, on SetComprehensionNode 82650392>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{x for y in z}" 82231136, on NoneType 1353870424>,
     'result': <NameNode path=[0, 'result'], "x" 82724176, on SetComprehensionNode 82650392>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 82726584, on SetComprehensionNode 82650392>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 82725520, on SetComprehensionNode 82650392>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 'first_formatting'], "" 82183896, on SliceNode 82183392>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'value', 'fourth_formatting'], "" 82183112, on SliceNode 82183392>,
     'has_two_colons': True,
     'init': False,
     'lower': <IntNode path=[0, 'value', 1, 'value', 'lower'], "1" 82183280, on SliceNode 82183392>,
     'on_attribute': 'value',
     'parent': <GetitemNode path=[0, 'value', 1], "[1:-1:2]" 82183560, on AtomtrailersNode 82762496>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 'second_formatting'], "" 82184344, on SliceNode 82183392>,
     'step': <IntNode path=[0, 'value', 1, 'value', 'step'], "2" 82182384, on SliceNode 82183392>,
     'third_formatting': <NodeList [0, 'value', 1, 'value', 'third_formatting'], "" 82183336, on SliceNode 82183392>,
     'type': 'slice',
     'upper': <UnitaryOperatorNode path=[0, 'value', 1, 'value', 'upper'], "-1" 82762944, on SliceNode 82183392>}
    
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
     'parent': <RedBaron [], "'a' r'b' b'c'" 82151632, on NoneType 1353870424>,
     'type': 'string_chain',
     'value': <NodeList [0, 'value'], "'a' r'b' b'c'" 82104728, on StringChainNode 82105792>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 82150904, on TernaryOperatorNode 82151352>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82184792, on TernaryOperatorNode 82151352>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 82183448, on TernaryOperatorNode 82151352>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 82151296, on NoneType 1353870424>,
     'second': <NameNode path=[0, 'second'], "c" 82183224, on TernaryOperatorNode 82151352>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82183840, on TernaryOperatorNode 82151352>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82182496, on TernaryOperatorNode 82151352>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 82184064, on TernaryOperatorNode 82151352>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 82150904, on TernaryOperatorNode 82151352>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82184792, on TernaryOperatorNode 82151352>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 82183448, on TernaryOperatorNode 82151352>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 82151296, on NoneType 1353870424>,
     'second': <NameNode path=[0, 'second'], "c" 82183224, on TernaryOperatorNode 82151352>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82183840, on TernaryOperatorNode 82151352>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82182496, on TernaryOperatorNode 82151352>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 82184064, on TernaryOperatorNode 82151352>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 82150904, on TernaryOperatorNode 82151352>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 82184792, on TernaryOperatorNode 82151352>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 82183448, on TernaryOperatorNode 82151352>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 82151296, on NoneType 1353870424>,
     'second': <NameNode path=[0, 'second'], "c" 82183224, on TernaryOperatorNode 82151352>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 82183840, on TernaryOperatorNode 82151352>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 82182496, on TernaryOperatorNode 82151352>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 82184064, on TernaryOperatorNode 82151352>}
    
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
     'formatting': <NodeList [0, 'formatting'], "" 82763056, on UnitaryOperatorNode 82182328>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "-1" 82184624, on NoneType 1353870424>,
     'target': <IntNode path=[0, 'target'], "1" 82762608, on UnitaryOperatorNode 82182328>,
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
     'formatting': <NodeList [0, 'formatting'], " " 81894256, on YieldNode 82762048>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "yield 42" 82760592, on NoneType 1353870424>,
     'type': 'yield',
     'value': <IntNode path=[0, 'value'], "42" 81893640, on YieldNode 82762048>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81891512, on YieldAtomNode 81895376>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 81891792, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81893752, on YieldAtomNode 81895376>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81891624, on YieldAtomNode 81895376>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 81895264, on YieldAtomNode 81895376>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 81891512, on YieldAtomNode 81895376>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 81891792, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 81893752, on YieldAtomNode 81895376>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 81891624, on YieldAtomNode 81895376>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 81895264, on YieldAtomNode 81895376>}
    
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 82785056, on WithContextItemNode 82787856>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 82786008, on WithContextItemNode 82787856>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 82786064, on RedBaron 82785672>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 82785784, on WithContextItemNode 82787856>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 82785840, on WithContextItemNode 82787856>}
    
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 82785056, on WithContextItemNode 82787856>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 82786008, on WithContextItemNode 82787856>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 82786064, on RedBaron 82785672>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 82785784, on WithContextItemNode 82787856>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 82785840, on WithContextItemNode 82787856>}
    
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

// Start custom overrides
/*
A node representing a function definition.

Equivalent python:

    def stuff(a, b):\n    return a + b\n

RedBaron .help() text:

    DefNode()
      name='stuff'
      decorators ->
      arguments ->
        * DefArgumentNode()
            target ->
              NameNode()
                value='a'
            value ->
              None
        * DefArgumentNode()
            target ->
              NameNode()
                value='b'
            value ->
              None
      value ->
        * ReturnNode()
            value ->
              BinaryOperatorNode()
                value='+'
                first ->
                  NameNode()
                    value='a'
                second ->
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 73830128, on ExecNode 73829680>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 73829512, on ExecNode 73829680>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 73830072, on ExecNode 73829680>,
     'globals': <NameNode path=[0, 'globals'], "a" 73830016, on ExecNode 73829680>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 73830240, on ExecNode 73829680>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 73671008, on NoneType 1353870424>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 73829288, on ExecNode 73829680>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 73829960, on ExecNode 73829680>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 73829400, on ExecNode 73829680>}
    
*/

class PROCKFPS_API PNDef : public ProckNode {
public: 
    virtual char *Name() { return "PNDef\0"; }
    virtual ProckNodeType Type() { return PNT_Def; }

	// Name of this function 
	char *Title() { return GetAsString("name"); }
    
	// PNDefArgs (?)
	std::vector<ProckNode *> *ArgumentList() { return GetAsList("arguments"); }
	std::vector<ProckNode *> *DecoratorList() { return GetAsList("decorators"); }
	std::vector<ProckNode *> *NodeList() { return GetAsList("value"); }

	// The return node lives inside the codelist of the function, not as part of the function itself
	//PNReturn *Return() { return (PNReturn *) GetAsNode("value"); }
};

// NOTE: There was a Def node and a Funcdef node. Dont forget: you replaced the first one with the 
// implementation of the second: might need to reimplement Funcdef. Is that for methods?