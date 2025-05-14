#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// iterate through combinations
// code adapted from here - 
//   https://stackoverflow.com/a/39844908
// just changed from C++ to C

// v: array of k integers, each will be between 0 and N-1
//    assume v was initially set to be 0, 1, 2, ..., k-1
// return 1 if success, 0 if no more combinations
int NextCombination(int * v, int k, int N) {
  // We want to find the index of the least significant element
  // in v that can be increased.  Let's call that index 'pivot'.
  int pivot = k - 1;
  while (pivot >= 0 && v[pivot] == N - k + pivot)
    --pivot;
  // pivot will be -1 iff v == {N - k, N - k + 1, ..., N - 1},
  // in which case, there is no next combination.
  if (pivot == -1)
    return 0;

  v[pivot]++;
  for (int i = pivot + 1; i < k; ++i)
    v[i] = v[pivot] + i - pivot;
  return 1;
}

// return a pointer to an int array initialized
//  to 0, 1, ..., k-1
// or NULL if fail
int * FirstCombination(int k, int N) {
  int *v = (int *) malloc(sizeof(int)*k);
  if (v == NULL) return NULL;
  for(int i=0; i < k; i++)
    v[i] = i;
  return v;
}

void PrintCombination(int *v, int k) {
  for(int i=0; i < k; i++) {
    if (i > 0) printf(", ");
    printf("%d", v[i]);
  }
  printf("\n");
}



