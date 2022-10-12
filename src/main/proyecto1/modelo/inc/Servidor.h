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
#include <future>
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
  /** El entero que representa el estado de la operación
      de lectura del servidor. */
  int read_status;
  /** El entero que representa el estado de la operación
      de escritura del servidor. */  
  int write_status;
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

  /**
   * Devuelve el número de clientes conectados
   * al servidor.
   * @return El número de clientes conectados
   * al servidor.
   *
   */
  int get_seed();

  /**
   * Devuelve el entero que representa el estado
   * de la operación de lectura del servidor.
   * @return 0, si no ocurrieron problemas durante
   * la ejecución; -1, en otro caso.
   *
   */
  int get_read_status();

  /**
   * Devuelve el entero que representa el estado
   * de la operación de escritura del servidor.
   * @return 0, si no ocurrieron problemas durante
   * la ejecución; -1, en otro caso.
   *
   */
  int get_write_status();

  /**
   * Actualiza en una unidad el número de clientes
   * conectados al servidor.
   *
   */
  void set_seed();

  /**
   * Define el estado de la operación de lectura
   * del servidor.
   * @param status 0, si no ocurrieron problemas durante
   * la ejecución; -1, en otro caso.
   *
   */
  void set_read_status(int status);

  /**
   * Define el estado de la operación de escritura
   * del servidor.
   * @param status 0, si no ocurrieron problemas durante
   * la ejecución; -1, en otro caso.
   *
   */
  void set_write_status(int status);
  
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

  /**
   * Se ancargará de la administración del cliente
   * aceptado; incorporándolo a la lista de usuarios
   * registados y escuchando las peticiones que este
   * envíe.
   * @param client_socket El socket del cliente.
   * @param id El identificador del cliente.
   * @param usuario El usuario asociado al socket.
   * @return 0, si su ejecución no tuvo ningún error;
   * -1, en otro caso.
   *
   */
  void administra_cliente(int client_socket, int id, Usuario* usuario);

  /**
   * Crea los hilos para la administración de los clientes.
   * @param client_socket El socket del cliente.
   * @param seed El identificador del cliente.
   * @param usuario El usuario asociado al socket.
   * @return El hilo que se encargará de administrar el
   * cliente.
   *
   */
  std::thread crea_hilo(int client_socket, int seed, Usuario* usuario);

  /*
  * Destructor de la clase. 
  */
  ~Servidor();

};

#endif
