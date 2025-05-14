
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <math.h>

#define T_LEADER   1
#define T_FOLLOWER 2

#define CRITRAD 10.0
#define SOL     25.0    /* speed of light! */
#define G       10.0

#define X      100  /* X coordinate of window */
#define Y      100  /* Y coordinate of window */
#define W     1280  /* width  of window       */
#define H      960  /* height of window       */
#define B       10  /* border width           */

#define NF    2500
#define NL      10

typedef struct motiontype {
  double x,y;
  double vx,vy;
  double ax,ay;
  double mass;
  unsigned int color;
  int size;
  int type;
  int erase;
} BODY;

Display *disp;
int scr;
Window win;
GC gc;
Pixmap pm;
XWindowAttributes attr;

BODY follower[NF];
BODY leader[NL];

void showbody(BODY *p);
void initializebody(BODY *p, int flag);
void updatebody(BODY *p);

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
  for(i=0;i<NL;i++)
    initializebody(&leader[i], 1);
  for(i=0;i<NF;i++)
    initializebody(&follower[i], 0);
  for(;;){
    for(i=0;i<NF;i++)
      showbody(&follower[i]); 
    for(i=0;i<NL;i++)
      showbody(&leader[i]); 
    XCopyArea(disp,pm,win,gc,0,0,attr.width,attr.height,0,0);
    XFlush(disp);
    usleep(16666);
  }
}
void initializebody(BODY *p, int flag)
{
  p->type = flag ? T_LEADER : T_FOLLOWER;
  p->x = drand48() * (double) W;
  p->y = drand48() * (double) H;
  if(p->type == T_LEADER){
    p->vx = drand48() * (double) 2.0 - 1.00;
    p->vy = drand48() * (double) 1.5 - 0.75;
    p->color = (lrand48() | lrand48()) & 0xffffff;
  } else {
    p->vx = drand48() * (double) 8.0 - 4.0;
    p->vy = drand48() * (double) 6.0 - 3.0;
    p->color = lrand48() & 0xffffff;
  }
  p->ax = 0.0;
  p->ay = 0.0;
  p->size = flag ? (15 + lrand48() % 6) : (2 + lrand48() % 9);
  p->mass = (double) p->size/10.0;
  p->erase = 1;
}
void showbody(BODY *p)
{
  int x,y,s;

  s = p->size / 2;
  x = p->x;
  y = p->y;
  XSetForeground(disp,gc,BlackPixel(disp,scr));
  if(p->type == T_FOLLOWER)
    XFillRectangle(disp, pm, gc, x-s, y-s, p->size, p->size);
  else
    XFillArc(disp,pm,gc,x-s,y-s,p->size,p->size,0,64*360);

  updatebody(p);

  s = p->size / 2;
  x = p->x;
  y = p->y;
  XSetForeground(disp,gc,p->color);
  if(p->type == T_FOLLOWER)
    XFillRectangle(disp, pm, gc, x-s, y-s, p->size, p->size);
  else
    XFillArc(disp,pm,gc,x-s,y-s,p->size,p->size,0,64*360);
}
int findclosestleader(double x, double y)
{
  int i,who;
  double dx,dy,d,mind;

  mind = 1e9;
  who = -1;
  for(i=0;i<NL;i++){
    dx = x - leader[i].x;
    dy = y - leader[i].y;
    d = dx*dx + dy*dy;
    if(d < mind){
      mind = d;
      who = i;
    }
  }
  if(who < 0) who = random() % NL;
  return who;
}
void updatebody(BODY *p)
{
  int k;
  double dx,dy,ds;

  p->x += p->vx;
  p->y += p->vy;
  if(p->x > W) p->x -= W;
  else if(p->x < 0) p->x += W;
  if(p->y > H) p->y -= H;
  else if(p->y < 0) p->y += H;
  if(p->type == T_LEADER)
    return;

  k = findclosestleader(p->x,p->y);
  dx = leader[k].x - p->x;
  dy = leader[k].y - p->y;
  ds = dx*dx + dy*dy;
  if(ds < CRITRAD){
    initializebody(p,0);
    return;
  } else {
    p->vx += (G * dx * p->mass * leader[k].mass)/ds;
    p->vy += (G * dy * p->mass * leader[k].mass)/ds;
  }
  ds = p->vx * p->vx + p->vy * p->vy;
  if(ds > SOL){
    p->vx *= SOL/ds;
    p->vy *= SOL/ds;
  }
}
