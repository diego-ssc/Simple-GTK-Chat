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

inline std::condition_variable cv;
/** Determinarán cuándo se inicia la interfaz */
inline std::mutex m;
inline std::unique_lock lk(m);

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
  /** El objeto que accede al búfer del cliente */
  GtkTextIter iter;
  /** El objeto que accede a la lista de usuarios
      del cliente */
  GtkTreeIter tree_iter;
  /** 0, si el servidor responde con un mensaje
      de información; 1, si fue de advertencia;
      2, en otro caso. */
  int response = -1;
  /** Guarda el mensaje de respuesta del servidor */
  std::string response_str;
  /** El modelo para la vista de usuarios */
  GtkListStore* store;

  bool interface = false;

public:

  /** Guarda el nombre del cliente */
  char nombre[256];
  static bool bandera_salida;

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
  char* get_buffer_recv();

  /**
   * Devuelve el servidor asociado al cliente.
   * @return El servidor asociado al cliente.
   *
   */
  struct hostent * get_servidor();

  /**
   * Devuelve true, si la interfaz ha sido inicializada;
   * false, en otro caso.
   *
   */
  bool get_bool_interface();
  
  /**
   * Devuelve un entero que indica si la respuesta
   * del servidor fue de información, advertencia
   * o error.
   * @return 0, si se trata de un mensaje de información;
   * 1, si fue de advertencia; 2, en otro caso.
   *
   */
  int get_response();

  /**
   * Devuelve el mensaje de respuesta del servidor.
   * @return El mensaje de respuesta del servidor.
   *
   */
  std::string get_str_response();

  /**
   * Devuelve el modelo de la lista de usuarios.
   *
   */
  GtkListStore* get_list_store();
  
  /**
   * Devuelve el objeto que guarda los mensajes
   * mostrados al cliente.
   * @param El objeto que guarda los mensajes
   * mostrados al cliente.
   *
   */
  void set_text_buffer(GtkTextBuffer* text_buffer);


  /**
   * Define el estado de la interfaz.
   * @param interface true, si la interfaz
   * ha sido inicializada; false, en otro caso.
   *
   */
  void set_bool_interface(bool interface);
  
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
   * @return 0, si el mensaje fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_message(std::string username,
			    std::string message);

  /**
   * Envía el nombre del usuario al servidor.
   * @param message El mensaje a enviar
   * @return 0, si el mensaje fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_identify(char* message);

  /**
   * Envía la petición de creación de sala al servidor.
   * @param message El nombre del cuarto
   * @return 0, si el mensaje fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_new_room(std::string roomname);

  /**
   * Envía la petición para obtener la lista
   * del chat general
   * @return 0, si el mensaje fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_user_list();

  /**
   * Envía la petición para obtener la lista
   * de un cuarto en particular.
   * @return 0, si el mensaje fue enviado correctamente;
   * -1, en otro caso
   *
   */
  int cliente_write_room_user_list(std::string roomname);
  
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
   * Crea el hilo de ejecución para el
   * recibo de mensajes.
   * @return El hilo de ejecución para el
   * recibo de mensajes.
   *
   */
  std::thread crea_hilo_recv();
  
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
