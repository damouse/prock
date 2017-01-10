# Prock

A full-featured virtual reality code visualizer, IDE, and debugger. At the time of this writing only python is supported.

## Build Notes

Python is compiled into the engine, but a properly pathed x64 python27 install might still be required. More information coming soon. 


## Design

This section contains notes about the design of Prock. Careful: these notes may not always be up to date. 

### Peter

Loads native code, creates an AST from it, and wraps that AST in a wrapper class ready for consumption by the engine.

#### ProckNode 

Abstract base, wrapper class for native AST nodes. Each ProckNode wraps a single native AST node. 

ProckNodes are never used directly. A subclass exists for each native AST node type. Nodes always return the correct subclasses as needed. 

ProckNodes map to native nodes 1:1. 

### Engine 

The engine is responsible for all drawing, animation, and input. It is implmented in a set of c++ classes and UE Blueprints. It uses two primitive classes, `Box` and `Line`, as building blocks to represent the AST. The BNL (Boxes 'n' Lines) is *not* a 1:1 mapping to the AST. Creating the BNL from AST is called *framing*, of which there are many types: direct code, class heirarchy, dependancy graph, etc. 

At the time of this writing Frame subclasses are not implemented: the CodeList frame is the default.

### Framing 

Wraps around a set of nodes/boxes and displays them in some meaningful way with respect to this frame. 

Exerts internal physics on boxes and external physics on other frames.


#### Ghost

The logical representation of a single variable between all references to that variable in a given scope. 

### Scope

Like programmatic scope, this component collects references to variables and replaces them with ghosts.

### Miscellanious Resources

[Parallel splines](https://answers.unrealengine.com/questions/319813/parallel-splines.html)