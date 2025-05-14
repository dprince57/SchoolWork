
#include "server.h"

NODE *head;
int maxdesc=0;

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
