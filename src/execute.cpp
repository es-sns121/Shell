#include "execute.h"

#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/wait.h>
#include <vector>

using namespace std;

char ** view (const vector<string> & args)
{
	size_t size = args.size() + 1;
	char ** new_args = (char **) malloc (sizeof(char) * size);

	for (size_t i = 0; i < size - 1; ++i) {
		new_args[i] = strdup(args[i].c_str());
	}
	
	new_args[size-1] = NULL;

	return new_args;

}

void redirect(vector<string> & args)
{
	vector<string>::iterator it = args.begin();
	
	int fd;
	
	for (; it != args.end();) {
		
		if ((*it).compare(">") == 0) {

			/* Erase the '>' */
			args.erase(it);

			if (it == args.end()) {
				fprintf(stderr, "Unexpected newline\n");
				exit(1);
			}

			fd = open((*it).c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0644);
		
			/* Redirect stdout */
			if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO) {
				perror("dup2");
				exit(1);
			}
		
			close(fd);

			/* Erase the filename */
			args.erase(it);
		
		} else if ((*it).compare(">>") == 0) {

			/* Erase the '>>' */
			args.erase(it);

			if (it == args.end()) {
				fprintf(stderr, "Unexpected newline\n");
				exit(1);
			}

			fd = open((*it).c_str(), O_WRONLY | O_CREAT, 0644);
			
			if (dup2(fd, STDOUT_FILENO) != STDOUT_FILENO) {
				perror("dup2");
				exit(1);
			}

			close(fd);

			/* Erase the filename */
			args.erase(it);

		} else if ((*it).compare("<") == 0) {

			/* Erase the '<' */
			args.erase(it);

			if (it == args.end()) {
				fprintf(stderr, "Unexpected newline\n");
				exit(1);
			}

			fd = open((*it).c_str(), O_WRONLY | O_TRUNC | O_CREAT, 0644);
			
			if (dup2(fd, STDIN_FILENO) != STDIN_FILENO) {
				perror("dup2");
				exit(1);
			}

			close(fd);

			/* Erase the filename */
			args.erase(it);
			
		} else {
			++it;
		}
	}
	
}

int execute(vector<string> & args)
{

	/* Empty argument list */
	if (args.size() == 0)
		return 1;

	/* Exit */
	if (args[0].compare("exit") == 0)
		return 0;

	int status;
	pid_t pid = fork();

	if (pid == 0) {
	/* Child process */

		/* Handle file redirection */
		redirect(args);

		/* Convert the vector to a null terminated array of c style strings */
		char ** new_args = view(args);	
			
		execvp(new_args[0], new_args);
	
		/* If execvp returns, an error occured. */
		perror(new_args[0]);
		exit(1);
	
	} else if (pid > 0) {
	/* Parent process */

		/* Wait for all children */
		do {

			(void) waitpid(-1, &status, WUNTRACED);
		
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		
		
	} else {
	/* Error */
	
		perror("fork");
		return -1;
	}

	args.clear();

	return 1;
}
