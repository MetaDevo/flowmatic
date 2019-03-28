# Flowmatic

A generic data flow / pipeline class family with a QML GUI. In other words, it's a backend and optional schematic frontend to dynamic graphs which perform data transforms and allow for previewing results of each node. It's designed to be ready off the shelf for image sequences that run over various dimensions, e.g. time or Z (depth).

For example, you could use this to make an image processing pipeline and be able to preview intermediate stages. Or you could make a video compositor, or your own visual programming language, or a robot control system.

# Running the Demo

[todo]

# How to Use Flowmatic

A node is represented in C++ by NodeData objects. Although decoupled from the UI, NodeData is a Q_OBJECT with properties and methods accessible by QtQuick (QML).

To specialize, you have two options:

1. Use NodeData with composition (in C++).

2. Subclass NodeData (in C++).

3. Use composition (in QML). To specify behaviors, you first in C++ have to register behavior makers with FlowGraph::registerBehaviorMaker().

# Dependencies

- C++11 compiler
- Qt5

# License

Copyright (c) 2018-2019 Samuel H. Kenyon. All Rights Reserved. The source code and any icons use the MIT License, which basically means it's free for personal or for commercial uses.

# Contact

Sam Kenyon <sam@metadevo.com>
