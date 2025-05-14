
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>

#define X  100  /* X coordinate of window */
#define Y  100  /* Y coordinate of window */
#define W 1200  /* width  of window       */
#define H  900  /* height of window       */
#define B   10  /* border width           */

#define RANDSPEED (5 + lrand48() % 6)
#define RANDSIZE (8 + lrand48() % 13)

typedef struct motiontype {
  double x,y;
  double speed,theta;
  int size;
} BODY;

Display *disp;
int scr;
Window win;
GC gc;

void showbody(BODY *p);
void initializebody(BODY *p);
void updatebody(BODY *p);

int main(int argc, char *argv[])
{
  XEvent ev;
  BODY bob,sally;
  int maxdepth;

  srand48(getpid());
  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
  gc   = XCreateGC(disp,win,0,0);
  XSetForeground(disp,gc,WhitePixel(disp,scr));
  XSetBackground(disp,gc,BlackPixel(disp,scr));
  XMapRaised(disp,win);

  initializebody(&bob); 
  initializebody(&sally); 
  for(;;){
    XClearWindow(disp,win);
    showbody(&bob);
    showbody(&sally);
    XFlush(disp);
    updatebody(&bob);
    updatebody(&sally);
    usleep(16666);
  }
}
void initializebody(BODY *p)
{
  p->x = drand48() * (double) W;
  p->y = drand48() * (double) H;
  p->theta = drand48() * (2.0 * M_PI);
  p->speed = RANDSPEED;
  p->size = RANDSIZE;
}
void showbody(BODY *p)
{
  int x,y,s;

  s = p->size / 2;
  x = p->x;
  y = p->y;
  XFillRectangle(disp, win, gc, x-s, y-s, p->size, p->size);
}
void updatebody(BODY *p)
{
  double dx,dy;

  dx = p->speed * cos(p->theta);
  dy = p->speed * sin(p->theta);
  p->x += dx;
  p->y += dy;
  if(p->x > W) p->theta = M_PI - p->theta;
  else if(p->x < 0) p->theta = M_PI - p->theta;
  if(p->y > H) p->theta = - p->theta;
  else if(p->y < 0) p->theta = - p->theta;
  p->speed += (drand48() - 0.5);
  if(p->speed < 0)
    p->speed = RANDSPEED;
  p->theta += (drand48() - 0.5);
  p->speed *= 0.99999;
}
