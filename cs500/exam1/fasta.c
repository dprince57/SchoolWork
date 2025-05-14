#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  f->max_seqs = 10;
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
	seq_t ** p = (seq_t **) realloc(fa->seqs, 2*fa->max_seqs*sizeof(seq_t *));
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
  if (line != NULL) free(line);
  return 0;
}


// print a fasta. fa should be non-NULL
void fasta_print(const fasta_t *fa) {
  for(int i=0; i < fa->num_seqs; i++) {
    seq_print(fa->seqs[i]);
  }
}
// lab4 functions, put them here
int fasta_seq_count(const fasta_t *fa){
  //open fa and print out number of sequences stored.
  return fa->num_seqs;
}
float fasta_GC(const fasta_t *fa){
  //init our variables for averageing
  float total_nucleotides = 0;
  float total_GC = 0;
  //first for loop to cycle through each seq_t
  for(int i = 0; i < fa->num_seqs;i++){
    //if sequence is NULL we continue. we do not break as we could possibly miss a sequence
    if(fa->seqs[i]->sequence == NULL)continue;
    //for loop to go through each letter in each sequence.
    for(int j = 0; fa->seqs[i]->sequence[j] != '\0'; j++){
      switch(fa->seqs[i]->sequence[j]){
        //switch cases for adding our number of letters and nucleotides.
        case 'g':
        case 'G':
        case 'c':
        case 'C':
          total_GC++;
          total_nucleotides++;
          break;
        default:
          total_nucleotides++;
          break;
      }
    }
  }
  //if nucleotides for some reason is empty we will return 0.0. otherwise do the math and send it
  if(total_nucleotides == 0)return 0.0;
  return (total_GC/total_nucleotides) * 100;
}
seq_t* fasta_max_length(const fasta_t *fa){
  //init our vars for function
  int longest = 0;
  int index = 0;
  //iterate through fa to find longest string.first longest will be stored
  for(int i = 0; i < fa->num_seqs;i++){
    if(fa->seqs[i]->len > longest){
      longest = fa->seqs[i]->len;
      index = i;
    }
  }
  //if somehow we have none, return null
  if(longest == 0)return NULL;
  printf("Longest sequence length: %d\n",fa->seqs[index]->len);
  return fa->seqs[index];
}
seq_t *fasta_min_length(const fasta_t *fa){
  //init our vars for function
  int shortest = 0;
  int index = 0;
  //our shortest needs inited with the first value if no value return null
  if(fa->seqs[0]->len != 0){
    shortest = fa->seqs[0]->len;
  }else{
    return NULL;
  }
  //iterate through fa to find longest string.first longest will be stored
  for(int i = 1; i < fa->num_seqs;i++){
    if(fa->seqs[i]->len < shortest){
      shortest = fa->seqs[i]->len;
      index = i;
    }
  }
  //if somehow we have none, return null
  if(shortest == 0)return NULL;
  printf("Shortest sequence length: %d\n",fa->seqs[index]->len);
  return fa->seqs[index];
}
void fasta_help(){

  printf("usage: ./fasta_driver.o filename.fa [commands]\n\n");
  printf("  filename.fa - path and filename of a fasta file.\n\n");
  printf("  commands can be any of the following:\n\n");
  printf("    --help - prints a usage statement\n");
  printf("    --print - prints all sequences\n");
  printf("    --seq_count - prints # of sequences\n");
  printf("    --max_length - prints the id and length of the longest sequence\n");
  printf("    --min_length - prints the id and length of the shortest sequence\n");
  printf("    --GC - prints the percentage of the sequence letters that are g, G, c , or C\n\n");
  printf("    -last_letters - prints the last letter of each sequence\n\n");
}
void seq_free(seq_t *s){
  //free(s->id);
  free(s->id_line);
  free(s->sequence);
  free(s);
}
void fasta_free(fasta_t *fa){
  for(int i = 0; i < fa->num_seqs;i++){
    if(fa->seqs[i] != NULL){
      seq_free(fa->seqs[i]);
    }
  }
  free(fa->seqs);
  free(fa);

}
void fasta_last(const fasta_t *fa){
  int letters = 1;
  for(int i=0; i < fa->num_seqs; i++) {
    for(int j = fa->seqs[i]->len - letters; j < fa->seqs[i]->len; j++){
      printf("%c",fa->seqs[i]->sequence[j]);
    }
    printf("\n");
  }
}
