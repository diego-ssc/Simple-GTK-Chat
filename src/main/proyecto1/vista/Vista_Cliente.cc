#include "inc/Vista_Cliente.h"

Vista_Cliente* Vista_Cliente::vista_cliente = nullptr;

extern "C" {
  G_MODULE_EXPORT void client_send_data() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_ip_data(gtk_entry_get_text(GTK_ENTRY(vista->get_ip_entry())));
    vista->set_port_data(gtk_entry_get_text(GTK_ENTRY(vista->get_port_entry())));
    gtk_widget_hide(vista->get_welcome_widget());
    Chat::get_instance()->inicia_cliente(atoi(vista->get_port_data()), vista->get_ip_data());
  }

  G_MODULE_EXPORT void ip_enter_signal() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_ip_data(gtk_entry_get_text(GTK_ENTRY(vista->get_ip_entry())));
    vista->set_port_data(gtk_entry_get_text(GTK_ENTRY(vista->get_port_entry())));
    gtk_widget_hide(vista->get_welcome_widget());
    Chat::get_instance()->inicia_cliente(atoi(vista->get_port_data()), vista->get_ip_data()); 
  }

  G_MODULE_EXPORT void port_enter_signal() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_ip_data(gtk_entry_get_text(GTK_ENTRY(vista->get_ip_entry())));
    vista->set_port_data(gtk_entry_get_text(GTK_ENTRY(vista->get_port_entry())));
    gtk_widget_hide(vista->get_welcome_widget());
    Chat::get_instance()->inicia_cliente(atoi(vista->get_port_data()), vista->get_ip_data()); 
  }

  G_MODULE_EXPORT void client_exit_app() {
    gtk_main_quit();
    exit(1);
  }
  
  G_MODULE_EXPORT void exit_client_welcome_window() {
    gtk_main_quit();
    exit(1);
  }

  G_MODULE_EXPORT void enter_icon() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_message_data(gtk_entry_get_text(GTK_ENTRY(vista->get_message_entry())));
    gtk_entry_set_text (GTK_ENTRY(vista->get_message_entry()), "");
  }

  G_MODULE_EXPORT void enter_signal() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_message_data(gtk_entry_get_text(GTK_ENTRY(vista->get_message_entry())));
    gtk_entry_set_text (GTK_ENTRY(vista->get_message_entry()), "");
  }

  G_MODULE_EXPORT void client_hide_show_user_list() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    GtkWidget *list = vista->get_user_list_container();
    if (gtk_widget_is_visible(list)) {
      gtk_widget_hide(list);
    } else {
      gtk_widget_show(list);
    }
  }

  G_MODULE_EXPORT void create_room() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->window_room_creation();
  }

  G_MODULE_EXPORT void room_dialog_enter_signal() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_room_name(gtk_entry_get_text(vista->get_room_creation_entry()));
    gtk_entry_set_text (GTK_ENTRY(vista->get_message_entry()), "");
    gtk_window_close(GTK_WINDOW(vista->get_room_dialog()));
  }
  
  G_MODULE_EXPORT void room_dialog_continue_button() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    vista->set_room_name(gtk_entry_get_text(vista->get_room_creation_entry()));
    gtk_entry_set_text (GTK_ENTRY(vista->get_message_entry()), "");
    gtk_window_close(GTK_WINDOW(vista->get_room_dialog()));
  }

  G_MODULE_EXPORT void room_dialog_cancel_button() {
    Vista_Cliente* vista = Vista_Cliente::get_instance();
    gtk_window_close(GTK_WINDOW(vista->get_room_dialog()));
  }
}

Vista_Cliente::Vista_Cliente(int argc, char ** argv) {
  gtk_init(&argc, &argv);
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "../src/media/Cliente_welcome.glade", &err);

  if (err != NULL) {
    fprintf (stderr, "No fue posible leer el archivo: %s\n", err->message);
    g_error_free(err);
    exit(1);
  }
  
  welcome = GTK_WIDGET(gtk_builder_get_object(builder, "client_welcome"));

  if (welcome == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"client_welcome\".\n");
    exit(1);
  }

  gtk_builder_add_callback_symbol(builder,"client_send_data",G_CALLBACK(client_send_data));
  gtk_builder_add_callback_symbol(builder,"ip_enter_signal",G_CALLBACK(ip_enter_signal));
  gtk_builder_add_callback_symbol(builder,"port_enter_signal",G_CALLBACK(port_enter_signal));
  gtk_builder_add_callback_symbol(builder,"exit_client_welcome_window",
				  G_CALLBACK(exit_client_welcome_window));
  gtk_builder_connect_signals(builder, NULL);
}

void Vista_Cliente::set_ip_data(const char* ip_data) {
  this->ip_data = ip_data;
}

void Vista_Cliente::set_port_data(const char* port_data) {
  this->port_data = port_data;
}

void Vista_Cliente::set_message_data(const char* message_data) {
  this->message_data = message_data;
}

void Vista_Cliente::set_room_name(const char* room_name) {
  this->room_name = room_name;
}

