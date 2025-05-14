#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  // ask for a grade
  int count = 0;
  float min = 100.0;
  float max = 0.0;
  float total = 0;
  while (1) {
    printf("Grade please (0-100, -1 to stop): ");
    float f;
    scanf("%f", &f);
    //if first number is less than 1, print empty
    if(count == 0 && f < 0){
        printf("Average: \nHighest: \nLowest: \n");
        return 0;
    }
    if (f < 0) {
      break;
    }//verify number between 0-100, if not tell user to fix ad do not add
    if(f >= 0 && f <= 100){
        if(f < min)min=f;
        if(f > max)max=f;
        total += f;
        count ++;
    }else{
        printf("A number between 0 and 100 please\n");
    }
  }
  //print average, highest, and lowest
  printf("Average: %f\nHighest: %f\nLowest: %f\n", total / count,max,min);
  return 0;
}
