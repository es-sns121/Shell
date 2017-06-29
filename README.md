# eshell : Evan's Shell 

This is a simple shell program written in c++. 
It supports file redirection (future) and piping
(future). It has a number of builtin functions:
help, exit, and cd (future).

## Building
If the makefile is present and a g++ compiler is in the $PATH, 
just type:
	
	> make

## Running the shell
Type:
	
	> ./eshell

To quit, type 'exit' and enter, or type CNTRL-D and enter.

## Source directory (src)
### Files

Makfile

main.cpp

- Main entry point

loop.h & loop.cpp

- Main shell loop

read.h & read.cpp

- Read input from stdin

parse.h & parse.cpp

- Parse line of input

execute.h & execute.cpp

- Execute parsed arguments
