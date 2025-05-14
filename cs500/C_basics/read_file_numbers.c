#include <stdio.h>
#include <stdlib.h>
/*
  Read in the numbers from the file, and ...

  print the average and max
 */

int main(int argc, char *argv[]) {

  FILE *f_in = stdin;

  if (argc > 1) {
    f_in = fopen(argv[1], "r");
    if (f_in == NULL) {
      perror("error");
      exit(0);
    }
  }

  // scanf %d loop
  int x;
  int total = 0;
  int max = 0;
  int first = 1;
  while (fscanf(f_in, "%d", &x) == 1) {
    //printf("%d\n", x);
    if (first) max = x;
    if (x > max) max = x;
    total += x;
    first = 0;
  }

  printf("total: %d\n", total);
  printf("max:   %d\n", max);
  
  return 0;
}
