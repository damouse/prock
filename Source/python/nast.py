'''
Helper functions for interacting with and mutating the AST produced by RedBaron.
'''

from redbaron import RedBaron

import json


def to_source(ast):
    '''
    Turn the given AST to formatted source code.
    Returns a list of strings.
    '''
    return [str(x) for x in ast]


def to_json(ast):
    ''' returns the full AST as formatted json '''
    return json.dumps(ast.fst(), indent=4)
