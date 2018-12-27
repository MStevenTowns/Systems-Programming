#include <stdio.h>
//swap two values
void swap(int x, int y);
int main()
{
  int x = 10;
  int y = 20;

  printf("before swap: x=%d y=%d\n",x,y);
  swap(x,y);
  printf("after swap: x=%d y=%d\n",x,y);

  printf("------------------------------\n");

}
void swap(int x,int y)
{
  int temp;
  temp = x;
  x = y;
}
