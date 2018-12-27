#include <stdio.h>

void inline test_inline_func1(int a, int b) {
  printf ("a=%d and b=%d\n", a, b);
}

int main() {

  int tmp;

  test_inline_func1(2,4);

  return 0;
}
