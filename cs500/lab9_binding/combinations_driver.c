#include "combinations.h"

int main(int argc, char *argv[]) {

  int N = 5, k = 2;
  int * v = FirstCombination(k, N);
  do {
    PrintCombination(v, k);
  }  while (NextCombination(v, k, N));

  free(v);
  
  return 0;
}
