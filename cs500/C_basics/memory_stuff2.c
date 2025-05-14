#include <stdio.h>
#include <stdlib.h>

double hello;

int fun(int i, double y) {
  // declare a new variable called i, and do
  //  i = x from main;
  printf("in fun1...\n"
	 "  i = %d, y = %f\n"
	 "  &i = %p\n" // note: C is pass by value
	 "  &y = %p\n",
	 i, y, &i, &y);
  i = 0;
  y = 2.718;
  // note - variables do NOT get copied out
  return 1;
}


int main(int argc, char *argv[]) {

  double d = 3.14;
  printf("&d = %p\n", &d);
  
  char name[100];
  printf("Name: ");
  scanf("%99s", &name);
  printf("Hi %s\n", name);

  printf("%p\n", name);
  printf("%p\n", &name);

  int x = 7;
  printf("&x = %p\n", &x);

  printf("&fun = %p\n", fun);
  fun(x, d);

  printf("Now... x = %d, d = %f\n", x, d);

  int nums[10];
  printf("&nums = %p\n", &nums); // &x - 10*4

  int * nums2 = (int *) malloc(sizeof(int) * 10);
  printf("&nums2 = %p\n", nums2);
  // dynamic memory is on "the heap" - loose collection of memory

  printf("&hello, global = %p\n", &hello);
  return 0;
}
