# Taken originally from the redbaron source: https://github.com/PyCQA/redbaron/blob/497a55f51a1902f67b30519c126469e60b4f569f/redbaron/base_nodes.py

import sys, pprint
from string import Template

from redbaron.nodes import *
from redbaron import nodes, RedBaron

WRITE_PATH = 'test.h'

# Whole header file
header_template = '''
/*
 * This file is dynamically generated by a python script based on AST node documentation from RedBaron.
 * 
 * DO NOT EDIT THIS FILE DIRECTLY.
 *
 * The classes defined here inherit from BoxActor, which is responsible for implementation, and PythonNode, 
 * which is responsible for interfacing with python AST nodes. Edit those classes to add functionality. 
 */

#pragma once

#include "GameFramework/Actor.h"
#include "BoxActor.h"
#include "NodeBox.generated.h"

$body
'''

# single class 
class_template = '''
/*
$comment

Equivalent python:

    $python

RedBaron .help() text:

    $description

Raw PyObject __dict__ dump:

    $dict
*/
UCLASS()
class PROCKFPS_API $class_name : public ABoxActor, public PythonNode {
    GENERATED_BODY()

public: 
    $class_name(PyObject *native) : PythonNode(native) {}
    $class_name() : PythonNode(nullptr) {}

$getters};
'''

# getters
list_template = '''\tstd::vector<NodeBox> $name();'''
str_template = '''\tchar *$name();'''
dict_template = '''\tNodeBox *$name();'''


class NodeDefinition():
    def __init__(self, name):
        self.name = name # the name of the node
        self.description = '' # baron's description
        self.example = '' # raw python example
        self.help_text = '' # result of calling .help(deep=True on the baron node)

        self.python = ''
        self.node = None

class PrintInterceptor(object):
    def __init__(self):
        self.current = []
        self.stdout = sys.stdout

    def off(self):
        sys.stdout = self.stdout

    def on(self):
        sys.stdout = self

    def tprint(self, message):
        self.stdout.write(str(message) + '\n')

    def clear(self):
        r = self.current
        self.current = []
        return r

    def write(self, message):
        self.current.append(message)
        # self.stdout.write(message)


def node_defs():
    ''' Constructs definitions of the node types from the baron documetnation '''
    with open('barondoc.txt', 'r') as f:
        lines = f.readlines()

    last, current_def = None, None
    defs = []
    iterator = iter(lines)
    running = True

    while running:
        try:
            line = iterator.next()
        except:
            return defs

        if len(line) == 1:
            continue

        if "====" in line:
            current_def = NodeDefinition(last.strip())
            defs.append(current_def)
        else:
            last = line
            continue

        while True:
            line = iterator.next()
            if '.. ipython:: python' in line:
                break
            elif line != '\n':
                current_def.description += line.strip()

        iterator.next()
        line = iterator.next()
        current_def.example += line.strip()

def parse_definitions():
    ''' Read the definitions and then construct C++ files from them '''
    definitions = node_defs()
    out = PrintInterceptor()
    out.on()

    for d in definitions:
        eval(d.example)
        d.help_text = out.clear()
        d.help_text = ''.join(d.help_text)

        s = d.example.replace('RedBaron("', '')
        d.python = s.split('")[0].')[0]

        d.example = d.example.replace('.help(deep=True)', '')

        # TODO: check if None!
        d.node = eval(d.example)

    out.off()
    return [x for x in definitions if x.node is not None]

def write_classes():
    out = PrintInterceptor()
    defs = parse_definitions()
    body = ''

    for d in defs:
        getters = ''

        print d.help_text
        print str(d.python)
        print str(d.description)
        # print '\t' + str(d.example)
        # print '\t' + str(d.node)
        pprint.pprint(d.node.__dict__)
        print ''

        # Build a list of getters for these classes
        if hasattr(d.node, 'node_list'):
            getters += Template(list_template).substitute(name='NodeList')
            getters += '\n'
        else:
            for key, template in {'_str_keys': str_template, '_dict_keys': dict_template, '_list_keys': list_template}.iteritems():
                target_list = eval('d.node.' + key)

                if len(target_list) == 0:
                    continue

                for name in target_list:
                    # We don't care about the formatting. Skip it for now
                    if '_formatting' in name: 
                        continue

                    getters += Template(template).substitute(name=''.join([x.title() for x in name.split('_')])) + '\n'

                getters += '\n'

            # Print the object's dictionary for future reference
            out.on()
            pprint.pprint(d.node.__dict__)
            pretty_dict = ''.join(out.clear())
            out.off()

        # Write out this class
        body += '\n' + Template(class_template).substitute(
            comment=d.description,
            python=d.python,
            description=d.help_text.replace('\n', '\n    '),
            class_name='PN' + d.name.replace("Node", ''),
            getters=getters,
            dict=pretty_dict.replace('\n', '\n    ')
        )

    with open(WRITE_PATH, 'w') as f:
        f.write(Template(header_template).substitute(body=body))

    # # Debug logging
    # for d in defs:
    #     print d.name
    #     print d.help_text
    #     print str(d.python)
    #     print str(d.description)
    #     # print '\t' + str(d.example)
    #     # print '\t' + str(d.node)

    #     getters = ''

    #     if hasattr(d.node, 'node_list'):
    #         getters += Template(list_template).substitute(name='NodeList')
    #         getters += '\n'
    #     else:
    #         for key, template in {'_str_keys': str_template, '_dict_keys': dict_template, '_list_keys': list_template}.iteritems():
    #             for name in eval('d.node.' + key):
    #                 getters += Template(str_template).substitute(name=''.join([x.title() for x in name.split('_')]))

    #             getters += '\n'




    #     # When assigning the c++ class:
    #     # Check _class_ field and choose corresponding c++ class. Dont fuck with type.

    #     # Building the c++ classes: 
    #     # Create a new class with the given class name
    #     # If node has a node_list field create bulk "children" field and continue
    #     # Else check all _keys fields, create appropriate getters

    #     print ''
    #     pprint.pprint(d.node.__dict__)

    #     try:
    #         print d.node.type
    #     except:
    #         print "NODE HAS NO TYPE: ", d.node.__class__
    #         print "isinstance of nodelist: ", isinstance(d.node, (nodes.NodeList, nodes.CommaProxyList))

    #     print ''
    # return

def print_enums():
    names = list(filter(lambda x: x.endswith("Node") or x.endswith("List"), dir(nodes)))

    # String to class:
    for n in names:
        print "\t} else if (strcmp(t, \"" + n + "\") == 0) {"
        print "\t\treturn new PN" + n.replace('Node', '') + "();"

    # string to enum
    # for c, r in defs:
    #     print "\tcase " + str(c) + ":"
    #     print "\t\treturn \"" + str(c.replace("PNT_", "")) + "\\0\";"
    #     # print "\t\tbreak;"


if __name__ == '__main__':
    # print_enums()
    write_classes()


