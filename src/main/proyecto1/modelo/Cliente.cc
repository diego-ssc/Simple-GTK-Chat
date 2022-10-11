#include "inc/Cliente.h"

bool Cliente::bandera_salida = false;

Cliente::Cliente(int puerto, const char * ip) {
  this->puerto = puerto;
  this->direccion_servidor.sin_family = AF_INET;
  this->direccion_servidor.sin_port = htons(puerto);
  this->direccion_servidor.sin_addr.s_addr = inet_addr(ip);
  bzero(&this->direccion_servidor.sin_zero,0);
  getnameinfo((struct sockaddr *) &this->direccion_servidor,
	      sizeof(direccion_servidor),
	      host_buffer,
	      sizeof(host_buffer),
	      NULL, 0, 0);
  this->servidor = gethostbyname((char *)host_buffer);
  this->procesador = Procesador_Cliente();
  this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
}

Procesador_Cliente Cliente::get_procesador() {
  return this->procesador;
}

char * Cliente::get_buffer_recv() {
  return this->buffer_recv;
}

int Cliente::get_socket() {
  return this->m_socket;
}

struct hostent * Cliente::get_servidor() {
  return this->servidor; 
}

int Cliente::cliente_connect() {
  return connect(m_socket,
		 (struct sockaddr *) &direccion_servidor,
		 sizeof(direccion_servidor));
}

int Cliente::cliente_write(char * message) {
  std::string str_message = procesador.write_message_new_user(message);
  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

int Cliente::cliente_read() {
  bzero(buffer_recv, 1024);
  return read(m_socket, this->buffer_recv, 1024);
}

void Cliente::cliente_close() {
  close(m_socket);
}

void Cliente::send_message() {

  	while(1) {
	  //cout<<"You : "<<def_col;
	  // std::cin.getline(buffer_send, 1024);
	  // send(file_descriptor, buffer_send, sizeof(buffer_send),0);
	  // if(strcmp(str,"#exit")==0) {
	  //   exit_flag=true;
	  //   t_recv.detach();	
	  // 		close(client_socket);
	  // 		return;
	  // }	
	}
	
}

void Cliente::recv_message() {
  while(1) {
    if(bandera_salida)
      return;
    int bytes_recibidos = recv(m_socket,nombre,sizeof(nombre),0);
    if(bytes_recibidos <= 0)
      continue;
    recv(m_socket, buffer_recv, sizeof(buffer_recv), 0);
    // if(strcmp(name,"#NULL")!=0)
    //   cout<<color(color_code)<<name<<" : "<<def_col<<str<<endl;
    // else
    //   cout<<color(color_code)<<str<<endl;
    // cout<<colors[1]<<"You : "<<def_col;
    // fflush(stdout);
  }
  
}

Cliente::~Cliente() {
  delete(servidor);
}
