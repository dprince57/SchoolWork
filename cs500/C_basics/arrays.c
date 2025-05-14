#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int grades[5]; // an array of 5 integers
  grades[0] = 99;
  grades[1] = 10;
  grades[2] = 55;
  grades[3] = 77;
  grades[4] = 98;

  // this is a buffer overflow
  grades[5] = 100;
  // though probably the program does not crash, but
  //  may not be correct - we just set something in
  //  memory that we weren't supposed to

  // a more severe buffer overflow, probably going to
  // crash
  for(int i=0; i < 1000; i++) {
    grades[i] = i;
    printf("%d ", i);
  }
  // Segmentation fault - using a part memory we're not
  //   supposed to.

  return 0;
}
