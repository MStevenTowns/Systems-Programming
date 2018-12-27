#include <stdio.h>
#include <stdlib.h>

extern void functionA ();

int main ()
{
  /* register the termination function */
  atexit(functionA );
   
  printf("Starting  main program...\n");

  printf("Exiting main program...\n");

  /*  return(0); */
}
