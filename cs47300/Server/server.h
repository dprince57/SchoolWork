
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
#include <crypt.h>

#define _XOPEN_SOURCE

#define S_BAD    0
#define S_GOOD   1
#define S_LOGIN  2
#define S_PASSWD 3

#define N     8192

#define BUFFERLEN  256

#define MESSAGE "\nWelcome to our grand chat server.\n\n"
#define MESSAGE1 "Please enter a 3 - 11 character username: "
#define MESSAGE2 "Password: "
#define MESSAGE3 "INPUT: "

#define SALT     "$5$pretzel$"

typedef struct connection {
  int desc;
  int status;
  char inbuf[N];
  char outbuf[N];
  char name[N];
  char passwd[N];
  struct connection *link;
} NODE;

int init_socket();
void CheckForNewConnections(int sock);
void CheckForInput();
void CheckForOutput();
void ProcessInput();
void RemoveBadConnections();
void Commands(char line[N], NODE *p);

