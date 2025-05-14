
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define X 100  /* X coordinate of window */
#define Y 100  /* Y coordinate of window */
#define W 800  /* width  of window       */
#define H 600  /* height of window       */
#define B 100  /* border width           */

Display *disp;
int scr;
Window win;
GC gc;

int main(int argc, char *argv[])
{
  XEvent ev;
  int toggle;
  int x,y;

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
        toggle = 0;
        break;
      case ButtonPress:
        switch(ev.xbutton.button){
          case 1:
            if(!toggle){
              x = ev.xbutton.x;
              y = ev.xbutton.y;
            } else {
              XDrawLine(disp,win,gc, x, y, ev.xbutton.x, ev.xbutton.y);
            }
            toggle = 1 - toggle;
            break;
          case 2:
          case 3:
            exit(0);
        }
    }
  }
}
