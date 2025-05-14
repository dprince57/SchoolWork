#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("%d\n", 1 || 1 && 0);

  printf("%d\n", 0x18 | 0x1c & 0x1b);
  printf("0x%x\n", 0x18 | 0x1c & 0x1b);
  /*
    0x18 = 0b 0001 1000

     0x1c = 0b 0001 1100
  &  0x1b = 0b 0001 1011
  ----------------------
            0b 0001 1000
          | 0b 0001 1000
         ----------------
            0b 0001 1000
            0x    1 8
             = in decimal 24
   */
  return 0;
}
