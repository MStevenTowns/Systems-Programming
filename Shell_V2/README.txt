Submitter: M. Steven Towns
Partner: Bradley Ewing 
Code Base: Bradley Ewing

Simple Shell written in C
use make to compile
run the techShell program that is created

What works:
	launching commands
	all 5 builtin commands (cd, pwd, exit, set, list)
	non-builtin commands
	single input parameter
	 	so ls -l works, but ls -l -r does not
	this applies to files as well
		so ls < test.txt will send only a single input from test.txt to ls
	error reporting
	pseudo piping
	multiple commands using ; 	

What doesn't:
	multiple inputs
	pipe using the pipe() command

