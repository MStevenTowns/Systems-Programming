//Brad Ewing

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Commands.h"
#include "Tokenizer.h" 
#include "Set_Variable.h" 

#define MAXLINE 80 
#define WHITE "\t \n" 
#define MAXARG 20 
typedef char *String; 

void execute(Command *cmd);

Command *cmds = NULL; 
Variable *vars = NULL;

char cwd[257];

bool end = false;

int main()
{
	//Setups the commands
	cmds = reset_commands(cmds);

	//Gets the current working directory
	getcwd(cwd, sizeof(cwd)/sizeof(char));

	do
	{
		int success = parser(cmds);  //parse commands
		if(success == 0)
		{
			Command *cmd; 

			for(cmd = cmds; cmd != NULL && cmd->tokens != NULL; cmd = cmd->link) 
			{
				int i;
				for(i = 0; i < cmd->num_tokens; i++)
				{
					if(cmd->tokens[i][0] == '$')
					{
						Variable *var = NULL;
						if((var = Get_Var(vars, (cmd->tokens[i])+1)) != NULL)
						{
							cmd->tokens[i] = realloc(cmd->tokens[i],strlen(var->value)+1);
							strcpy(cmd->tokens[i],var->value);
						}
					}
				}
			}

			for(cmd = cmds; cmd != NULL && cmd->tokens != NULL; cmd = cmd->link)
			{
				execute(cmd);
			}

			cmds = reset_commands(cmds);
		}
	}while(!end); 
	return 0;
}

void execute(Command *cmd)
{
	//implementation of pseudo-piping, this relies on tmp files to take output and redirect back to input
	if(cmd->pipe && cmd->link != NULL)
	{
		//add number to pseudo pipe file to incrament for n-pipes
		char *pipe_file = malloc(strlen(cmd->tokens[0])+3);
		pipe_file[0] = '.';
		strcpy(pipe_file+1, cmd->tokens[0]);
		pipe_file[strlen(cmd->tokens[0])+1] = '0';
		pipe_file[strlen(cmd->tokens[0])+2] = '\0';
		while(access(pipe_file,R_OK) >= 0) 
		{
			pipe_file[strlen(pipe_file)-1] = pipe_file[strlen(pipe_file)-1]+1;
		}

		//redirect output
		cmd->redirect_out = true;
		free(cmd->redirect_out_file);
		cmd->redirect_out_file = malloc(strlen(pipe_file)+1);
		strcpy(cmd->redirect_out_file, pipe_file);

		//redirect input
		cmd->link->redirect_in = true;
		free(cmd->link->redirect_in_file);
		cmd->link->redirect_in_file = malloc(strlen(pipe_file)+1);
		strcpy(cmd->link->redirect_in_file, pipe_file);

		//delete tmp file when done
		Command *rm_cmd = allocate_new_command(cmds);

		char **rm_tok = allocate_new_token(rm_cmd);
		(*rm_tok) = malloc(strlen("rm")+1);
		strcpy((*rm_tok),"rm");

		char **file_tok = allocate_new_token(rm_cmd);
		(*file_tok) = malloc(strlen(pipe_file)+1);
		strcpy((*file_tok),cmd->redirect_out_file);
	}

	//setup for redirection, opens files.
	if(cmd->redirect_in)
	{
		if(access(cmd->redirect_in_file,R_OK) >= 0)  
		{
			cmd->redirect_in_fd = dup(fileno(stdin));
			freopen(cmd->redirect_in_file, "r", stdin);
		} 
		else 
		{
			perror("techShell");
			return;
		}
	}

	if(cmd->redirect_out)
	{
		fflush(stdout);
		fgetpos(stdout, &(cmd->redirect_out_pos));
		cmd->redirect_out_fd = dup(fileno(stdout));
		freopen(cmd->redirect_out_file, "w", stdout);
	}

	//All of these are the built-in commands
	if(strcmp(cmd->tokens[0],"exit") == 0)
	{
		end = true;    //exits shell
	} 

	//sets a variable value to a given string
	else if(strcmp(cmd->tokens[0], "set") == 0)
	{
		if(cmd->tokens[2] != NULL)
		{
			vars = Set_Var(vars, cmd->tokens[1], cmd->tokens[2]);
		}
		else if(cmd->tokens[1] != NULL)
		{
			vars = Set_Var(vars, cmd->tokens[1], "");
		}
		else
		{
			printf("techShell: No variable given.\n");
		}
	}  

	//list the set variables
	else if(strcmp(cmd->tokens[0], "list") == 0)
	{
		Variable *var;
		for(var = vars; var != NULL; var = var->link)
		{
			printf("%s:%s\n",var->name, var->value);
		}
	}
	
	//print current directory
	else if(strcmp(cmd->tokens[0], "pwd") == 0)
	{
		printf("%s\n",cwd);   //Prints current working directory
	}
	
	//change directory
	else if(strcmp(cmd->tokens[0], "cd") == 0)
	{
		if(cmd->tokens[1] != NULL)
		{
			chdir(cmd->tokens[1]); //changes current directory
		}
		else
		{
			chdir(getenv("HOME")); //if no token after cd prints current directory
		}
		getcwd(cwd, sizeof(cwd)/sizeof(char));
	}

	//any other commands are launched from here
	//currently only is able to accept 1 token of input
	else
	{
		if((cmd->pid = fork()) == 0) //executes if child process (pid == 0)
		{
			if(execvp(cmd->tokens[0],cmd->tokens)<0)  
			{
				perror("techShell");
				exit(1);      //if no tokens return error
			}
		}
		else    //If parent process wait for child to execute
		{
			wait(&(cmd->status));
		}
	}

	//finishing redirection, closes files and resets back to stdout 
	if(cmd->redirect_in)
	{
		dup2(cmd->redirect_in_fd, fileno(stdin));
		close(cmd->redirect_in_fd);
	}

	if(cmd->redirect_out)
	{
		fflush(stdout);
		dup2(cmd->redirect_out_fd, fileno(stdout));
		close(cmd->redirect_out_fd);
		clearerr(stdout);
		fsetpos(stdout, &(cmd->redirect_out_pos));        
	}
}
