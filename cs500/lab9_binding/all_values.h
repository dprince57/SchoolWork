#ifndef ALL_VALUES_H_
#define ALL_VALUES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// malloc and init an array of integers for the first
// set of N values, with each value ranging from  min to max.
// return the pointer, or NULL if failure
int *FirstValues(int N, int min, int max);

// change v to be the next values.
// return 1 if success and 0 if no more
int NextValues(int *v, int N, int min, int max);

// print the values
void PrintValues(int *v, int N);


#endif
