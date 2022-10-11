#include "inc/Chat.h"

Chat* Chat::chat = nullptr;

void catch_ctrl_c(int signal);

const int& Chat::get_argc() {
  return argc;
}

char** Chat::get_argv() {
  return (char **)argv;
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
   vista->main_window(); 
   return 0;
 }

int Chat::inicia_servidor(int puerto) {
  std::unique_ptr<Servidor> servidor(new Servidor(puerto));
  return servidor->ejecuta();
}

int Chat::inicia_cliente(int puerto, const char * ip) {
  printf("puerto: %d \n ip: %s \n", puerto, ip);
  // std::shared_ptr<Cliente> cliente(new Cliente(puerto, ip));
  Cliente *cliente = new Cliente(puerto, ip);
  if (!valida_cliente(cliente)) 
    return -1;
  
  if (cliente->cliente_connect() == -1) {
    vista_cliente->window_connection_error();
    return -1;
  }

  vista_cliente->client_window();

  // Leerá siempre, en un hilo (recibir, mostrando en buffer)
  // Escribirá en signal handler

  
    // SIGINT: interrupción externa
  std::signal(SIGINT, catch_ctrl_c);
  // cliente->cliente_write();
  cliente->cliente_read();
  cliente->cliente_close();
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
  // char cadena[200] = "#exit";
  // send(client_socket,str,sizeof(str),0);
  // exit_flag=true;
  // t_send.detach();
  // t_recv.detach();
  // close(client_socket);
  exit(signal);
  
}


// int Chat::inicio() {
//   //interfaz();
//   if (argc == 3)
//     return Chat::inicia_servidor(atoi(argv[2]));
//   else
//     return Chat::inicia_cliente(atoi(argv[2]), argv[3]);
// }


