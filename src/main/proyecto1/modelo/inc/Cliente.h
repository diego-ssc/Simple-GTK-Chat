#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

class Cliente {
  int puerto;
  int file_descriptor;
  struct sockaddr_in direccion_servidor;
  struct hostent *servidor;
  char buffer[14];

  void error(const char *mensaje);
  struct hostent * get_server_hostname(void *host_buffer);
  
public:
  
  Cliente(int puerto, void *buffer);

  void set_puerto(int puerto);
  int get_file_descriptor();

  /*
  * Devuelve un descriptor de archivo de socket o -1,
  * en caso de error.
  */
  void cliente_socket();

  void cliente_connect(int descriptor_archivo);

  void cliente_write(int descriptor_archivo);

  void cliente_read(int descriptor_archivo);

  /*
  * Cierra el descriptor de archivo de socket parámetro.
  */
  void cliente_close(int descriptorArchivo);

  // /**
  // * Destructor de la clase Cliente
  // **/
  // ~Cliente();

  // /*
  // * Sobrecarga del operador indirección para las variables de clase.
  // */
  // int& operator*();
  // struct sockaddr_int& operator*();
  // struct hostent& operator*();

};
