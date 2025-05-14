
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
        XDrawLine(disp,win,gc,10,10,W-10,H-10);
        fprintf(stderr,"Exposed.\n");
        break;
      case ButtonPress:
        switch(ev.xbutton.button){
          case 1:
            XDrawLine(disp,win,gc,W-10,10,10,H-10);
            XDrawPoint(disp,win,gc,W/2,20);
            printf("%d,%d\n", ev.xbutton.x, ev.xbutton.y);
            break;
          case 2:
          case 3:
            exit(0);
        }
    }
  }
}
