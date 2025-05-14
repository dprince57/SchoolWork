#include <iostream>
#include <stdlib.h>
using namespace std;



// A will be some permuation of 0, 1, ..., n-1.
int doSomething(int A[], char data[], int n) {
  for(int i=0;i<n;i++)
    cout << data[A[i]-1] << " ";
}


// permute will have A go through all the permutations of
// 0, 1, 2, ..., n-1.
int permute(int A[], int n, int level, char data[]) {
  if (level == 0) {
    /*for(int i=0;i<n;i++)
      //      cout << A[i] << " ";
      cout << data[A[i]-1] << " ";*/
    doSomething(A, data, n);
    cout << endl;
    return 0;
  }
  if (level == n) {
    for(int i=0;i<n;i++) A[i] = -1;
  }
  for(int i=0;i<n;i++) {
    if (A[i] == -1) {
      A[i] = level;
      permute(A,n,level-1,data);
      A[i] = -1;
    }
  }
}


int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: ./a.out n" << endl;
    return 0;
  }
  int n = atoi(argv[1]);
  int A[n];

  // data will store whatever the things are that we want to permute.
  // for this example, we'll permute the letters abcde...
  char data[n];
  for(int i=0;i<n;i++) 
    data[i] = 'a' + (i % 26);

  // A is just used inside of permute.
  permute(A,n,n,data);
}
