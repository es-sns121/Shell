/*
	Author: Evan Smith
	Date:   6/13/2017
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

string shell_prefix = " $> ";

string path;

void sigint_handler(int signo) {
	cout << endl << path << shell_prefix << flush;
	signal(SIGINT, sigint_handler);
}

/* esh built ins */
int esh_exit(char **args) {
	return 1;
}

int esh_launch(char **args) {
	/* Check that first argument isn't a built in. */
	
	if (0 == strcmp(args[0], "exit")) {
		
		return esh_exit(args);
	
	} else if (NULL != args[0]) {
	
		pid_t pid;
		
		pid = fork();
		
		if (0 == pid) {
		/* Child Process */
			
			execvp(args[0], args);
			
			perror("esh");
			
			exit(-1);
		
		} else if (pid > 0) {
		/* Parent Process */
			int status;

			do {
				
				waitpid(-1, &status, WUNTRACED);
			
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

		} else {
		/* Error */
			
			perror("esh");
			
		}
	}

	return 0;
}

void free_args(char **args) {
	char * arg;
	size_t index = 0;
	arg = args[0];

	while (NULL != arg) {
		free(arg);
		arg = args[++index];
	}
}

char **view(vector<char *> & tokenized_input) {
	size_t size = tokenized_input.size();
	/* size + 1 to allow the array to be null terminated */
	char **args = (char **) malloc(sizeof(char *) * size);
	
	for (size_t i = 0; i < size; ++i) {
		args[i] = tokenized_input[i];
	}

	tokenized_input.clear();

	args[size] = NULL;

	return args;
}

char **esh_read_line() {
	
	string input;
	stringstream input_line;
	string token;
	vector<char *> tokenized_input;
	char ** args = NULL;

	getline(cin, input);
	if (cin.eof())
		return args;

	input_line.str(input);

	while (input_line >> token) {
	
		// Handle file redirection here. Look for < > << >> and skip these 
		// tokens along with the following file name. 

		tokenized_input.push_back(strdup(token.c_str()));
	
		token.clear();
	}
	
	char *n = NULL;
	tokenized_input.push_back(n);

	args = view(tokenized_input);

	return args;
}

void esh_loop() {
	char **args; 
	
	while (true) {
		cout << path << shell_prefix;

		args = esh_read_line();
		
		if (NULL == args) {
			cout << endl;	
			break;
		}

		if (esh_launch(args)) {
			free_args(args);
			break;
		}
	}	
}

#define BUFSIZE 50

int main(int argc, char *argv[], char *envp[]) {
		
	/* register SIGINT signal handler */
	signal(SIGINT, sigint_handler);

/* Set path */
	char *buf = (char *) malloc(sizeof(char) * BUFSIZE);
	/* Get current working directory */
	getcwd(buf, BUFSIZE);

	path = string(buf);
	
	free(buf);

/* Shell loop */
	esh_loop();

/* Clean up */

	return 0;
}
