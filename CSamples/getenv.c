#include <stdio.h>
#include <stdlib.h>

int main ()
{
  printf("HOME : %s\n", getenv("HOME"));
  printf("ROOT : %s\n", getenv("ROOT"));
  printf("PATH : %s\n", getenv("PATH"));

  return(0);
}
