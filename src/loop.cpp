#include "loop.h"
#include "read.h"
#include "parse.h"
#include "execute.h"

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

void loop ()
{
	string path("");
	string prefix(" > ");
	
	char * line;
	vector<string> args;	
	int status = 0;

	do {
		
		cout << path << prefix;

	/* Read a line of input from stdin */
		line = read_line();
	
	/* EOF detected */
		if (line == NULL) {
			cout << endl;
			return;
		}

	/* Parse the line of input into a null termiated array of c style strings */
		string str_line = line;
		free(line);

		args = parse(str_line);

	/* Execute the arguments */
		status = execute(args);
	
	} while (status);
}
