#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "inc/Cliente.h"
#include <netdb.h>
#include <iostream>

Cliente::Cliente(int puerto, void *buffer) {
  this->puerto = puerto;
  this->servidor = Cliente::get_server_hostname(buffer);
  bzero(&this->direccion_servidor, sizeof(this->direccion_servidor));
  this->direccion_servidor.sin_family = AF_INET;
  bcopy((char *)&this->servidor->h_addr,
	(char *)&direccion_servidor.sin_addr.s_addr,
	this->servidor->h_length);
  this->direccion_servidor.sin_port = htons(puerto);
}

struct hostent * Cliente::get_server_hostname(void *host_buffer) {
  int hostname = gethostname((char *)host_buffer, sizeof(host_buffer));
  if (hostname == -1) {
    perror("Error al obtener el nombre del host.");
    exit(1);
  }

  struct hostent *host_entry = gethostbyname((char *)host_buffer);
  if (host_entry == NULL) {
    perror("Error al obtener host_entry.");
    exit(1);
  }
  
  return host_entry;
}

void Cliente::set_puerto(int puerto) {
  this->puerto = puerto;
}

int Cliente::get_file_descriptor() {
  return this->file_descriptor;
}

void Cliente::error(const char *mensaje) {
  std::cerr << mensaje << " : " << strerror(errno)<< std::endl;
  exit(1);
}

void Cliente::cliente_socket() {
  int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_file_descriptor < 0)
    Cliente::error("Error al abrir el socket.");

  this->file_descriptor = socket_file_descriptor;
}

void Cliente::cliente_connect(int descriptor_archivo) {
  int status = connect(descriptor_archivo,
		       (struct sockaddr *) &this->direccion_servidor,
		       sizeof(this->direccion_servidor));
  if (status > 0)
    Cliente::error("Error al conectar con el servidor.");
}

void Cliente::cliente_write(int descriptor_archivo) {
  std::cout<<"Ingrese su mensaje:"<<std::endl;
  bzero(this->buffer, 14);
  // fgets(this->buffer, 4000000, stdin);
  std::string mensaje = "Hello, there!";
  strcpy(this->buffer, mensaje.c_str());
  std::cout<<"buffer: "<<this->buffer<<std::endl;
  std::cout<<"strlenbuffer: "<<strlen(this->buffer)<<std::endl;
  // int status = write(descriptor_archivo, this->buffer, strlen(this->buffer));
  int status = 0;
  std::cout<<"write"<<std::endl;
  if (status < 0)
    Cliente::error("Error al escribir al socket.");
  
  bzero(this->buffer, 14);
}

void Cliente::cliente_read(int descriptor_archivo) {
  int status = read(descriptor_archivo, this->buffer, 14);
  if (status < 0)
    Cliente::error("Error al leer del socket.");
}

void Cliente::cliente_close(int descriptor_archivo) {
  close(descriptor_archivo);
}
