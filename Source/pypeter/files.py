'''
Helper functions for interacting with files. Read, write, import, export, 
messing with the system paths, etc.
'''

from utils import log

from redbaron import RedBaron


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
