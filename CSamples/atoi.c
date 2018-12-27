#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int val;
  char str[20];
   
  strcpy(str, "123456");
  val = atoi(str);
  printf("String value = %s, Int value = %d\n", str, val);

  strcpy(str, "CSC 222 class");
  val = atoi(str);
  printf("String value = %s, Int value = %d\n", str, val);

  return(0);
}
