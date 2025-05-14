#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  char c;
  printf("%d\n", sizeof(c)); // how many bytes

  short int sh;
  printf("%d\n", sizeof(sh));

  printf("%d\n%d\n%d\n", sizeof(int), sizeof(long), sizeof(long long));

  /*
    Ranges of things...

    char is 1 byte, that is 8 bits
      range: -2**7 to 2**7-1, -128 to 127
    2s complement - look it up

    unsigned char, 8 bits, so 0 to 2**8 - 1 = 255
    0b11111111 = 255
  */
  c = 127; // stored in 2's complement, 0111 1111
  printf("c = %d (0x%x)\n", c, c);
  c = c+1; // so, 0b 1000 0000, which in 2s complement means -128
  printf("c = %d (0x%x)\n", c, c);
  // note: why was c=c+1 not an error? C is minimalist, the
  //  compiler is not going to do anything for us.
  // In C, oftentimes, the code will run, even if it is
  //  wrong or strange.

  /*
   unsigned int, 4 bytes, 32 bits, from 0 to 2**32 -1,
         (2**10)**3 * 2**2 - 1
      roughly (1000)**3 * 2**2 - 1, roughly 4 billion

  signed int, 4 bytes, 32 bits, 
     -2**31 to 2**31-1, roughly -2billion to 2billion
  unsigned short, 2 bytes, 16 bits, from 0 to 2**16-1,
     roughly 0 to 65535

  unsigned long, 8 bytes, 64 bits, 0 to 2**64-1
             roughly, 0 to 16 * (1000)**6, 16 * 10**18
  */

  return 0;
}
