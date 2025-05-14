#ifndef __FASTA_H__
#define __FASTA_H__

// structure to store a sequence
typedef
struct SEQ {
  char *id;       // id of the sequence - the part after the '>' on the id line and before any ' '
  char *id_line;  // id line of the seq, including the '>'
  char *sequence; // sequence - part after the id line and before the next id line in the file, with newlines trimmed out
  int len;        // length of the sequence (i.e., strlen(sequence))
} seq_t;


// structure to store a fasta file
typedef
struct FASTA {
  seq_t **seqs;  // array of sequences (pointers to seq_t's)
  int num_seqs;  // how many sequences are we storing
  int max_seqs;  // maximum # of sequences allocated in seqs
} fasta_t;


// print the sequence. s should not be NULL.
void seq_print(const seq_t *s);

// return a pointer to a new seq_t, using id_line for the id line
// return NULL on error
seq_t * seq_new(const char *id_line);

// create a new fasta_t structure with no sequences yet
// return NULL on error
fasta_t *fasta_new();

// read a fasta file. fa should already be created before the function,
// and f should already be opened.
// return 0 on success, non-zero on error.
int fasta_read(FILE *f, fasta_t *fa);

// print a fasta. fa should be non-NULL
void fasta_print(const fasta_t *fa);

// free all memory in the seq_t - the sequence, id_line and the structure itself
void seq_free(seq_t *s);

// free all memory in fa - the seq_t's and the structure itself.
void fasta_free(fasta_t *fa);

#endif
