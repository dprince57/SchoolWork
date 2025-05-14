/*
  read a file one character at a time.
 */



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



int
main(int argc, char *argv[])
{
  FILE * f = stdin; // f is a FILE pointer
  if (argc > 1) {
    f = fopen(argv[1], // filename, a string, with an absolute path or a relative
	      "r");    // string literal, char *, specifying how to open, "r" for read, "w" for write
    if (f == NULL) {
      perror("error");
      exit(0);
    }
  }
  // note: with a FILE *, there are "f" versions of printf, scanf, ... fprintf, fscanf

  int ch;
  int space_count = 0;
  int colon_count = 0;
  while ((ch = fgetc(f)) != EOF) { // read a character, check if it's != EOF
    printf("%c", toupper(ch));
    if(ch == ' ')space_count++;
    if(ch == ';')colon_count++;
    if(ch == '\n')printf("\n");
  }

  fclose(f); f = NULL;

  printf("\n\nthere were %d spaces.\nThere were %d semi colons\n", space_count,colon_count);

  return 0;
}


