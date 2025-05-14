#include "binding_region.h"

// print the binding region
void br_print(const br_t *r) {
  printf("%u-%u (total length %u)\n", r->start, r->end, r->end - r->start+1);
  for(int i=r->start; i <= r->end; i++) {
    printf("%c", r->seq->sequence[i]);
  }
  printf("\n");
}

// malloc the structure, put the things in, return a pointer to it, NULL if failure
br_t *br_new(seq_t *s, pbm_t *p, unsigned int start, unsigned int end) {
  br_t *r = (br_t *) malloc(sizeof(br_t));
  if (r == NULL) {
    return NULL;
  }

  r->seq = s;
  r->pbm = p;
  r->start = start;
  r->end = end;

  return r;
}

// free memory from this structure
void br_free(br_t *r) {
  if (r == NULL) return;
  free(r);
}

// init a new binding regions structure, including space to
//  store some initial number of binding regions.
// return pointer, NULL if failure
brs_t * brs_new() {
  brs_t *regions = (brs_t *) malloc(sizeof(brs_t));
  if (regions == NULL) {
    return NULL;
  }

  regions->max_regions = 2;
  regions->regions = (br_t **)
    malloc(sizeof(br_t *)*regions->max_regions);
  if (regions->regions == NULL) {
    free(regions);
    return NULL;
  }

  regions->num_regions = 0;

  return regions;
}

// free memory allocated to the binding regions
void brs_free(brs_t *regions) {
  if (regions == NULL) return;
  for(int i=0; i < regions->num_regions; i++)
    br_free(regions->regions[i]);
  
  if (regions->regions != NULL) free(regions->regions);
  free(regions);
}

// print the binding regions
void brs_print(const brs_t *regions) {
  printf("%d binding regions.\n", regions->num_regions);
  for(int i=0; i < regions->num_regions; i++) {
    br_print(regions->regions[i]);
  }
}

// return escore of the given sequence s, looking to
// match the first 8 characters of s
pbm_row_t * pbm_lookup(const pbm_t *pbm, const char *s) {
  // loop through the rows, looking for s
  for(int i=0; i < pbm->num_rows; i++) {
    if (strncasecmp(pbm->rows[i]->mer8, s, 8) == 0 ||
	strncasecmp(pbm->rows[i]->mer8_rc, s, 8) == 0) {
      return pbm->rows[i];
    }
  }
  return NULL;
}


// br will have a sequence, and a range to search within (start to end).
//  do the search and return the next binding region within the range,
//  so the start and end will be updated to that.
//  if there are no binding regions, then set start=end=end.
//  return a pointer to the binding region (br)
br_t * br_next(br_t *br, float escore_cutoff, int min_length) {
  seq_t *seq = br->seq; pbm_t *pbm = br->pbm;

  // start at beginning of region, and loop through it
  int curr_index;
  int start_of_region = -1;
  for(curr_index = br->start; curr_index < seq->len - 8 && curr_index < br->end;
      curr_index++) {
    // look at 8 characters starting at curr_index
    pbm_row_t *row = pbm_lookup(pbm,
				seq->sequence+
				curr_index);
    if (row != NULL && row->e_score >= escore_cutoff) {
      // we have one 8mer that works. if this is the
      // start of a new region, then save that
      if (start_of_region < 0)
	start_of_region = curr_index;
	  
      // o/w, in the middle of a binding region, then just
      // let it keep going
    }
    else {
      // this 8mer does not work. if we were in the
      // middle of a region, then end it at curr_index-1
      if (start_of_region >= 0) {
	// check the total length
	int total_length = 8 + curr_index-start_of_region-1;
	if (total_length >= min_length) {
	  // if length is big enough, then update the br and return
	  br->start = start_of_region;
	  br->end = start_of_region+total_length-1;
	  return br;
	}
      }
      // region wasn't big enough, keep looking
      start_of_region = -1;
    }
  }
  // done looking through the sequence, see if we're in the middle of
  //  a binding region that was big enough
  if (start_of_region >= 0) {
    int total_length = 8 + curr_index-start_of_region-1;
    if (total_length >= min_length) {
      br->start = start_of_region;
      br->end = start_of_region+total_length-1;
      return br;
    }
  }
  // if made it to here, then no regions found, signal that
  // by setting start = end
  br->start = br->end;
  return br;
}


