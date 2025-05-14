
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#define N 8192

int main(int argc, char *argv[]){
  char *ipstring;
  char *portstring;
  unsigned short int port;
  unsigned int addr;
  int sock;

  struct sockaddr_in sa; /* socket address for the internet */

  ipstring = argv[1];
  portstring = argv[2];

  addr = inet_addr(ipstring);

  port = atoi(portstring);
  port = htons(port);

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = addr;
  sa.sin_port = port;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    perror("socket");
    exit(0);
  }

  if(connect(sock, (struct sockaddr*) &sa, sizeof(struct sockaddr_in)) < 0) {
    perror("connect");
    exit(0);
  }

  for(;;){
    CheckServer(sock);
    CheckClient(sock);
    usleep(100000);
  }
}

int CheckClient(int sock){
  int err, nbytes, nread;
  char b[N];

  err = ioctl(0, FIONREAD, &nbytes);
  if(nbytes <= 0)
    return 0;

  nread = read(0, b, N);
  if(nread <= 0)
    return 0;

  write(sock, b, nread);
  return 0;
}
int CheckServer(int sock){
  int err, nbytes, nread;
  char b[N+1];

  for(;;){
    err = ioctl(sock, FIONREAD, &nbytes);
    if(nbytes <= 0)
      return 0;

    nread = read(sock, b, N);
    if(nread <= 0)
      return 0;

    b[nread] = 0;
    printf("%s\n", b);
  }
  return 0;
}
