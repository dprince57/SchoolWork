
#include <gtk/gtk.h>

void adios(GtkWidget *wid, gpointer p);
void au_revoir(GtkWidget *wid, gpointer p);
void action(GtkWidget *wid, gpointer p);

#define SPACING 16

int main(int argc, char *argv[])
{
  GtkWidget *win, *hbox, *lab, *qbut, *abut;

  gtk_init(&argc, &argv);

/* setup main window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(win, "destroy", G_CALLBACK(adios), 0);

/* setup box */
  hbox = gtk_hbox_new(FALSE, SPACING);
  gtk_container_add(GTK_CONTAINER(win), hbox);
  
/* setup quit button */
  qbut = gtk_button_new_with_label("Quit");
  g_signal_connect(qbut, "clicked", G_CALLBACK(au_revoir), 0);
  gtk_container_add(GTK_CONTAINER(hbox), qbut);
  
/* setup label */
  lab = gtk_label_new("Hello");
  gtk_container_add(GTK_CONTAINER(hbox), lab);
  
/* setup action button */
  abut = gtk_button_new_with_label("Press");
  g_signal_connect(abut, "clicked", G_CALLBACK(action), lab);
  gtk_container_add(GTK_CONTAINER(hbox), abut);

  gtk_widget_show(win);
  gtk_widget_show(hbox);
  gtk_widget_show(qbut);
  gtk_widget_show(lab);
  gtk_widget_show(abut);

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
void action(GtkWidget *wid, gpointer p)
{
  gtk_label_set_text(GTK_LABEL(p),"Goodbye");
}

