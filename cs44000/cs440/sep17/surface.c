
#include <stdio.h>
#include <math.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define WID   400
#define HGT   566
#define RAD   100

typedef struct point_type {
  int x,y,r;
  int dr;
} POINT;

POINT pt;

cairo_surface_t *surf = 0;
int flag = 0;

void init_point();
void do_click(GtkWidget *wid, GdkEventButton *ev, gpointer p);
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p);
gboolean do_config(GtkWidget *wid, GdkEventConfigure *ev, gpointer p);

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
  g_signal_connect(dar,"configure-event",G_CALLBACK(do_config), 0);
  g_signal_connect(dar,"draw",G_CALLBACK(do_draw), 0);

  gtk_widget_show_all(win);

  gtk_main();
}
void init_point()
{
  pt.x = WID/2;
  pt.y = HGT/2;
  pt.r = RAD;
  pt.dr = -1;
}
void do_click(GtkWidget *wid, GdkEventButton *ev, gpointer p)
{
  if(ev->button == GDK_BUTTON_PRIMARY){
    pt.x = ev->x;
    pt.y = ev->y;
    gtk_widget_queue_draw(wid);
  }
}
void draw_stuff(cairo_t *gc)
{
  cairo_set_line_width(gc, 3.0);
  cairo_arc(gc, pt.x, pt.y, pt.r, 0, 2*M_PI);
  cairo_set_source_rgb(gc, 0.0, 0.0, 0.0);
  cairo_stroke(gc);
}
gboolean do_draw(GtkWidget *wid, cairo_t *gc, gpointer p)
{
  cairo_set_source_surface(gc, surf, 0, 0);
  cairo_paint(gc);
  draw_stuff(gc);
  return FALSE;
}
gboolean do_config(GtkWidget *wid, GdkEventConfigure *ev, gpointer p)
{
  cairo_t *gc;

  g_print("Configure.\n");
  surf = cairo_image_surface_create_from_png("bob.png");
/*
  surf = gdk_window_create_similar_surface(gtk_widget_get_window(wid),
              CAIRO_CONTENT_COLOR, WID, HGT);
*/
  return TRUE;
}
