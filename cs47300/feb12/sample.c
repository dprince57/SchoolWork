#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bitstring {
  unsigned sex:1;
  unsigned year:2;
  unsigned nclass:3;
  unsigned park:2;
} __attribute__ ((__packed__))DATA;

int main()
{
  DATA x;

  x.sex = 1;
  x.year = 2;
  x.nclass = 3;
  x.park = 3;
  printf("%d %d %d %d - %d\n", x.sex, x.year, x.nclass, x.park, sizeof(DATA));
}
