/*
  read a file and print line numbers.

  use getline, took code from geline man page.
 */



#include <stdio.h>
#include <stdlib.h>

/*
 ssize_t getline(char **restrict line, size_t *restrict len,
                       FILE *restrict stream) {
    *len = 120;
    *line = (char *) malloc ( sizeof(char) * *len);
}
 */

int
main(int argc, char *argv[])
{
  FILE *stream;
  
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  // lab8 - optional extra arguments say to print just the first
  // __ lines and just the last __ lines
  // printf("Usage: %s <file> [first_n_lines] [last_m_lines]\n");
  // If argc==2, print the whole file
  // If argc==3, print just the first first_n_lines lines
  // If argc==4, print the first first_n_lines, then a line of ---------, then the last last_m_lines
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }

  //            something                      != -1
  //printf("line = %p, len = %lu\n", line, len);
  /*
    if line is NULL, then getline will do this - 
    line = (char*) malloc(sizeof(char) * 120);
    len = 120;
   */
  int line_no = 1;
  while ((nread = getline(&line,// ->  line: NULL
			  &len, // ->  len: 0
			  stream)) != -1) {
    //printf("line = %p, len = %lu\n", line, len);
    //printf("Retrieved line of length %zd:\n", nread);
    //fwrite(line, nread, 1, stdout);

    // before printing, check if line is a blank line...
    // use strcmp
    
    printf("%5d: %s", line_no, line);
    
    line_no++;
  }

  if (line != NULL) {
    free(line);
    line = NULL;
  }
  
  fclose(stream);
  exit(EXIT_SUCCESS);
  return 0;
}


