all: esh

esh: main.cpp
	g++ -Wall -g -o esh main.cpp

clean: 
	rm -rf esh
