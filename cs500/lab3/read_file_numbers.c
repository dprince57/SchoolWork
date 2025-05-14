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
  float count = 0.0;
  float total = 0.0;
  int indicator = 0; //this is our validator for increasing or decreasing.
  int last = 0;
  int max = 0;
  int min = 0;
  int first = 1; // TRUE
  while (fscanf(f_in, "%d", &x) == 1) {
    //printf("%d\n", x);
    if (first){max = min = x;last = x;} //Initialize our variables.

    if (x > max) max = x;
    if (x < min) min = x;

    if (x < last) indicator--;
    if (x > last) indicator++;

    total += x;
    first = 0;
    count++;
  }
  if(indicator > 0)     {printf("increasing order: yes\ndecreasing order: no\n");}
  else if(indicator < 0){printf("increasing order: no\ndecreasing order: yes\n");}
  else                  {printf("increasing order: no\ndecreasing order: no\n");}

  printf("max: %d\nmin: %d\naverage: %.1f\n", max,min,total/count);

  if(f_in != stdin){
    fclose(f_in);
  }

  return 0;
}
