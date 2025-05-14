#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fasta.h"
#include "fasta.h"


// print the sequence. s should not be NULL.
void seq_print(const seq_t *s) {
  // print the sequence - first the idline and then the sequence
  printf("%s\n%s\n", (*s).id_line, s->sequence);
}

// return a pointer to a new seq_t, using id_line for the id line
// return NULL on error
seq_t * seq_new(const char *id_line) {
  // create a new seq_t, malloc the space
  seq_t *s = (seq_t *) malloc(sizeof(seq_t));
  if (s == NULL) return NULL;

  // initialize the fields in s...
  
  s->id_line = strdup(id_line); // note: this is malloc'ed
  s->id = s->id_line;           // todo: extract just the id
  s->sequence = NULL; // no sequence yet
  s->len = 0;         // no sequence yet
  return s;
}

// create a new fasta_t structure with no sequences yet
// return NULL on error
fasta_t *fasta_new() {
  // malloc space for a new fasta_t structure
  fasta_t *f = (fasta_t *) malloc(sizeof(fasta_t));
  if (f == NULL) return NULL;
  
  f->num_seqs = 0; // initially no sequences

  // malloc space for some initial amount of sequences
  f->max_seqs = 1000;
  f->seqs = (seq_t **) malloc(f->max_seqs * sizeof(seq_t *));
  if (f->seqs == NULL) { // can't malloc space
    free(f); // free space already malloc'ed that we won't need now
    return NULL;
  }

  return f;
}

// read a fasta file. fa should already be created before the function,
// and f should already be opened.
// return 0 on success, non-zero on error.
int fasta_read(FILE *f, fasta_t *fa) {
  seq_t *current_seq = NULL;
  
  // read through f a line at a time...
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  while ((nread = getline(&line, &len, f)) != -1) {
    // line may have a '\n', if so remove it
    if (nread > 0 && line[nread-1] == '\n') {
      line[nread-1] = '\0';
      nread--;
    }
  
    if (nread > 0 && line[0] == '>') {
      // start of a new sequence. 
      current_seq = seq_new(line);

      // make sure we have enough room in the fa for another seq
      while (fa->num_seqs >= fa->max_seqs) {
	// try to double the number of sequences we can store
	seq_t ** p = (seq_t **) realloc(fa->seqs, 2*fa->num_seqs*sizeof(seq_t *));
	// on malloc error, return error.
	if (p == NULL) return 1;
	// if we made it here, we successfully doubled the # of sequences we can store
	fa->seqs = p;
	fa->max_seqs *= 2;
      }

      // now put the new seq into the fa
      fa->seqs[fa->num_seqs] = current_seq;
      (fa->num_seqs)++;
    }
    else {
      // continue the previous sequence
      if (current_seq != NULL) { // shouldn't be NULL, but just in case of a badly formatted file
	// malloc more space so we can store what we have already and line
	char *s = (char *) realloc(current_seq->sequence,
				   (current_seq->len+nread+1)*
				   sizeof(char));
	if (s == NULL) { // error malloc'ing
	  return 1;
	}
	current_seq->sequence = s;
	strcpy(current_seq->sequence+current_seq->len, line); 
	current_seq->len += nread;
      }
    }
  }
  // free memory
  if (line != NULL) { free(line); line = NULL; }
  return 0;
}


// print a fasta. fa should be non-NULL
void fasta_print(const fasta_t *fa) {
  for(int i=0; i < fa->num_seqs; i++) {
    seq_print(fa->seqs[i]);
  }
}


// free all memory in the seq_t - the sequence, id_line and the structure itself
void seq_free(seq_t *s) {
  if (s != NULL) {
    if (s->sequence != NULL)
      free(s->sequence);
    if (s->id_line != NULL)
      free(s->id_line);
    free(s);
  }
}

// free all memory in fa - the seq_t's and the structure itself.
void fasta_free(fasta_t *fa) {
  if (fa != NULL) {
    for(int i=0; i < fa->num_seqs; i++) {
      seq_free(fa->seqs[i]);
    }
    free(fa->seqs);
    free(fa);
  }
}
