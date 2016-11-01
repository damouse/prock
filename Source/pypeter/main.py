'''
Python "native" portion of the processor script. Called directly by the engine on startup, should bootstrap the 
environment and do imports as needed. 
'''

import json

from redbaron.nodes import *
from redbaron import RedBaron

from utils import log


def load_file(path):
    '''
    Load the file by opening it as opposed to importing it. 
    '''
    with open(path, "r") as source_code:
        ast = RedBaron(source_code.read())

    return ast


def import_file(s):
    '''
    Directly import the python code instead of loading the file. Should work, 
    but doesn't-- redbaron is not happy with that
    '''
    # import sys
    # sys.path.insert(0, u'../../../../../../Code/unreal/ProckFPS 4.13/')

    # # Import the target module directly. Much better way to do things so that local dependencies resolve...
    # import samplecode
    # ue.log(samplecode)
    pass


def to_source(ast):
    '''
    Turn the given AST to formatted source code.
    Returns a list of strings.
    '''
    return [str(x) for x in ast]


def to_json(ast):
    ''' returns the full AST as formatted json '''
    return json.dumps(ast.fst(), indent=4)


def load_source(path="../../../../../../Code/unreal/Prock/samplecode.py"):
    '''
    Load the source code. Note that we should be taking arguments here eventually. 
    Hardcoded for now.
    '''
    ast = load_file(path)
    return [x for x in ast]


def test_source(path):
    ''' A demo function here to play with the AST graph '''

    ast = load_file(path)
    import pprint
    pprint.pprint(ast.__dict__)
    # print ast.__class__
    return

    # Below are some random examples on how you could interact with the AST once its loaded
    # Example for turning the ast back to source
    # for x in nast.to_source(ast):
    #     log(x)

    # Example for turning the ast to json
    # log('\nPrinting full AST: ' + nast.to_json(ast))

    '''
    Common child names for a given node type: 
        assignment:             target
        binaryOperatorNode:     first, second
        if, else:               test, value
        while:                  test, else

    The following nodes leaf nodes:
        Int, Name

    if/else has a list under its value key
    '''

    for x in ast:
        if x.type in ["comment", "endl"]:
            continue

        print x.__dict__
        print ""
        # Note that every node has _dict_keys, _str_keys, and _list_keys which define its attrs
        print x._dict_keys
        print x._str_keys
        print x._list_keys
        print ""

        print x.value
        # return
        # print "Type: " + x.type

        # if hasattr(x, 'target'):
        #     print '\ttarget: ', x.target

        # if hasattr(x, 'value'):
        #     print '\tvalue: ', x.value
        #     x.value.help()

        # if hasattr(x, 'left'):
        #     print '\tleft: ', x.left

        # print ""

        # if x.type == "assignment":
        # print "Target: " + str(x.target) + " Value: " + str(x.value)

    # Prints a human readable version of the nodes shown above. Each
    # enter here could have one of the following keys: [value, operator, target]
    # log('\nPrinting help text for first line')

    # # Insert a comment at the given index
    # ast.insert(1, "# Test insert")

    # return it as a list so c++ is happy
    # return ast


def handshake():
    ''' Just a sanity method to make sure the python methods are properly accessible in cpp '''
    return "Python native functions imported"

if __name__ == '__main__':

    # load the sample file (in this directory)
    ast = test_source('../../samplecode.py')
