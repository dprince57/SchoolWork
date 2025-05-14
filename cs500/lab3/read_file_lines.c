
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
    added empty checker function.

    Purpose is to iterate through lines and check for whitespace. if the line is         only spaces or is just a newline we skip return 0 and skip the line. strcmp
    had no way to check if a line had a single space on it to this was my soultion.
*/
int empty_checker(const char *line){
    for(int i = 0;line[i] != '\0'; i++){
        if(!isspace(line[i])){
            return 0; 
        }
    }
    return 1;
}

 
  
   
int main(int argc, char *argv[])
{
  FILE *stream;

  char *line = NULL;
  size_t len = 0;
  ssize_t nread;


  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  stream = fopen(argv[1], "r");
  if (stream == NULL) {
    perror(argv[1]);
    exit(EXIT_FAILURE);
  }
  int blanks = 0;
  int line_no = 1;
  while ((nread = getline(&line, &len, stream)) != -1) {
    if(empty_checker(line)){
        blanks++;
    }else{
        printf("%5d: %s", line_no, line);
    }
    line_no++;
  }

  if (line != NULL) {
    free(line);
    line = NULL;
  }
  printf("Number of empty lines skipped: %d\n",blanks);

  fclose(stream);
  exit(EXIT_SUCCESS);
  return 0;
}


