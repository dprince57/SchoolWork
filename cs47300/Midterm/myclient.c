
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#define K 4096
#define DEFAULTPORT 2327

#define USER "BobbyHill"
#define USERLEN 9
#define PASS "bwah"
#define PASSLEN 4

#define KILLCMD "k cockroach"
#define KILLLEN 11

struct sockaddr_in name;

int port,local,fini;

int main(int argc, char *argv[])
{
  char b[K];
  int i,err,nr;
  unsigned long addr;
  char *hostname;
  struct hostent *hp;

  setbuf(stdin ,0);
  setbuf(stdout,0);
  name.sin_family = AF_INET;
  hostname = (argc > 1) ? argv[1] : "cs.indstate.edu";
  if(isdigit(hostname[0])){
    addr = inet_addr(hostname);
    name.sin_addr.s_addr = addr;
  } else {
    hp = gethostbyname(hostname);
    if(hp == NULL){
      perror("Getting Host");
      exit(0);
    }
/*
    memcpy(&name.sin_addr, hp->h_addr, hp->h_length);
*/
    fprintf(stderr,"%08x\n", *((unsigned int *) hp->h_addr));
    name.sin_addr.s_addr = *((unsigned int *) hp->h_addr);
  }
  port = (argc==3) ? atoi(argv[2]) : DEFAULTPORT;
  local = socket(AF_INET,SOCK_STREAM,0);
  if(local < 0){
    fprintf(stderr,"Opening local socket\n");
    exit(0);
  }
  name.sin_port = htons(port);
  if(connect(local,(struct sockaddr *)&name, sizeof(struct sockaddr_in)) < 0){
    fprintf(stderr,"Unable to connect.\n");
    exit(0);
  }
  write(local, USER, USERLEN);
  usleep(50000);
  write(local, PASS, PASSLEN);
  printf("Connected, username: %s\n", USER);
  for(fini=0;!fini;usleep(50000)){
    LineFromServer();
    err=ioctl(0,FIONREAD,&nr);
    if(nr)
      LineForServer();
  }
}
int LineFromServer()
{
  char b[K];
  char *line;
  int n,nr,err;
  fd_set iset;
  struct timeval zero;

  zero.tv_sec=0;
  zero.tv_usec=0;
  FD_ZERO(&iset);
  FD_SET(local,&iset);
  select(local+1,&iset,0,0,&zero);
  if(!FD_ISSET(local,&iset))
    return;
  if((n=read(local,b,K-1)) < 0) return;
  if(n == 0){
    fprintf(stderr,"Connect closed by remote host.\n");
    exit(0);
  }
  b[n]=0;
  line = strtok(b," ");
  line = strtok(0, " ");
  if(strcmp(line,"cockroach") == 0){
    line = strtok(0, " ");
    if(strcmp(line,"has") == 0)
      write(local, KILLCMD, KILLLEN);
  }
  fflush(stdout);
}
int LineForServer()
{
  char b[K];
  int n;

  n=read(0,b,K-1);
  if(n <= 0)
    return;
  b[n]=0;
  write(local,b,n);
}
