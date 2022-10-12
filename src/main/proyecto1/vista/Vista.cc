#include "inc/Vista.h"
#include "inc/Vista_Cliente.h"

Vista* Vista::vista = nullptr;

G_MODULE_EXPORT void button_clicked_servidor() {
printf("It works.\n");
}

G_MODULE_EXPORT void button_clicked_cliente() {
  Vista_Cliente::get_instance()->welcome_window();
  gtk_widget_hide(Vista::get_instance()->get_window());
}

G_MODULE_EXPORT void exit_app() {
  // gtk_window_close(GTK_WINDOW(Vista::get_instance()->get_window()));
  gtk_main_quit();
  exit(1);
}

Vista::Vista(int argc, char ** argv) {
  gtk_init(&argc, &argv);
  g_object_set(gtk_settings_get_default (), "gtk-application-prefer-dark-theme", FALSE, NULL);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "../src/media/Main.glade", &err);

  if (err != NULL) {
    fprintf (stderr, "No fue posible leer el archivo: %s\n", err->message);
    g_error_free(err);
    exit(1);
  }
  
  window = GTK_WIDGET(gtk_builder_get_object(builder, "Welcome"));

  if (window == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"Welcome\".\n");
    exit(1);
  }
  label = GTK_LABEL(gtk_builder_get_object(builder, "Chat"));

  gtk_builder_add_callback_symbol(builder,"button_clicked_servidor",G_CALLBACK(button_clicked_servidor));
  gtk_builder_add_callback_symbol(builder,"button_clicked_cliente",G_CALLBACK(button_clicked_cliente));
  gtk_builder_add_callback_symbol(builder,"exit_app",G_CALLBACK(exit_app));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);
}

GtkWidget* Vista::get_window() {
  return this->window;
}

void Vista::main_window() {
  gtk_widget_show_all(window);
  gtk_main();
}

