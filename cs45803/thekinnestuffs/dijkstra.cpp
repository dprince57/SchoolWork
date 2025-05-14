#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <list>
#include <stdlib.h>
#include <cfloat>
using namespace std;


/*
  todo: get weights in....
        also make sure to update Q when it's not just an array...
 */

class vertex {
public:
  double d; // distance from source to this vertex
  int pi; // parent along shortest path from source
  vector<int> E; // edges
  vector<double> W; // weights of the edges

  vertex() {
    d = DBL_MAX; // "infinity"
    pi = -1; // no parent yet
  }

  void print() {
    cout << "d = " << d << ", pi = " << pi << ". ";
    for(int i = 0;i<E.size();i++) 
      cout << "w(.," << E[i] << ")=" << W[i] << " ";
    cout << endl;
  }

  bool isNeighbor(int v) {
    for(int i=0;i<E.size();i++) {
      if (E[i] == v) return true;
    }
    return false;
  }

  // add neighbor if it is not already an edge.  return true/false
  // indicating if edge was added.
  bool addNeighbor(int v, int w) {
    for(int i=0;i<E.size();i++) {
      if (E[i] == v) return false;
    }
    E.push_back(v);
    W.push_back(w);     
    return true;
  }
};


class graph {
public:
  vector<vertex> V;

  graph(int n) {
    loadRandom(n);
  }

  void loadRandom(int n) {
    V.resize(0);
    for(int i=0;i<n;i++) {
      vertex v;
      V.push_back(v);
    }

    // pick neighbors and weights at random.
    for(int i=0;i<n;i++) {
      int numNeighbors = rand() % n/10;
      double weight;
      int neighbor;
      for(int j=0;j<numNeighbors;j++) {
	neighbor = rand() % n;
	weight = (double) (rand() % 100);
	V[i].addNeighbor(neighbor, weight);
	V[neighbor].addNeighbor(i, weight);
      }
    }
  }

  graph(double M[], int n) {
    loadMatrix(M,n);
  }

  void loadMatrix(double M[], int n) {
    V.resize(0);
    for(int i=0;i<n;i++) {
      vertex v;
      V.push_back(v);
      for(int j=0;j<n;j++) {
	if (M[i*n+j] != 0) {
	  V[i].addNeighbor(j,M[i*n+j]);
	}
      }
    }
  }

  void print() {
    cout << "----------------------------" << endl;
    for(int i=0; i<V.size(); i++) {
      cout << "vertex " << i << ": ";
      V[i].print();
    }
  }


  void initialize_single_source(int s) {
    for(int i=0; i<V.size(); i++) {
      V[i].d = DBL_MAX; 
      V[i].pi = -1;
    }
    V[s].d = 0;
  }


  void dijkstra(int s) {
    initialize_single_source(s);
    //S = empty;
    
    // Q = all of V.
    vector<int> Q;
    for(int i=0;i<V.size();i++) {
      Q.push_back(i); 
      // Q has indices of things we haven't processed.
    }

    
    while (Q.size() > 0) {
      // u = extract_min(Q); vertex with minimal d value
      int iSmall = 0, valSmall = V[Q[0]].d;
      for(int i=0; i < Q.size(); i++) {
	if (V[Q[i]].d != -1 && V[Q[i]].d < valSmall) {
	  iSmall = i;
	  valSmall = V[Q[i]].d;
	}
      }
      int u = Q[iSmall];
      Q.erase(Q.begin() + iSmall);

      //S = S union u;
      for(int i=0; i < V[u].E.size(); i++) {
	// relax, see if going through u is better 
	int v = V[u].E[i];
	if (V[v].d > V[u].d + V[u].W[i]) {
	  V[v].d = V[u].d + V[u].W[i];
	  V[v].pi = u;
	}
      }
    }
  }
    
};


int main(int argc, char *argv[]) {
  double M[8*8] = 
  // O, A, B, C,  D, E, F, T
    {0, 2, 5, 4,  0, 0, 0, 0, // O
     2, 0, 2, 0,  7, 0, 12,0, // A
     5, 2, 0, 1,  4, 3, 0, 0, // B
     4, 0, 1, 0,  0, 4, 0, 0, // C
     
     0, 7, 4, 0,  0, 1, 0, 5, // D
     0, 0, 3, 4,  1, 0, 0, 7, // E
     0,12, 0, 0,  0, 0, 0, 3, // F
     0, 0, 0, 0,  5, 7, 3, 0}; // T
  
  graph G(M,8);
  G.print();
  G.dijkstra(0);
  G.print();

  int n;
  if (argc > 1) 
    n = atoi(argv[1]);
  else {
    cout << "Okay, time for a test...";
    cout << "How many vertices? ";
    cin >> n;
  }

  graph G2(n);
  G.dijkstra(0);

  cout << "Done running Dijkstra on random graph with " << n << " vertices" << endl;

  return 0;
}



