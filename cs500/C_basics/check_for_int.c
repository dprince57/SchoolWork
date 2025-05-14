#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  /*
    Give me an integer please: asdf
      Bad input, please try again.
   */
  char s[100];
  int number;
  int number_read = 0;

  do {
    printf("Give me an integer please: ");
    /*if (scanf("%d", &number) != 1) {
      printf("  Bad input, please try again.\n");
      }
      else {
      printf("Thanks!\n");
      }*/
    if (scanf("%99s", &s) != 1) {
      printf("Okay, goodbye.\n");
      return 0;
    }
    // now, try to convert to int
    if (sscanf(s, "%d", &number) != 1) {
      printf("  Bad input, please try again.\n");    
    }
    else {
      printf("Thanks!\n");
      number_read = 1;
    }
  } while (number_read == 0);

  return 0;
}
