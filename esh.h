#ifndef ESH_H
#define ESH_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace esh {

class esh_shell {
	public:
		esh_shell();
		int start();
		void set_debug(const bool &);
	private:

		bool read_flag;

	/* Strings that make up the prompt: path + shell prefix = shell_prompt */
		std::string shell_prefix;
		std::string path_to_cwd;
		std::string shell_prompt;
	
	/* SIGINT signal handler */
		void sigint_handler( int );

	/* Update the path to the current working directory */
		void update_path();

	/* Update the shell prompt string */
		void update_prompt();

	/* Tokenize a line of input */
		void tokenize_input();

	/* Get a line of user input */
		void get_line();

	/* Loop waiting for user input */
		void loop();
	
	/* Parse input and call shell builtin or call execute */
		void launch();

	/* Fork and execute commands */
		void execute();

		/*
		 *	map<string, void (*) ()> built_in_functions;
		 *		cd
		 *		help
		 *		exit
		 */
};

} /* namespace esh */

#endif /* ESH_H */
