
/*
  types, defines, includes, prototypes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

#define S_BAD    0
#define S_GOOD   1

#define PORT  2150
#define N     8192

#define MESSAGE "\nWelcome to our chat server.\n\n"

typedef struct connection {
  int desc;
  int status;
  char inbuf[N];
  char outbuf[N];
  struct connection *link;
} NODE;

int init_socket();
void CheckForNewConnections(int sock);
void CheckForInput();
void CheckForOutput();
void ProcessInput();
void RemoveBadConnections();

