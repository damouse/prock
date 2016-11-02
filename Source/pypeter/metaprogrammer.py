'''
Metaprogrammer for AST Node Classes. 

Looks through the RedBaron source for classes of Node and scrapes their documentation
to build a list of examples and valid fields. Writes these out as c++ classes. 
'''
import sys, pprint, os
from string import Template

from redbaron.nodes import *
from redbaron import nodes, RedBaron

CLASS_FILE = '../ProckFPS/ProckNode.h'
ENUM_FILE = '../ProckFPS/ProckNode.cpp'

# type enum
enum_template = '''
enum ProckNodeType {
    PNT_Base,
$body};

// Begin Node Definition
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

# Constructs definitions of the node types from the baron documentation
def read_baron_definitions():
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

# Go through the RedBaron declarations and build a list of nodes. Ignore the nodes we've already heard about in docs
def read_node_declarations(known):
    read = list(filter(lambda x: x.endswith("Node") or x.endswith("List"), dir(nodes)))
    decs = [x for x in read if len(list(filter(lambda y: y.name == x, known))) == 0]

    # Filter out duplicats that appear later
    return filter(lambda x: x != 'Node' and x != 'NodeList', decs)

def template_unknowns(names):
    # Because the list of nodes returned here are just the class names and not the whole 
    # definition, have to fake the entries on this a little. 
    # Assuming that all these nodes return 'value'
    return '\n'.join([Template(anonymous_template).substitute(
        class_name='PN' + x.replace('Node', ''),
        name=x.replace('Node', ''),
        type='PNT_' + x.replace('Node', ''),
    ) for x in names])

def parse_definitions():
    ''' Reads in the redbaron types and builds definition objects for each '''
    definitions = read_baron_definitions()
    out = PrintInterceptor()
    out.on()

    for d in definitions:
        eval(d.example)
        d.help_text = '\n'.join(filter(lambda x: '#' not in x, out.clear()[0].split('\n')))

        s = d.example.replace('RedBaron("', '')
        d.python = s.split('")[0].')[0]

        d.example = d.example.replace('.help(deep=True)', '')

        # TODO: check if None!
        d.node = eval(d.example)

    out.off()
    return [x for x in definitions if x.node is not None]

def template_enums(defs, unknowns):
    body = ''

    for d in defs:
        body += '\tPNT_' + d.name.replace("Node", '') + ',\n'

    for n in unknowns:
        body += '\tPNT_' + n.replace("Node", '') + ',\n'

    return Template(enum_template).substitute(body=body)

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
            getters += Template(list_template).substitute(name='NodeList', key='node_list')
            getters += '\n'
        else:
            for key, template in {'_str_keys': str_template, '_dict_keys': dict_template, '_list_keys': list_template}.iteritems():
                target_list = eval('d.node.' + key)

                if len(target_list) == 0:
                    continue

                for name in target_list:
                    if name == 'type':
                        continue
                    # We don't care about the formatting. Skip it for now
                    # EDIT: but it looks like in some cases it captures meaningful code, like comments
                    if '_formatting' in name: 
                        continue

                    getters += Template(template).substitute(
                        name=''.join([x.title() for x in name.split('_')]),
                        key=name,
                    ) + '\n'

                # getters += '\n'

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

    # Build the enum list from all node types
    enums = template_enums(defs, unknowns)

    # Write out the header file definitions
    foldAndWrite(CLASS_FILE, enums + body)

    enum = ''

    # TODO: write this out to the file instead of copy pasting
    for n in unknowns:
        enum +="\t} else if (strcmp(t, \"" + n + "\") == 0) {\n"
        enum +="\t\treturn new PN" + n.replace('Node', '') + "();\n"

    for d in defs:
        enum +="\t} else if (strcmp(t, \"" + d.name + "\") == 0) {\n"
        enum +="\t\treturn new PN" + d.name.replace('Node', '') + "();\n"

    foldAndWrite(ENUM_FILE, enum)


# Replaces the exising lines with these new lines
def foldLines(f, addition):
    start_marker = '// Start Generated Code'
    end_marker = '// End Generated Code'
    ret = []

    with open(f) as inf:
        ignoreLines = False
        written = False

        for line in inf:
            # print line

            if end_marker in line:
                ignoreLines = False

            if ignoreLines:
                if not written:
                    # print 'WRITING: ', addition
                    written = True
                    ret.append(addition)
                    # [ret.append(x) for x in addition]
            else:
                ret.append(line)

            if start_marker in line:
                ignoreLines = True

    return ret


def foldAndWrite(fileName, addition):
    ''' Opens a file and folds in the given string between the comment delimiters '''
    # fileName = os.path.join(outputPath, fileName)
    start_marker = '// Start Generated Code'
    end_marker = '// End Generated Code'
    ret = []

    with open(fileName) as inf:
        ignoreLines = False
        written = False

        for line in inf:
            # print line

            if end_marker in line:
                ignoreLines = False

            if ignoreLines:
                if not written:
                    # print 'WRITING: ', addition
                    written = True
                    ret.append(addition)
                    # [ret.append(x) for x in addition]
            else:
                ret.append(line)

            if start_marker in line:
                ignoreLines = True

    with open(fileName, 'w') as f:
        [f.write(x) for x in ret]

def print_enums():
    '''
    Import all of the Node classes from redbaron and write out factory constructors for them
    Note that not all of the classes we'd
    '''

    names = list(filter(lambda x: x.endswith("Node") or x.endswith("List"), dir(nodes)))

    # String to class:
    for n in names:
        print "\t} else if (strcmp(t, \"" + n + "\") == 0) {"
        print "\t\treturn new PN" + n.replace('Node', '') + "();"

if __name__ == '__main__':
    # print_enums()
    write_classes()


