#ifndef COMBINATIONS_H
#define COMBINATIONS_H

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
int NextCombination(int * v, int k, int N);

// return a pointer to an int array initialized
//  to 0, 1, ..., k-1
// or NULL if fail
int * FirstCombination(int k, int N);

// print the combination
void PrintCombination(int *v, int k);


#endif
