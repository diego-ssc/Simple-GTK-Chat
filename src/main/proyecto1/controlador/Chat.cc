#include <gtk/gtk.h>
#include "inc/Chat.h"
#include "../vista/inc/Vista.h"
#include <iostream>

Chat* Chat::chat = nullptr;

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

Servidor* Chat::inicia_servidor(int puerto) {
  int tamano_cola = 10;
  Servidor* servidor = new Servidor(puerto);
  servidor->servidor_socket();
  int file_descriptor = servidor->get_file_descriptor();
  servidor->servidor_bind(file_descriptor);
  servidor->servidor_listen(file_descriptor, tamano_cola);
  return servidor;
}

Cliente* Chat::inicia_cliente(int puerto, void * buffer) {
  Cliente* cliente = new Cliente(puerto, buffer);
  cliente->cliente_socket();
  cliente->cliente_connect(cliente->get_file_descriptor());
  return cliente;
}

void Chat::inicio() {
  //interfaz();
  int puerto = 1234;
    std::cout<<"Hello."<<std::endl;
  Servidor* servidor = Chat::inicia_servidor(puerto);
  Cliente* cliente = Chat::inicia_cliente(puerto, servidor->get_host_buffer());
  int socket_cliente = cliente->get_file_descriptor();
  int socket_servidor = servidor->get_file_descriptor();
  
  std::cout<<"Prev.write."<<std::endl;
  cliente->cliente_write(socket_cliente);
  std::cout<<"Prev.read"<<std::endl;
  cliente->cliente_read(socket_cliente);
  std::cout<<"Prev.Accept."<<std::endl;
  int client_file_descriptor = servidor->servidor_accept(socket_servidor);
  std::cout<<"Accept."<<std::endl;
  servidor->servidor_send(client_file_descriptor);
  servidor->servidor_read(client_file_descriptor);
  cliente->cliente_close(socket_cliente);
  servidor->servidor_close(socket_servidor);
  servidor->servidor_close(client_file_descriptor);
}

