#ifndef VISTA_H
#define VISTA_H
#include <gtk/gtk.h>

static void activate(GtkApplication* app) {
  GtkWidget *window;
  GtkWidget *label;

  window = gtk_application_window_new (app);
  label = gtk_label_new("Proyecto 1");
  gtk_container_add (GTK_CONTAINER (window), label);
  gtk_window_set_title(GTK_WINDOW (window), "Proyecto 1: Chat");
  gtk_window_set_default_size(GTK_WINDOW (window), 400, 200);
  gtk_widget_show_all(window);
}

#endif
