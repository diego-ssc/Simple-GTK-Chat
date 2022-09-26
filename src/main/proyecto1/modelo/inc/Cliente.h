//#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <thread>
#include <signal.h>
#include <mutex>
#include <errno.h>
#include <bits/stdc++.h>
#include <json/json.h>

class Cliente {

  struct sockaddr_in direccion_servidor;
  struct hostent *servidor;
  int puerto;
  int file_descriptor;
  char buffer_recv[1024];
  char buffer_send[1024];
  char host_buffer[256];

  void error(const char *mensaje);
  struct hostent * get_server_hostname(void *host_buffer);
  
public:

  char nombre[256];
  static bool bandera_salida;
  std::thread hilo_envio, hilo_recepcion;
  Cliente(int puerto);

  void verifica_servidor();
  int get_file_descriptor();

  void cliente_socket();

  void cliente_connect();

  void cliente_write();

  void cliente_read();

  /*
  * Cierra el descriptor de archivo de socket parámetro.
  */
  void cliente_close();
  
  void send_message();
  void recv_message();
  
  /**
  * Destructor de la clase Cliente
  **/
  ~Cliente();

};
