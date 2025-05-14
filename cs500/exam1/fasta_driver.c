/*
  Status - program reads in a fasta file into a fasta_t and prints it.

  Next todo 
  - /do/ something useful or interesting with the fasta that has 
    been read in - letter frequency counts, GC content, total length, etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fasta.h"

int main(int argc, char *argv[]) {
  /*
    lab4: make the program so it requires at least 1 command line argument and uses
    that as the file name to try to open with fopen.

    lab4: make the program so it handles the following command-line arguments
      --help - prints a usage statement                                           DONE
      --print - prints all sequences                                              DONE
      --seq_count - prints # of sequences                                         DONE
      --max_length - prints the id and length of the longest sequence             DONE
      --min_length - prints the id and length of the shortest sequence            DONE
      --GC - prints the percentage of the sequence letters that are g, G, c, or C DONE
   */
  int args = 0;
  if(argc > 2)args = 1;
  if(argc < 2){
    fasta_help(); //use fasta help to print usage statement
    exit(0); //leave the program NOW
  }
  if(strcmp(argv[1], "--help") == 0){
    fasta_help(); //use fasta help to print usage statement
    exit(0); //leave the program NOW
  }
  // lab4: if --help is given as the first or second command-line argument, print
  //  a usage statement. Also, if no arguments were given, print the usage statement.
  //  call fasta_help and then exit.

  // create empty fa structure
  fasta_t *fa = fasta_new();

  // open a fasta text file
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    perror(argv[1]);
    exit(0);
  }
  // read from the text file into our structure
  fasta_read(f, fa);
  fclose(f); f = NULL;

  // lab4 - process the rest of the command-line arguments. you should loop through
  // argv from index 2 to the end. each time in the loop, check if the argument is
  // one of the ones we expect, and if so call the appropriate function that is defined
  // only call fasta_print if --print was given.
  int i = 2;
  while(args){
    if(argv[i] == NULL)break;
    if(strcmp(argv[i],"--help") == 0){fasta_help();}
    if(strcmp(argv[i],"--print") == 0)fasta_print(fa);
    if(strcmp(argv[i],"--seq_count") == 0)printf("%d\n",fasta_seq_count(fa));
    if(strcmp(argv[i],"--GC") == 0)printf("%.2f%% GC\n",fasta_GC(fa));
    if(strcmp(argv[i],"--max_length") == 0)seq_print(fasta_max_length(fa));
    if(strcmp(argv[i],"--min_length") == 0)seq_print(fasta_min_length(fa));
    if(strcmp(argv[i],"-last_letters") == 0)fasta_last(fa);

    i++;
  }
  // lab4 - call the fasta_free function to free all memory.
  // if you run the program with valgrind, it should say that there are no
  // leaks or errors
  fasta_free(fa);
  return 0;
}


