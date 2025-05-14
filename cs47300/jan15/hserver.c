
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#define PORT 2150

int init_socket();
void CheckForNewConnections(int sock);

int main(int argc, char *argv[]){
  int sock;
  
  sock = init_socket();
  for(;;){
    CheckForNewConnections(sock);
    usleep(10000);
  }
}

int init_socket() {
  int sock;
  struct sockaddr_in sa;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    perror("socket");
    exit(0);
  }

  memset(&sa, 0, sizeof(struct sockaddr_in));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(PORT);

  if(bind(sock, (struct sockaddr *) &sa, sizeof(struct sockaddr_in)) < 0){
    perror("bind");
    exit(0);
  }

  listen(sock, 4);

  return sock;
}

void CheckForNewConnections(int sock) {
  fd_set inset; /* bit string for input descriptors */
  struct timeval zero={0,0};
  struct sockaddr_in sa;
  int desc, size;

  FD_ZERO(&inset); /* turn off all bits */
  FD_SET(sock, &inset); /* turn on (make == 1) the bit for the socket */

  select(sock+1, &inset, 0, 0, &zero);
  if(!FD_ISSET(sock, &inset))
    return;
  /* if make it here, there is a new connection */

  desc = accept(sock, (struct sockaddr *) &sa, &size);
  if(desc < 0) {
    perror("accept");
    return;
  }
  write(desc, "Hello.\n", 7);
  close(desc);
}
