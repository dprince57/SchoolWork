
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <sys/time.h>

#define WID  1200
#define HGT   900
#define RAD    20

#define FRICTION 0.98

typedef struct point_type {
  int x,y,t;
  int ddf;    /* drag drop flag */
  int moving;
  gdouble vx,vy;
  gdouble dx,dy;
  gdouble xlast,ylast;
  long tlast;
} POINT;

POINT pt;

void init_point();
void do_press(GtkWidget *wid, GdkEventButton *ev, gpointer p);
void do_release(GtkWidget *wid, GdkEventButton *ev, gpointer p);
void do_motion(GtkWidget *wid, GdkEventButton *ev, gpointer p);
gboolean do_timer(gpointer p);
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p);

int main(int argc, char *argv[])
{
  GtkWidget *win, *dar;

  init_point();

  gtk_init(&argc, &argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win), "The Three Musketeers");
  gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
  g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), 0);

  dar = gtk_drawing_area_new();
  gtk_widget_set_size_request(dar,WID,HGT);
  gtk_container_add(GTK_CONTAINER(win), dar);
  gtk_widget_add_events(dar,
    GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK);
  g_signal_connect(dar,"button-press-event",G_CALLBACK(do_press), 0);
  g_signal_connect(dar,"button-release-event",G_CALLBACK(do_release), 0);
  g_signal_connect(dar,"motion-notify-event",G_CALLBACK(do_motion), 0);
  g_signal_connect(dar,"draw",G_CALLBACK(do_draw), 0);
  gtk_widget_set_double_buffered(dar, TRUE);

  gtk_widget_show_all(win);
  g_timeout_add(50, (GSourceFunc) do_timer, (gpointer) dar);

  gtk_main();
}
void init_point()
{
  memset(&pt,0,sizeof(POINT));
  pt.x = WID/2;
  pt.y = HGT/2;
}
void do_press(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  pt.dx = 0; pt.dy = 0;
  pt.vx = 0; pt.vy = 0;
  pt.moving = 0;
  pt.ddf = 1;
  pt.x = (int) ev->x;
  pt.y = (int) ev->y;
  gtk_widget_queue_draw(wid);
}
void do_release(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  pt.ddf = 0;
  pt.moving = 1;
}
long get_dt()
{
  struct timeval tv;
  long t,dt;

  gettimeofday(&tv, 0);
  t = tv.tv_sec * 1000 + tv.tv_usec/1000;
  dt = t - pt.tlast;
  pt.tlast = t;
  return dt;
}
void do_motion(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  long dt;

  if(pt.ddf){
    pt.xlast = pt.x;
    pt.ylast = pt.y;
    pt.x = (int) ev->x;
    pt.y = (int) ev->y;
    gtk_widget_queue_draw(wid);
    pt.dx = ((gdouble) ev->x - pt.xlast);
    pt.dy = ((gdouble) ev->y - pt.ylast);
    dt = 1 + get_dt();
    pt.vx = (9.0*pt.vx + pt.dx/(gdouble) dt)/10.0;
    pt.vy = (9.0*pt.vy + pt.dy/(gdouble) dt)/10.0;
    printf("%lf   %lf\n", pt.vx, pt.vy);
  }
}
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p)
{
  double r,g,b;

  cairo_set_source_rgb(gc, 0.9, 0.8, 0.5);
  cairo_paint(gc);

  cairo_set_line_width(gc, 4.0);
  cairo_arc(gc, pt.x, pt.y, RAD, 0, 2*M_PI);
  cairo_set_source_rgb(gc, 0, 0, 0.75);
  cairo_fill_preserve(gc);
  cairo_set_source_rgb(gc, 0.0, 0.0, 0.0);
  cairo_stroke(gc);
  return FALSE;
}
gboolean do_timer(gpointer p)
{
  GtkWidget *wid;
  long dt;

  if(pt.moving){
    wid = (GtkWidget *) p;
    dt = get_dt();
    pt.x += dt*pt.vx;
    pt.y += dt*pt.vy;
    pt.vx *= FRICTION;
    pt.vy *= FRICTION;
    if(pt.y <= RAD && pt.vy <= 0){
      pt.y = fabs(pt.y);
      pt.vy = fabs(pt.vy);
    }
    if(pt.y >= HGT-RAD && pt.vy >= 0){
      pt.y = HGT+HGT-fabs(pt.y);
      pt.vy = -fabs(pt.vy);
    }
    if(pt.x <= RAD && pt.vx <= 0){
      pt.x = fabs(pt.x);
      pt.vx = fabs(pt.vx);
    }
    if(pt.x >= WID-RAD && pt.vx >= 0){
      pt.x = WID+WID-fabs(pt.x);
      pt.vx = -fabs(pt.vx);
    }
    gtk_widget_queue_draw(wid);
  }
  return TRUE;
}

