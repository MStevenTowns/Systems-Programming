#include <unistd.h>

int main(void)
{
  char *execArgs[] = { "echo", "Hello, World!", NULL };
  execvp("echo", execArgs);

  return 0;
}
