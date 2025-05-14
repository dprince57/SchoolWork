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
  // create empty pbm structure
  pbm_t *pbm = pbm_new("CHES-1-like");

  // open a fasta text file
  char * filename = "/u1/junk/kinne/ahmad-lab/data_files/CHES-1-like_8mers_11111111.txt";
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror(filename);
    exit(0);
  }
  // read from the text file into our structure
  pbm_read(f, pbm);
  fclose(f); f = NULL;

  pbm_print(pbm);

  return 0;
}


