#pragma once

#include "BoxActor.h"
#include "PythonBindings.h"
#include <map>

// The type of each node, used to test for type before casts. This is instead of using dynaic_cast, 
// which requires RTTI and incurs a performance overhead
enum ProckNodeType : int;

/**
 * Abstract base class for all ProckNodes. A ProckNode "glues" a BoxActor to a native
 * Python AST Node as returned by RedBaron: it is neither an actor or an AST node, 
 * but it wraps AST nodes and spawns Boxes to represent them as needed.
 */
class PROCKFPS_API ProckNode {
public:
	//virtual ~ProckNode();
	// Factory Method: creates the appropriate ProckNode subclass based on the given PyObject. 
	// Don't use the default constructor to create new ProckNodes!
	static ProckNode* NewNode(PyObject* astNode);

	// Spawn box for this node at the given position and spawn children recursively
	// The base implementation of this method simply spawns the box with labels for maxiumum information
	void Spawn(UWorld *world, FVector pos);

	// Dump the underlying python object. Equivalent to python: str(obj)
	void PrintRaw();

	// Return this class name without the leading 'PN'
	virtual char *Name();

	// Return the enumerated type for this node. Use this to check type instead of c++ casts
	virtual ProckNodeType Type();

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

enum ProckNodeType {
    PNT_Base,
	PNT_ArgumentGeneratorComprehension,
	PNT_Assert,
	PNT_Assignment,
	PNT_AssociativeParenthesis,
	PNT_Atomtrailers,
	PNT_Binary,
	PNT_BinaryOperator,
	PNT_BooleanOperator,
	PNT_Call,
	PNT_CallArgument,
	PNT_Class,
	PNT_Comma,
	PNT_Comparison,
	PNT_ComprehensionIf,
	PNT_ComprehensionLoop,
	PNT_Decorator,
	PNT_DefArgument,
	PNT_Del,
	PNT_DictArgument,
	PNT_Dict,
	PNT_DictComprehension,
	PNT_DottedAsName,
	PNT_Dot,
	PNT_Elif,
	PNT_Else,
	PNT_Except,
	PNT_Exec,
	PNT_Finally,
	PNT_For,
	PNT_FromImport,
	PNT_Funcdef,
	PNT_GeneratorComprehension,
	PNT_Getitem,
	PNT_Global,
	PNT_If,
	PNT_Ifelseblock,
	PNT_Import,
	PNT_Lambda,
	PNT_ListArgument,
	PNT_ListComprehension,
	PNT_List,
	PNT_NameAsName,
	PNT_Print,
	PNT_Raise,
	PNT_Repr,
	PNT_Return,
	PNT_Set,
	PNT_SetComprehension,
	PNT_Slice,
	PNT_StringChain,
	PNT_TernaryOperator,
	PNT_Try,
	PNT_Tuple,
	PNT_UnitaryOperator,
	PNT_Yield,
	PNT_YieldAtom,
	PNT_While,
	PNT_WithContextItem,
	PNT_With,
	PNT_BinaryRawString,
	PNT_BinaryString,
	PNT_Break,
	PNT_CodeBlock,
	PNT_CommaProxyList,
	PNT_Comment,
	PNT_ComparisonOperator,
	PNT_Complex,
	PNT_Continue,
	PNT_Def,
	PNT_Dictitem,
	PNT_DotProxyList,
	PNT_DottedName,
	PNT_Ellipsis,
	PNT_ElseAttribute,
	PNT_Endl,
	PNT_FloatExponantComplex,
	PNT_FloatExponant,
	PNT_Float,
	PNT_Hexa,
	PNT_IfElseBlockSibling,
	PNT_Int,
	PNT_LeftParenthesis,
	PNT_LineProxyList,
	PNT_Long,
	PNT_Name,
	PNT_Octa,
	PNT_Pass,
	PNT_RawString,
	PNT_RightParenthesis,
	PNT_Semicolon,
	PNT_Space,
	PNT_Star,
	PNT_String,
	PNT_UnicodeRawString,
	PNT_UnicodeString,
};

// Begin Node Definition

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
     'generators': <NodeList [0, 'value', 1, 'value', 0, 'generators'], " for y in z" 69152720, on ArgumentGeneratorComprehensionNode 69152104>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(x for y in z)" 69152384, on AtomtrailersNode 69149304>,
     'result': <NameNode path=[0, 'value', 1, 'value', 0, 'result'], "x" 69152664, on ArgumentGeneratorComprehensionNode 69152104>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 69220448, on AssertNode 69220616>,
     'init': False,
     'message': <NameNode path=[0, 'message'], "message" 69220392, on AssertNode 69220616>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "assert test, message" 69220280, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 69220672, on AssertNode 69220616>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 69220728, on AssertNode 69220616>,
     'type': 'assert',
     'value': <NameNode path=[0, 'value'], "test" 69220896, on AssertNode 69220616>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], " " 69150872, on AssignmentNode 69150592>,
     'init': False,
     'on_attribute': 'root',
     'operator': '',
     'parent': <RedBaron [], "a = b" 69151096, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 69150984, on AssignmentNode 69150592>,
     'target': <NameNode path=[0, 'target'], "a" 69148912, on AssignmentNode 69150592>,
     'type': 'assignment',
     'value': <NameNode path=[0, 'value'], "b" 69150424, on AssignmentNode 69150592>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 69149640, on AssociativeParenthesisNode 69149808>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 69219888, on AssociativeParenthesisNode 69149808>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 69139368, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 69152608, on AssociativeParenthesisNode 69149808>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 69150704, on AssociativeParenthesisNode 69149808>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 69149752, on AssociativeParenthesisNode 69149808>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 69149640, on AssociativeParenthesisNode 69149808>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 69219888, on AssociativeParenthesisNode 69149808>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(foo)" 69139368, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 69152608, on AssociativeParenthesisNode 69149808>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 69150704, on AssociativeParenthesisNode 69149808>,
     'type': 'associative_parenthesis',
     'value': <NameNode path=[0, 'value'], "foo" 69149752, on AssociativeParenthesisNode 69149808>}
    
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
     'parent': <RedBaron [], "0b10101" 69390176, on NoneType 1962241112>,
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
     'first': <IntNode path=[0, 'first'], "1" 69424072, on BinaryOperatorNode 69423176>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 69423904, on BinaryOperatorNode 69423176>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "1 + 1" 69388104, on NoneType 1962241112>,
     'second': <IntNode path=[0, 'second'], "1" 69424352, on BinaryOperatorNode 69423176>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 69424408, on BinaryOperatorNode 69423176>,
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
     'first': <NameNode path=[0, 'first'], "x" 69425696, on BooleanOperatorNode 69424576>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 69425192, on BooleanOperatorNode 69424576>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 69425304, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "y" 69389840, on BooleanOperatorNode 69424576>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 69390288, on BooleanOperatorNode 69424576>,
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
     'first': <NameNode path=[0, 'first'], "x" 69425696, on BooleanOperatorNode 69424576>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 69425192, on BooleanOperatorNode 69424576>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "x and y" 69425304, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "y" 69389840, on BooleanOperatorNode 69424576>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 69390288, on BooleanOperatorNode 69424576>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 69457344, on CallArgumentNode 69426536>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 69456840, on AtomtrailersNode 69423400>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 69457568, on CallArgumentNode 69426536>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 69457008, on CallArgumentNode 69426536>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 0, 'first_formatting'], "" 69457344, on CallArgumentNode 69426536>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(b, c=d)" 69456840, on AtomtrailersNode 69423400>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 0, 'second_formatting'], "" 69457568, on CallArgumentNode 69426536>,
     'target': None,
     'type': 'call_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 69457008, on CallArgumentNode 69426536>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 69486464, on CommaNode 69487136>,
     'init': False,
     'on_attribute': 'value',
     'parent': <ListNode path=[0], "[1, 2, 3]" 69486744, on RedBaron 69426088>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], " " 69487248, on CommaNode 69487136>,
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
     'first': <IntNode path=[0, 'first'], "42" 69522152, on ComparisonNode 69521704>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 69521928, on ComparisonNode 69521704>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "42 > 30" 69486856, on NoneType 1962241112>,
     'second': <IntNode path=[0, 'second'], "30" 69522264, on ComparisonNode 69521704>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 69521872, on ComparisonNode 69521704>,
     'type': 'comparison',
     'value': <ComparisonOperatorNode path=[0, 'value'], ">" 69488368, on ComparisonNode 69521704>}
    
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
     'first_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'first_formatting'], " " 69485512, on ComprehensionIfNode 69486016>,
     'init': False,
     'on_attribute': 'ifs',
     'parent': <ComprehensionLoopNode path=[0, 'generators', 0], " for x in x if c...n" 69488312, on ListComprehensionNode 69485736>,
     'second_formatting': <NodeList [0, 'generators', 0, 'ifs', 0, 'second_formatting'], " " 69485344, on ComprehensionIfNode 69486016>,
     'type': 'comprehension_if',
     'value': <NameNode path=[0, 'generators', 0, 'ifs', 0, 'value'], "condition" 69485232, on ComprehensionIfNode 69486016>}
    
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
     'first_formatting': <NodeList [0, 'generators', 0, 'first_formatting'], " " 69524448, on ComprehensionLoopNode 69426312>,
     'fourth_formatting': <NodeList [0, 'generators', 0, 'fourth_formatting'], " " 69525120, on ComprehensionLoopNode 69426312>,
     'ifs': <NodeList [0, 'generators', 0, 'ifs'], "" 69525288, on ComprehensionLoopNode 69426312>,
     'init': False,
     'iterator': <NameNode path=[0, 'generators', 0, 'iterator'], "y" 69524560, on ComprehensionLoopNode 69426312>,
     'on_attribute': 'generators',
     'parent': <ListComprehensionNode path=[0], "[x for y in z]" 69389784, on RedBaron 69488480>,
     'second_formatting': <NodeList [0, 'generators', 0, 'second_formatting'], " " 69522096, on ComprehensionLoopNode 69426312>,
     'target': <NameNode path=[0, 'generators', 0, 'target'], "z" 69525232, on ComprehensionLoopNode 69426312>,
     'third_formatting': <NodeList [0, 'generators', 0, 'third_formatting'], " " 69525008, on ComprehensionLoopNode 69426312>,
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 69557832, on DecoratorNode 69557944>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 69558168, on RedBaron 69524784>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 69558056, on DecoratorNode 69557944>}
    
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
     'call': <CallNode path=[0, 'decorators', 0, 'call'], "(*a)" 69557832, on DecoratorNode 69557944>,
     'init': False,
     'on_attribute': 'decorators',
     'parent': <DefNode path=[0], "@stuff.plop(*a)\...n" 69558168, on RedBaron 69524784>,
     'type': 'decorator',
     'value': <DottedNameNode path=[0, 'decorators', 0, 'value'], "stuff.plop" 69558056, on DecoratorNode 69557944>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 72638928, on DelNode 72639096>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "del stuff" 69425920, on NoneType 1962241112>,
     'type': 'del',
     'value': <NameNode path=[0, 'value'], "stuff" 72638984, on DelNode 72639096>}
    
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 72641560, on DictArgumentNode 72639656>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 72641168, on AtomtrailersNode 72639208>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 72641448, on DictArgumentNode 72639656>}
    
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
     'formatting': <NodeList [0, 'value', 1, 'value', 0, 'formatting'], "" 72641560, on DictArgumentNode 72639656>,
     'init': False,
     'on_attribute': 'value',
     'parent': <CallNode path=[0, 'value', 1], "(**b)" 72641168, on AtomtrailersNode 72639208>,
     'type': 'dict_argument',
     'value': <NameNode path=[0, 'value', 1, 'value', 0, 'value'], "b" 72641448, on DictArgumentNode 72639656>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 72598920, on DictComprehensionNode 69556544>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72600208, on DictComprehensionNode 69556544>,
     'generators': <NodeList [0, 'generators'], " for c in d" 72598752, on DictComprehensionNode 69556544>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 69556488, on NoneType 1962241112>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 72599480, on DictComprehensionNode 69556544>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 72599256, on DictComprehensionNode 69556544>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 72599536, on DictComprehensionNode 69556544>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 72598920, on DictComprehensionNode 69556544>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72600208, on DictComprehensionNode 69556544>,
     'generators': <NodeList [0, 'generators'], " for c in d" 72598752, on DictComprehensionNode 69556544>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{a: b for c in d}" 69556488, on NoneType 1962241112>,
     'result': <DictitemNode path=[0, 'result'], "a: b" 72599480, on DictComprehensionNode 69556544>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 72599256, on DictComprehensionNode 69556544>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 72599536, on DictComprehensionNode 69556544>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 72597968, on RedBaron 72704520>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 72597968, on RedBaron 72704520>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 72597968, on RedBaron 72704520>,
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
     'parent': <AtomtrailersNode path=[0], "a.b" 72597968, on RedBaron 72704520>,
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 72598024, on ExecNode 72642120>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 72641392, on ExecNode 72642120>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72597744, on ExecNode 72642120>,
     'globals': <NameNode path=[0, 'globals'], "a" 72597800, on ExecNode 72642120>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 72597576, on ExecNode 72642120>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 72639320, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 72599032, on ExecNode 72642120>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 72600936, on ExecNode 72642120>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 72597632, on ExecNode 72642120>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 72598024, on ExecNode 72642120>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 72641392, on ExecNode 72642120>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72597744, on ExecNode 72642120>,
     'globals': <NameNode path=[0, 'globals'], "a" 72597800, on ExecNode 72642120>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 72597576, on ExecNode 72642120>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 72639320, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 72599032, on ExecNode 72642120>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 72600936, on ExecNode 72642120>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 72597632, on ExecNode 72642120>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 72598024, on ExecNode 72642120>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 72641392, on ExecNode 72642120>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72597744, on ExecNode 72642120>,
     'globals': <NameNode path=[0, 'globals'], "a" 72597800, on ExecNode 72642120>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 72597576, on ExecNode 72642120>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 72639320, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 72599032, on ExecNode 72642120>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 72600936, on ExecNode 72642120>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 72597632, on ExecNode 72642120>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 72598024, on ExecNode 72642120>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 72641392, on ExecNode 72642120>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72597744, on ExecNode 72642120>,
     'globals': <NameNode path=[0, 'globals'], "a" 72597800, on ExecNode 72642120>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 72597576, on ExecNode 72642120>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 72639320, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 72599032, on ExecNode 72642120>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 72600936, on ExecNode 72642120>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 72597632, on ExecNode 72642120>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 72598024, on ExecNode 72642120>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 72641392, on ExecNode 72642120>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72597744, on ExecNode 72642120>,
     'globals': <NameNode path=[0, 'globals'], "a" 72597800, on ExecNode 72642120>,
     'init': False,
     'locals': <NameNode path=[0, 'locals'], "b" 72597576, on ExecNode 72642120>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "exec '1 + 1' in a, b" 72639320, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 72599032, on ExecNode 72642120>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 72600936, on ExecNode 72642120>,
     'type': 'exec',
     'value': <StringNode path=[0, 'value'], "'1 + 1'" 72597632, on ExecNode 72642120>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 72821168, on GeneratorComprehensionNode 72821056>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 72822288, on GeneratorComprehensionNode 72821056>,
     'generators': <NodeList [0, 'generators'], " for y in z" 72821336, on GeneratorComprehensionNode 72821056>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(x for y in z)" 69557664, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 72821392, on GeneratorComprehensionNode 72821056>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 72821952, on GeneratorComprehensionNode 72821056>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 72821504, on GeneratorComprehensionNode 72821056>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 73131176, on GetitemNode 73130672>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 73131568, on GetitemNode 73130672>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 72822568, on RedBaron 72821840>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 73130952, on GetitemNode 73130672>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 73131512, on GetitemNode 73130672>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 73131008, on GetitemNode 73130672>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 73131176, on GetitemNode 73130672>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 73131568, on GetitemNode 73130672>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 72822568, on RedBaron 72821840>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 73130952, on GetitemNode 73130672>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 73131512, on GetitemNode 73130672>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 73131008, on GetitemNode 73130672>}
    
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
     'first_formatting': <NodeList [0, 'value', 1, 'first_formatting'], "" 73131176, on GetitemNode 73130672>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'fourth_formatting'], "" 73131568, on GetitemNode 73130672>,
     'init': False,
     'on_attribute': 'value',
     'parent': <AtomtrailersNode path=[0], "a[b]" 72822568, on RedBaron 72821840>,
     'second_formatting': <NodeList [0, 'value', 1, 'second_formatting'], "" 73130952, on GetitemNode 73130672>,
     'third_formatting': <NodeList [0, 'value', 1, 'third_formatting'], "" 73131512, on GetitemNode 73130672>,
     'type': 'getitem',
     'value': <NameNode path=[0, 'value', 1, 'value'], "b" 73131008, on GetitemNode 73130672>}
    
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 73130560, on NoneType 1962241112>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 73164840, on IfelseblockNode 73162992>}
    
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
     'parent': <RedBaron [], "if a: pass\nelif...n" 73130560, on NoneType 1962241112>,
     'type': 'ifelseblock',
     'value': <NodeList [0, 'value'], "if a: pass\nelif...n" 73164840, on IfelseblockNode 73162992>}
    
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
     'arguments': <CommaProxyList [0, 'arguments'], "x" 72818928, on LambdaNode 72820328>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 72820776, on LambdaNode 72820328>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "lambda x: y" 72820496, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 72822456, on LambdaNode 72820328>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 72819096, on LambdaNode 72820328>,
     'type': 'lambda',
     'value': <NameNode path=[0, 'value'], "y" 73130224, on LambdaNode 72820328>}
    
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
     'formatting': <NodeList [0, 'arguments', 0, 'formatting'], "" 73207704, on ListArgumentNode 73205184>,
     'init': False,
     'on_attribute': 'arguments',
     'parent': <DefNode path=[0], "def a(*b): pass\n" 73206920, on RedBaron 72821000>,
     'type': 'list_argument',
     'value': <NameNode path=[0, 'arguments', 0, 'value'], "b" 73207760, on ListArgumentNode 73205184>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 73235648, on ListComprehensionNode 73233688>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 73235984, on ListComprehensionNode 73233688>,
     'generators': <NodeList [0, 'generators'], " for y in z" 73234920, on ListComprehensionNode 73233688>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 73207256, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 73235704, on ListComprehensionNode 73233688>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 73235144, on ListComprehensionNode 73233688>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 73235088, on ListComprehensionNode 73233688>,
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 73235648, on ListComprehensionNode 73233688>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 73235984, on ListComprehensionNode 73233688>,
     'generators': <NodeList [0, 'generators'], " for y in z" 73234920, on ListComprehensionNode 73233688>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "[x for y in z]" 73207256, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 73235704, on ListComprehensionNode 73233688>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 73235144, on ListComprehensionNode 73233688>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 73235088, on ListComprehensionNode 73233688>,
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
     'parent': <FromImportNode path=[0], "from x import a as d" 69457288, on RedBaron 73206864>,
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
     'parent': <FromImportNode path=[0], "from x import a as d" 69457288, on RedBaron 73206864>,
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 73270328, on RaiseNode 73272960>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 73273240, on RaiseNode 73272960>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 73269656, on RaiseNode 73272960>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 73271896, on RaiseNode 73272960>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 73271280, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 73273128, on RaiseNode 73272960>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 73272120, on RaiseNode 73272960>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 73270440, on RaiseNode 73272960>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 73272008, on RaiseNode 73272960>}
    
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
     'fifth_formatting': <NodeList [0, 'fifth_formatting'], " " 73270328, on RaiseNode 73272960>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 73273240, on RaiseNode 73272960>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 73269656, on RaiseNode 73272960>,
     'init': False,
     'instance': <NameNode path=[0, 'instance'], "foo" 73271896, on RaiseNode 73272960>,
     'on_attribute': 'root',
     'parent': <RedBaron [], "raise Exception(...r" 73271280, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 73273128, on RaiseNode 73272960>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 73272120, on RaiseNode 73272960>,
     'traceback': <NameNode path=[0, 'traceback'], "bar" 73270440, on RaiseNode 73272960>,
     'type': 'raise',
     'value': <AtomtrailersNode path=[0, 'value'], "Exception()" 73272008, on RaiseNode 73272960>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 73204848, on ReturnNode 73204792>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 69522600, on NoneType 1962241112>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 73204064, on ReturnNode 73204792>}
    
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
     'formatting': <NodeList [0, 'formatting'], " " 73204848, on ReturnNode 73204792>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "return stuff" 69522600, on NoneType 1962241112>,
     'type': 'return',
     'value': <NameNode path=[0, 'value'], "stuff" 73204064, on ReturnNode 73204792>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 73348096, on SetComprehensionNode 73305056>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], "" 73348432, on SetComprehensionNode 73305056>,
     'generators': <NodeList [0, 'generators'], " for y in z" 73347368, on SetComprehensionNode 73305056>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "{x for y in z}" 73304048, on NoneType 1962241112>,
     'result': <NameNode path=[0, 'result'], "x" 73348152, on SetComprehensionNode 73305056>,
     'second_formatting': <NodeList [0, 'second_formatting'], "" 73347592, on SetComprehensionNode 73305056>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 73347536, on SetComprehensionNode 73305056>,
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
     'first_formatting': <NodeList [0, 'value', 1, 'value', 'first_formatting'], "" 73303264, on SliceNode 73302144>,
     'fourth_formatting': <NodeList [0, 'value', 1, 'value', 'fourth_formatting'], "" 73205632, on SliceNode 73302144>,
     'has_two_colons': True,
     'init': False,
     'lower': <IntNode path=[0, 'value', 1, 'value', 'lower'], "1" 73302312, on SliceNode 73302144>,
     'on_attribute': 'value',
     'parent': <GetitemNode path=[0, 'value', 1], "[1:-1:2]" 73303096, on AtomtrailersNode 73306008>,
     'second_formatting': <NodeList [0, 'value', 1, 'value', 'second_formatting'], "" 73204344, on SliceNode 73302144>,
     'step': <IntNode path=[0, 'value', 1, 'value', 'step'], "2" 73205072, on SliceNode 73302144>,
     'third_formatting': <NodeList [0, 'value', 1, 'value', 'third_formatting'], "" 73206080, on SliceNode 73302144>,
     'type': 'slice',
     'upper': <UnitaryOperatorNode path=[0, 'value', 1, 'value', 'upper'], "-1" 73204400, on SliceNode 73302144>}
    
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
     'parent': <RedBaron [], "'a' r'b' b'c'" 73349664, on NoneType 1962241112>,
     'type': 'string_chain',
     'value': <NodeList [0, 'value'], "'a' r'b' b'c'" 73349384, on StringChainNode 73350448>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 73389168, on TernaryOperatorNode 73351008>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 73389336, on TernaryOperatorNode 73351008>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 73388944, on TernaryOperatorNode 73351008>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 73350112, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 73389504, on TernaryOperatorNode 73351008>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 73389000, on TernaryOperatorNode 73351008>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 73389056, on TernaryOperatorNode 73351008>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 73389392, on TernaryOperatorNode 73351008>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 73389168, on TernaryOperatorNode 73351008>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 73389336, on TernaryOperatorNode 73351008>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 73388944, on TernaryOperatorNode 73351008>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 73350112, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 73389504, on TernaryOperatorNode 73351008>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 73389000, on TernaryOperatorNode 73351008>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 73389056, on TernaryOperatorNode 73351008>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 73389392, on TernaryOperatorNode 73351008>}
    
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
     'first': <NameNode path=[0, 'first'], "a" 73389168, on TernaryOperatorNode 73351008>,
     'first_formatting': <NodeList [0, 'first_formatting'], " " 73389336, on TernaryOperatorNode 73351008>,
     'fourth_formatting': <NodeList [0, 'fourth_formatting'], " " 73388944, on TernaryOperatorNode 73351008>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "a if b else c" 73350112, on NoneType 1962241112>,
     'second': <NameNode path=[0, 'second'], "c" 73389504, on TernaryOperatorNode 73351008>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 73389000, on TernaryOperatorNode 73351008>,
     'third_formatting': <NodeList [0, 'third_formatting'], " " 73389056, on TernaryOperatorNode 73351008>,
     'type': 'ternary_operator',
     'value': <NameNode path=[0, 'value'], "b" 73389392, on TernaryOperatorNode 73351008>}
    
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
     'formatting': <NodeList [0, 'formatting'], "" 73464632, on UnitaryOperatorNode 73464688>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "-1" 73464744, on NoneType 1962241112>,
     'target': <IntNode path=[0, 'target'], "1" 73464968, on UnitaryOperatorNode 73464688>,
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
     'formatting': <NodeList [0, 'formatting'], " " 73432256, on YieldNode 73432144>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "yield 42" 73432312, on NoneType 1962241112>,
     'type': 'yield',
     'value': <IntNode path=[0, 'value'], "42" 73431472, on YieldNode 73432144>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 73350896, on YieldAtomNode 73270496>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 73234752, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 73347256, on YieldAtomNode 73270496>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 73350392, on YieldAtomNode 73270496>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 73348040, on YieldAtomNode 73270496>}
    
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
     'first_formatting': <NodeList [0, 'first_formatting'], "" 73350896, on YieldAtomNode 73270496>,
     'init': False,
     'on_attribute': 'root',
     'parent': <RedBaron [], "(yield 42)" 73234752, on NoneType 1962241112>,
     'second_formatting': <NodeList [0, 'second_formatting'], " " 73347256, on YieldAtomNode 73270496>,
     'third_formatting': <NodeList [0, 'third_formatting'], "" 73350392, on YieldAtomNode 73270496>,
     'type': 'yield_atom',
     'value': <IntNode path=[0, 'value'], "42" 73348040, on YieldAtomNode 73270496>}
    
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 73501776, on WithContextItemNode 73499368>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 73501160, on WithContextItemNode 73499368>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 73500992, on RedBaron 73498752>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 73501048, on WithContextItemNode 73499368>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 73501272, on WithContextItemNode 73499368>}
    
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
     'as': <NameNode path=[0, 'contexts', 0, 'as'], "b" 73501776, on WithContextItemNode 73499368>,
     'first_formatting': <NodeList [0, 'contexts', 0, 'first_formatting'], " " 73501160, on WithContextItemNode 73499368>,
     'init': False,
     'on_attribute': 'contexts',
     'parent': <WithNode path=[0], "with a as b: pass\n" 73500992, on RedBaron 73498752>,
     'second_formatting': <NodeList [0, 'contexts', 0, 'second_formatting'], " " 73501048, on WithContextItemNode 73499368>,
     'type': 'with_context_item',
     'value': <NameNode path=[0, 'contexts', 0, 'value'], "a" 73501272, on WithContextItemNode 73499368>}
    
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
