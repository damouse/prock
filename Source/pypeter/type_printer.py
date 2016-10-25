# Taken originally from the redbaron source: https://github.com/PyCQA/redbaron/blob/497a55f51a1902f67b30519c126469e60b4f569f/redbaron/base_nodes.py

from redbaron.nodes import *
from redbaron import nodes

defs = []

for name in list(filter(lambda x: x.endswith("Node"), dir(nodes))):
    c = "PNT_" + name.replace("Node", "")
    r = getattr(nodes, name).generate_identifiers()[0]
    defs.append((c, r))

# Enum
# for c, r in defs: 
#     print c + ","

# Enum to String
for c, r in defs:
    print "\t} else if (strcmp(t, \"" + str(r) + "\") == 0) {"
    print "\t\treturn " + str(c) + ";"

# string to enum
# for c, r in defs:
#     print "\tcase " + str(c) + ":"
#     print "\t\treturn \"" + str(c.replace("PNT_", "")) + "\\0\";"
#     # print "\t\tbreak;"


