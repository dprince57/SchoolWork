#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Usage: ./lcs string1 string2" << endl;
    return 0;
  }

  char *x = argv[1], *y = argv[2];
  int n = strlen(x), m = strlen(y);

  if (n < m) {
    cout << "Put the longer one first." << endl;
    return 0;
  }

  int A[n+1][m+1];
  string theStrings[n+1][m+1];

  for(int i=0; i < n+1; i++) {
    A[i][0] = 0;
    theStrings[i][0] = "";
  }

  for(int j=0; j < m+1; j++) {
    A[0][j] = 0;
    theStrings[0][j] = "";
  }

  for(int i=1; i < n+1; i++)
    for(int j=1; j < m+1; j++) {
      int val = 0;
      theStrings[i][j] = "";

      if (x[i-1] == y[j-1]) {
	val = 1 + A[i-1][j-1];
	theStrings[i][j] = theStrings[i-1][j-1] + x[i-1];
      }

      if (A[i][j-1] > val) {
	val = A[i][j-1];
	theStrings[i][j] = theStrings[i][j-1];
      }

      if (A[i-1][j] > val) {
	val = A[i-1][j];
	theStrings[i][j] = theStrings[i-1][j];
      }


      A[i][j] = val;
    }
  
  cout << A[n][m] << endl << theStrings[n][m] << endl;
}
