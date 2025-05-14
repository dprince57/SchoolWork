#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  /*
      1
      2
    ...
     10
    ...
    100
   */
  for(int i=1; i <= 100; i++) {
    printf("%20ld**2 = %20ld\n", i, i*i);
  }

  printf("Max value for an unsigned long: %lu\n", (1L << 64) -1);
  printf("Max value for an unsigned long: %lu\n", -1L);


  return 0;
}
