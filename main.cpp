/*
	Author: Evan Smith
	Date:   6/13/2017
*/

#include "esh.h"

using namespace std;

int main(int argc, char *argv[], char *envp[]) {
		
	esh::esh_shell shell;
	
	return shell.start();

}
