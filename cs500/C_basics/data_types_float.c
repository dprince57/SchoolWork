#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  float f = 3.14;
  printf("%d\n", sizeof(f));

  /*
    scientific notation...
    +/-   2.7182818 x 10**1
    sign   mantissa     exponent
    +/-   0b10101011101110000000010 x 2**(0b00000110)

    float is 4 bytes, 32 bits, 23? bits for mantissa, 8? bits for exponent, 1 bit for sign
      3.14 * 10**0
      3.14 * 2**0
    if 8 bits for exopnent: -128 to 127, max value is something like 2**127 = 10**30ish
    if 23 bits for mantissa: 7-8? significant digits in decimal
    With 7-8 sig digits, what is the value of this...
    x = 1.0;
    x = x + 0.00000000001; 
    1.00000000001 is more than 7-8 digits.
    x will be still 1.0
  */

  printf("f before inc: %.15f\n", f);
  f = f + 0.0000000001;
  printf("f after inc:  %.15f\n", f);

  // double: 8 bytes,
  double d = 3.14;
  printf("%d\n", sizeof(double));
  printf("d before inc: %.15lf\n", d);
  d = d + 0.0000000001;
  printf("d after inc:  %.15lf\n", d);
  return 0;
}
