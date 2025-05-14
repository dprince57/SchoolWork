/*
  read a file by line, and print in reverse order

 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
  FILE *stream;
  char *line = NULL;
  
  size_t len = 0;
  ssize_t nread;
  
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  //char *lines[100];
  int max_lines = 10;
  char **lines = (char **)malloc(sizeof(char *) * max_lines);
  int line_no = 0;

  // getline will do a malloc or realloc
  while ((nread = getline(&line,// ->  line: NULL
			  &len, // ->  len: 0
			  stream)) != -1) {
    lines[line_no] = strdup(line); // like malloc
    line_no++;
    
    if (line_no >= max_lines) {
      // increase our space by 2
      printf("lines increasing, currently %d at %p\n",
	     max_lines, lines);
      max_lines *= 2;
      lines = (char **)realloc(lines,
			       sizeof(char *)*max_lines);
      printf("lines increased, currently %d at %p\n",
	     max_lines, lines);
      //break;
    }
  }

  for(int i=line_no-1; i >= 0; i--) {
    printf("%5d (%p): %s", i+1, lines[i], lines[i]);
  }
  
  free(line);
  fclose(stream);
  exit(EXIT_SUCCESS);
}


