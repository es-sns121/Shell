all: esh

esh: esh.h esh.cpp main.cpp 
	g++ -Wall -g -o esh esh.cpp main.cpp
clean: 
	rm -f esh
