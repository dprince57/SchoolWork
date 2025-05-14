#include <stdio.h>
#include <stdlib.h>

int main() {
  int numLines, numbersPerLine;

  scanf("%i", &numLines);
  scanf("%i", &numbersPerLine);

  int line;
  for(line=0; line < numLines; line++) {
    int count = 0;

    int i;
    for(i=0; i < numbersPerLine; i++) {
      int x;
      scanf("%i",&x);
      if (x < 0) count++;
    }

    printf("Case %i: %i\n", line+1, count);
  }

  return 0;
}
