#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "inc/Servidor.h"
#include <iostream>

Servidor::Servidor(int puerto, const char * ip) {
  bzero((char *) &this->direccion_servidor, sizeof(this->direccion_servidor));
  this->direccion_servidor.sin_family = AF_INET;
  this->direccion_servidor.sin_addr.s_addr = inet_addr(ip);
  this->direccion_servidor.sin_port = htons(puerto);
  this->puerto = puerto;
}

int Servidor::get_file_descriptor() {
  return this->file_descriptor;
}

char* Servidor::get_host_buffer() {
  return this->host_buffer;
}

void Servidor::error(const char *mensaje) {
  std::cerr << mensaje << " : " << strerror(errno)<< std::endl;
  exit(1);
}

void Servidor::servidor_socket() {
  int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_file_descriptor < 0)
    Servidor::error("[Servidor] Error al abrir el socket.");

  this->file_descriptor = socket_file_descriptor;
}

void Servidor::servidor_bind(int descriptor_archivo) {
  int status = bind(descriptor_archivo, (struct sockaddr *) &this->direccion_servidor,
       sizeof(this->direccion_servidor));

  if (status < 0)
    Servidor::error("[Servidor] Error al enlazar el socket.");
}

void Servidor::servidor_listen(int descriptor_archivo, int tamano_cola) {
  int status = listen(descriptor_archivo, tamano_cola);
  if (status == 0) {
    std::cout << "[Servidor] Esperando conexiones..." << std::endl;
  } else {
    Servidor::error("[Servidor] Error al esperar conexiones.");
  }
}

int Servidor::servidor_accept(int descriptor_archivo) {
  socklen_t longitud_cliente = sizeof(this->direccion_cliente);
  std::cout<<"[Servidor] Aceptando..."<<std::endl;
  int socket = accept(descriptor_archivo
                      , (struct sockaddr *) &this->direccion_cliente
                      , &longitud_cliente);

  if (socket < 0) 
    Servidor::error("[Servidor] Error al aceptar la conexión.");

  std::cout<<"[Servidor] Conexión aceptada."<<std::endl;
  
  return socket;
}

void Servidor::servidor_accept_message() {
    std::cout<<"[Servidor] Se ha establecido una conexión de "
	   << inet_ntoa(this->direccion_cliente.sin_addr)
	   <<", con puerto "<< ntohs(this->direccion_cliente.sin_port)
	   <<"."
	   <<std::endl;
}

void Servidor::servidor_send(int descriptor_archivo) {
    send(descriptor_archivo, "[Servidor] Conexión establecida correctamente.\n", 47, 0);
}

void Servidor::servidor_read(int descriptor_archivo) {
  const int tamano_buffer = 1024;
  bzero(this->host_buffer, tamano_buffer);
  int status = read(descriptor_archivo, this->host_buffer, tamano_buffer);

  if (status < 0)
    Servidor::error("[Servidor] Error al leer del socket.");

  std::cout<<inet_ntoa(this->direccion_cliente.sin_addr)
	   <<" : "<<this->host_buffer
	   <<std::endl;

}

void Servidor::servidor_close(int descriptor_archivo) {
  close(descriptor_archivo);
}

Servidor::~Servidor() {
}
