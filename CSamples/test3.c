#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  int x = 1; 
  int* y = malloc(sizeof(int));
  *y = 2;

  if (fork() == 0) {
    x++; (*y)++;
  }

  if (fork() == 0) {
    x++; (*y)++;
  }

  printf("%d %d\n", x, y);
}

