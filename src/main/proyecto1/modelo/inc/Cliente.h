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
#include <gtk/gtk.h>
#include "Procesador_Cliente.h"
#include "Fabrica_Procesadores.h"

class Cliente {

  /** La dirección del servidor asociado
      al cliente */
  struct sockaddr_in direccion_servidor;
  /** El servidor asociado al cliente */
  struct hostent *servidor;
  /** El puerto del cliente */
  int puerto;
  /** El socket del cliente */
  int m_socket;
  /** El búfer de recepción de mensajes */
  char buffer_recv[1024];
  /** El búfer que contiene el nombre del
      servidor */
  char host_buffer[256];
  /** El procesador del cliente */
  Procesador_Cliente procesador;
  /** El objeto que guarda los mensajes que
      se mostrarán en la vista del cliente. */
  GtkTextBuffer* text_buffer;
  
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
   * Devuelve el objeto que guarda los mensajes
   * mostrados al cliente.
   * @param El objeto que guarda los mensajes
   * mostrados al cliente.
   *
   */
  void set_text_buffer(GtkTextBuffer* text_buffer);
  
  /**
   * Conecta el socket del cliente al socket del servidor.
   * @return 0, si el socket se conectó correctamente; -1,
   * en otro caso
   *
   */
  int cliente_connect();

  /**
   * Envía el mensaje público del usuario al servidor.
   * @param message El mensaje a enviar
   * @return 0, si el mensage fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_message(std::string username,
			    std::string message);

  /**
   * Envía el nombre del usuario al servidor.
   * @param message El mensaje a enviar
   * @return 0, si el mensage fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_identify(std::string message);
  
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
  void send_messages();

  /**
   * Método para recepción de mensajes del cliente.
   *
   */
  void recv_messages();
  
  /**
  * Destructor de la clase Cliente
  *
  */
  ~Cliente();

};

#endif
