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

    # print ast.__dict__
    # ast.help()

    # Below are some random examples on how you could interact with the AST once its loaded
    # Example for turning the ast back to source
    # for x in nast.to_source(ast):
    #     log(x)

    # Example for turning the ast to json
    # log('\nPrinting full AST: ' + nast.to_json(ast))

    # for x in ast:
    #     if x.type in ["comment", "endl"]:
    #         continue

    #     # This could be: endl, assignment, comment, etc. Print .help() for more information
    #     print "Type: \t" + x.type

    #     if x.type == "assignment":
    #         print "Target: " + str(x.target) + " Value: " + str(x.value)

    #     # Here's the core peter algo: for every line 

    # Prints a human readable version of the nodes shown above. Each
    # enter here could have one of the following keys: [value, operator, target]
    # log('\nPrinting help text for first line')

    # # Insert a comment at the given index
    # ast.insert(1, "# Test insert")

    # return it as a list so c++ is happy
    # return ast
    return [x for x in ast]

def handshake():
    ''' Just a sanity method to make sure the python methods are properly accessible in cpp '''
    return "Python native functions imported"

if __name__ == '__main__':

    # load the sample file (in this directory)
    load_source('../../samplecode.py')


