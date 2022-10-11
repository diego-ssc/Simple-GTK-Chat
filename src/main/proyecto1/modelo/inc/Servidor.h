#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <netinet/in.h>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <list>
#include <thread>
#include <mutex>
#include "Cuarto.h"
#include "Procesador_Servidor.h"
#include "Fabrica_Procesadores.h"

/**
 * Clase que encapsula el comportamiento de un servidor
 * que administrará el chat.
 *
 */
class Servidor {

  /** El puerto al que se enlazará el servidor. */
  int puerto;
  /** El entero que representa el socket del servidor. */
  int file_descriptor;
  /** Objeto que representa al servidor. */
  struct sockaddr_in direccion_servidor;

  /** Objeto que representa un cliente. */
  struct sockaddr_in direccion_cliente;

  /** Arreglo que almacenará los datos recibidos de los clientes. */
  char host_buffer[1024];
  /** Registra el número de clientes; además, funge como identificador
      de los mismos. */
  int seed;

  Procesador_Servidor procesador;
  
  /**
   * Diccionarios que almacenarán la información de los usuarios
   * conectados y las salas creadas, a partir de un identificador
   * entero.
   *
   */
  std::map<int, Usuario> usuarios;
  std::map<int, Cuarto> cuartos;
  
public:

  Servidor(int puerto);

  int get_file_descriptor();

  char* get_host_buffer();
  
  /*
  * Devuelve un descriptor de archivo de socket o -1,
  * en caso de error.
  */
  int servidor_socket();

  int servidor_bind();

  int servidor_listen(int tamano_cola);

  /*
  * Devuelve un nuevo descriptor de archivo de socket o -1,
  * en caso de error.
  */
  int servidor_accept();
  
  void servidor_send(int descriptor_archivo, char * message);

  int servidor_read(int descriptor_archivo);

  /*
  * Cierra el descriptor de archivo de socket parámetro.
  */
  void servidor_close(int descriptor_archivo);

  void global_message(std::string message);

  void global_message_from(std::string message, int id);

  void send_message_to(std::string message, int id);
  
  
  void administra_cliente(int client_socket, int id, Usuario* usuario);
  
  /**
   * Comienza la ejecución del servidor.
   * @return 0, si la ejecución terminó correctamente;
   * -1, en otro caso
   *
   */
  int ejecuta();

  /*
  * Destructor de la clase. 
  */
  ~Servidor();

};

#endif
