#include "execute.h"

#include <cstdio>
#include <cstdlib>
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

int execute(const vector<string> & args)
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
		char ** new_args = view(args);	
		execvp(new_args[0], new_args);
	
	/* If execvp returns, an error occured. */
		perror(args[0].c_str());
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

	return 1;
}
