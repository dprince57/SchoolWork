/*
  read a file one character at a time.
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int
main(int argc, char *argv[])
{
  FILE * f = stdin;
  if (argc > 1) {
    f = fopen(argv[1], "r");
    if (f == NULL) {
      perror("error");
      exit(0);
    }
  }

  int ch;
  int space_count = 0;
  while ((ch = fgetc(f)) != EOF) {
    printf("%c", toupper(ch));
    if (ch == ' ') space_count++;
  }
  
  fclose(f); f = NULL;

  printf("\n\nthere were %d spaces.\n", space_count);
  
  return 0;
}


