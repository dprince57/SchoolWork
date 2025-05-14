

#ifndef __PBM_H__
#define __PBM_H__

// 
typedef
struct PBM_ROW {
  char *mer8;    // sequence of 8 letters of DNA
  char *mer8_rc; // reverse complement of mer8
  float e_score;  // -.5 to .5, higher is more likely to bind
  float median;   // ??
  float z_score;  // ??
} pbm_row_t;


// structure to store a pbm file
typedef
struct PBM {
  pbm_row_t **rows;
  int num_rows;
  int max_rows;
} pbm_t;


// print the pbm row. s should not be NULL.
void pbm_row_print(const pbm_row_t *r);

// return a pointer to a new pbm_row_t, read it in
//  from line
pbm_row_t * pbm_row_new(char *line);

// create a new pbm_t structure with no rows yet
// return NULL on error
pbm_t *pbm_new();

// read a pbm file. p should already be created before the function,
// and f should already be opened.
// return 0 on success, non-zero on error.
int pbm_read(FILE *f, pbm_t *p);

// print a pbm. p should be non-NULL
void pbm_print(const pbm_t *p);



// lab5 - you will define the following functions in your pbm.c file, and
// call them in pbm_driver.c when processing the command-line arguments.

// print a usage statement and exit.
// make your usage statement match Jeff's exactly.
void pbm_help();

// return the number of rows in the pbm structure.
int pbm_row_count(const pbm_t *p);

// return a pointer to the highest e-score in the file.
// if there is a tie, then return the first in the file among all tied
// for the highest.
// return NULL if no rows.
pbm_row_t* pbm_max_escore(const pbm_t *p);

// return a pointer to the lowest e-score in the file.
// if there is a tie, then return the first in the file among all tied
// for the lowest.
// return NULL if no rows.
pbm_row_t* pbm_min_escore(const pbm_t *p);

// return a the average e_score in the pbm, 0 if no records
float pbm_avg_escore(const pbm_t *p);

// print escores that pass the filters, at least min and at most max
void pbm_filter_escores(const pbm_t *p, float min, float max);

// free all memory in the pbm_row_t - the sequence, and the structure itself
void pbm_row_free(pbm_row_t *s);

// free all memory in pbm - the pbm_row_t's and the structure itself.
void pbm_free(pbm_t *p);

void pbm_median(pbm_t *p);

#endif


