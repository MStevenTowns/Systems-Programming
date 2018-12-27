#include <stdio.h>
 
void func() {
  int x = 0; // x is initialized only once across three calls of func() and
  // the variable will get incremented three 
  //times after these calls. The final value of x will be 3.
  printf("%d\n", x); // outputs the value of x
  x = x + 1;
}
 
int main() { //int argc, char *argv[] inside the main is optional in the particular program
  func(); // prints 0
  func(); // prints 1
  func(); // prints 2
  return 0;
}
