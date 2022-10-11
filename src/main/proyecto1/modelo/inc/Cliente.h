#ifndef CLIENTE_H_
#define CLIENTE_H_

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
#include "Procesador_Cliente.h"

class Cliente {

  struct sockaddr_in direccion_servidor;
  struct hostent *servidor;
  int puerto;
  int m_socket;
  char buffer_recv[1024];
  char host_buffer[256];
  Procesador_Cliente procesador;
  
public:

  char nombre[256];
  static bool bandera_salida;
  std::thread hilo_envio, hilo_recepcion;

  /**
   * Método constructor de la clase Cliente.
   * @param puerto El puerto al que se conectará el socket del
   * cliente.
   * @param ip El ip al que se conectará el socket del cliente.
   * 
   */
  Cliente(int puerto, const char * ip);

  /**
   * Devuelve el socket del cliente.
   * @return El socket del cliente.
   * 
   */
  int get_socket();

  /**
   * Devuelve el procesador de json del cliente.
   * @return El procesador de json del cliente.
   *
   */
  Procesador_Cliente get_procesador();

  /**
   * Devuelve el buffer de recepción del cliente.
   * @return El buffer de recepción del cliente.
   *
   */
  char * get_buffer_recv();

  /**
   * Devuelve el servidor asociado al cliente.
   * @return El servidor asociado al cliente.
   *
   */
  struct hostent * get_servidor();

  /**
   * Conecta el socket del cliente al socket del servidor.
   * @return 0, si el socket se conectó correctamente; -1,
   * en otro caso
   *
   */
  int cliente_connect();

  /**
   * Escribe los datos a enviar al socket servidor.
   * @param message El mensaje a enviar
   * @return 0, si el mensage fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write(char * message);
  
  /**
   * Lee los datos recibidos en el socket del cliente.
   * @return 0, si los datos fueron recibidos correctamente; -1,
   * en otro caso
   *
   */
  int cliente_read();

  /**
   * Cierra el socket del cliente.
   * 
   */
  void cliente_close();

  /**
   * Envía mensaje a todos los clientes..
   *
   */
  void send_message();

  /**
   * Método para recepción de mensajes del cliente.
   *
   */
  void recv_message();
  
  /**
  * Destructor de la clase Cliente
  *
  */
  ~Cliente();

};

#endif
