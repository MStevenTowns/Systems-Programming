#include "Commands.h"

Command *allocate_new_command(Command *cmd)//adds a new command to the list
{
	if(cmd == NULL)
		return NULL;

	Command *link;
	for(link = cmd; link->link != NULL; link = link->link);
	link->link = (Command*)malloc(sizeof(Command));
	memset(link->link, 0, sizeof(Command));
	return link->link;
}

Command *reset_commands(Command *cmd)// clears command line
{ 
	Command *link;
	Command *before;
	if(cmd == NULL)
	{
		link = (Command*)malloc(sizeof(Command));
		memset(link, 0, sizeof(Command));
		return link;
	}

	while(cmd != NULL)
	{
		before = NULL;

		for(link = cmd; link->link != NULL; link = link->link) { before = link; } //get link to command before last

		Command *last = link;
		int i;
		for(i = 0; i < last->num_tokens; i++)
		{
			free((last->tokens[i]));
			last->tokens[i] = NULL;
		}
		free(last->tokens);
		last->tokens = NULL;
		free(last->redirect_in_file);
		free(last->redirect_out_file);
		last->redirect_in_file = NULL;
		last->redirect_out_file = NULL;
		free(last); 

		if(before != NULL)
			before->link = NULL;
		else
			cmd = NULL;
	}

	link = (Command*)malloc(sizeof(Command));
	memset(link, 0, sizeof(Command));
	return link;
}

char ** allocate_new_token(Command *cmd)
{
	cmd->tokens = realloc(cmd->tokens, cmd->num_tokens+1);
	return (cmd->tokens+(cmd->num_tokens++));
}
