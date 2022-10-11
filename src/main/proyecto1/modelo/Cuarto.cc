#include "inc/Cuarto.h"

Cuarto::Cuarto(int id) {
  this->id = id;
  this->nombre = "Cuarto " + id;
}

int Cuarto::get_id() {
  return this->id;
}

std::string Cuarto::get_nombre() {
  return this->nombre;
}

/**
 * Se copian los elementos del árbol binario ordenado
 * en una lista para encapsular la información
 * del cuarto.
 *
 */
std::list<std::string> Cuarto::get_room_usernames() {
  std::list<std::string> room_usernames;
  std::map<std::string, Usuario>::iterator i;
  for (i = users.begin(); i != users.end(); ++i)
    room_usernames.push_back(i->first);

  return room_usernames;
}

bool Cuarto::is_in(std::string nombre_usuario) {
  std::map<std::string, Usuario>::iterator i;
  i = users.find(nombre_usuario);
  
  return i != users.end();
}

bool Cuarto::is_invited(std::string nombre_usuario) {
  std::unordered_map<std::string, Usuario>::iterator i;
  i = invited_users.find(nombre_usuario);
  
  return i != invited_users.end();
}

int Cuarto::add_member(std::string username, Usuario &&user) {
  if (is_in(username)) 
    return -1;
  if (!is_invited(username))
    return -2;

  // users.emplace(username, user);
  users[username] = std::move(user);
  std::unordered_map<std::string, Usuario>::iterator i = // eliminar de la lista de invitados,
    invited_users.find(username);                        // una vez agregado
  invited_users.erase(i);
  return 0;
}

int Cuarto::invite_member(std::string username, Usuario &&user) {
  if (is_in(username)) 
    return -1;
  if (is_invited(username)) 
    return -2;

  invited_users[username] = std::move(user);
  // invited_users.emplace(username, user);
  return 0;
}

int Cuarto::eliminate_member(std::string username) {
  if (!is_in(username))
    return -1;
  std::map<std::string, Usuario>::iterator i =
    users.find(username);
  users.erase(i);
  return 0;
}

Cuarto::~Cuarto() {}
