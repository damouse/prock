'''
Python "native" portion of the processor script. Called directly by the engine on startup, should bootstrap the 
environment and do imports as needed. 
'''

import json, pprint

from redbaron import nodes
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
    '''
    ast = load_file(path)
    return ast


def test_source(path):
    ''' A demo function here to play with the AST graph '''

    ast = load_file(path)
    # print isinstance(ast, (nodes.NodeList, nodes.CommaProxyList))
    pprint.pprint(ast.__dict__)
    # print ast.__class__


def handshake():
    ''' Just a sanity method to make sure the python methods are properly accessible in cpp '''
    return "Python native functions imported"

if __name__ == '__main__':

    # load the sample file (in this directory)
    ast = test_source('../../samplecode.py')
