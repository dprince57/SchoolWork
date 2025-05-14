
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

int main(int argc, char *argv[])
{
  XEvent ev;

  disp = XOpenDisplay(NULL);
  scr  = DefaultScreen(disp);
  win  = XCreateSimpleWindow(disp,DefaultRootWindow(disp),X,Y,W,H,B,0,0);
  XSelectInput(disp,win, ButtonPressMask | ExposureMask);
  XMapRaised(disp,win);

  for(;;){
    XNextEvent(disp,&ev);
    switch(ev.type){
      case Expose:
        printf("exposed\n");
        break;
      case ButtonPress:
        switch(ev.xbutton.button){
          case 1:
            printf("Button 1 pressed\n");
            break;
          case 2:
          case 3:
            exit(0);
        }
    }
  }
}
