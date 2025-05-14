
#include "server.h"

extern NODE *head;
extern int maxdesc;

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
