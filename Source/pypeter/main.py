'''
Python "native" portion of the processor script. Called directly by the engine on startup, should bootstrap the 
environment and do imports as needed. 
'''

import json

from utils import log
import files
import nast

def load_source(path="../../../../../../Code/unreal/ProckFPS 4.13/samplecode.py"):
    '''
    Load the source code. Note that we should be taking arguments here eventually. 
    Hardcoded for now.
    '''
    ast = files.load_file(path)

    # Below are some random examples on how you could interact with the AST once its loaded
    # Example for turning the ast back to source
    # for x in nast.to_source(ast):
    #     log(x)

    # Example for turning the ast to json
    # log('\nPrinting full AST: ' + nast.to_json(ast))

    # Prints a human readable version of the nodes shown above. Each
    # enter here could have one of the following keys: [value, operator, target]
    # log('\nPrinting help text for first line')
    # ast[0].help()

    # # Insert a comment at the given index
    # ast.insert(1, "# Test insert")

def handshake():
    ''' Just a sanity method to make sure the python methods are properly accessible in cpp '''
    return "Python native functions imported"

if __name__ == '__main__':

    # load the sample file (in this directory)
    load_source('sample.py')


