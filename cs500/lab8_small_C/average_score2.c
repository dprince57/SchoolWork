#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Goal: ask for grades as long as they type a positive number, and print the average.
*/
char *letter_grade(int grade){
  switch(grade){
    case 98 ... 100:
        return "A+";
    case 92 ... 97:
        return "A";
    case 90 ... 91:
        return "A-";
    case 87 ... 89:
        return "B+";
    case 84 ... 86:
        return "B";
    case 80 ... 83:
        return "B-";
    case 77 ... 79:
        return "C+";
    case 74 ... 76:
        return "C";
    case 70 ... 73:
        return "C-";
    case 67 ... 69:
        return "D+";
    case 64 ... 66:
        return "D";
    case 61 ... 63:
        return "D-";
    case 0 ... 60:
        return "F";
  }
  return "No grade given";
}
int main(int argc, char *argv[]) {

  // lab8 - do not printf asking for input, just scanf without printing.
  
  // ask for a grade
  int count = 0;
  float total = 0;
  while (1) {
    printf("Grade please (0-100, -1 to stop): ");
    // int, string, char, double/float
    float f;
    scanf("%f", &f);
    if (f < 0) {
      break;
    }
    if(f>100){
      printf("grades inside 100 please\n");
      continue;
    }
    total += f;
    count ++;
  }
  //printf("After loop, i = %d\n", i);

  printf("Average: %f\n", total / count);
  
  // lab8 - also print the letter grade, using the default grading scale in Canvas (below)
  printf("Letter grade: %s\n",letter_grade(total/count));

  return 0;
}
