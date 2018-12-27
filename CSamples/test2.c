
#include <stdio.h>
int sum(int a, int b);
int mult(int a, int b);
int combine(int (*f)(int,int), int (*g)(int,int), int a, int b);

int main() {
  int c = combine(sum, mult, 10, 20);
  printf("%d\n", c);
}

int sum(int a, int b) { return a + b; }

int mult(int a, int b) { return a * b; }

int combine(int (*f)(int,int), int (*g)(int,int), int a, int b) {
  return f(g(a,a),g(b,b));
}


