top = ..

# source files
main = $(top)/src/main.cpp
util = $(top)/src/loop.cpp  $(top)/src/read.cpp $(top)/src/parse.cpp $(top)/src/execute.cpp
src = $(main) $(util)

# binary
bin = eshell

# rule dependencies 
dep = $(top)/src/loop.h $(top)/src/read.h $(top)/src/parse.h $(top)/src/execute.h $(src)

flags = -Wall -g 

all: eshell

eshell: $(dep)
	@mkdir -p $(top)/bin
	g++ $(flags) $(src) -o $(top)/bin/$(bin) 

.PHONY: clean
clean:
	@printf "Clean: removing $(bin) binary...\n"
	@mkdir -p $(top)/bin
	rm -rf $(top)/bin/$(bin)
