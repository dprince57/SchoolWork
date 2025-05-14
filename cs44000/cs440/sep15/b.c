gboolean do_timer(gpointer p);

  g_timeout_add(50, (GSourceFunc) do_timer, (gpointer) dar);

gboolean do_timer(gpointer p)
{
  GtkWidget *wid;

  wid = (GtkWidget *) p;
  pt.t++;
  gtk_widget_queue_draw(wid);
  return TRUE;
}
