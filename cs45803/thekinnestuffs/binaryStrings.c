#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned long x;
  int numBits = 8;
  unsigned long maxVal = 1 << 8;

  for(x = 0; x != maxVal; x++) {
    int index;
    for(index=7;index>=0;index--)
      printf("%i", (x & (1 << index)) >> index);
    printf(" %i\n", x);
  }

  return 0;
}
