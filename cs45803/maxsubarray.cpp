#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: ./maxsub n fast|slow" << endl;
    exit(0);
  }

  int n = atoi(argv[1]);

  vector<int> A;

  // seed the random number generator.
  //srand(time(NULL));
  srand(7);

  // put n random values into array.
  int i;
  for(i=0;i<n;i++)
    A.push_back(rand() % 20 - 5);

  // debug, print A
  //for(i=0;i<n;i++)
  //cout << A[i] << endl;

  int count=0;

  // try all possible sub-arrays.
  int bestSoFar= A[0];
  int bestB=0, bestE=0;

  if (argc > 2 && strcmp(argv[2],"fast")==0) {
    /*
      for you to do - the divid and conquer algorithm.
     */ 
  }
  else {
    // here is the brute force algorithm...
    
    // for begin=0 to n-1
    for(int b=0; b <= n-1; b++) {
      // for end=begin to n-1
      for(int e=b; e <= n-1; e++) {
	int total = 0;
	// for i=begin to end
	for(int i=b; i<=e; i++) {
	  total += A[i];
	  count++;
	}
	if (total > bestSoFar) {
	  bestSoFar = total;
	  bestB = b; bestE = e;
	}
      }
    }
  }

  // 
  cout << "Optimal is ... " << bestSoFar << " with (b,e) = " << bestB << ", " 
       << bestE << endl;

  cout << "Number of times access A was " << count << endl;

  int expected;
  expected = (n*n*n+3*n*n+2*n)/6;
  cout << "Expected # accesses was " << expected << endl;
  

  return 0;
}
