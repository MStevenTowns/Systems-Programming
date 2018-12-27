#ifndef PARSER_TS_H
#define PARSER_TS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Commands.h"

#define REDIRECT_INPUT 1
#define REDIRECT_OUTPUT 2  
#define CHAR_PIPE_OFFSET 0 
#define CHAR_SEMICOLON_OFFSET 1
#define CHAR_LESSTHAN_OFFSET 2
#define CHAR_GREATERTHAN_OFFSET 3
#define CHAR_QUOTATION_OFFSET 4
#define CHAR_NULLTERM_OFFSET 5 
//#define CHAR_PIPE_OFFSET 0 
//#define CHAR_SEMICOLON_OFFSET 1
#define INCOMPLETE_PARSE 1

char *next_segment();
int parser(Command *cmds);
char **get_special_char(char *string);

#endif

