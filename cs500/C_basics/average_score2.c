#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Goal: ask for grades as long as they type a positive number, and print the average.
*/

int main(int argc, char *argv[]) {

  // ask for a grade
  int count = 0;
  float total = 0;
  while (1) {
    printf("Grade please (0-100, -1 to stop): ");
    // int, string, char, double/float
    float f;
    scanf("%f", &f);
    if (f < 0) {
      break;
    }
    total += f;
    count ++;
  }
  //printf("After loop, i = %d\n", i);

  printf("Average: %f\n", total / count);
  return 0;
}
