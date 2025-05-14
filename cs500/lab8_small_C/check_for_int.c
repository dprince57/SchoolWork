#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  // lab8 - ask for a phone number, and keep asking until they use
  // the correct format
  printf("Give me a phone number please in the format of (ddd)-ddd-dddd: \n");
  
  /*
    Give me an integer please: asdf
      Bad input, please try again.
   */
  char s[100];
  int area, first, second;
  int number_read = 0;

  do {
    /*if (scanf("%d", &number) != 1) {
      printf("  Bad input, please try again.\n");
      }
      else {
      printf("Thanks!\n");
      }*/
    printf("Give me an integer please: ");
    if (scanf("%99s", s) != 1) {
      printf("Okay, goodbye.\n");
      return 0;
    }
    // now, try to convert to int
    if (sscanf(s, "(%3d)-%3d-%4d", &area, &first, &second) != 3){
        printf("  Bad input, please try again.\n");
    }else {
      printf("Thanks!\n");
      number_read = 1;
    }
  } while (number_read == 0);

  return 0;
}
