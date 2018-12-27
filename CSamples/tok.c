#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char str[100];
enum {NOT_FOUND=0,FOUND};
static char *ptr;

char *mystrtok(char* string)
{
	char *p;
	if(string != NULL)
	{
		ptr=string;
		p=string;
	}
	else
	{
		if(*ptr == '\0')
		return NULL;

		p=ptr;
	}

	while(*ptr != '\0')
	{
		if(*ptr == ' ')
		{
			if(ptr == p)
			{
				p++;
				ptr++;
			}
			else
			{
				*ptr='\0';
				ptr++;
				return p;
			}
		}
		ptr++;
	}
	return p;
}

int main()
{
	int i;
	char *p_str,*token;

	printf("\n Enter a string to tokenize: ");
	scanf("%[^\n]",str);

	/* simple tokenizing */  
	for (i = 1, p_str = str; ; i++, p_str = NULL)
	{
		token = mystrtok(p_str);
		if (token == NULL)
		break;
		printf("\n%d: %s",i,token);
	}
	printf("\n");
}
