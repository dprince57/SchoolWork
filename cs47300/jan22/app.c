
#include "server.h"

extern NODE *head;

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
