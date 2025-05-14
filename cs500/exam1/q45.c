// copy/paste q45 from the canvas exam, fix the problem, and
// leave a comment at the top saying what was wrong.
// e.g., 
// q45 answer: (0) missing free of malloc’ed memory
// q45 explanation: it was ...





//q45 answer: (2) unsafe %s scanf
//explanation: if you let scanf go past the end of the array you will get a buffer overflow.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[]) {
  //
  // scanf strings until eof, and print out the total # characters in all of them
  char s[100];
  int val = 0;
  while (scanf("%99s", s) == 1) {
    val += strlen(s);
  }

  printf("%d\n", val);

  return 0;
}