// find the largest binding region between br->start and br->end
// like br_next, leave the largest one as br->start to br->end
br_t * br_largest(br_t *br, float escore_cutoff, int min_length) {
  int end_org = br->end;

  // longest found, initialize these
  int largest_length = -1;
  int start_best = br->end, end_best = br->end;

  // look for a br
  br_next(br, escore_cutoff, min_length);

  // as long as there is still more room to look for a longer br
  while (br->start < end_org) {
    int length = br->end - br->start + 1;
    if (length > largest_length) {
      largest_length = length;
      start_best = br->start; end_best = br->end;
    }
    br->start = br->end+1; br->end = end_org;
    br_next(br, escore_cutoff, min_length);
  }
  br->start = start_best; br->end = end_best;
  return br;
}

// search through the given fasta for binding regions, using
//  the given pbm data, escore cutoff and minimum length.
// for any results found, create br structures for them and
//  store them in regions
void brs_find(brs_t *regions,
	      fasta_t *fa, pbm_t *pbm,
	      float escore_cutoff, int min_length) {
  // loop through each sequence
  for(int i=0; i < fa->num_seqs; i++) {
    seq_t *seq = fa->seqs[i];

    // set up a br with the range we are looking within, the whole sequence
    br_t *br = br_new(seq, pbm, 0, seq->len-1);

    // look for next binding region in this sequence
    br_next(br, escore_cutoff, min_length);
    // keep going as long as we didn't get all the way through seq
    while (! (br->start >= seq->len-1 || br->end >= seq->len-1)) {
      // add the binding region to brs
      br_t *region = br_new(seq, pbm, br->start, br->end);
      brs_add(regions, region);

      // look for the next one
      br->start = region->end+1; br->end = seq->len-1;
      br_next(br, escore_cutoff, min_length);
    }
    
    free(br); // done with this temp variable
  }
}


// add a new binding region to the binding regions structure
// return 0 on failure, 1 on success.
int brs_add(brs_t *regions, br_t *region) {
  // if the regions doesn't have room for another, realloc to
  //  make room
  while (regions->max_regions <= regions->num_regions) {
    int new_max = regions->max_regions * 2; // grow by factor 2
    br_t **p = (br_t **) realloc(regions->regions, sizeof(br_t *) * new_max);
    if (p == NULL) return 0; // failed to add it
    regions->max_regions = new_max;
    regions->regions = p;
  }
  // add it in the next slot
  regions->regions[(regions->num_regions)++] = region;
  return 1; // success
}

// take dna letter and return one of the others, base by on amount.
// amount should be 1, 2, or 3
// nt should be A, C, G, or T
char dna_letter_add(char nt, int amount) {
  char *nts = "ACGT";
  nt = toupper(nt);
  int i;
  for(i=0; i < 4; i++) {
    if (nt == nts[i]) break;
  }
  if (i >= 4) return nt;
  return nts[(i+amount) % 4];
}


// print mutation
void mut_print(mut_t *mut) {
  printf("Mutate position %d from %c to %c.\n", mut->position, mut->change_from, mut->change_to);
}

