#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
  What is 8 + 7?
   16
  Sorry, that is wrong. It was 15.
*/

int main(int argc, char *argv[]) {

  if (argc > 2)
    srand(atoi(argv[1]));
  srand(time(NULL));
  int response;
  int correct_count = 0;
  // lab8 - loop until they get one wrong, output the total correct at the end
  while(1){
    int x = rand() % 10, y = rand() % 10;
    printf("What is %d + %d?\n", x, y);
    scanf("%d", &response);

    if (response == x + y) {
        printf("Correct!\n");
        correct_count++;
    }else{
        printf("Sorry, that is wrong. It was %d.\n", x+y);
        break;
    }
  }
  printf("Number of correct in a row: %d\n", correct_count);

  return 0;
}
