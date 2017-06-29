#include "parse.h"

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

vector<string> parse (const string & line)
{
	stringstream ss;
	ss.str(line);
	
	vector<string> args;
	args.reserve(100);
	
	string token;

	while (ss >> token) 
	{
		args.push_back(token);
		token.clear();
	}

	return args;
}
