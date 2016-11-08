'''
Metaprogrammer for AST Node Classes. 

Looks through the RedBaron source for classes of Node and scrapes their documentation
to build a list of examples and valid fields. Writes these out as c++ classes. 

Usage: run this file. Results are written to CLASS_FILE and ENUM_FILE 
between comment delimiters. 
'''
import sys, pprint, os
from string import Template

from redbaron.nodes import *
from redbaron import nodes, RedBaron

CLASS_FILE = '../ProckFPS/ProckNode.h'
HEADER_FILE = '../ProckFPS/BaseNode.h'
ENUM_FILE = '../ProckFPS/BaseNode.cpp'

# type enum
enum_template = '''
enum ProckNodeType {
    PNT_Base,
$body};
'''

# single class 
class_template = '''/*
$comment

Equivalent python:

    $python

RedBaron .help() text:

    $description
Python __dict__ dump:

    $dict
*/
class PROCKFPS_API $class_name : public ProckNode {
public: 
    virtual char *Name() { return "$name\0"; }
    virtual ProckNodeType Type() { return $type; }

$getters};
'''

# classes we know the name of but not any of the implementation details
anonymous_template = '''
class PROCKFPS_API $class_name : public ProckNode {
public: 
    virtual char *Name() { return "$name\0"; }
    virtual ProckNodeType Type() { return $type; }

    char *Value() { return GetAsString("value"); }
};
'''

# getters
list_template = '''\tstd::vector<ProckNode *> *$name() { return GetAsList("$key"); } '''
str_template = '''\tchar *$name() { return GetAsString("$key"); } '''
dict_template = '''\tProckNode *$name() { return GetAsNode("$key"); } '''


# Reads in the redbaron types and builds definition objects for each
def parse_definitions():
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
            break

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

    # The .help() method on redbaron objects is extremely informative but prints its results
    # instead of returning them. This captures stdout of the eval(d.example) statement below
    # so we can include this information
    out = PrintInterceptor()
    out.on()

    for d in defs:
        eval(d.example)
        d.help_text = '\n'.join(filter(lambda x: '#' not in x, out.clear()[0].split('\n')))
        d.python = d.example.replace('RedBaron("', '').split('")[0].')[0]
        d.example = d.example.replace('.help(deep=True)', '')
        d.node = eval(d.example)

    out.off()
    return [x for x in defs if x.node is not None]

# Go through the RedBaron declarations and build a list of node names. Ignore the nodes that appear in the list of NodeDefinitions 
def read_node_declarations(known):
    read = list(filter(lambda x: x.endswith("Node") or x.endswith("List"), dir(nodes)))
    decs = [x for x in read if len(list(filter(lambda y: y.name == x, known))) == 0]

    # Filter out spcific duplicates.
    return filter(lambda x: x != 'Node' and x != 'NodeList', decs)

# Scrape all the publically declared nodes in RedBaron to catch any nodes not seen in barondoc.txt, 
# the documentation. Because we only have node names here we assume all these nodes return "value"
def template_unknowns(names):
    return '\n'.join([Template(anonymous_template).substitute(
        class_name='PN' + x.replace('Node', ''),
        name=x.replace('Node', ''),
        type='PNT_' + x.replace('Node', ''),
    ) for x in names])

def template_enums(defs, unknowns):
    body = ['\tPNT_' + d.name.replace("Node", '') + ',\n' for d in defs]
    body += ['\tPNT_' + n.replace("Node", '') + ',\n' for n in unknowns]
    return Template(enum_template).substitute(body=''.join(body))

# Should include a list of override types
def write_classes():
    out = PrintInterceptor()
    defs = parse_definitions()
    body = ''

    for d in defs:
        getters = ''
        class_name = 'PN' + d.name.replace("Node", '')

        # Build a list of getters for these classes
        if hasattr(d.node, 'node_list'):
            getters += Template(list_template).substitute(name='NodeList', key='node_list') + '\n'
        else:
            for key, template in {'_str_keys': str_template, '_dict_keys': dict_template, '_list_keys': list_template}.iteritems():
                target_list = eval('d.node.' + key)

                if len(target_list) == 0:
                    continue

                for name in target_list:
                    # We don't care about the formatting. Skip it for now
                    if name == 'type' or '_formatting' in name:
                        continue

                    getters += Template(template).substitute(name=''.join([x.title() for x in name.split('_')]), key=name) + '\n'

            # Print the object's dictionary for future reference
            out.on()
            pprint.pprint(d.node.__dict__)
            pretty_dict = ''.join(out.clear())
            out.off()

        # Write out this class
        body += '\n' + Template(class_template).substitute(
            name=d.name.replace("Node", ''),
            comment=d.description,
            python=d.python,
            description=d.help_text.replace('\n', '\n    '),
            class_name=class_name,
            getters=getters,
            dict=pretty_dict.replace('\n', '\n    '),
            type='PNT_' + d.name.replace("Node", '')
        )

    # Load the list of "Unknown" nodes, or nodes we know the name of but not the implementations
    unknowns = read_node_declarations(defs)
    body += '\n\n//\n// Generalized, "primitive" nodes'
    body += template_unknowns(unknowns)
    foldAndWrite(CLASS_FILE, body)

    # Build the enum list from all node types and write the whole body out
    enums = template_enums(defs, unknowns)
    foldAndWrite(HEADER_FILE, enums)

    # Create and write string to class conversions
    enum = ["\t} else if (strcmp(t, \"" + n + "\") == 0) {\n\t\treturn new PN" + n.replace('Node', '') + "();\n" for n in unknowns]
    enum += ["\t} else if (strcmp(t, \"" + d.name + "\") == 0) {\n\t\treturn new PN" + d.name.replace('Node', '') + "();\n" for d in defs]
    
    foldAndWrite(ENUM_FILE, ''.join(enum))

# Writes "addition" into the named file between the two delimiters hardcoded into the method
def foldAndWrite(fileName, addition):
    start_marker = '// Start Generated Code\n'
    end_marker = '// End Generated Code\n'
    ret = []

    with open(fileName) as inf:
        lines = inf.readlines()
        ret = lines[:lines.index(start_marker) + 1] + lines[lines.index(end_marker):]
        ret.insert(lines.index(start_marker) + 1, addition)

    with open(fileName, 'w') as f:
        [f.write(x) for x in ret]

# Data wrapper class
class NodeDefinition():
    def __init__(self, name):
        self.name = name
        self.description = ''
        self.example = ''
        self.help_text = ''
        self.python = ''
        self.node = None

# Utility for capturing stdout
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

if __name__ == '__main__':
    write_classes()


