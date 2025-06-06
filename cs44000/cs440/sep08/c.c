

#include <gtk/gtk.h>

void adios(GtkWidget *wid, gpointer p);
void au_revoir(GtkWidget *wid, gpointer p);

int main(int argc, char *argv[])
{
  GtkWidget *win, *but;

  gtk_init(&argc, &argv);

/* setup main window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(win, "destroy", G_CALLBACK(adios), 0);

/* setup quit button */
  but = gtk_button_new_with_label("Quit");
  g_signal_connect(but, "clicked", G_CALLBACK(au_revoir), 0);
  gtk_container_add(GTK_CONTAINER(win), but);

  gtk_widget_show(win);
  gtk_widget_show(but);

  gtk_main();
  g_print("finished main loop\n");
}
void adios(GtkWidget *wid, gpointer p)
{
  gtk_main_quit();
  g_print("adios\n");
}
void au_revoir(GtkWidget *wid, gpointer p)
{
  gtk_main_quit();
  g_print("au_revoir\n");
}
