#include <stdio.h>
#include <string.h>

int main ()
{
  char command[50];

  strcpy( command, "ls -l" );
  system(command);

  sleep(1000);

  return(0);
}
