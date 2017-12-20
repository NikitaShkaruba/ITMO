# python_to_cpp - An alpha version of a python to cpp compiler

I used [libpypa](https://github.com/vinzenz/libpypa) to build **python abstract syntax tree builder**,
so then i can translate it into **my own cpp abstract syntax tree**, which could be printed into cpp code.
God dem it is beautiful. But compilers - it's a lot of work, like really.

If you are willing to investigate this repository - it's in early alpha:
* It successfully translated only test/python_src/hello_world.py and test//python_src/print_function.cpp
* It can't withdraw types from dynamically typed pythonn
