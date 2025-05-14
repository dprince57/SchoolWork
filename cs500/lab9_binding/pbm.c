#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pbm.h"



// print the pbm row. s should not be NULL.
void pbm_row_print(const pbm_row_t *r) {
  printf("%s\t%s\t%.5f\t%.2f\t%.4f\n", r->mer8, r->mer8_rc, r->e_score, r->median, r->z_score);
}

// return a pointer to a new pbm_row_t, read it in
//  from line
pbm_row_t * pbm_row_new(char *line) {
  pbm_row_t * r = (pbm_row_t *) malloc(sizeof(pbm_row_t));
  if (r == NULL) return NULL;

  // start scanning the line for tokens...
  char *s = strtok(line, " \t");
  if (s == NULL) {
    free(r);
    return NULL;
  }
  
  // mer8
  r->mer8 = strdup(s);
  if (r->mer8 == NULL) {
    free(r);
    return NULL;
  }

  // mer8_rc
  s = strtok(NULL, " \t");
  if (s == NULL) {
    free(r->mer8); // inside of the struct
    free(r);        // structure
    return NULL;
  }
  r->mer8_rc = strdup(s);
  if (r->mer8_rc == NULL) {
    free(r->mer8);
    free(r);
    return NULL;
  }

  // e_score
  s = strtok(NULL, " \t");
  if (s == NULL) {
    free(r->mer8_rc);
    free(r->mer8); 
    free(r);        
    return NULL;
  }
  r->e_score = strtof(s, NULL);

  // median
  s = strtok(NULL, " \t");
  if (s == NULL) {
    free(r->mer8_rc);
    free(r->mer8); 
    free(r);        
    return NULL;
  }
  r->median = strtof(s, NULL);


  // z_score
  s = strtok(NULL, " \t");
  if (s == NULL) {
    free(r->mer8_rc);
    free(r->mer8); 
    free(r);        
    return NULL;
  }
  r->z_score = strtof(s, NULL);

  return r;
}


// create a new pbm_t structure with no rows yet
// return NULL on error
pbm_t *pbm_new(char *name) { // CHANGE
  pbm_t * p = (pbm_t *) malloc(sizeof(pbm_t));
  if (p == NULL) return NULL;

  p->max_rows = 33000;
  p->rows = (pbm_row_t **) malloc(sizeof(pbm_t *)*p->max_rows);
  if (p->rows == NULL) {
    free(p);
    return NULL;
  }

  p->num_rows = 0;
  p->name = strdup(name); // NEW

  return p;
}


// read a pbm file. p should already be created before the function,
// and f should already be opened.
// return 0 on success, non-zero on error.
int pbm_read(FILE *f, pbm_t *p) {
  pbm_row_t *current_row = NULL;
  
  // read through f a line at a time...
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int line_count = 0;
  while ((nread = getline(&line, &len, f)) != -1) {
    // skip the first line, the header line
    if (line_count == 0) {
      line_count++;
      continue;
    }
    
    // line may have a '\n', if so remove it
    if (nread > 0 && line[nread-1] == '\n') {
      line[nread-1] = '\0';
      nread--;
    }

    // the line will be a new row
    current_row = pbm_row_new(line);
    if (current_row == NULL) {
      printf("error createing new row...\n");
      return 1;
    }

    // store into p.
    // realloc if needed
    while (p->num_rows >= p->max_rows) {
      pbm_row_t ** rows = (pbm_row_t **) realloc(p->rows, sizeof(pbm_row_t *) * (p->max_rows * 2));
      if (rows == NULL) {
	printf("error growing rows array...\n");
	return 1;
      }
      p->rows = rows;
      p->max_rows *= 2;
    }

    if (p->max_rows > p->num_rows) {
      p->rows[p->num_rows++] = current_row;
      //p->num_rows++;
    }

    line_count++;
  }

  if (line != NULL) { free(line); line = NULL; }

  return 0;
}

// print a pbm. p should be non-NULL
void pbm_print(const pbm_t *p) {
  printf("%s\n", p->name); // CHANGE
  printf("8-mer	8-mer	E-score	Median	Z-score\n");
  for(int i=0; i < p->num_rows; i++) {
    pbm_row_print(p->rows[i]); // pbm_row_t *
  }
}

// free all memory in the pbm_row_t - the sequence, and the structure itself
void pbm_row_free(pbm_row_t *s) {
  if (s == NULL) return;
  if (s->mer8 != NULL) free(s->mer8);
  if (s->mer8_rc != NULL) free(s->mer8_rc);
  free(s);
}

// free all memory in pbm - the pbm_row_t's and the structure itself.
void pbm_free(pbm_t *p) {
  if (p == NULL) return;
  if (p->rows != NULL) {
    for(int i=0; i < p->num_rows; i++)
      pbm_row_free(p->rows[i]);
    free(p->rows);
  }
  if (p->name != NULL) free(p->name);
  free(p);
}

