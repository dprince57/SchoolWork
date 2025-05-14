#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main() {
  int N;

  cin >> N;

  for(int i=0; i < N; i++) {
    int num, howmany;
    cin >> num >> howmany;
    string s;
    cin >> s;

    //cout << num << " ";
    for(int j=0; j < s.size(); j++) {
      for(int k=0; k < howmany; k++) 
	cout << s[j];
    }
    cout << endl;
  }

  return 0;
}
