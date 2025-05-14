
#include "server.h"

extern NODE *head;

void ProcessInput()
{
  NODE *p, *q;
  char buffer[BUFFERLEN];
  char *word;

  for(p = head ; p ; p = p->link){
    if(p->inbuf[0] == 0)
      continue;
    if(p->inbuf[0] == '/'){          /* a command */
      Commands(p->inbuf, p);
    } else {                         /* a message for all */
      for(q = head ; q ; q = q->link){
        if((q != p) && (q->status != S_BAD)){
          strcat(q->outbuf, "\n");
          strcat(q->outbuf, p->name);
          strcat(q->outbuf, ": ");
          strcat(q->outbuf, p->inbuf);
          strcat(q->outbuf, MESSAGE3);
        } else if((q == p) && (q->status != S_BAD))
          strcat(p->outbuf, MESSAGE3);
      }
    }
    p->inbuf[0] = 0;                    /* empty input buffer */
  }
}
