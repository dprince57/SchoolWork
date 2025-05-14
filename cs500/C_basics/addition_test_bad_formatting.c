#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  What is 8 + 7?
   16
  Sorry, that is wrong. It was 15.
*/

int main(int argc, char *argv[]) {

srand(time(NULL)); int x = rand() % 10, y = rand() % 10;
      printf("What is %d + %d?\n", x, y);  int response;
scanf("%d", &response);

if (response == x + y) printf("Correct!\n");
  else 
printf("Sorry, that is wrong. It was %d.\n", x+y);

return 0;
}
