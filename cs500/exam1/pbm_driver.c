/*
  Natural things we want to do...
  row_count
  max e_score
  min e_score
  rows with e_score >= cutoff
  basic stats: median e_score, 1st/3rd quartiles, ...
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pbm.h"

int main(int argc, char *argv[]) {
  /*
    lab5: make the program so it requires at least 1 command line argument and uses
    that as the file name to try to open with fopen.

    lab5: make the program so it handles the command-line arguments as Jeff's
    program does.
  */

  
  // lab5: if --help is given as the first or second command-line argument,
  //  print a usage statement. Also, if no arguments were given, print the usage
  //  statement. call pbm_help and then exit.
  if(argc == 1 || strcmp(argv[1],"--help") == 0){pbm_help();exit(0);}
  //if(strcmp(argv[1],"--help") == 0){pbm_help();exit(0);}

  
  // create empty pbm structure
  pbm_t *pbm = pbm_new();

  // open a fasta text file
  char * filename = argv[1];
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror(filename);
    exit(0);
  }
  // read from the text file into our structure
  pbm_read(f, pbm);
  fclose(f); f = NULL;

  // lab5 - only print if the --print option was given

  // lab4 - process the rest of the command-line arguments. you should loop through
  // argv from index 2 to the end. each time in the loop, check if the argument is
  // one of the ones we expect, and if so call the appropriate function that is defined
  // in pbm.c and pbm.h
  //
  // note: for --large_escore and --small_escore, you will need to pull out the
  //  parameter after the = in the argument, and make a call to pbm_filter_escores
  //  using that value.
  int args = 0;
  if(argc > 2)args = 1;
  for(int i = 2; args; i++){
    if(argv[i] == NULL)args = 0;
    else if(strcmp(argv[i], "--help") == 0)pbm_help();
    else if(strcmp(argv[i], "--print") == 0)pbm_print(pbm);
    else if(strcmp(argv[i], "--row_count") == 0)printf("%d\n",pbm_row_count(pbm));
    else if(strcmp(argv[i], "-max_median") == 0)pbm_median(pbm);
    else if(strcmp(argv[i], "--max_escore") == 0){pbm_row_print(pbm_max_escore(pbm));}
    else if(strcmp(argv[i], "--min_escore") == 0){pbm_row_print(pbm_min_escore(pbm));}
    else if(strcmp(argv[i], "--avg_escore") == 0){printf("Average escore: %.6f\n",pbm_avg_escore(pbm));}
    //strncmp used to only look at first 15 char of argv. Remembered a way to do this from past ISU, used google to find it on Cplusplus website.
    else if(strncmp(argv[i], "--large_escore=", 15) == 0){
      pbm_filter_escores(pbm, -100, atof(argv[i] + 15));
    }
    else if(strncmp(argv[i], "--small_escore=", 15) == 0){
      pbm_filter_escores(pbm, atof(argv[i] + 15), 100);
    }
  }
  // lab5 - call the pbm_free function to free all memory.
  // if you run the program with valgrind, it should say that there are no
  // leaks or errors
  pbm_free(pbm);

  return 0;
}


