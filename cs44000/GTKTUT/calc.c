
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define NBUTTONS     15
#define SPACING      10
#define BUT_ROWS      5
#define BUTS_PER_ROW  3
#define SHORTSTR     64

#define OP_NOP   0
#define OP_EQU   1
#define OP_ADD   2
#define OP_SUB   3
#define OP_MUL   4
#define OP_DIV   5

typedef struct hardwaretype {
  int op;
  long acc;
  long tmp;
  GtkWidget *disp;
} CALCULATOR;

typedef struct buttontype {
  char *lab;
  int val;
  void (*funptr)();
} BUTTON;

void adios(GtkWidget *wid, gpointer p);
void do_number(GtkWidget *wid, gpointer p);
void do_clear(GtkWidget *wid, gpointer p);
void do_op(GtkWidget *wid, gpointer p);

BUTTON blist[NBUTTONS]={
  {"1", 1, do_number},
  {"2", 2, do_number},
  {"3", 3, do_number},
  {"4", 4, do_number},
  {"5", 5, do_number},
  {"6", 6, do_number},
  {"7", 7, do_number},
  {"8", 8, do_number},
  {"9", 9, do_number},
  {"C", 0, do_clear},
  {"0", 0, do_number},
  {"=", OP_EQU, do_op},
  {"-", OP_SUB, do_op},
  {"*", OP_MUL, do_op},
  {"+", OP_ADD, do_op},
};

CALCULATOR  calc;

int main(int argc, char *argv[])
{
  GtkWidget *win, *vbox, *tmp1, *tmp2;
  int i,j,k;

  calc.acc = calc.tmp = 0;
  gtk_init(&argc, &argv);

/* setup main window */
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(win, "destroy", G_CALLBACK(adios), 0);

/* setup box */
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, SPACING);
  gtk_container_add(GTK_CONTAINER(win), vbox);
  
/* setup display */
  tmp1 = gtk_frame_new("");
  gtk_container_add(GTK_CONTAINER(vbox), tmp1);
  calc.disp = gtk_label_new("0");
  gtk_widget_set_size_request(calc.disp, 260,60);
  gtk_container_add(GTK_CONTAINER(tmp1), calc.disp);
  gtk_widget_modify_font(calc.disp,pango_font_description_from_string("Monospace 24"));

  k = 0;  /* button counter */
  for(i=0;i<BUT_ROWS;i++){
    tmp1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, SPACING);
    gtk_container_add(GTK_CONTAINER(vbox), tmp1);
    for(j=0;j<BUTS_PER_ROW;j++){
      tmp2 = gtk_button_new_with_label(blist[k].lab);
      gtk_widget_set_size_request(tmp2, 80,60);
      gtk_container_add(GTK_CONTAINER(tmp1), tmp2);
      g_signal_connect(tmp2, "clicked", G_CALLBACK(blist[k].funptr), &blist[k]);
      gtk_widget_modify_font(tmp2,pango_font_description_from_string("Monospace 20"));
      k++;
    }
  }
  gtk_widget_show_all(win);
  
  gtk_main();
  g_print("finished main loop\n");
}
void display(long n)
{
  char s[SHORTSTR];

  sprintf(s,"%ld", n);
  gtk_label_set_text(GTK_LABEL(calc.disp), s);
}
void adios(GtkWidget *wid, gpointer p)
{
  gtk_main_quit();
  g_print("adios\n");
}
void do_clear(GtkWidget *wid, gpointer p)
{
  calc.acc = calc.tmp = 0;
  display(calc.tmp);
}
void do_op(GtkWidget *wid, gpointer p)
{
  BUTTON *q;

  q = (BUTTON *) p;
  if(q->val == OP_EQU){
    switch(calc.op){
      case OP_ADD: calc.acc += calc.tmp; break;
      case OP_SUB: calc.acc -= calc.tmp; break;
      case OP_MUL: calc.acc *= calc.tmp; break;
    }
  } else {
    calc.op = q->val;
    calc.acc = calc.tmp;
  }
  calc.tmp = 0;
  display(calc.acc);
}
void do_number(GtkWidget *wid, gpointer p)
{
  BUTTON *q;

  q = (BUTTON *) p;
  calc.tmp = 10L * calc.tmp + (long) q->val;
  display(calc.tmp);
}
