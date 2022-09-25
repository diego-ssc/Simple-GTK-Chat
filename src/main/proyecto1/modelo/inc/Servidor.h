#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

class Servidor {
  int puerto;
  int file_descriptor;
  struct sockaddr_in direccion_servidor;
  struct sockaddr_in direccion_cliente;
  char host_buffer[14];

  void error(const char *mensaje);
  
public:

  Servidor(int puerto);

  void set_puerto(int puerto);

  int get_file_descriptor();

  char* get_host_buffer();
  
  /*
  * Devuelve un descriptor de archivo de socket o -1,
  * en caso de error.
  */
  void servidor_socket();

  void servidor_bind(int descriptor_archivo);

  void servidor_listen(int descriptorArchivo, int tamano_cola);

  /*
  * Devuelve un nuevo descriptor de archivo de socket o -1,
  * en caso de error.
  */
  int servidor_accept(int descriptorArchivo);

  void servidor_send(int descriptor_archivo);

  void servidor_read(int descriptor_archivo);

  /*
  * Cierra el descriptor de archivo de socket parámetro.
  */
  void servidor_close(int descriptor_archivo);

  // /*
  // * Destructor de la clase. // Mal comentario
  // */
  // ~Servidor();

  // /*
  // * Sobrecarga del operador indirección para las variables de clase.
  // */
  // int& operator*();
  // struct sockaddr_int& operator*();

};