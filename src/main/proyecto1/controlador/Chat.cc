#include "inc/Chat.h"

Chat* Chat::chat = nullptr;

void catch_ctrl_c(int signal);

const int& Chat::get_argc() {
  return argc;
}

char** Chat::get_argv() {
  return (char **)argv;
}

std::thread Chat::get_thread_h() {
  return move(h);
}

std::thread Chat::get_thread_rcv() {
  return move(rcv);
}

Servidor* Chat::get_servidor() {
  return this->servidor;
}

Cliente* Chat::get_cliente() {
  return this->cliente;
}

void Chat::set_vista(Vista* vista) {
  this->vista = vista;
}

void Chat::set_vista_servidor(Vista_Servidor* vista) {
  this->vista_servidor = vista;
}

void Chat::set_vista_cliente(Vista_Cliente* vista) {
  this->vista_cliente = vista;
}

Vista* Chat::get_vista() {
  return this->vista;
}

Vista_Servidor* Chat::get_vista_servidor() {
  return this->vista_servidor;
}

Vista_Cliente* Chat::get_vista_cliente() {
  return this->vista_cliente;
}

 int Chat::inicio() {
   set_vista(Vista::get_instance(get_argc(), get_argv()));
   set_vista_cliente(Vista_Cliente::get_instance(get_argc(), get_argv()));
   set_vista_servidor(Vista_Servidor::get_instance(get_argc(), get_argv()));
   vista->main_window(); 
   return 0;
 }

int Chat::inicia_servidor(int puerto) {
  servidor = new Servidor(puerto);
  int tamano_cola = 10;
    
  if (servidor->servidor_socket() == -1) {
    vista_servidor->window_socket_error();
    return -1;
  }
    
  if (servidor->servidor_bind() !=  0) {
    vista_servidor->window_bind_error();
    return -1;
  }

  if (servidor->servidor_listen(tamano_cola) == -1) {
    vista_servidor->window_listen_error();
    return -1;
  }

  gtk_widget_hide(vista_servidor->get_welcome_widget());
  
  h = std::thread (&Chat::ejecuta_servidor, this);
  vista_servidor->server_window();

  return 0;
}

void Chat::ejecuta_servidor() {
  
  while(true) {
    int client_socket = servidor->servidor_accept();
    if (client_socket == -1)
      vista_servidor->window_accept_error();

    servidor->set_text_buffer(gtk_text_view_get_buffer
			      (GTK_TEXT_VIEW(vista_servidor->get_text_box())));  
    servidor->set_seed();
    int seed = servidor->get_seed();
    Usuario* usuario = new Usuario(seed, client_socket);
    std::thread t = servidor->crea_hilo(usuario);
    usuario->set_thread(std::move(t));

    while (gtk_events_pending())
      gtk_main_iteration();

    if (servidor->get_write_status() < 0)
      vista_servidor->window_send_error();
  }
}

void Chat::termina_servidor() {
  servidor->termina_ejecucion();
}

int Chat::inicia_cliente(int puerto, const char * ip) {
  cliente = new Cliente(puerto, ip);
  if (!valida_cliente(cliente))//move(cliente) 
    return -1;
  
  if (cliente->cliente_connect() < 0) {
    vista_cliente->window_connection_error();
    return -1;
  }

  gtk_widget_hide(vista_cliente->get_welcome_widget());
  vista_cliente->client_name_window();
  
  client_name = vista_cliente->get_username();
  char* client_name_id = new char[client_name.length() + 1];
  strcpy(client_name_id, client_name.c_str());
  cliente->cliente_write_identify(client_name_id);
  rcv = cliente->crea_hilo_recv();
  vista_cliente->client_window(cliente);

  delete [] client_name_id;  
  return 0;
}

void Chat::cliente_envia_mensaje_publico(std::string message) {
  cliente->cliente_write_message(client_name, message);
}

void Chat::cliente_crea_cuarto(std::string roomname) {
  cliente->cliente_write_new_room(roomname);
}

int Chat::verifica_respuesta() {
  int response = cliente->get_response();
  std::string str_response = cliente->get_str_response();
  if (response == 0) {
    vista_cliente->window_main_info(str_response);
  } else if (response == 1) {
    vista_cliente->window_main_warning(str_response);	  
  } else if (response == 2) {
    vista_cliente->window_main_error(str_response);
  }
  return response;
}

void Chat::lista_usuarios(std::string roomname) {
  if (roomname.compare("General") == 0) {
    cliente->cliente_write_user_list();
    return;
  }
  
  cliente->cliente_write_room_user_list(roomname);
}

bool Chat::valida_cliente(Cliente* cliente) {
  struct hostent* servidor = cliente->get_servidor();
  if (servidor == NULL) {
    vista_cliente->window_null_server_error();
    return false;
  }

  int socket = cliente->get_socket();
  if (socket < 0) {
    vista_cliente->window_socket_error();
    return false;
  }

  return true; 
}

/**
 * Define las acciones al capturar "Ctrl + C".
 * @param signal Señal a la que responderá al detectarse
 * la combinación de teclas.
 * 
 */
void catch_ctrl_c(int signal) {
  exit(signal);
}

