#include <stdio.h>

main()
{
  int    fd;
  fpos_t pos;

  printf("stdout, before dup\n");

  fflush(stdout);
  fgetpos(stdout, &pos);
  fd = dup(fileno(stdout));
  freopen("stdout.out", "w", stdout);

  f();

  fflush(stdout);
}

f()
{
  printf("stdout in f()");
}