// find best mutation for br, where there are no regions remaining that are
//  longer than length and are above escore
// br - a binding region
// escore_cutoff - try to get escores below this amount
// min_length - try to get br below this length
// k - consider up to k mutations
void br_seq_mutate(br_t *br, float escore_cutoff, int min_length, int k) {
    seq_t *seq = br->seq;
    int original_length = br->end - br->start + 1;

    // Track the best solution
    int best_length = original_length;
    mut_t best_mutations[k];
    int mutation_count = 0;

    printf("%u-%u (total length %d)\n", br->start, br->end, original_length);

    for (int round = 0; round < k; round++) {
        mut_t current_best_mutation;
        int current_best_length = best_length;

        // Try mutating each position in the binding region
        for (int i = br->start; i <= br->end; i++) {
            char original = seq->sequence[i];

            // Try all three possible mutations
            for (int letter_change = 1; letter_change <= 3; letter_change++) {
                char mutated = dna_letter_add(original, letter_change);
                seq->sequence[i] = mutated;

                // Evaluate the sequence after the mutation
                int start = br->start, end = br->end;
                br_next(br, escore_cutoff, min_length);

                int length = br->end - br->start + 1;
                if (length < current_best_length) {
                    current_best_length = length;
                    current_best_mutation.position = i;
                    current_best_mutation.change_from = original;
                    current_best_mutation.change_to = mutated;
                }

                // Reset sequence and region
                seq->sequence[i] = original;
                br->start = start;
                br->end = end;
            }
        }

        // Apply the best mutation of this round
        if (current_best_length < best_length) {
            best_length = current_best_length;
            best_mutations[mutation_count++] = current_best_mutation;
            seq->sequence[current_best_mutation.position] = current_best_mutation.change_to;
            br_next(br, escore_cutoff, min_length);
        } else {
            break;  // No improvement possible
        }
    }

    // Report results
    if (best_length < original_length) {
        printf("Binding site shrinks to length %d\n", best_length);
        printf("%d mutations.\n", mutation_count);
        for (int i = 0; i < mutation_count; i++) {
            mut_print(&best_mutations[i]);
        }
    } else {
        printf("No mutation found to shrink binding site.\n");
    }
}


// Function to print the sequence with pbm escores and binding regions
//  s - sequence to print
//  ps - pbms, skipped if ps == NULL
//  regions - binding regions, skipped if regions == NULL
// Sequence is printed 70 characters per line.
// Escores are printed on two lines with one line for + values
//  and one for - values, and the first digit is printed (so 0.12
//  would have the 1 printed on the + line).
// Each pbm gets its own two lines for the escores.
// Binding sites are printed with the first letter of the pbm's name.
// An example printout that includes these for the example files:
/*
   0:CGCTCCAGCTTATTGTCCAGCTGATTGTAGGAGTAGATCAGCGACTGGATAGTTCCGCGCAGCTCCTCGT
e=+0.0   10212100   0000 2200   0  0  1   000   0000   01 000      00010200:CHES-1-like_8mers_11111111.txt
e=-0. 110        010    1    010 00 00 010   010    110  0   123210        :CHES-1-like_8mers_11111111.txt
e=+0.00 010100000     00 10011    00  0 0 0 1   0 00  0011 02       001010 :Jumeau_8mers_11111111.txt
e=-0.  0         12100  0     0000  10 0 0 0 111 1  10    0  0132200      1:Jumeau_8mers_11111111.txt
e=+0.   0   02221    000021 101000  0  0       01  0 021  1     0   0     1:Pnt_8mers_11111111.txt
e=-0.021 110     0002      0      00 00 1000000  00 1   00 11021 010 11000 :Pnt_8mers_11111111.txt
e=+0.     01011110    01012110000111100         1 0000             00  00 0:Tin_8mers_11111111.txt
e=-0.01000        0100                 000000200 0    0001112122101  00  0 :Tin_8mers_11111111.txt
e=+0.    1 101211     02112 1   1  000   0      000                        :Tup_8mers_11111111.txt
e=-0.1231 0      01220     0 021 10   010 130200   110002213222310200100010:Tup_8mers_11111111.txt
e=+0.0     101 011 02121   100    11  00000    0 000                    0 0:Twi_8mers_11111111.txt
e=-0. 10111   0   1     100   0020  00     0000 0   00000012211211111210 0 :Twi_8mers_11111111.txt
bind:                                                                     

  70:TGCTGGAAAGGGTAGGGGGTTAGGGTTAGTGGCTTAAAATTAGCCTCGCTGCGGACCATTAATCATCGGA
e=+0.0                       0    01112210 0      00   0   221211          :CHES-1-like_8mers_11111111.txt
e=-0. 01120011232323321010011 0001        0 022110  001 110      0001211343:CHES-1-like_8mers_11111111.txt
e=+0.0  0              1   0 0   022111010  0  0       1   011120  00      :Jumeau_8mers_11111111.txt
e=-0. 01 31000213310010 120 0 100         10 00 1200001 010      00  100201:Jumeau_8mers_11111111.txt
e=+0.  01100   0  0 0  110 1111   1  1120120      0 10    111011   001 1021:Pnt_8mers_11111111.txt
e=-0.00     001 01 0 00   0    000 01       021000 1  1000      120   0    :Pnt_8mers_11111111.txt
e=+0.     000       0  0100001001000022110100            01221221010  0 01 :Tin_8mers_11111111.txt
e=-0.00101   1002000 00                      011101101111           00 0  0:Tin_8mers_11111111.txt
e=+0.      0     0      20   1311 222333334311   0      04444443100       0:Tup_8mers_11111111.txt
e=-0.111010 12223 111210  110    0            001 212200           0110010 :Tup_8mers_11111111.txt
e=+0.1211100 0 0      0000  0 0  0010121200 0       00 1101101011  00      :Twi_8mers_11111111.txt
e=-0.       1 1 321012    10 0 01          1 2210210  0          10  011012:Twi_8mers_11111111.txt
bind:                                TTTTTTTTTTTTTT      TTTTTTTTTTTTTT   
 */
