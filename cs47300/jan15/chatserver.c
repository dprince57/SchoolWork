
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

NODE *head;
int maxdesc=0;

int init_socket();
void CheckForNewConnections(int sock);
void CheckForInput();
void CheckForOutput();
void ProcessInput();
void RemoveBadConnections();

int main(int argc, char *argv[])
{
  int sock;

  sock = init_socket();
  for(;;){
    CheckForNewConnections(sock);
    CheckForInput();
    ProcessInput();
    CheckForOutput();
    RemoveBadConnections();
    usleep(10000);
  }
}
int init_socket()
{
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
NODE *makenode(int desc)
{
  NODE *p;

  p = malloc(sizeof(NODE));
  p->desc = desc;
  p->status = S_GOOD;
  p->inbuf[0] = 0;
  p->outbuf[0] = 0;
  p->link = 0;
  return p;
}
void CheckForNewConnections(int sock)
{
  struct sockaddr_in sa;
  fd_set inset;  /* bit string for input descriptors */
  struct timeval zero={0,0};
  int desc, size;
  NODE *p;

  FD_ZERO(&inset);        /* turn off all bits */
  FD_SET(sock, &inset);   /* turn on (make == 1) the bit for the socket */
  select(sock+1, &inset, 0, 0, &zero);
  if( !FD_ISSET(sock, &inset))
    return;
/*
  if we make it to here, there is a new connection
*/
  desc = accept(sock, (struct sockaddr *) &sa, &size);
  if(desc < 0){
    perror("accept");
    return;
  }
  p = makenode(desc);
  p->link = head;
  head = p;
  strcpy(p->outbuf, MESSAGE);
  fprintf(stderr,"Descriptor: %d\n", desc);
  if(desc > maxdesc)
    maxdesc = desc;
}
/*
  1. remember to remove newlines when looking for a name
  2. pay attention to windoze users  (\n\r)
*/
void CheckForInput()
{
  fd_set inset;
  NODE *p;
  struct timeval zero={0,0};
  int n;

  FD_ZERO(&inset);
  for(p = head ; p ; p = p->link)
    if(p->status != S_BAD)
      FD_SET(p->desc, &inset);
  select(maxdesc+1, &inset, 0, 0, &zero); 
  for(p = head ; p ; p = p->link)
    if(FD_ISSET(p->desc, &inset)){
      n = read(p->desc, p->inbuf, N);
      if(n <= 0)
        p->status = S_BAD;
      else
        p->inbuf[n] = 0;
    }
}
/*
  1. if user is in login state:
       a. check if name is valid (remove newlines)
       b. make sure they do not get messages
       c. change state (maybe send an extra message) when
            they move to the normal state
         otherwise they need the login prompt again
  2. check for control and escape characters
  3. check for buffer overflow: compare length of message
         to size of remain buffer space
*/
void ProcessInput()
{
  NODE *p, *q;

  for(p = head ; p ; p = p->link)
    if(p->inbuf[0]){
      for(q = head ; q ; q = q->link)
        if((q != p) && (q->status != S_BAD))
          strcat(q->outbuf, p->inbuf);
      p->inbuf[0] = 0;                    /* empty input buffer */
    }
}
/*
  really should check to see if n (returned by write) is the
  same as the length you sent
*/
void CheckForOutput()
{
  fd_set outset;
  NODE *p;
  struct timeval zero={0,0};
  int n;

  FD_ZERO(&outset);
  for(p = head ; p ; p = p->link)
    if(p->status != S_BAD)
      if(p->outbuf[0])
        FD_SET(p->desc, &outset);
  select(maxdesc+1, 0, &outset, 0, &zero); 
  for(p = head ; p ; p = p->link)
    if(FD_ISSET(p->desc, &outset)){
      n = write(p->desc, p->outbuf, strlen(p->outbuf));
      if(n <= 0)
        p->status = S_BAD;
      else
        p->outbuf[0] = 0;
    }
}
void RemoveBadConnections()
{
}
