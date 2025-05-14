#include <stdio.h>

/* usage: a.out ^number^ */

int main(int argc,char argv[])
{
  int i;
  int num;
  float ans;
  num = argv[1];
  for(i=0; i < num; i++)
  {
    ans = num % i;
    if (ans == 0 && num != i)
    {  
      printf("Number is not prime!\n");
      return 0;
    }
  }
  printf("Number is prime!\n");
  return 1;
}
