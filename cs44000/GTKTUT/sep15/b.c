
#include <stdio.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define WID   600
#define HGT   450
#define RAD   100

typedef struct point_type {
  int x,y,t;
} POINT;

POINT pt;

void init_point();
void do_click(GtkWidget *wid, GdkEvent *ev, gpointer p);
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p);
gboolean do_timer(gpointer p);

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
  gtk_widget_add_events(dar, GDK_BUTTON_PRESS_MASK);
  g_signal_connect(dar,"button-press-event",G_CALLBACK(do_click), 0);
  g_signal_connect(dar,"draw",G_CALLBACK(do_draw), 0);

  g_timeout_add(50, (GSourceFunc) do_timer, (gpointer) dar);
  gtk_widget_show_all(win);

  gtk_main();
}
void init_point()
{
  pt.x = WID/2;
  pt.y = HGT/2;
  pt.t = 0;
}
void do_click(GtkWidget *wid, GdkEvent *ev, gpointer p)
{
  pt.x = ev->button.x;
  pt.y = ev->button.y;
  gtk_widget_queue_draw(wid);
}
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p)
{
  double r,g,b;

  fprintf(stderr,"draw: %d %d\n", pt.x, pt.y);
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
gboolean do_timer(gpointer p)
{
  GtkWidget *wid;

  wid = (GtkWidget *) p;
  pt.t++;
  gtk_widget_queue_draw(wid);
  return TRUE;
}
