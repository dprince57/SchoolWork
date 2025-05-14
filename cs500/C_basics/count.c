#include <stdio.h>
#include <stdlib.h>
/*
    Goal:
    10
    9
    8
    ...
    1
    Blastoff!
*/
//23456789012345678901234567890123
int main(int argc, char *argv[]) {

  int i;
  for(i=10; i >= 1; i--) {
    printf("%d\n", i);
  }
  /*
   0. init
   1. check condition
   2. run the body of the loop
   3. increment
   Go to 1.
  */
  //printf("Note: i = %d\n", i);
  printf("Blastoff!\n");


  return 0;
}
