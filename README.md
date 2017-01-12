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

## Modes of Operation

Prock has three modes: Reading, Running, and Riting. These correspond to displaying, executing, and editting code. 

### Running

This section is a work in progress. 

Some defintitions: 

    Scope           collection of variables. Can be created during a run cycle
    Run Cycle       one step of the runner, corresponding to the execution of a single line of code

    Tick:           windup animation
    Turnover:       step debugger and update values instantaneously
    Tock:           winddown animation

Unlike reading, running relies more on the native python extensions. Find this interface in `pypeter/debugger.py`.

#### Problems

- How does the engine find its place with respect to the statement currently being evaluated by the debugger? 


### Miscellanious Resources

[Parallel splines](https://answers.unrealengine.com/questions/319813/parallel-splines.html)