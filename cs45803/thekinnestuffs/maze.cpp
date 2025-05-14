#include <iostream>
#include <stdlib.h>
using namespace std;

// undirected graph class.
class graph{
public:
  int *G;
  int n;

  // constructor, initialize all weights to 0.
  graph(int numVertices) {
    n = numVertices;
    G = new int[n*n];
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
	setE(i,j,0);
  }

  // get value of an Edge
  virtual int E(int i, int j) {
    return G[i*n+j];
  }

  // set value of an edge
  virtual void setE(int i, int j, int val) {
    G[i*n+j] = val;
    G[j*n+i] = val;
  }

  // initialize weights to random.
  void random() {
    for(int i=0;i<n;i++)
      for(int j=i+1;j<n;j++) {
	int val = rand() % 100;
	setE(i,j,val);
	setE(j,i,val);
      }
  }

  ~graph() {
    delete [] G;
  }
};


// undirected grid graph
class gridGraph : public graph {
public:
  int w, h;

  gridGraph(int width, int height) : graph(width*height) {
    w = width; h = height;
  }

  ~gridGraph(){
  }

  // return edge value
  int E(int x1, int y1, int x2, int y2) {
    return graph::E(x1*w+y1, x2*w+y2);
  }

  // set edge value
  void setE(int x1, int y1, int x2, int y2, int val) {
    if (x1 >= w || y1 >= h || x2 >= w || y2 >= h ||
	x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) return;
    graph::setE(x1*w+y1, x2*2+y2, val);
  }

  void random() {
    for(int x=0; x<w; x++)
      for(int y=0; y<h; y++) {
	setE(x,y, x+1,y, rand() % 100);
	setE(x,y, x,y+1, rand() % 100);
	setE(x,y, x-1,y, rand() % 100);
	setE(x,y, x,y-1, rand() % 100);
      }
  }


  void print() {
    for(int y=0; y < h; y++) 
      for(int x=0; x < w; x++) {
	
      }
  }
};

int main() {
  gridGraph G(5,5);

  G.random();
}
