# Compiler in C++

## Overview
This compiler is designed in C++ and translates a simplified tiger-like programming language into Haverford Educational RISC Architecture ([HERA](http://www.haverford.edu/resources/software/HERA/index.html)) assembly code which can be executed on the HERA-C simulator. Framework for this project was provided by David Wonacott as part of the curriculum for H350 Compiler Design, and the rest of the work was completed by Anna Nguyen and Abbi Marmer-Adams. It demonstrates not only compiler design, but also data structure creation, management and traversal, as well as error handling, code generation, and rigorous testing.


## Features
The project implements elements of compiler design including:
- Abstract syntax tree construction and traversal
- Symbol table management for variable and function tracking
- Semantic Analysis for type checking
- Syntax-directed translation and Intermediate code generation for HERA assembly language
- Testing framework, with scripts and test cases for each new symbol and identified areas of potential semantic ambiguity


## Project Structure:
```
├── Documentation
│   ├── AST_attributes.txt
│   ├── sources.txt
│   └── User_Manuel.txt 
├── Demo 
│   └── demo.mp4
├──.gitignore
├──.script-for-dave
├──AST-print-attributes.cpp
├──AST-print.cpp
├──AST.cpp # AST node definitions and implementations
├──AST.h
├──AST_appel.h
├──AST_attribute_types.h
├──All_Tests.sh # Script to run all tests
├──CMakeLists.txt     # Build configuration
├──HERA_code.cpp  # Intermediate code generation
├──README.md    # Project documentation
├──ST.cpp # Symbol Table structures and logic
├──ST.h
├──ST.t
├──depth.cpp
├──errormsg.cpp     # Error handling utilities
├──errormsg.h
├──height.cpp
├──layout_frames.cpp   # Stack frame layout logic
├──lazy.cpp
├──lazy.h
├──lazy.t
├──parent.cpp
├──result_reg.cpp
├──static_checks.cpp # Static semantic analysis routines
├──static_checks.h
├──symbol.h
├──test.hera
├──test.tig
├──tiger-grammar.yy  # identify and prioritize tokens
├──tiger-lex.ll # 
├──tiger.cpp
├──tigerParseDriver.cpp
├──tigerParseDriver.h
├──typecheck.cpp
├──typecheck.h
├──types.cpp
├──types.h
└── util.cpp
```

## Limitations
This was completed up to milestone 6. See milestones [here](https://docs.google.com/document/d/1WNeB8NJ1VvdgfXOVZiMSvajAKcltCRBuIbd7KEtPUfc/edit?tab=t.0)
This program can only be executed using the [HERA-C simulator](https://drive.google.com/file/d/0B6Vy4hWlwRO2ME5yd0lwTjJfaWM/view?resourcekey=0-GanNaJ6NpIydhCyVJB3Ojw) from Haverford college. This can be tedious to configure properly, so we have included a demonstration video below.

## Demonstration Video
This video demonstrates tests being run on our compiler by feeding it tiger-like syntax, generating HERA code, executing the code, and displaying the contents of the registers. 
The first few lines, labeled on the left with ‘line 1… line n’ is the text of the test.
The HERA code generated is between #include <Tiger-stdlib-stack-data.hera> and #include <Tiger-stdlib-stack.hera>. The final contents of the registers are displayed under the line “Registers:”.

https://github.com/user-attachments/assets/dec5a9f0-78cd-453d-8d15-bd9ef4cf5d5d
