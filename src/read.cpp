#include "read.h"

#include <iostream>
#include <string.h>

using namespace std;

char * read_line ()
{
	string line;
	getline(cin, line);

	if (cin.eof())
		return NULL;
	
	return strdup(line.c_str());
}
