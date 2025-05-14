#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Goal: ask for 3 grades, and print the average.
*/

int main(int argc, char *argv[]) {

  // ask for a grade
  int i;
  float total = 0;
  for(i=0; i < 3; i++) {
    //printf("%d\n", i);
    printf("Grade please (0-100): ");
    // int, string, char, double/float
    float f;
    scanf("%f", &f);
    total += f;
  }
  //printf("After loop, i = %d\n", i);

  printf("Average: %f\n", total / 3);
  return 0;
}
