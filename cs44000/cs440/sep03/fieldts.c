
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <math.h>

#define X  100  /* X coordinate of window */
#define Y  100  /* Y coordinate of window */
#define W 1200  /* width  of window       */
#define H  900  /* height of window       */
#define B   10  /* border width           */

#define XC  600.0
#define YC  450.0

#define NF 1024

#define EPSILON  2.0

#define RANDVX (16.0 * drand48() - 8.0)
#define RANDVY (12.0 * drand48() - 6.0)

#define MAXSIZE       12
#define RANDSIZE     (2+lrand48() % (MAXSIZE-1))
#define RANDCOLOR    ((lrand48() | lrand48()) & 0xffffff)

typedef struct motiontype {
  double x,y;
  double vx,vy;
  int size;
  unsigned int color;
} BODY;

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
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
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
    XCopyArea(disp,pm,win,gc,0,0,attr.width,attr.height,0,0);
    XFlush(disp);
    usleep(20000);
  }
}
void initializebody(BODY *p, int flag)
{
  p->x = drand48() * (double) W;
  p->y = drand48() * (double) H;
  p->vx = RANDVX;
  p->vy = RANDVY;
  p->size  = RANDSIZE;
  p->color = RANDCOLOR;
}
void showbody(BODY *p, int whoami)
{
  int x,y,s;

  s = p->size / 2;
  x = p->x;
  y = p->y;
  XSetForeground(disp,gc,BlackPixel(disp,scr));
  XFillRectangle(disp, pm, gc, x-s, y-s, p->size, p->size);
  updatebody(p,whoami);
  s = p->size / 2;
  x = p->x;
  y = p->y;
  XSetForeground(disp,gc,p->color);
  XFillRectangle(disp, pm, gc, x-s, y-s, p->size, p->size);
}
int findclosest(double x, double y, int whoami)
{
  int i,who;
  double dx,dy,d,mind;

  mind = 1e9;
  who = -1;
  for(i=0;i<NF;i++){
    if(i == whoami)
      continue;
    dx = x - follower[i].x;
    dy = y - follower[i].y;
    if(dx > W/2) dx = W - dx;
    if(dy > H/2) dy = H - dy;
    d = dx*dx + dy*dy;
    if(d < mind){
      mind = d;
      who = i;
    }
  }
  if(who < 0) who = lrand48() % NF;
  return who;
}
void updatebody(BODY *p, int whoami)
{
  int k;
  double ax,ay,dx,dy,th,grav;

  k = findclosest(p->x,p->y,whoami);
  ax = follower[k].x - p->x;
  ay = follower[k].y - p->y;
  if(ax > W/2) ax = W - ax;
  if(ay > H/2) ay = H - ay;
  p->vx = (9.0 * p->vx + ax)/10.0;
  p->vy = (9.0 * p->vy + ay)/10.0;
  p->x += p->vx;
  p->y += p->vy;
  if(p->x > W) p->x -= W;
  else if(p->x < 0) p->x += W;
  if(p->y > H) p->y -= H;
  else if(p->y < 0) p->y += H;
  if(p->vx * p->vx + p->vy * p->vy < EPSILON){
    p->vx = RANDVX;
    p->vy = RANDVY;
  }
}
