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

std::thread Chat::get_thread_wrt() {
  return move(wrt);
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

int Chat::inicia_servidor(int puerto) {//ejecuta_servidor
  servidor = new Servidor(puerto);
  int tamano_cola = 10;
    
  if (servidor->servidor_socket() < 0) {
    vista_servidor->window_socket_error();
    return -1;
  }
    
  if (servidor->servidor_bind() < 0) {
    vista_servidor->window_bind_error();
    return -1;
  }

  if (servidor->servidor_listen(tamano_cola) < 0) {
    vista_servidor->window_listen_error();
    return -1;
  }

  gtk_widget_hide(vista_servidor->get_welcome_widget());
  
  h = std::thread (&Chat::ejecuta_servidor, this, servidor);
  vista_servidor->server_window();

  return 0;
}

void Chat::ejecuta_servidor(Servidor* servidor) {
  
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
    usuario->set_thread(move(t));
    
    // while (gtk_events_pending())
    //   gtk_main_iteration();
        
    if (servidor->get_read_status() < 0)
      vista_servidor->window_read_error();

    if (servidor->get_write_status() < 0)
      vista_servidor->window_send_error();
  }

  servidor->termina_ejecucion();

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

  
  std::string username_str = vista_cliente->get_username();
  char* username = new char[username_str.length() + 1];
  strcpy(username, username_str.c_str());
  
  cliente->cliente_write_identify(username);
  
  
  vista_cliente->client_window();
  
  cliente->set_text_buffer(gtk_text_view_get_buffer
			    (GTK_TEXT_VIEW(vista_cliente->get_text_box())));
  
  // wrt = std::thread (&Cliente::cliente_write_message, cliente,
  // 		  username_str, vista_cliente->get_message_data());
  rcv = std::thread (&Cliente::recv_messages, cliente);  
  rcv.join();
  delete []username;
  return 0;
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

