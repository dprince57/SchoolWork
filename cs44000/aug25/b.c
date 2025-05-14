#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>

#define X 100  /* X coordinate of window */
#define Y 100  /* Y coordinate of window */
#define W 800  /* width  of window       */
#define H 600  /* height of window       */
#define B 100  /* border width           */

Display *disp;
int scr;
Window win;
GC gc;

int draw_c_curve(int dx,int dy,int len);


typedef struct points
{
  int x1;
  int x2;
  int y1;
  int y2;
} PList;

int curve(int x, int y, int len);

int main(int argc, char *argv[])
{
  XEvent ev;
  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
  gc   = XCreateGC(disp,win,0,0);
  XSetForeground(disp,gc,WhitePixel(disp,scr));
  XSetBackground(disp,gc,BlackPixel(disp,scr));
  XSelectInput(disp,win, ButtonPressMask | ExposureMask);
  XMapRaised(disp,win);

  for(;;){
    XNextEvent(disp,&ev);
    switch(ev.type){
      case Expose:
        break;
      case ButtonPress:
        switch(ev.xbutton.button){
          case 1:
            curve(W/2,H/2,100);
            break;
          case 2:
          case 3:
            exit(0);
        }
    }
  }
}
int draw_c_curve(int x,double y,int len,int max){
  XDrawLine(disp,win,gc,x,y,x+len,y+len); // this line may or may not be known to summon the wumpus
}
