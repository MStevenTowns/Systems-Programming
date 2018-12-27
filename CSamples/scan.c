#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char str[100];
enum {NOT_FOUND=0,FOUND};
static char *ptr;

 
int main()
{
  int i;
  char *p_str,*token;
 
  printf("\n Enter a string to tokenize: ");
  scanf("%[^\n]",str);
  p_str = str;
  printf("\n%s\n",p_str);
}
