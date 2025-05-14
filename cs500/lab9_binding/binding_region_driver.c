
#include "binding_region.h"

int main(int argc, char *argv[]) {

  /*
    ./binding_region_driver.o fasta pbm
   */
  if (argc < 3) {
    printf("Usage: %s fasta_filename pbm_filename [pbm_filename2] [pbm_filename3] ...\n", argv[0]);
    exit(0);
  }

  // read in the FA file
  char *filename = argv[1];
  fasta_t *fa = fasta_new();
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror(filename);
    exit(0);
  }
  fasta_read(f, fa);
  fclose(f); f = NULL;
  // for each seq in fa->seqs, print it
  for(int i=0; i < fa->num_seqs; i++)
    seq_print_pbms_brs(fa->seqs[i], NULL, NULL);

  

  // also make a brs_t to store all of the binding regions from all of the
  // transcription factors. so the loop below will store both in this one
  // and in the one just for the individual TF.
  // search for binding regions
  brs_t *regions_all = brs_new();

  // keep a list of all of the pbms, we'll need them all together for
  // printing at the end
  pbms_t *pbms_all = pbms_new();

  // remaining command-line arguments are pbm files to check
  for(int k=2; k < argc; k++) {
    // read in the pbm file
    filename = argv[k];
    printf("%s\n", filename);
    pbm_t *pbm = pbm_new(filename);
    f = fopen(filename, "r");
    if (f == NULL) {
      perror(filename);
      exit(0);
    }
    pbm_read(f, pbm);
    fclose(f); f = NULL;


    // add pbm to list of all pbms
    pbms_add(pbms_all, pbm);

    // search for binding regions
    brs_t *regions = brs_new();
    float escore_cutoff = 0.3;
    int min_length = 11;

    brs_find(regions, fa, pbm, escore_cutoff, min_length);
    // copy into regions_all as well.
    brs_find(regions_all, fa, pbm, escore_cutoff, min_length);

    
    // try to mutate

    for(int i=0; i < regions->num_regions; i++) {
      br_print(regions->regions[i]);
      br_seq_mutate(regions->regions[i], escore_cutoff-0.2, min_length, 2);

    }
    
    brs_free(regions);

    printf("\n");
  }

  // sort regions_all before printing
  brs_sort(regions_all);

  // print each of the sequences with escores and binding sites
  for(int i=0; i < fa->num_seqs; i++)
    seq_print_pbms_brs(fa->seqs[i], pbms_all, regions_all);

  // free memory
  brs_free(regions_all);
  pbms_free(pbms_all);
  fasta_free(fa);
  
  return 0;
}
