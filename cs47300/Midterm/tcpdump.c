
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

typedef
  unsigned char
uchar;

#define N    2048
#define EHL    14
#define IPHL   20

int read_ether_head(int fd, uchar b[]);
int read_ip_head(int fd, uchar b[]);
void print_ether_head(uchar b[]);

int main(int argc, char *argv[])
{
  int fd;
  uchar ehead[N],iphead[N],ipbody[N];
  int ippacketsize;

  fd = open(argv[1], O_RDONLY);
  for(;;){
    if(!read_ether_head(fd, ehead))
      break;
    print_ether_head(ehead);
    ippacketsize = read_ip_head(fd,iphead);
    printf("ip packet length = %d\n", ippacketsize);
/*
    print_ip_head(iphead);
    read_ip_body(fd, ipbody, ippacketsize);
*/
  }
}
int read_ether_head(int fd, uchar b[])
{
  if(read(fd, b, EHL) != EHL)
    return 0;
  return 1;
}
char *ethertostring(char s[], uchar b[])
{
  int i;

  for(i=0;i<6;i++)
    sprintf(s+3*i,"%c%02x", i ? ':' : ' ', b[i]);
}
void print_ether_head(uchar b[])
{
  char s[N];

  ethertostring(s,b);
  printf("%-28s: %s\n", "Ethernet Destination Address", s);
  ethertostring(s,b+6);
  printf("%-28s: %s\n", "Ethernet Source Address", s);
}
int read_ip_head(int fd, uchar b[])
{
  int hsize;
  short int *p;

  if(read(fd, b, IPHL) != IPHL)
    return 0;
  hsize = b[0] & 0xf;
  printf("%d\n", hsize);
  if(hsize > 5)
    read(fd, b+IPHL, 4*(hsize - 5));
/*
  p = (short int *) b+2;
  return ntohs(*p);
*/
  printf("%d %d\n", b[2], b[3]);
  return ((b[2] << 8) | b[3]);
}
