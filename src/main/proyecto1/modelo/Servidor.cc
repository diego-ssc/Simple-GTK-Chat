#include "inc/Servidor.h"

#define MAX_LEN 1024

Servidor::Servidor(int puerto) {
  bzero((char *) &this->direccion_servidor, sizeof(this->direccion_servidor));
  this->direccion_servidor.sin_family = AF_INET;
  this->direccion_servidor.sin_addr.s_addr = INADDR_ANY;//inet_addr(ip);
  this->direccion_servidor.sin_port = htons(puerto);
  this->puerto = puerto;
  this->procesador = Procesador_Servidor();
}

char* Servidor::get_host_buffer() {
  return this->host_buffer;
}

int Servidor::get_file_descriptor() {
  return this->file_descriptor;
}

int Servidor::servidor_socket() {
  int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  this->file_descriptor = socket_file_descriptor;
  return socket_file_descriptor;
}

int Servidor::servidor_bind() {
  int status = bind(this->file_descriptor,
		    (struct sockaddr *) &this->direccion_servidor,
		    sizeof(this->direccion_servidor));

  return status;
}

int Servidor::servidor_listen(int tamano_cola) {
  int status = listen(this->file_descriptor, tamano_cola);

  return status;
}

int Servidor::servidor_accept() {
  socklen_t longitud_cliente = sizeof(this->direccion_cliente);
  std::cout<<"[Servidor] Aceptando..."<<std::endl;
  int socket = accept(this->file_descriptor
                      , (struct sockaddr *) &this->direccion_cliente
                      , &longitud_cliente);
  
  return socket;
}

void Servidor::servidor_send(int descriptor_archivo, char * message) {
  send(descriptor_archivo, message, sizeof(message), 0);
}

int Servidor::servidor_read(int descriptor_archivo) {
  const int tamano_buffer = 1024;
  bzero(this->host_buffer, tamano_buffer);// Limpia el buffer, en caso de no estar vacío 
  int status = read(descriptor_archivo, this->host_buffer, tamano_buffer);

  return status;

}

void Servidor::servidor_close(int descriptor_archivo) {
  close(descriptor_archivo);
}

void Servidor::global_message(std::string message) {
  char temp[MAX_LEN];
  strcpy(temp, message.c_str());
  std::map<int, Usuario>::iterator i;
  for (i = usuarios.begin(); i != usuarios.end(); ++i) 
    servidor_send(i->second.get_socket(), temp);
}

void Servidor::global_message_from(std::string message, int sender_id) {
  char temp[MAX_LEN];
  strcpy(temp, message.c_str());
  std::map<int, Usuario>::iterator i;
  for (i = usuarios.begin(); i != usuarios.end(); ++i) {
    if(i->second.get_id() == sender_id) continue;
    servidor_send(i->second.get_socket(), temp);
  }
}

void Servidor::send_message_to(std::string message, int id) {
  char temp[MAX_LEN];
  strcpy(temp, message.c_str());
  servidor_send(usuarios.at(id).get_socket(), temp);
}

void Servidor::administra_cliente(int client_socket, int id, Usuario* usuario) {
  servidor_read(client_socket);
  // std::string name = procesador.parse_message_id(std::string(get_host_buffer()));
  usuario->set_name(get_host_buffer());
  usuarios[id] = std::move(*usuario);// Revisar
  // std::string welcome_message = usuario->get_nombre() + " has joined.";
  procesador.write_message_id_new_user(usuario->get_nombre());
  
}


int Servidor::ejecuta() {
  int tamano_cola = 10;

  servidor_socket();
  servidor_bind();
  servidor_listen(tamano_cola);
  
  while(true) {
    int client_socket = servidor_accept();
    seed++;
    Usuario* usuario = new Usuario(seed, client_socket);
    std::thread t(&Servidor::administra_cliente, this, client_socket, seed, usuario);
    usuario->set_thread(move(t));
    
    // servidor_send(client_socket, );
    servidor_read(client_socket);
    servidor_close(get_file_descriptor());// loop before
    servidor_close(client_socket);
  }
  

  return 0;
}

Servidor::~Servidor() {}
