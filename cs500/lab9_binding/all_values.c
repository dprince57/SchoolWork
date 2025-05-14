#include "all_values.h"

// malloc and init an array of integers for the first
// set of N values, with each value ranging from  min to max.
// return the pointer, or NULL if failure
int *FirstValues(int N, int min, int max) {
  int *v =  (int *) malloc(sizeof(int) * N);
  if (v == NULL) return NULL;

  for(int i=0; i < N; i++)
    v[i] = min;

  return v;
}

// change v to be the next values.
int NextValues(int *v, int N, int min, int max) {
  // starting at the rightmost position in v, increase it,
  // and carry as needed.
  int i;
  for(i=N-1; i >= 0; i--) {
    v[i]++;
    if (v[i] > max) v[i] = min;
    else break;
  }

  // everything went to min, so went all the way through all the possible values
  if (i < 0) return 0;

  return 1;
}

void PrintValues(int *v, int N) {
  printf("Values: ");
  int first = 1;
  for(int i=0; i < N; i++) {
    if (! first) printf(", ");
    printf("%d", v[i]);
    first = 0;
  }
  printf("\n");
}

