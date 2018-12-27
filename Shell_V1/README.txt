M. Steven Towns

Simple Shell written in C
Use 'gcc -Wall -o "%e" "%f"' to compile

What works:
	launching commands
	all 3 builtin commands (cd, pwd, exit)
	non-builtin commands
	single input parameter
	 	so ls -l works, but ls -l -r does not
	this applies to files as well
		so ls < test.txt will send a single input from test.txt to ls
	some very basic errors
What doesn't:
	multiple inputs
	output to file
	multiple commands
	piping
