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
pbm_t *pbm_new() {
  pbm_t * p = (pbm_t *) malloc(sizeof(pbm_t));
  if (p == NULL) return NULL;

  p->max_rows = 33000;
  p->rows = (pbm_row_t **) malloc(sizeof(pbm_t *)*p->max_rows);
  if (p->rows == NULL) {
    free(p);
    return NULL;
  }

  p->num_rows = 0;

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

  // free the line
  if (line != NULL) free(line);
  
  return 0;
}

// print a pbm. p should be non-NULL
void pbm_print(const pbm_t *p) {
  printf("8-mer	8-mer	E-score	Median	Z-score\n");
  for(int i=0; i < p->num_rows; i++) {
    pbm_row_print(p->rows[i]); // pbm_row_t *
  }
}


// lab5 - put your completed lab5 functions here
void pbm_help(){
  printf("usage: ./pbm_driver.o filename.txt [commands]\n\n");
  printf("  filename.txt - path and filename of a pbm file.\n\n");
  printf("  commands can be any of the following:\n\n");
  printf("    --help - prints a usage statement\n");
  printf("    --print - prints all rows\n");
  printf("    --row_count - prints # of rows\n");
  printf("    --max_escore - prints the row with highest escore\n");
  printf("    --min_escore - prints the row with lowest escore\n");
  printf("    --avg_escore - prints the average escore\n");
  printf("    --large_escore=val - prints rows with escore at least val\n");
  printf("    --small_escore=val - prints rows with escore at most val\n\n");
}

int pbm_row_count(const pbm_t *p){
  return p->num_rows;
}

pbm_row_t* pbm_max_escore(const pbm_t *p){
  float max = -0.6;
  int max_i = 0;
  for(int i = 0; i < p->num_rows; i++){
    if(p->rows[i]->e_score > max){
      max = p->rows[i]->e_score;
      max_i = i;
    }
  }
  if(max == -0.6){return NULL;}
  printf("Highest escore: %.6f\n",p->rows[max_i]->e_score);
  return p->rows[max_i];
}
pbm_row_t* pbm_min_escore(const pbm_t *p){
  float min = 0.6;
  int min_i = 0;
  for(int i = 0; i < p->num_rows; i++){
    if(p->rows[i]->e_score < min){
      min = p->rows[i]->e_score;
      min_i = i;
    }
  }
  if(min == 0.6){return NULL;}
  printf("Lowest escore: %.6f\n",p->rows[min_i]->e_score);
  return p->rows[min_i];

}
float pbm_avg_escore(const pbm_t *p){
  float total = 0;
  if(p->num_rows == 0)return 0.0;
  for(int i = 0; i < p->num_rows; i++){
    total += p->rows[i]->e_score;
  }
  return total/p->num_rows;
}
void pbm_filter_escores(const pbm_t *p, float min, float max){
  if(min == -100){
    for(int i = 0; i < p->num_rows; i++){
      if(p->rows[i]->e_score >= max){
        pbm_row_print(p->rows[i]);
      }
    }
  }
  else if(max == 100){
    for(int i = 0; i < p->num_rows; i++){
      if(p->rows[i]->e_score <= min){
        pbm_row_print(p->rows[i]);
      }
    }
  }
}
void pbm_row_free(pbm_row_t *s){
  free(s->mer8);
  free(s->mer8_rc);
  free(s);
}

void pbm_free(pbm_t *p){
  for(int i = 0;i < p->num_rows;i++){
    if(p->rows[i] != NULL){
      pbm_row_free(p->rows[i]);
    }
  }
  free(p->rows);
  free(p);
}
