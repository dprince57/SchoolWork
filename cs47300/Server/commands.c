
#include "server.h"

extern NODE *head;

int countusers()
{
  NODE *p;
  int count = 0;

  for(p = head; p ; p = p->link)
    if(p->status == S_GOOD)
      count++;

  return count;
}
void Commands(char line[N], NODE *p)
{
  NODE *q;
  char buffer[BUFFERLEN];
  char *word;

  word = strtok(line," ");
  if(strcmp(word, "/tell") == 0) {
    word = strtok(0," ");
    for(q = head; q ; q = q->link)
      if(strcmp(q->name, word) == 0){
        word = strtok(0,"\n");
        strcat(q->outbuf, "\n");
        strcat(q->outbuf, p->name);
        strcat(q->outbuf, " whispers: ");
        strcat(q->outbuf, word);
        strcat(q->outbuf, "\n");
        strcat(q->outbuf, MESSAGE3);
        strcat(p->outbuf, MESSAGE3);
      }
  } else {
    word = strtok(line, "\n");
    if(strcmp(word, "/users") == 0){ 
      sprintf(buffer,"There are %d users.\n", countusers());
      strcat(p->outbuf,buffer);
    } else if(strcmp(word, "/quit") == 0){
      p->status = S_BAD;
    } else
      strcat(p->outbuf,"Command not found.\n");
  }
}
