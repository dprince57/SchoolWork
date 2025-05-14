
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define DX  8
#define DY  6

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
  int i;
  int nlpc;
  int x1,y1,x2,y2,dx,dy;

  nlpc = (argc > 1) ? atoi(argv[1]) : 1;
  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
  gc   = XCreateGC(disp,win,0,0);
  XSetForeground(disp,gc,WhitePixel(disp,scr));
  XSetBackground(disp,gc,BlackPixel(disp,scr));
  XSelectInput(disp,win, ButtonPressMask | ExposureMask);
  XMapRaised(disp,win);

  srand(getpid());
  for(;;){
    XNextEvent(disp,&ev);
    switch(ev.type){
      case Expose:
        x1 = W/2;
        y1 = H/2;
        break;
      case ButtonPress:
        switch(ev.xbutton.button){
          case 1:
            for(i=0;i<nlpc;i++){
              dx = rand() % (2*DX + 1) - DX;
              dy = rand() % (2*DY + 1) - DY;
              x2 = x1 + dx ;
              y2 = y1 + dy;
              XDrawLine(disp,win,gc, x1,y1, x2,y2);
              x1 = x2;
              y1 = y2;
            }
            break;
          case 2:
          case 3:
            exit(0);
        }
    }
  }
}
