#include <stdio.h>
int main()
{
  int x;
  for(x=0;x<10;x++)
    {  
      if(x==5)
	{
	  continue;
	}
      printf("%d\n",x);
    }
  return 0;
}
