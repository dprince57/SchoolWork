
#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
  GtkWidget *win;

  gtk_init(&argc, &argv);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_show(win);
  gtk_main();
}
