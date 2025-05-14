#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // printing the arguments
  for(int i=0; i < argc; i++) {
    printf("%s\n", argv[i]);
  }

  // let's check if they are in alphabetical order
  /*
      argv[0]    argv[1]  argv[2]   argv[3]
    ./cmd_args.o apple    ball      dog
      In alphabetcal order
    ./cmd_args.o apple dog ball
      Not in order, dog should be after ball.
   */

  int all_ok = 1;
  for(int i=2; i < argc; i++) {
    // check if argv[i] is after argv[i-1]
    if (strcmp(argv[i], argv[i-1]) < 0) {
      printf(" Not in order, %s should be after %s.\n",
	     argv[i-1], argv[i]);
      all_ok = 0;
    }
  }
  if (all_ok) printf("In alphabetical order\n");

  /*
    apple   Ball   dog
    97      66   100
    If we don't like this, then we have to write our own
    strcmpi
   */

  /*
    Say we wanted to
    ./cmd_args.o 1 2 3
     1+2+3 = 6

    then we need to convert the argv[i], use atoi, strtol
   */
  
  return 0;
}
