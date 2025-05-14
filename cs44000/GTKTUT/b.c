
#include <gtk/gtk.h>

void adios(GtkWidget *wid, gpointer p);

int main(int argc, char *argv[])
{
  GtkWidget *win;

  gtk_init(&argc, &argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(win, "destroy", G_CALLBACK(adios), 0);
  gtk_widget_show(win);
  gtk_main();
  g_print("finished main loop\n");
}
void adios(GtkWidget *wid, gpointer p)
{
  gtk_main_quit();
  g_print("adios\n");
}
