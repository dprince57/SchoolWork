#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // lab8 - assume the arguments are floating point numbers, and output
  // both the sum of all of them, and the product of all of them.
  float sum = 0.0;
  float product = 1.0;
  // printing the arguments
  for(int i=1; i < argc; i++) {
    sum += atof(argv[i]);
    product *= atof(argv[i]);
  }

  // lab8
  printf("Sum: %f\n", sum);
  printf("Product: %f\n", product);

  return 0;
}
