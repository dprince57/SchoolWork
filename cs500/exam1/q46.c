// copy/paste q46 from the canvas exam, fix the problem, and
// leave a comment at the top saying what was wrong.
//
// e.g., 
// q46 answer: (0) missing free of malloc’ed memory
// q46 explanation: it was ...

//Q46 answer: [4] missing var initiation
//Q46 explanation: If you never give it the value NULL you cannot pass it to getline() bad behavior will happen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[]) {
  //
  // reads in from stdin until EOF and prints the lines with line #s on the front

  char * line = NULL;
  size_t max_length = 0;
  ssize_t ret_val = 0;
  int line_number = 1;

  while ((ret_val = getline(&line, &max_length, stdin)) > 0) {
    printf("%4d: %s", line_number, line);
    line_number ++;
  }

  if (line != NULL) free(line);

  return 0;
}
