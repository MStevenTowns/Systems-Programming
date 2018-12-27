#include <stdio.h>
#include <errno.h>

extern int errno ;

int main ()
{
  FILE * pFile;
  pFile = fopen ("unexist.ent","rb");
  if (pFile == NULL)
    {
      printf( "Error Value is : %d, Error String is  %s\n", errno,  strerror(errno) );
    }
  else
    fclose (pFile);
  return 0;
}
