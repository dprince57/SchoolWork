#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define X 100  /* X coordinate of window */
#define Y 100  /* Y coordinate of window */
#define B 100  /* border width           */
#define NCOLORS 3

Display *disp;
int scr;
Window win;
GC gc;
int H;
int W;

char *colors[NCOLORS]={"red","green","blue"};
XColor xcolors[NCOLORS];
XColor xc,sc;
int c;

int main(int argc, char *argv[])
{
  XEvent ev;


  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  H = DisplayHeight(disp,scr);
  W = DisplayWidth(disp,scr);
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
  gc   = XCreateGC(disp,win,0,0);
  XSetForeground(disp,gc,WhitePixel(disp,scr));
  XSetBackground(disp,gc,BlackPixel(disp,scr));
  XSelectInput(disp,win, ButtonPressMask | ExposureMask);
  XMapRaised(disp,win);

  for(c=0;c<NCOLORS;c++){
    XAllocNamedColor(disp,DefaultColormapOfScreen(DefaultScreenOfDisplay(disp)),colors[c],&sc,&xc);
    xcolors[c]=sc;
  }

  for(;;)
  {
     XSetForeground(disp,gc,xcolors[random()%NCOLORS].pixel);
     XFillRectangle(disp,win,gc,random()%W,random()%H,50,40);
     XFillArc(disp,win,gc,random()%W,random()%H,50,50,0,360*64);
     if(random()%1000<1)
     {
       XClearWindow(disp,win);
     }
     XFlush(disp);
     usleep(100000);
  }
}

