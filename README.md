# eshell : Evan's Shell 

This is a simple shell program written in c++. 
It supports file redirection and piping
(future). It has a number of builtin functions:
help, exit, and cd (future).

This application is written in c++ and compiled with
gcc compiler version 4.4.7.

## Building
If the makefile is present and a valid g++ compiler is in $PATH, 
just type:
	
	> make

## Running the shell
Type:
	
	> ./eshell

To quit, type 'exit' and enter, or type CNTRL-D and enter.

## Source directory (src)
### Files

Makefile

- Builds application

main.cpp

- Main entry point

loop.h & loop.cpp

- Shell loop. Read, parse, execute.

read.h & read.cpp

- Read input from stdin

parse.h & parse.cpp

- Parse line of input

execute.h & execute.cpp

- Execute parsed arguments
