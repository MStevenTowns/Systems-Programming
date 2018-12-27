#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

char str[100];
static char *ptr;

char *tokenize(char* string)
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
		
		while((*ptr==' ' || *ptr=='\t'))
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
	FILE *inputFile;
	FILE *outputFile;
	char c;
	int i;
	char *p_str,*token;
	char *tokens[100];
	char input[100];
	//char output[1024];
	//char inFile[100];
	char outFile[100];
	while(1)
	{
		outputFile=NULL;
		inputFile=NULL;
		i=0;
		for(int i=0;i<99; i++)//make sure inputs are null
		{
			tokens[i]='\0';
			input[i]='\0';
			outFile[i]='\0';
			//inFile[i]='\0';
		}
		
		printf("\nTowns_Shell: ");
		scanf("%[^\n]",str);
		while((c = getchar()) != '\n' && c != EOF);//eat the \n at the end of scanf
 
		for (i=0, p_str=str; ; i++, p_str=NULL)//tokenize everything
		{
			token = tokenize(p_str);
			if (token == NULL)
			break;
			tokens[i]=token;
		}
		
		i=1;
		while(tokens[i]!='\0')//parse tokens into varius pieces
		{
			if(*tokens[i]=='<')
			{
				i++;
				inputFile=fopen(tokens[i],"r");
				//fscanf(inputFile, "%c", input);
				fscanf(inputFile, "%[^\n]", input);
				fclose(inputFile);
			}
			else if(*tokens[i]=='>')
			{
				i++;
				outputFile=fopen(tokens[i], "w");
			}
			else
			{
				for(int j=0;j<strlen(tokens[i]);j++)
				{
					input[(int)strlen(input)]=tokens[i][j];
				}
			}
			
			i++;
		}
		//printf("\n%s\n", input);
		//printf("\ninFile: %s",inFile);
		//printf("\noutFile: %s",outFile);
		
		if(strcmp(tokens[0],"cd")==0)
		{
			if (chdir(input) != 0)
				perror("chdir() error()");
		}
		else if(strcmp(tokens[0],"pwd")==0)
		{
			char cwd[1024];

			if (chdir("./") != 0)
				perror("chdir() error()");
			else
			{
				if (getcwd(cwd, sizeof(cwd)) == NULL)
					perror("getcwd() error");
				else
					if(strcmp(outFile,"")!=0)
					
					fprintf(outputFile, "%s/\n", cwd);
					else printf("%s/\n", cwd);
			}
		}
		else if(strcmp(tokens[0],"exit")==0)
		{
			exit(0);
		}
		else//not built in
		{	
			pid_t pid;
			// fork another process 
			pid = fork();
			if (pid < 0) //error
			{ 
				fprintf(stderr, "Fork Failed");
				exit(-1);
			}
			else if (pid == 0) //child process started
			{ 
				char *cmd[]={tokens[0],input,(char *)0};
				if(strcmp(input,"")==0)//0 if same
				{
					//printf("\n null input\n");
					cmd[1]=NULL;
				}
				
				if(strcmp(outFile,"")!=0)
				outputFile=freopen(outFile, "w+", stdout);
				
				execvp(tokens[0], cmd);
			}
			else //parrent process
			{
				// parent will wait for the child to complete 
				wait(NULL);
				//printf ("Child Complete");
				//exit(0);
			}
		}
		
	}
}
