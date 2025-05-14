
#include <stdio.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <sys/time.h>

#define WID  1200
#define HGT   480
#define RAD    40

typedef struct point_type {
  int x,y,t;
  int ddf;    /* drag drop flag */
} POINT;

POINT pt;

void init_point();
void do_press(GtkWidget *wid, GdkEventButton *ev, gpointer p);
void do_release(GtkWidget *wid, GdkEventButton *ev, gpointer p);
void do_motion(GtkWidget *wid, GdkEventButton *ev, gpointer p);
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

  gtk_widget_show_all(win);

  gtk_main();
}
void init_point()
{
  pt.x = WID/2;
  pt.y = HGT/2;
  pt.t = 0;
  pt.ddf = 0;
}
void do_press(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  pt.ddf = 1;
  pt.x = (int) ev->x;
  pt.y = (int) ev->y;
  gtk_widget_queue_draw(wid);
}
void do_release(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  pt.ddf = 0;
  printf("release:  %lf  %lf\n", ev->x, ev->y);
}
void do_motion(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  static long t1 = 0,t2 = 0, min = 1L << 40;
  long dt;
  static gdouble xlast,ylast;
  gdouble ds,dx,dy,v;
  struct timeval tv;

  if(pt.ddf){
    pt.x = (int) ev->x;
    pt.y = (int) ev->y;
    gtk_widget_queue_draw(wid);
  }
  dx = (ev->x - xlast);
  dy = (ev->y - ylast);
  xlast = ev->x;
  ylast = ev->y;
  ds = sqrt(dx*dx + dy*dy);
  gettimeofday(&tv, 0);
  t1 = t2;
  t2 = tv.tv_sec * 1000 + tv.tv_usec/1000;
  dt = t2 - t1;
  v = ds/(gdouble) dt;
  if(dt < min)
    min = dt;
  printf("elapsed time:%ld %ld %lf %lf\n", dt, min, ds, v);
}
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p)
{
  double r,g,b;

  cairo_set_source_rgb(gc, 0.9, 0.8, 0.5);
  cairo_paint(gc);

  cairo_set_line_width(gc, 3.0);

  cairo_arc(gc, pt.x, pt.y, RAD, 0, 2*M_PI);

  r = 0.5 + 0.5*sin((double)pt.t * 2.0*M_PI/180.0);
  g = 0.5 + 0.5*sin(1.1 + (double)pt.t * 1.0*M_PI/180.0);
  b = 0.5 + 0.5*sin(2.3 + (double)pt.t * 3.0*M_PI/180.0);
  cairo_set_source_rgb(gc,r,g,b);
  cairo_fill_preserve(gc);
  cairo_set_source_rgb(gc, 0.0, 0.0, 0.0);
  cairo_stroke(gc);
  return FALSE;
}
