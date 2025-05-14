

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
  char *name; // NEW
} pbm_t;


// print the pbm row. s should not be NULL.
void pbm_row_print(const pbm_row_t *r);

// return a pointer to a new pbm_row_t, read it in
//  from line
pbm_row_t * pbm_row_new(char *line);

// create a new pbm_t structure with no rows yet
// return NULL on error
pbm_t *pbm_new(char *name); // CHANGE

// read a pbm file. p should already be created before the function,
// and f should already be opened.
// return 0 on success, non-zero on error.
int pbm_read(FILE *f, pbm_t *p);

// print a pbm. p should be non-NULL
void pbm_print(const pbm_t *p);

// free memory
void pbm_free(pbm_t *p);



#endif
