#include "esh.h"

using namespace std;
using namespace esh;

#define DEFAULT_PREFIX " $> "
#define BUFSIZE 512


void print_prompt (string * p) {
	static string * prompt = NULL;
	static bool first_call(true);
	
	if (first_call == true && p != NULL) {
		
		prompt = p;
		first_call = false;
	
	}
	
	if (prompt != NULL) {
		cout << *prompt << flush;
	}
}

void SIGINT_handler (int signo) {

	signal(SIGINT, SIGINT_handler);
	cout << endl;	
	print_prompt(NULL);

}

esh_shell::esh_shell () : shell_prefix(DEFAULT_PREFIX) {
	
	debug = false;

	update_prompt();
	
	print_prompt(&shell_prompt);
}

void esh_shell::update_path	() {
	
	char * buf = (char *) malloc (sizeof(char) * BUFSIZE);

/* Get the current working directory */
	getcwd(buf, BUFSIZE-1);

	path_to_cwd.assign(buf);
	
	free(buf);

}

void esh_shell::update_prompt () {
	
	update_path();

	shell_prompt.assign(path_to_cwd + shell_prefix);

}

void get_line() {
	
}

int esh_shell::loop () {
	do {
		get_line();
	} while (read_flag);

	return 0;
}

int esh_shell::start () {
	return loop();
}
