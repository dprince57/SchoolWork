//Code by: Dakota Prince
//Math by: Jerald Worthington
//         Roger Bisimwa
 
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

vector<int> primes;

int extendedE(int a,int b){
  int j;
  int n = b;
  int x[3];
  int y[3];
  int quotient  = a / b;
  int remainder = a % b;

  x[0] = 0;
  y[0] = 1;
  x[1] = 1;
  y[1] = quotient * -1;

  int i = 2;
  for (; (b % (a%b)) != 0; i++)
  {
    a = b;
    b = remainder;
    quotient = a / b;
    remainder = a % b;
    x[i % 3] = (quotient * -1 * x[(i - 1) % 3]) + x[(i - 2) % 3];
    y[i % 3] = (quotient * -1 * y[(i - 1) % 3]) + y[(i - 2) % 3];
  }
  j = x[(i-1)%3];
  if(j < 0)
    j = j + n;  
  return j;
}
int isprime(int n){
  float j;
  for(int i=1;i<sqrt(n);i++){
    j = n%i;
    if(j == 0)
      return 0;
  }
}

int gcd(int x,int y){
  int j;
  for(y=x;y<=x;--y){
    j = x%y;
    if(j==0)
      return y;
  }
}

int phi(const int n){
  if (n < 2)
    return 0;
 
  if (isprime(n) == 0)
    return n-1;
 
  if (n & 1 == 0){
    int m = n >> 1;
    return !(m & 1) ? phi(m)<<1 : phi(m);
  }
 
  for (vector<int>::iterator p = primes.begin();
        p != primes.end() && *p <= n;
        ++p )
  {
    int m = *p;
    if ( n % m  ) continue;
 
    int o = n/m;
    int d = gcd(m, o);
    return (d==1) ? phi(m)*phi(o) : phi(m)*phi(o)*d/phi(d);
  }
}
int genKey(){
  int i,j,k,num,raNum;
  num = 10242;
  
  int p,q,n;
  int e,d,nP;
  int pX,qX;
  int a[num];
  
  j = 1;

  srand(time(NULL));
  pX = rand() % num;
  qX = rand() % num;
  
  cout << "pX " << pX << endl;
  cout << "qX " << qX << endl;



  // Initializing For Loop for Sieve's 
  for(i=0;i<num;i++){
    a[i] = i + 1;
  }

  cout << "Seives setup" << endl;
  // Sieve's Algoritm to find primes 
  for(i=2;i<sqrt(num);i++){
    for(k=0;k<num;k++){
      j = a[k] % i;
      if(j == 0 && a[k] != i){
        a[k] = 0;
      }
    }
  }



  cout << "Sieves complete" << endl;
  //for loop for putting our newly found primes into 
  //a vector
  for(i=2;i<num;i++){
    if(a[i] != 0)
      primes.push_back(a[i]);
      if(i > pX && pX == 0){
        p = a[i];
      }    
      if(i > qX && qX == 0){
        q = a[i];
      }    
  }


  cout << "vector made" << endl;
  //p = 61;
  //q = 53;
  cout << "p " << p << endl;
  cout << "q " << q << endl;
  n = p * q;
  cout << "n " << n << endl;

  nP = phi(p)*phi(q);

  cout <<  "After Phi Function " << nP << endl;
  e = 17; 
//  for(i = 1;i<nP;i++){
//    e = gcd(i,nP);
//    if(e == 1)
//    e = i;
//  break;
//  }
  
  cout << "public key " << e << endl;
  d = extendedE(e,nP);
  cout << "private key " << d << endl;

  return e,d;
}

int main(int argc,char *argv[]){
  genKey();
}
