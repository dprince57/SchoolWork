
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

#define K  1024

int fun(void *nothing, int argc, char *argv[], char **fields);

int main(int argc, char *argv[])
{
  sqlite3 *db;
  char *mess;
  char query[K];
  int i, rv;     /* rv = return value */
  
  rv = sqlite3_open(argv[1], &db);
  if(rv){
    printf("cannot access %s\n", argv[1]);
    exit(0);
  }
  sprintf(query,"update master set middle='Sally' where first='Diana' and last='Wong'");
  mess = 0;
  rv = sqlite3_exec(db, query, fun, 0, &mess); 
  if(rv){
    if(mess)
      fprintf(stderr,"%s\n", mess);
    else
      fprintf(stderr,"unknown error\n");
    exit(0);
  }
  sqlite3_close(db);
}
int fun(void *nothing, int argc, char *argv[], char *fields[])
{
  int i;
  char b[K];

  *b = 0;
  for(i = 0 ; i < argc ; i++){
    if(i) strcat(b," ");
    strcat(b,argv[i]);
  }
  puts(b);
  return 0;
}

