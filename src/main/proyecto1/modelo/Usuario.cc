#include "inc/Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(Usuario && user) : th(std::move(user.th)) {
  this->id = user.id;
  this->nombre = user.nombre;
  this->estado = user.estado;
  this->socket = user.socket;
}

Usuario & Usuario::operator=(Usuario && user) {
    if (th.joinable())
        th.join();
    id = user.id;
    nombre = user.nombre;
    estado = user.estado;
    socket = user.socket;
    th = std::move(user.th);

    user.id = 0;
    user.nombre = nullptr;   
    user.estado = nullptr;
    user.socket = 0;
    
    return *this;
}

Usuario::Usuario(int id, std::string nombre,
		 int socket, std::thread th) {
  this->id = id;
  this->nombre = nombre;
  this->socket = socket;
  this->th = std::move(th); //std::thread can't be copied
  this->estado = "ACTIVE";
}

Usuario::Usuario(int id, int socket) {
  this->id = id;
  this->socket = socket;
  this->estado = "ACTIVE";
}
  
void Usuario::set_thread(std::thread th) {
  this->th = move(th);
}

void Usuario::set_status(std::string estado) {
  this->estado = estado;
}

void Usuario::set_name(std::string nombre) {
  this->nombre = nombre;
}

int Usuario::get_id() {
  return this->id;
}

std::string Usuario::get_nombre() {
  return this->nombre;
}

std::string Usuario::get_estado() {
  return this->estado;
}

int Usuario::get_socket() {
  return this->socket;
}

std::thread Usuario::get_thread() {
  return move(this->th); //std::thread can't be copied
}

