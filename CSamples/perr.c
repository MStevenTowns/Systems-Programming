#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
  FILE *fh;
 
  if ((fh = fopen("mylib/myfile","r")) == NULL)
    {
      perror("Could not open data file");
      abort();
    }
}
