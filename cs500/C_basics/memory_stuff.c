#include <stdio.h>
#include <stdlib.h>

void fun(int arg1, int arg2) {

  int x, y;
  printf("&arg2       = %p\n", &arg2);
  printf("&arg1       = %p\n", &arg1);
  printf("&x          = %p\n", &x);
  printf("&y          = %p\n", &y);
}

int global1, global2;

int main(int argc, char *argv[]) {

  printf("&argc       = %p\n", &argc);
  printf("&argv       = %p\n", &argv);
  
  int local_var;
  // & local_var pronounced "address of local_var"
  printf("&local_var  = %p\n", &local_var);

  int local_var2, local_var3;
  printf("&local_var2 = %p\n", &local_var2);
  printf("&local_var3 = %p\n", &local_var3);

  fun(5, 6);

  int local_var4;
  printf("&local_var4 = %p\n", &local_var4);
  
  printf("&global1    = %p\n", &global1); // globals, data
  printf("&global2    = %p\n", &global2);

  printf("&fun        = %p\n", &fun);     // code, "code"
  printf("&main       = %p\n", &main);

  int * array = (int *) malloc(sizeof(int) * 10); // the heap
  printf("&array      = %p\n", &array);
  printf("array       = %p\n", array);
  array[0] = 1;
  return 0;
}
