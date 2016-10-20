'''
Python "native" portion of the processor script. Called directly by the engine on startup, should bootstrap the 
environment and do imports as needed. 
'''

import unreal_engine as ue
ue.log('Peter imported and bootstrapping')

from redbaron import RedBaron

import sys
sys.path.insert(0, u'../../../../../../Code/unreal/ProckFPS 4.13/')

# Import the target module directly. Much better way to do things so that local dependencies resolve...
import samplecode
ue.log(samplecode)

# ... but apparently redbaron only parses strings and not python modules. Why?
with open("../../../../../../Code/unreal/ProckFPS 4.13/samplecode.py", "r") as source_code:
    red = RedBaron(source_code.read())

ue.log(red.dumps())

ue.log('done')



# def import_parse(dir, name):
# 	''' load the module 'name' from the given directory '''
# 	pass

# def main():
# 	pass