void seq_print_pbms_brs(seq_t *s, pbms_t *ps, brs_t *regions) {
    if (s == NULL) return;

    int regions_i = 0; // Index into binding regions, assumed in sorted order
    int print_width = 70;

    for (int i = 0; i < s->len; i += print_width) {
        // Print the sequence
        printf("%4d:%.*s\n", i, print_width, s->sequence + i);

        // Print e-scores if PBMs are provided
        if (ps != NULL) {
            for (int i_pbms = 0; i_pbms < ps->num_pbms; i_pbms++) {
                pbm_t *p = ps->pbms[i_pbms];
                char line_pos[print_width + 1];
                char line_neg[print_width + 1];
                memset(line_pos, ' ', print_width);
                memset(line_neg, ' ', print_width);
                line_pos[print_width] = '\0';
                line_neg[print_width] = '\0';

                for (int j = 0; j < print_width && (i + j) < s->len; j++) {
                    pbm_row_t *row = pbm_lookup(p, s->sequence + (i + j));
                    if (row != NULL) { // Check if pbm_lookup() returned a valid pointer
                        float escore = row->e_score; // Access e_score from the row
                        if (escore > 0.8f) {
                            line_pos[j] = '1'; // Mark significant positive score
                        } else if (escore < -0.8f) {
                            line_neg[j] = '1'; // Mark significant negative score
                        }
                    }
                }

                printf("e=+0.%s:%s\n", line_pos, p->name);
                printf("e=-0.%s:%s\n", line_neg, p->name);
            }
        }

        // Print binding sites
        if (regions != NULL) {
            char line_binding[print_width + 1];
            memset(line_binding, ' ', print_width);
            line_binding[print_width] = '\0';

            while (regions_i < regions->num_regions) {
                br_t *br = regions->regions[regions_i];

                if (br->start >= i && br->start < i + print_width) {
                    int start_pos = br->start - i;
                    int end_pos = (br->end < i + print_width) ? (br->end - i) : (print_width - 1);

                    for (int k = start_pos; k <= end_pos; k++) {
                        line_binding[k] = '1'; // Marker for binding region
                    }

                    if (br->end < i + print_width) {
                        regions_i++; // Move to the next region if this one is fully on the current line
                    } else {
                        break; // Region spans to the next line, don't advance regions_i yet
                    }
                } else {
                    break; // Current region doesn't start in this range
                }
            }

            printf("bind:%s\n", line_binding);
        }

        printf("\n");
    }
}

// sort the regions based on start position.
// use qsort and make the right compare function.
static int compare_binding_regions(const void *a, const void *b) {
    const br_t *region1 = *(const br_t **)a;
    const br_t *region2 = *(const br_t **)b;
    return (int)(region1->start - region2->start);
}

void brs_sort(brs_t *brs) {
    if (brs == NULL || brs->regions == NULL || brs->num_regions <= 1) {
        return; // Nothing to sort
    }

    qsort(brs->regions, brs->num_regions, sizeof(br_t *), compare_binding_regions);
}
// init a new  pbms structure, including space to
//  store some initial number of  pbms.
// return pointer, NULL if failure
pbms_t *pbms_new() {
    pbms_t *pbms = (pbms_t *)malloc(sizeof(pbms_t));
    if (pbms == NULL) {
        return NULL;
    }

    pbms->max_pbms = 2; // Initial capacity
    pbms->num_pbms = 0;
    pbms->pbms = (pbm_t **)malloc(sizeof(pbm_t *) * pbms->max_pbms);
    if (pbms->pbms == NULL) {
        free(pbms);
        return NULL;
    }

    return pbms;
}

