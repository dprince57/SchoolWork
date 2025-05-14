
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <math.h>

#include "../vroot.h"

#define X  100  /* X coordinate of window */
#define Y  100  /* Y coordinate of window */
#define B   10  /* border width           */

#define XC  600.0
#define YC  450.0

#define NF 256

#define MAXSIZE      50
#define RANDSIZE     (2+lrand48() % (MAXSIZE-1))
#define RANDSPEED(X) ((1+MAXSIZE-(X)) + lrand48() % 3)
#define RANDCOLOR    ((lrand48() | lrand48()) & 0xffffff)

typedef struct motiontype {
  double x,y;
  double theta;
  double speed;
  int size;
  unsigned int color;
} BODY;

int W,H;
Display *disp;
int scr;
Window win;
GC gc;
Pixmap pm;
XWindowAttributes attr;

BODY follower[NF];

void showbody(BODY *p, int flag);
void initializebody(BODY *p, int flag);
void updatebody(BODY *p, int flag);

int main(int argc, char *argv[])
{
  XEvent ev;
  int i;

  srand48(getpid());
  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  win = DefaultRootWindow(disp);
  XGetWindowAttributes(disp,win,&attr);
  W = attr.width;
  H = attr.height;

  gc   = XCreateGC(disp,win,0,0);
  XMapRaised(disp,win);

  XGetWindowAttributes(disp, win, &attr);
  pm = XCreatePixmap(disp,win,attr.width,attr.height,attr.depth);

  XSetBackground(disp,gc,BlackPixel(disp,scr));
  XSetForeground(disp,gc,BlackPixel(disp,scr));
  XFillRectangle(disp,pm,gc,0,0,attr.width,attr.height);
  XClearWindow(disp,win);
  for(i=0;i<NF;i++)
    initializebody(&follower[i], 0);
  for(;;){
    for(i=0;i<NF;i++)
      showbody(&follower[i], i);
    XClearWindow(disp,win);
    XCopyArea(disp,pm,win,gc,0,0,attr.width,attr.height,0,0);
    XFlush(disp);
    usleep(20000);
  }
}
void initializebody(BODY *p, int flag)
{
  p->x = drand48() * (double) W;
  p->y = drand48() * (double) H;
  p->theta = drand48() * (2.0 * M_PI);
  p->size  = RANDSIZE;
  p->speed = RANDSPEED(p->size);
  p->color = RANDCOLOR;
}
void showbody(BODY *p, int whoami)
{
  int x,y,s;

  s = p->size / 2;
  x = p->x;
  y = p->y;
  XSetForeground(disp,gc,BlackPixel(disp,scr));
  XFillArc(disp, pm, gc, x-s, y-s, p->size, p->size,0,360*64);
  updatebody(p,whoami);
  s = p->size / 2;
  x = p->x;
  y = p->y;
  XSetForeground(disp,gc,p->color);
  XFillArc(disp, pm, gc, x-s, y-s, p->size, p->size,0,360*64);
}
void updatebody(BODY *p, int whoami)
{
  double ax,ay,dx,dy,th,grav;

  ax = W/2 - p->x;
  ay = H - p->y;
  p->theta = (p->theta + atan2(ay,ax))/2.0;
  dx = p->speed * cos(p->theta);
  dy = p->speed * sin(p->theta);
  if(p->x >= W || p->y >= H){ 
    p->x = (lrand48() % W)+1;
    p->y = (lrand48() % H)+1;
  }
  p->x += dx;
  p->y += dy;
  p->speed += (2.0 * drand48() - 1.0);
  if(p->speed < 0)
    p->speed = RANDSPEED(p->size);
  p->speed *= 0.99;
}
