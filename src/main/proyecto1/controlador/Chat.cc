#include <gtk/gtk.h>
#include "inc/Chat.h"
#include "../vista/inc/Vista.h"
#include <iostream>
#include <thread>
#include <future>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Chat* Chat::chat = nullptr;
void catch_ctrl_c(int signal);

void Chat::interfaz() {
  GtkApplication *app;
  int status;

  app = gtk_application_new(NULL, G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), this->argc, (char**)this->argv);
  g_object_unref(app);

  if (status < 0) {
    perror("Ocurrió un error al inicializar la interfaz.");
    exit(1);
  }
}

int Chat::inicia_servidor(int puerto) {
  int tamano_cola = 10;
  std::unique_ptr<Servidor> servidor(new Servidor(puerto));
  servidor->servidor_socket();
  int file_descriptor = servidor->get_file_descriptor();
  servidor->servidor_bind(file_descriptor);
  servidor->servidor_listen(file_descriptor, tamano_cola);
  //
  int new_file_descriptor = servidor->servidor_accept(file_descriptor);
  servidor->servidor_accept_message();
  servidor->servidor_send(new_file_descriptor);
  servidor->servidor_read(new_file_descriptor);
  servidor->servidor_close(file_descriptor);
  servidor->servidor_close(new_file_descriptor);
  return 0;
}

int Chat::inicia_cliente(int puerto) {
  std::shared_ptr<Cliente> cliente(new Cliente(puerto));
  cliente->cliente_socket();
  cliente->cliente_connect();
  
    // SIGINT: interrupción externa
  std::signal(SIGINT, catch_ctrl_c);
  cliente->cliente_write();
  cliente->cliente_read();
  cliente->cliente_close();
  return 0;
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


int Chat::inicio(int ejecutable, int puerto) {
  //interfaz();

  if (ejecutable == 0)
    return Chat::inicia_servidor(puerto);

  return Chat::inicia_cliente(puerto);
  

}

