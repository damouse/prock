# Prock

A full-featured virtual reality code visualizer, IDE, and debugger. It works by embedding a full Python runtime into Unreal Engine 4, consuming python programs, and outputting a 3D representation of the resulting program. 

Python is compiled into the engine, but a properly pathed x64 python27 install might still be required. More information coming soon. 

Tested on Windows with python2.7. 

The key hypothesis of this project is that there exists a visual representation of almost any program that is more useful in understanding it compared to just reading the code. Unfortunatly, this project has been suspended due to the scope of work involved-- finding those representations is hard!

## Demo

Quick video demo of interactions in an early build:
[![IMAGE ALT TEXT](http://img.youtube.com/vi/RdVaZoD8ptc/0.jpg)](http://www.youtube.com/watch?v=RdVaZoD8ptc)

Rendered code in a timeline format: 
![Pathlining](pathlining.PNG?raw=true)

Python code mid-execution:
![Debugging](running.PNG?raw=true)