void Vista_Cliente::set_user_list(std::list<std::string> users) {
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

const char* Vista_Cliente::get_ip_data() {
  return this->ip_data;
}

const char* Vista_Cliente::get_port_data() {
  return this->port_data;
}

const char* Vista_Cliente::get_message_data() {
  return this->message_data;
}
	     
const char* Vista_Cliente::get_room_name() {
  return this->room_name;
}

GtkEntry* Vista_Cliente::get_ip_entry() {
  return this->ip;
} 

GtkEntry* Vista_Cliente::get_port_entry() {
  return this->port;
}

GtkEntry* Vista_Cliente::get_message_entry() {
  return this->message_box;
}

GtkEntry* Vista_Cliente::get_room_creation_entry() {
  return this->room_creation_entry;
}

GtkWidget* Vista_Cliente::get_user_list() {
  return this->user_list;
}

GtkWidget* Vista_Cliente::get_user_list_container() {
  return this->user_list_container;
}

GtkWidget* Vista_Cliente::get_welcome_widget() {
  return this->welcome;
}

GtkWidget* Vista_Cliente::get_client_widget() {
  return this->window;
}

GtkWidget* Vista_Cliente::get_room_dialog() {
  return this->room_dialog;
}

void Vista_Cliente::welcome_window() {
  ip = GTK_ENTRY(gtk_builder_get_object(builder, "ip_entry"));
  port = GTK_ENTRY(gtk_builder_get_object(builder, "port_entry"));
  g_object_unref(builder);
  gtk_widget_show_all(welcome);
}

void Vista_Cliente::client_window() {
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "../src/media/Cliente.glade", &err);

  if (err != NULL) {
    fprintf (stderr, "No fue posible leer el archivo: %s\n", err->message);
    g_error_free(err);
    exit(1);
  }
  
  message_box = GTK_ENTRY(gtk_builder_get_object(builder, "message_entry"));
  window = GTK_WIDGET(gtk_builder_get_object(builder, "client_window"));
  user_list = GTK_WIDGET(gtk_builder_get_object(builder, "user_list"));
  user_list_container = GTK_WIDGET(gtk_builder_get_object(builder, "user_list_container"));
    
  if (message_box == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"message_entry\".\n");
    exit(1);
  }
  
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

  gtk_builder_add_callback_symbol(builder,"client_exit_app",G_CALLBACK(client_exit_app));
  gtk_builder_add_callback_symbol(builder,"enter_icon",G_CALLBACK(enter_icon));
  gtk_builder_add_callback_symbol(builder,"enter_signal",G_CALLBACK(enter_signal));
  gtk_builder_add_callback_symbol(builder,
				  "client_hide_show_user_list",
				  G_CALLBACK(client_hide_show_user_list));
  gtk_builder_add_callback_symbol(builder,"create_room",G_CALLBACK(create_room));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);
  gtk_widget_show_all(window);
  gtk_widget_hide(user_list_container);
  gtk_main();
}

void Vista_Cliente::window_error(const char * error_message, GtkWidget* parent) {
  GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_MESSAGE_ERROR,
					     GTK_BUTTONS_OK,
					     error_message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Error");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);   
}

void Vista_Cliente::window_warning(const char * warning_message, GtkWidget* parent) {
  GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_MESSAGE_WARNING,
					     GTK_BUTTONS_OK,
					     warning_message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Warning");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);   
  } 

void Vista_Cliente::window_info(const char * info_message, GtkWidget* parent) {
  GtkWidget* dialog = gtk_message_dialog_new(GTK_WINDOW(parent),
					     GTK_DIALOG_DESTROY_WITH_PARENT,
					     GTK_MESSAGE_INFO,
					     GTK_BUTTONS_OK,
					     info_message);
  gtk_window_set_title(GTK_WINDOW(dialog), "Information");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);   
}

void Vista_Cliente::window_room_creation() {
  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "../src/media/Room_Dialog.glade", &err);

  if (err != NULL) {
    fprintf (stderr, "No fue posible leer el archivo: %s\n", err->message);
    g_error_free(err);
    exit(1);
  }
  							    
  room_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "room_dialog"));
  room_creation_entry = GTK_ENTRY(gtk_builder_get_object(builder, "room_creation_entry"));
    
  if (room_creation_entry == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"room_creation_entry\".\n");
    exit(1);
  }
  
  if (room_dialog == NULL) {
    fprintf(stderr, "No ha sido posible extraer widget \"room_dialog\".\n");
    exit(1);
  }
  
  gtk_builder_add_callback_symbol(builder,"room_dialog_continue_button",
				  G_CALLBACK(room_dialog_continue_button));
  gtk_builder_add_callback_symbol(builder,"room_dialog_cancel_button",
				  G_CALLBACK(room_dialog_cancel_button));
  gtk_builder_add_callback_symbol(builder,"room_dialog_enter_signal",
				  G_CALLBACK(room_dialog_enter_signal));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);
  gtk_widget_show_all(room_dialog);
}


void Vista_Cliente::window_port_error() {
  window_error("Ingrese un puerto válido", welcome);
}

void Vista_Cliente::window_ip_error() {
  window_error("Ingrese un IP válido", welcome);
}

void Vista_Cliente::window_null_server_error() {
  window_error("No existe este host.", welcome);
}

void Vista_Cliente::window_socket_error() {
  window_error("Error al abrir el socket.", welcome);
}
	
void Vista_Cliente::window_connection_error() {// info connected
  window_error("Error al conectar con el servidor.", welcome);
}

void Vista_Cliente::window_write_error() {
  window_error("Error al escribir al socket.", window);
}

void Vista_Cliente::window_read_error() {
  window_error("Error al leer del socket.", window);
}

