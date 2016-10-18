'''
Python "native" portion of the processor script. Called directly by the engine on startup, should bootstrap the 
environment and do imports as needed. 
'''

import unreal_engine as ue
ue.log('Peter imported and bootstrapping')

import redbaron

def import_parse(dir, name):
	''' load the module 'name' from the given directory '''
	pass

def main():
	pass