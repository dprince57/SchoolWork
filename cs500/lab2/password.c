#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Goal: ask for password, keep asking until they type "gcc"
*/

int main(int argc, char *argv[]) {

  printf("password: ");
  char s[10];      // array of 10 characters, C string
  scanf("%9s", s); // reads at most 99 characters from the user, until they type enter
  int counter = 10;
  // don't do this - potential buffer overflow
  //scanf("%s", s);

  while (counter != 0) { // you get 10 chances
    // body
    if(strcmp(s, "gcc") == 0 || strcmp(s, "cs500") == 0 || strcmp(s, "lab2") == 0)break; //is s a password?
    printf("Password incorrect. Chances remaining %d\npassword: ",counter);
    scanf("%9s", s);
    counter--;
  }

  return 0;
}
