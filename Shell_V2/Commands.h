#ifndef COMMAND_TS_H
#define COMMAND_TS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TOKENS 32
struct command
{
	char **tokens;
	int num_tokens;
	int pid;
	int status;
	bool pipe; 
	int pipe_fd[2];

	bool redirect_in;
	char *redirect_in_file;
	int redirect_in_fd;
	bool redirect_out;
	bool redirect_append;
	char *redirect_out_file;
	int redirect_out_fd;
	fpos_t redirect_out_pos;

	struct command *link;
};
typedef struct command Command;

Command *allocate_new_command(Command *cmd);
Command *reset_commands(Command *cmd);

char **allocate_new_token(Command *cmd);

#endif
