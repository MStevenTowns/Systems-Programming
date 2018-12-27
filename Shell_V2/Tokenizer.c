#include "Tokenizer.h"

char *next_segment()
{
	static bool newline = false; 
	if(newline)
	{
		newline = false;
		return NULL;
	}

	char * segment = NULL;
	int character;

	while((character = fgetc(stdin)) == ' ' || character == '\t'); 
	while(character != ' ' && character != '\t')//parses command when whitespace is encountered
	{
		if(character == '\n')
		{
			if(segment != NULL) 
			newline = true;
			break;
		}
		int segment_length = 0;
		if(segment != NULL)
		segment_length = strlen(segment);

		char *concat = calloc(segment_length+2,sizeof(char));

		if(segment_length > 0)
		strcpy(concat,segment);
		*(concat+segment_length) = character;
		*(concat+segment_length+1) = '\0';

		free(segment);
		segment = concat;
		character = fgetc(stdin);
	}
	if(character == ' ' || character == '\t')
	{
		ungetc(character, stdin);
	}
	return segment;
}

int parser(Command *cmds)
{
	printf("%%techShell> ");
	bool redirect = false;
	int direction = 0;
	Command *cmd = cmds;
	char *segment;
	while((segment = next_segment()) != NULL)
	{
		bool parsed = false;
		do
		{ //stores special symbols such as redirection < >
			char **special_chars = get_special_char(segment);
			char *minimum = NULL;
			int i;
			for(i = 0; i < 6; i++)
			{
				if(special_chars[i] != NULL)
				{
					if(minimum != NULL)
					{
						if(special_chars[i] < minimum)
						minimum = special_chars[i];
					}
					else
					minimum = special_chars[i];
				}
			}
			if(minimum == NULL)
			{
				fprintf(stderr,"INVALID INPUT");
				return INCOMPLETE_PARSE;
			}
			//All chars before special char is a regular token
			char character = (*minimum);
			*minimum = '\0';
			if(redirect)
			{
				if(strlen(segment) > 0)
				{
					if(direction == REDIRECT_INPUT)
					{
						cmd->redirect_in_file = malloc(strlen(segment)+1);
						strcpy(cmd->redirect_in_file, segment);
					}
					else if(direction == REDIRECT_OUTPUT)
					{
						cmd->redirect_out_file = malloc(strlen(segment)+1);
						strcpy(cmd->redirect_out_file, segment);
					}
					else
					{
						fprintf(stderr,"INVALID REDIRECTION");
						return INCOMPLETE_PARSE;
					}
					redirect = false;
				}
			}
			else if(strlen(segment) > 0) //chars before minimum
			{
				char **tok = allocate_new_token(cmd);
				(*tok) = malloc(strlen(segment)+1);
				strcpy((*tok),segment);
			}
			char *remainder = malloc(strlen(minimum+1)+1);
			strcpy(remainder, minimum+1);
			free(segment);
			segment = remainder;
			minimum = NULL;
			char *closing;
			switch(character)
			{
				//checks special commands
				case '<':
					cmd->redirect_in = true;
					redirect = true;
					direction = REDIRECT_INPUT;
					break;
				case '>':
					cmd->redirect_out = true;
					redirect = true;
					direction = REDIRECT_OUTPUT;
					break;
				case '\0':
					parsed = true;
					break; 
				case '|':
					cmd->pipe = true;
				case ';':
					if(redirect)
					{
						fprintf(stderr,"No Redirection");
						return INCOMPLETE_PARSE;
					}
					allocate_new_command(cmds);
					cmd = cmd->link;
					break;
				case '"':
					if((closing = strchr(segment,'"')) != NULL)
						(*closing) = '\0';
					char **tok = allocate_new_token(cmd);
					(*tok) = malloc(strlen(segment)+1);
					strcpy((*tok),segment);
					if(closing != NULL)
					{
						char *remainder = malloc(strlen(closing+1)+1);
						strcpy(remainder, closing+1);
						free(segment);
						segment = remainder;
					}
					else
					{
						(*segment) = '\0';
						char next_char = fgetc(stdin);
						while(next_char != '"')
						{
							if(next_char == '\n')
							{
								fprintf(stderr,"No Redirection");
								return INCOMPLETE_PARSE;
							}
							int seg_length = 0;
							if((*tok) != NULL)
								seg_length = strlen(*tok); 
							char *concat = calloc(seg_length+2,sizeof(char));
							if(seg_length > 0)
								strcpy(concat,(*tok));
							*(concat+seg_length) = next_char;
							*(concat+seg_length+1) = '\0';
							free((*tok));
							(*tok) = concat;
							next_char = fgetc(stdin);
						}
					}
			}
		} while(!parsed);
		free(segment);
		segment = NULL;
	}
	if(cmds->tokens == NULL)
		return INCOMPLETE_PARSE;
	else
		return 0;
}

char **get_special_char(char *string)
{
	char **chars = calloc(6,sizeof(char*)); 
	chars[CHAR_PIPE_OFFSET] = strchr(string,'|');
	chars[CHAR_SEMICOLON_OFFSET] = strchr(string,';');
	chars[CHAR_LESSTHAN_OFFSET] = strchr(string,'<');
	chars[CHAR_GREATERTHAN_OFFSET] = strchr(string,'>');
	chars[CHAR_QUOTATION_OFFSET] = strchr(string, '"');
	chars[CHAR_NULLTERM_OFFSET] = strchr(string,'\0'); 
	//chars[CHAR_PIPE_OFFSET] = strchr(string,'|');
	//chars[CHAR_SEMICOLON_OFFSET] = strchr(string,';');
	return chars;
}
