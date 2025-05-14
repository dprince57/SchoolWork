#ifndef BINDING_REGION_H
#define BINDING_REGION_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "pbm.h"
#include "fasta.h"
#include "combinations.h"
#include "all_values.h"


typedef 
struct BINDING_REGION {
  seq_t * seq;
  pbm_t * pbm;
  unsigned int start;
  unsigned int end;
} br_t;

typedef 
struct BINDING_REGIONS {
  br_t **regions;
  int max_regions;
  int num_regions;
} brs_t;


void br_print(const br_t *r);
br_t *br_new(seq_t *s, pbm_t *p, unsigned int start, unsigned int end);
void br_free(br_t *r);

brs_t * brs_new();
void brs_print(const brs_t *regions);
void brs_find(brs_t *regions,
	      fasta_t *fa, pbm_t *pbm,
	      float escore_cutoff, int min_length);
int brs_add(brs_t *regions, br_t *region);
void brs_free(brs_t *regions);

// search for best mutation
void br_seq_mutate(br_t *br, float escore_cutoff, int min_length, int k_max);

// find next binding region between br->start and br->end
br_t * br_next(br_t *br, float escore_cutoff, int min_length);

// sort the regions by start position - required to do
//  this before printing the binding regions
void brs_sort(brs_t *brs);




// return escore of the given sequence s
pbm_row_t * pbm_lookup(const pbm_t *pbm, const char *s);


// information about a single nucleotide mutation
typedef
struct MUTATION {
  seq_t *seq;
  int position;
  char change_from;
  char change_to;
} mut_t;

void mut_print(mut_t *mut);

// list of mutations
typedef 
struct MUTATION_LIST {
  mut_t **mutations;
  int max_mutations;
  int num_mutations;
} mutations_t;

mutations_t * mutations_new();
void mutations_print(const mutations_t *mutations);
int mutations_add(mutations_t *mutations, mut_t *mutation);
void mutations_free(mutations_t *mutations);

void mutations_seq_do(mutations_t *mutations, seq_t *seq);
void mutations_seq_undo(mutations_t *mutations, seq_t *seq);


// for keeping a list of pbm's
typedef 
struct PBM_LIST {
  pbm_t **pbms;
  int max_pbms;
  int num_pbms;
} pbms_t;

pbms_t * pbms_new();
void pbms_print(const pbms_t *pbms);
int pbms_add(pbms_t *pbms, pbm_t *pbm);
void pbms_free(pbms_t *pbms);


// print a sequence, and optionally the escores from pbms and
// binding sites
void seq_print_pbms_brs(seq_t *s, pbms_t *ps, brs_t *regions);



#endif
