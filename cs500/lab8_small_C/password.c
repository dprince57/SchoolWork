#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Goal: ask for password, keep asking until they type "gcc"

  lab8 - also accept any of the following: cs500 lab8 fun

  lab8 - if they get it wrong 3 times, then exit

  lab8 - if they get it correct print success
*/

int main(int argc, char *argv[]) {

  printf("password: ");
  char s[10];      // array of 10 characters, C string
  scanf("%9s", s); // reads at most 99 characters from the user, until they type enter
  int times = 1;
  // don't do this - potential buffer overflow
  //scanf("%s", s);

  while (1){
    if(strcmp(s, "gcc") == 0 || strcmp(s, "cs500") == 0 || strcmp(s,"lab8") == 0 || strcmp(s,"fun") == 0) {
        printf("Password correct. Welcome.\n");
        break;
    }
    if(times == 3){printf("Failed password 3 times. Good bye.\n");break;}
    times++;
    printf("password: ");
    scanf("%9s", s); 
  }

  // lab8
  
  return 0;
}
