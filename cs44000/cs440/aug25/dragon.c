
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>

#define X  100  /* X coordinate of window */
#define Y  100  /* Y coordinate of window */
#define W 1200  /* width  of window       */
#define H  900  /* height of window       */
#define B   10  /* border width           */

#define SQRT2   1.41421

typedef struct turtletype {
  double x,y;
  double th;
} TURTLE;

Display *disp;
int scr;
Window win;
GC gc;

void recurse(int depth, int flag, double len, TURTLE *p);

int main(int argc, char *argv[])
{
  XEvent ev;
  TURTLE tom;
  int maxdepth;

  srandom(getpid());
  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
  gc   = XCreateGC(disp,win,0,0);
  XSetForeground(disp,gc,WhitePixel(disp,scr));
  XSetBackground(disp,gc,BlackPixel(disp,scr));
  XSelectInput(disp,win, ButtonPressMask | ExposureMask);
  XMapRaised(disp,win);

  XSetLineAttributes(disp,gc, 4, 0, 0, 0);
  for(;;){
    XNextEvent(disp,&ev);
    switch(ev.type){
      case Expose:
        break;
      case ButtonPress:
        switch(ev.xbutton.button){
          case 1:
            XClearWindow(disp,win);
          case 2:
            tom.th = 0;
            tom.x = (double) W/4;
            tom.y = (double) H/2;
            recurse(maxdepth, 0, (double) W/2, &tom);
            maxdepth++;
            break;
          case 3:
            exit(0);
        }
    }
  }
}
int randcolor(int x, int y)
{
  int r,g,b;

  r = (255*x)/W;
  b = (255*y)/H;
  return (r << 16) | b;
} 
void recurse(int depth, int flag, double len, TURTLE *p)
{
  double dx,dy;

  if(depth <= 0){
    dx = len * cos(p->th); 
    dy = len * sin(p->th);
    XSetForeground(disp, gc, randcolor(p->x,p->y));
    XDrawLine(disp, win, gc, p->x, p->y, dx+p->x, dy+p->y);
    p->x += dx;
    p->y += dy;
  } else {
    len /= SQRT2;
    if(flag){
      p->th += M_PI/4.0;
      recurse(depth-1,flag,len,p);
      p->th -= M_PI/2.0;
      recurse(depth-1,!flag,len,p);
      p->th += M_PI/4.0;
    } else {
      p->th -= M_PI/4.0;
      recurse(depth-1,!flag,len,p);
      p->th += M_PI/2.0;
      recurse(depth-1,flag,len,p);
      p->th -= M_PI/4.0;
    }
  }
}
