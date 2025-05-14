
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N  99

typedef
  unsigned char
uchar;

uchar ma[N][N];

int delta[4][2]={
  { 2, 0},
  { 0, 2},
  {-2, 0},
  { 0,-2}
};

void makemaze();
void printmaze();

int main(int argc, char *argv[])
{
  srand48(getpid());
  makemaze();
  printmaze();
}
int getneighbors(int li[], int row, int col)
{
  int i,r,c,n;

  n = 0;
  for(i=0;i<4;i++){
    r = row + delta[i][0];
    c = col + delta[i][1];
    if(ma[r][c] == 0)
      li[n++] = i;
  }
  return n;
}
void shuffle(int li[], int n)
{
  int i,j,k,t;

  for(i=0;i<n;i++){
    j = lrand48() % n;
    k = lrand48() % n;
    if(j != k){
      t = li[j]; li[j] = li[k]; li[k] = t;
    }
  }
}
void dfs(int row, int col)
{
  int i,j,r,c,n,dr,dc;
  int li[4];

  ma[row][col] = 1;
  n = getneighbors(li,row,col);
  if(n > 1)
    shuffle(li,n);
  for(i=0;i<n;i++){
    j = li[i];
    dr = delta[j][0];
    dc = delta[j][1];
    r = row + dr;
    c = col + dc;
    if(ma[r][c] == 0){
      ma[row+dr/2][col+dc/2] = 1;
      dfs(row+dr,col+dc);
    }
  }
}
void makemaze()
{
  int i,j,k,u,v;

  memset(ma,0,N*N*sizeof(uchar));
  for(i=0;i<N;i++){
    ma[i][0] = 1;
    ma[0][i] = 1;
    ma[i][N-1] = 1;
    ma[N-1][i] = 1;
  }
  u = v = 2;
  dfs(u,v);
}
void printmaze()
{
  int i,j;

  for(i=0;i<N;i++){
    for(j=0;j<N;j++)
      printf("%d", ma[i][j] ? 9 : 0);
    printf("\n");
  }
}
