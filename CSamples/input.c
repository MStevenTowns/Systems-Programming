//reading input from console
#include <stdio.h>
int main()
{
  int num1;
  int num2;
  printf( "Please enter two numbers: " );
  scanf( "%d %d", &num1,&num2 );
  printf( "You entered %d %d\n", num1, num2 );
  return 0;
}
