#ifndef SHELL_H
#define SHELL_H

class esh_shell {
	public:
		esh_shell();
		~esh_shell();
		void loop();

	private:
		string shell_prefix;
		string path_to_cwd;
		string shell_prompt;

		/*
		 *	map<string, void (*) ()> built_in_functions;
		 *		cd
		 *		help
		 *		exit
		 */
}

#endif /* SHELL_H */
