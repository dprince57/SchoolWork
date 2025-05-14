#include <iostream>
#include <stdlib.h>
using namespace std;

int G[100][100];

int main() {
  for(int i=0; i< 100; i++) {
    for(int j=0; j<100; j++) {
      G[i][j] = 0;
    }
  }

  for(int i=0; i< 100; i++) {
    for(int j=i+1; j<100; j++) {
      if (rand() % 10 == 0) {
	G[i][j] = G[j][i] = 1;
      }
    }
  }

  int maxDegree = 0, numIsolated = 0;

  for(int v=0; v < 100; v++) {
    int myDegree = 0;

    for(int u=0; u < 100; u++) {
      if (G[v][u] || G[u][v]) myDegree++;
    }

    if (myDegree == 0) numIsolated++;

    if (myDegree > maxDegree) maxDegree = myDegree;
  }

  cout << "Isolated vertices " << numIsolated << endl;
  cout << "Maximum degree " << maxDegree << endl;

  return 0;
}
