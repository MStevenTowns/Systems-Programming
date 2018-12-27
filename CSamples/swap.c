#include <stdio.h>
//swap two values
void swap(int* iPtrX,int* iPtrY);
void fakeswap(int x, int y);
int main()
{
  int x = 10;
  int y = 20;
  int *p1 = &x;
  int *p2 = &y;
  printf("before swap: x=%d y=%d\n",x,y);
  swap(p1,p2);
  printf("after swap: x=%d y=%d\n",x,y);

  printf("------------------------------\n");
  printf("before fakeswap: x=%d y=%d\n",x,y);
  fakeswap(x,y);
  printf("after fakeswap: x=%d y=%d",x,y);
  return 0;
}
void swap(int* iPtrX, int* iPtrY)
{
  int temp;
  temp = *iPtrX;
  *iPtrX = *iPtrY;
  *iPtrY = temp;
}
void fakeswap(int x,int y)
{
  int temp;
  temp = x;
  x = y;
}