// Free memory allocated to PBMs
void pbms_free(pbms_t *pbms) {
    if (pbms == NULL) {
        return;
    }

    for (int i = 0; i < pbms->num_pbms; i++) {
        if (pbms->pbms[i] != NULL) {
            pbm_free(pbms->pbms[i]); // Assuming pbm_free is defined elsewhere
        }
    }

    free(pbms->pbms);
    free(pbms);
}

// Print the PBMs
void pbms_print(const pbms_t *pbms) {
    if (pbms == NULL) {
        return;
    }

    printf("%d PBMs:\n", pbms->num_pbms);
    for (int i = 0; i < pbms->num_pbms; i++) {
        if (pbms->pbms[i] != NULL) {
            pbm_print(pbms->pbms[i]); // Assuming pbm_print is defined elsewhere
        }
    }
}

// Add a new PBM to the PBMs structure
int pbms_add(pbms_t *pbms, pbm_t *pbm) {
    if (pbms == NULL || pbm == NULL) {
        return 0;
    }

    if (pbms->num_pbms >= pbms->max_pbms) {
        int new_max = pbms->max_pbms * 2;
        pbm_t **new_array = (pbm_t **)realloc(pbms->pbms, sizeof(pbm_t *) * new_max);
        if (new_array == NULL) {
            return 0; // Allocation failed
        }
        pbms->pbms = new_array;
        pbms->max_pbms = new_max;
    }

    pbms->pbms[pbms->num_pbms++] = pbm;
    return 1; // Success
}

// Initialize a new mutations structure
mutations_t *mutations_new() {
    mutations_t *mutations = (mutations_t *)malloc(sizeof(mutations_t));
    if (mutations == NULL) return NULL;

    mutations->max_mutations = 2;
    mutations->num_mutations = 0;
    mutations->mutations = (mut_t **)malloc(sizeof(mut_t *) * mutations->max_mutations);
    if (mutations->mutations == NULL) {
        free(mutations);
        return NULL;
    }

    return mutations;
}

// Free memory allocated to mutations
void mutations_free(mutations_t *mutations) {
    if (mutations == NULL) return;

    for (int i = 0; i < mutations->num_mutations; i++) {
        free(mutations->mutations[i]);
    }

    free(mutations->mutations);
    free(mutations);
}

// Print the mutations
void mutations_print(const mutations_t *mutations) {
    if (mutations == NULL) {
        return;
    }

    for (int i = 0; i < mutations->num_mutations; i++) {
        if (mutations->mutations[i] != NULL) {
            mut_print(mutations->mutations[i]);
        }
    }
}

// Add a new mutation to the mutations structure
int mutations_add(mutations_t *mutations, mut_t *mutation) {
    if (mutations == NULL || mutation == NULL) {
        return 0;
    }

    if (mutations->num_mutations >= mutations->max_mutations) {
        int new_max = mutations->max_mutations * 2;
        mut_t **new_mutations = (mut_t **)realloc(mutations->mutations, sizeof(mut_t *) * new_max);
        if (new_mutations == NULL) return 0;

        mutations->mutations = new_mutations;
        mutations->max_mutations = new_max;
    }

    mutations->mutations[mutations->num_mutations++] = mutation;
    return 1; // Success
}

// Apply mutations to the sequence
void mutations_seq_do(mutations_t *mutations, seq_t *seq) {
    if (mutations == NULL || seq == NULL) {
        return;
    }

    for (int i = 0; i < mutations->num_mutations; i++) {
        mut_t *mut = mutations->mutations[i];
        seq->sequence[mut->position] = mut->change_to;
    }
}

// Undo mutations in the sequence
void mutations_seq_undo(mutations_t *mutations, seq_t *seq) {
    if (mutations == NULL || seq == NULL) {
        return;
    }

    for (int i = 0; i < mutations->num_mutations; i++) {
        mut_t *mut = mutations->mutations[i];
        seq->sequence[mut->position] = mut->change_from;
    }
}
