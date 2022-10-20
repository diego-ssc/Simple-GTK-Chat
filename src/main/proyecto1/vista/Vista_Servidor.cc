#include "inc/Vista_Servidor.h"

Vista_Servidor* Vista_Servidor::vista_servidor = nullptr;

extern "C" {
  //Senales
  G_MODULE_EXPORT void server_send_data() {
    Vista_Servidor* vista = Vista_Servidor::get_instance();
    vista->set_port_data(gtk_entry_get_text(GTK_ENTRY(vista->get_port_entry())));
    Chat::get_instance()->inicia_servidor(atoi(vista->get_port_data()));
  }

  G_MODULE_EXPORT void server_enter_signal_send_data() {
    Vista_Servidor* vista = Vista_Servidor::get_instance();
    vista->set_port_data(gtk_entry_get_text(GTK_ENTRY(vista->get_port_entry())));
    Chat::get_instance()->inicia_servidor(atoi(vista->get_port_data()));
  }
  
  G_MODULE_EXPORT void server_exit_app() {
    gtk_main_quit();
    Chat* chat = Chat::get_instance();
    delete chat->get_servidor();
    chat->get_thread_h().detach();
    chat->termina_servidor();
    delete chat;
    exit(1);
  }

  G_MODULE_EXPORT void server_exit_welcome_window() {
    gtk_main_quit();
    exit(1);
  }
  
  G_MODULE_EXPORT void server_hide_show_user_list() {
    Vista_Servidor* vista = Vista_Servidor::get_instance();
    GtkWidget *list = vista->get_user_list_container();
    if (gtk_widget_is_visible(list)) {
      gtk_widget_hide(list);
    } else {
      gtk_widget_show(list);
    }
  }
  
}

Vista_Servidor::Vista_Servidor(int argc, char** argv) {
  gtk_init(&argc, &argv);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "../src/media/Servidor_welcome.glade", &err);

  if (err != NULL) {
    fprintf (stderr, "No fue posible leer el archivo: %s\n", err->message);
    g_error_free(err);
    exit(1);
  }
  
  welcome = GTK_WIDGET(gtk_builder_get_object(builder, "server_welcome"));

  if (welcome == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"server_welcome\".\n");
    exit(1);
  }

  gtk_builder_add_callback_symbol(builder,"server_send_data",G_CALLBACK(server_send_data));
  gtk_builder_add_callback_symbol(builder,
				  "server_enter_signal_send_data",
				  G_CALLBACK(server_enter_signal_send_data));
  gtk_builder_add_callback_symbol(builder,"server_exit_welcome_window",
				  G_CALLBACK(server_exit_welcome_window));  
  gtk_builder_connect_signals(builder, NULL);
}

void Vista_Servidor::window_error(const char * error_message, GtkWidget* parent) {
  GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_MESSAGE_ERROR,
					     GTK_BUTTONS_OK,
					     error_message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);   
}

void Vista_Servidor::window_warning(const char* warning_message, GtkWidget* parent) {
  GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_MESSAGE_WARNING,
					     GTK_BUTTONS_OK,
					     warning_message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Advertencia");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);   
}

void Vista_Servidor::window_info(const char* info_message, GtkWidget* parent) {
  GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_MESSAGE_INFO,
					     GTK_BUTTONS_OK,
					     info_message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Información");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);   
}

void Vista_Servidor::set_port_data(const char* port_data) {
  this->port_data = port_data;
}

void Vista_Servidor::set_room_name(const char* roomname) {
  this->room_name = roomname;
}

void Vista_Servidor::set_user_list(std::list<std::string> users) {
  std::list<std::string>::iterator i;
  GtkListStore *lista = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
  GtkTreeIter j;
  
  for (i = users.begin(); i != users.end(); ++i) {
    gtk_list_store_append (lista, &j);
    gtk_list_store_set (lista, &j, 0, *i, 1, *++i, -1);
  }
  GtkTreeModel *modelo = GTK_TREE_MODEL(lista);
  gtk_tree_view_set_model(GTK_TREE_VIEW(user_list), modelo);
  g_object_unref (modelo);
}

const char* Vista_Servidor::get_port_data() {
  return this->port_data;
}

GtkEntry* Vista_Servidor::get_port_entry() {
  return this->port;
}


GtkWidget* Vista_Servidor::get_user_list() {
  return this->user_list;
}

GtkWidget* Vista_Servidor::get_user_list_container() {
  return this->user_list_container;
}

GtkWidget * Vista_Servidor::get_welcome_widget() {
  return this->welcome;
}

GtkWidget * Vista_Servidor::get_server_widget() {
  return this->window;
}

GtkWidget * Vista_Servidor::get_text_box() {
  return this->text_box;
}

void Vista_Servidor::welcome_window() {
  port = GTK_ENTRY(gtk_builder_get_object(builder, "port_entry"));
  g_object_unref(builder);
  gtk_window_set_position(GTK_WINDOW(welcome), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_widget_show_all(welcome);
}

void Vista_Servidor::server_window() {
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "../src/media/Servidor.glade", &err);

  if (err != NULL) {
    fprintf (stderr, "No fue posible leer el archivo: %s\n", err->message);
    g_error_free(err);
    exit(1);
  }

  window = GTK_WIDGET(gtk_builder_get_object(builder, "server_window"));
  user_list = GTK_WIDGET(gtk_builder_get_object(builder, "user_list"));
  user_list_container = GTK_WIDGET(gtk_builder_get_object(builder, "user_list_container"));
  text_box = GTK_WIDGET(gtk_builder_get_object(builder, "server_text_box"));
  
  if (window == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"client_window\".\n");
    exit(1);
  }

  if (user_list == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"user_list\".\n");
    exit(1);
  }

  if (user_list_container == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"user_list_container\".\n");
    exit(1);
  }

  if (text_box == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"text_box\".\n");
    exit(1);
  }

  gtk_builder_add_callback_symbol(builder,"server_exit_app",G_CALLBACK(server_exit_app));
  gtk_builder_add_callback_symbol(builder,
				  "server_hide_show_user_list",
				  G_CALLBACK(server_hide_show_user_list));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
  gtk_widget_show_all(window);
  gtk_widget_hide(user_list_container);
  gtk_main();
}

void Vista_Servidor::window_bind_error() {
  window_error("Error al enlazar el servidor con el socket", welcome);
}

void Vista_Servidor::window_listen_error() {
  window_error("Error al escuchar conexiones", welcome);  
}

void Vista_Servidor::window_accept_error() {
  window_error("Error al aceptar la conexión", window);    
}

void Vista_Servidor::window_socket_error() {
  window_error("Error al abrir el socket", welcome);   
}

void Vista_Servidor::window_send_error() {
  window_error("Error al enviar los datos", window);   
}

void Vista_Servidor::window_read_error() {
  window_error("Error al leer los datos", window);   
}


void Vista_Servidor::servidor_accepted_message(int ip, int puerto) {
  std::string message = "Se ha establecido una conexión con " + std::to_string(ip) +
    "con puerto " + std::to_string(puerto);

  // escribir en buffer de mensajes del servidor
  /*     // 	   << inet_ntoa(this->direccion_cliente.sin_addr) */
  /*     // 	   <<", con puerto "<< ntohs(this->direccion_cliente.sin_port) */
  // strerror(errno)
}
