#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("Hello world!\n");
  printf("%d\n", 2 || 7);
  // 2 || 7
  // || is boolean or, will be 0 or 1
  // is 2 true or false? anything not 0 is true
  // 7 is not 0, also true
  // 1 || 1
  // 1

  return 0;
}
