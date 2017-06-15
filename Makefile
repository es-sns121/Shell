all: esh

esh: esh.cpp
	g++ -Wall -g -o esh esh.cpp

clean: 
	rm -rf esh
