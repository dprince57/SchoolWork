
#include "server.h"
#include <signal.h>

NODE *head;
int PORT;
int maxdesc=0;
int sock;
void cleanup();

int main(int argc, char *argv[])
{
  signal(SIGINT, cleanup);
  if(argc < 2){
    fprintf(stderr,"usage: %s PORT\n",argv[0]);
    exit(0);
  }
  PORT = atoi(argv[1]);

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
void cleanup()
{
  NODE *p;

  for(p = head ; p ; p = p->link)
    close(p->desc);
  close(sock);
  exit(0);
}
