# Taken originally from the redbaron source: https://github.com/PyCQA/redbaron/blob/497a55f51a1902f67b30519c126469e60b4f569f/redbaron/base_nodes.py

import sys, pprint, os
from string import Template

from redbaron.nodes import *
from redbaron import nodes, RedBaron

WRITE_PATH = '../ProckFPS/ProckNode.h'

# single class 
class_template = '''
/*
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
$getters};
'''

# getters
list_template = '''\tstd::vector<ProckNode *> *$name() { return GetAsList("$key"); } '''
str_template = '''\tchar *$name() { return GetAsString("$key"); } '''
dict_template = '''\tProckNode *$name() { return GetAsNode("$key"); } '''


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


def read_baron_definitions():
    ''' Constructs definitions of the node types from the baron documentation '''
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

def read_node_declarations():
    ''' Go through the RedBaron declarations and build a list of nodes '''
    names = list(filter(lambda x: x.endswith("Node") or x.endswith("List"), dir(nodes)))

    # TODO: make sure the entire list of nodes contains any ones missing from here
    # String to class:
    for n in names:
        print "\t} else if (strcmp(t, \"" + n + "\") == 0) {"
        print "\t\treturn new PN" + n.replace('Node', '') + "();"


def parse_definitions():
    ''' Reads in the redbaron types and builds definition objects for each '''
    definitions = read_baron_definitions()
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
        class_name = 'PN' + d.name.replace("Node", '')

        # print d.help_text
        # print str(d.python)
        # print str(d.description)
        # # print '\t' + str(d.example)
        # # print '\t' + str(d.node)
        # pprint.pprint(d.node.__dict__)
        # print ''

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
                    # We don't care about the formatting. Skip it for now
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
            comment=d.description,
            python=d.python,
            description=d.help_text.replace('\n', '\n    '),
            class_name=class_name,
            getters=getters,
            dict=pretty_dict.replace('\n', '\n    ')
        )

    # String to class conversion
    for d in defs:
        print "\t} else if (strcmp(t, \"" + d.name + "\") == 0) {"
        print "\t\treturn new PN" + d.name.replace('Node', '') + "();"


    foldAndWrite(WRITE_PATH, body)


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

    # return ret

    # lines = foldLines(fileName, lines)

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


