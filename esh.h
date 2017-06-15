#ifndef SHELL_H
#define SHELL_H

class esh_shell {
	public:
		esh_shell();
		~esh_shell();
		void start();

	private:

	/* Strings that make up the prompt: path + shell prefix = shell_prompt */
		string shell_prefix;
		string path_to_cwd;
		string shell_prompt;
	
	/* Update the prompt upon shell startup and after changing directories */
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
}

#endif /* SHELL_H */
