
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define X 100  /* X coordinate of window */
#define Y 100  /* Y coordinate of window */
#define W 1440 /* width  of window       */
#define H 960  /* height of window       */
#define B 100  /* border width           */

Display *disp;
int scr;
Window win;
GC gc;

int main(int argc, char *argv[])
{
  XEvent ev;
  int i;

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
            for(i=0;i<1000000;i++){
              XSetForeground(disp,gc,random() & 0xffffff);
              XSetLineAttributes(disp,gc,
                1+random() % 7,
                0,0,0);
              XDrawArc(disp, win, gc,
                random() % W,
                random() % H,
                random() % (W/2),
                random() % (H/2),
                0,
                64*360);
            }
            break;
          case 2:
          case 3:
            exit(0);
        }
    }
  }
}
