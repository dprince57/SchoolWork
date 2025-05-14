#define K 1024

int main() {
  char name[K];
  int n;
  // 0 is stdin, 1 is stdout, 2 is stderr for the first parameter
  // the second parameter is the message
  // the third parameter is how many characters
  write(1, "What is your name: ", 19);
  n = read(0, name, K);
  if(n > 0) {
    write(1, "Hello, ", 7);
    write(1, name ,n);
  }
}
