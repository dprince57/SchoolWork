/* EXOO'S COPY, MODIFY AND DO WHATEVER TO INTEGRATE TO SERVER */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _XOPEN_SOURCE

#include <crypt.h>

#define K         1024
#define PASSWD "passwd"

int checkpass(char cipher[], char *who, char *plain);
int makepass(char *who, char *plain);

int main(int argc, char *argv[])
{
  char b[K];
  int rv;

  rv = checkpass(b, argv[1], argv[2]);
  switch(rv){
    case  1: printf("good\n"); break;
    case  0: printf("bad\n"); break;
    case -1: makepass(argv[1],argv[2]); break;
  }
}
void adios(char *mess)
{
  fprintf(stderr,"mess = %s\n", mess);
  exit(0);
}
int checkpass(char cipher[], char *who, char *plain)
{
  FILE *fd;
  char sugar[5];
  char salt[K];
  char a[K];  /* recreated encrypted password */
  char b[K];  /* password file line */
  char *pfiletoken[2],*dollartoken[3],*r;
  int i;

  fd = fopen(PASSWD,"r");
  if(!fd)
    adios("fopen");
  while(fgets(b,K,fd)){
    pfiletoken[0] = strtok(b,":\n");
    if(strcmp(pfiletoken[0],who) == 0){
      pfiletoken[1] = strtok(0, ":\n");
      dollartoken[0] = strtok(pfiletoken[1]+1,"$");
      dollartoken[1] = strtok(0, "$");
      dollartoken[2] = strtok(0, "$");
      sprintf(salt,"$%s$%s$", dollartoken[0], dollartoken[1]);
      r = crypt(plain,salt);
      strcpy(a,r);
      r = strrchr(a,'$') + 1;
      fclose(fd);
      if(strcmp(dollartoken[2], r) ==0){
        return 1;
      } else {
        return 0;
      }
    }
  }
  return -1;
} 
int makepass(char *who, char *plain)
{
  char sugar[5];
  char salt[K];
  char cipher[K];
  char *p;
  int i;
  FILE *fd;

  srandom(getpid() ^ time(0));
  for(i=0;i<4;i++)
    sugar[i] = 'a' + random() % 26;
  sugar[4] = 0;
  sprintf(salt,"$5$%s$", sugar);
  p = crypt(plain,salt);
  strcpy(cipher,p);
  fd = fopen(PASSWD,"a");
  if(!fd) adios("fopen");
  fprintf(fd,"%s:%s\n",who,cipher);
  fclose(fd);
  return 1;
} 
