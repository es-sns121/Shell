top = ..

# source files
src = $(top)/src/main.cpp $(top)/src/eshell.cpp

# binary
bin = eshell

# rule dependencies 
dep = $(top)/src/eshell.h $(src)

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
