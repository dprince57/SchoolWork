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
  // create empty fa structure
  fasta_t *fa = fasta_new();

  // open a fasta text file
  FILE *f = fopen("example.fa", "r");
  if (f == NULL) {
    perror("example.fa");
    exit(0);
  }
  // read from the text file into our structure
  fasta_read(f, fa);
  fclose(f); f = NULL;

  // print the sequences
  fasta_print(fa);

  return 0;
}


