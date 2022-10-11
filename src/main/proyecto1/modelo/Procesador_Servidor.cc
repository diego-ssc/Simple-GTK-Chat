#include "inc/Procesador_Servidor.h"

/** Diccionario que mapea cadenas equivalentes al enum
    Protocolo */
std::unordered_map<Protocolo, std::string, EnumClassHash>
const Procesador_Servidor::table_protocolo = { {Protocolo::IDENTIFY, "IDENTIFY"},
					       {Protocolo::STATUS, "STATUS"},
					       {Protocolo::USERS, "USERS"},
					       {Protocolo::MESSAGE, "MESSAGE"},
					       {Protocolo::PUBLIC_MESSAGE, "PUBLIC_MESSAGE"},
					       {Protocolo::NEW_ROOM, "NEW_ROOM"},
					       {Protocolo::INVITE, "INVITE"},
					       {Protocolo::JOIN_ROOM, "JOIN_ROOM"},
					       {Protocolo::ROOM_USERS, "ROOM_USERS"},
					       {Protocolo::ROOM_MESSAGE, "ROOM_MESSAGE"},
					       {Protocolo::LEAVE_ROOM, "LEAVE_ROOM"},
					       {Protocolo::DISCONNECT, "DISCONNECT"}};

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_id(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::IDENTIFY);
  verifica_miembro(Sintaxis::username);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());  
  return lista;
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_status(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::STATUS);
  verifica_miembro(Sintaxis::status);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::status)].asString());  
  return lista;  
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_users(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::USERS);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::type)].asString());
  return lista;
}

std::list<std::string> Procesador_Servidor::parse_message_private_message(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::MESSAGE);
  verifica_miembro(Sintaxis::username);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());  
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());
  return lista;
}

std::list<std::string> Procesador_Servidor::parse_message_public_message(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::PUBLIC_MESSAGE);
  verifica_miembro(Sintaxis::username);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());
  return lista;  
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_new_room(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::NEW_ROOM);
  verifica_miembro(Sintaxis::roomname);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());  
  return lista;
}

std::list<std::string> Procesador_Servidor::parse_message_invite(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::INVITE);
  verifica_miembro(Sintaxis::roomname);
  verifica_miembro(Sintaxis::usernames);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  Json::Value array = parsed_message[table_sintaxis.at(Sintaxis::usernames)];
  for (Json::Value::ArrayIndex i = 0; i != array.size(); i++)
      lista.push_back(array[i].asString());
  return lista;
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_join_room(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::JOIN_ROOM);
  verifica_miembro(Sintaxis::roomname);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  return lista;
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_room_users(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::ROOM_USERS);
  verifica_miembro(Sintaxis::roomname);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  return lista;  
}

std::list<std::string> Procesador_Servidor::parse_message_room_message(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::ROOM_MESSAGE);
  verifica_miembro(Sintaxis::roomname);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());
  return lista;
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_leave_room(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::LEAVE_ROOM);
  verifica_miembro(Sintaxis::roomname);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  return lista;  
}
    
/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Servidor::parse_message_disconnect(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::DISCONNECT);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::type)].asString());
  return lista;
}




std::string Procesador_Servidor::write_message_id_success() {
  write_message_info("success");
  parsed_message["operation"] = "IDENTIFY";
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_id_new_user(std::string username) {
  vacia_json();
  parsed_message["type"] = "NEW_USER";
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_id_failure(std::string username) {
  write_message_warning("El usuario '" + username + "' ya existe.");
  parsed_message["operation"] = "IDENTIFY";
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_status_success() {
  write_message_info("success");
  parsed_message["operation"] = "STATUS";
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_status_new_status(std::string username,
					    std::string status) {
  vacia_json();
  parsed_message["type"] = "NEW_STATUS";
  parsed_message["username"] = username;
  parsed_message["status"] = status;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_status_failure(std::string status) {
  write_message_warning("El estado ya es '" + status + "'");
  parsed_message["operation"] = "STATUS";
  parsed_message["status"] = status;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_users(std::list<std::string> usernames) {
  vacia_json();
  parsed_message["type"] = "USER_LIST";
  Json::Value array;
  std::list<std::string>::iterator i;
  for (i = usernames.begin(); i != usernames.end(); ++i)
    array.append(*i);
  parsed_message["usernames"] = array;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_private_message_new(std::string username,
								   std::string message) {
  vacia_json();
  parsed_message["type"] = "MESSAGE_FROM";
  parsed_message["username"] = username;
  parsed_message["message"] = message;
  return writer.write(parsed_message);

}

std::string Procesador_Servidor::write_message_private_message_failure(std::string username) {
  write_message_warning("El usuario '" + username + "' no existe");
  parsed_message["operation"] = "MESSAGE";
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_public_message_new(std::string username,
								  std::string message) {
  vacia_json();
  parsed_message["type"] = "PUBLIC_MESSAGE_FROM";
  parsed_message["username"] = username;
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_new_room_success() {
  write_message_info("success");
  parsed_message["operation"] = "NEW_ROOM";
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_new_room_failure(std::string sala) {
  write_message_warning("El cuarto '" + sala + "' ya existe");
  parsed_message["operation"] = "NEW_ROOM";
  parsed_message["roomname"] = sala;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_invite_success(std::string roomname) {
  write_message_info("success");
  parsed_message["operation"] = "INVITE";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_invite_new(std::string roomname,
							  std::string username) {
    vacia_json();
    parsed_message["type"] = "INVITATION";
    parsed_message["message"] = username + "te invita al cuarto '" + roomname + "'";
    parsed_message["username"] = username;
    parsed_message["roomname"] = roomname;
    return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_invite_failure_room(std::string roomname) {
  write_message_warning("El cuarto '" + roomname + "' no existe");
  parsed_message["operation"] = "INVITE";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_invite_failure_users(std::string username) {
  write_message_warning("El usuario '" + username + "' no existe");
  parsed_message["operation"] = "INVITE";
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_join_room_success(std::string roomname) {
  write_message_info("success");
  parsed_message["operation"] = "JOIN_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_join_room_new(std::string roomname,
							     std::string username) {

  vacia_json();
  parsed_message["type"] = "JOINED_ROOM";
  parsed_message["roomname"] = roomname;
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_join_room_failure_existence(std::string roomname) {
  write_message_warning("El cuarto '" + roomname + "' no existe");
  parsed_message["operation"] = "JOIN_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_join_room_failure_invite(std::string roomname) {
  write_message_warning("El usuario no ha sido invitado al cuarto '" + roomname + "'");
  parsed_message["operation"] = "JOIN_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_join_room_failure_joined(std::string roomname) {
  write_message_warning("El usuario ya se unió al cuarto '" + roomname + "'");
  parsed_message["operation"] = "JOIN_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_room_users_new(std::list<std::string> usernames) {
  vacia_json();	    
  parsed_message["type"] = "ROOM_USER_LIST";
  Json::Value array;
  std::list<std::string>::iterator i;
  for (i = usernames.begin(); i != usernames.end(); ++i)
    array.append(*i);
  parsed_message["usernames"] = array;
  return writer.write(parsed_message);  
}

std::string Procesador_Servidor::write_message_room_users_failure_existence(std::string roomname) {
  write_message_warning("El cuarto '" + roomname + "' no existe");
  parsed_message["operation"] = "ROOM_USERS";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);  
}

std::string Procesador_Servidor::write_message_room_users_failure_invite(std::string roomname) {
  write_message_warning("El usuario no se ha unido al cuarto '" + roomname + "'");
  parsed_message["operation"] = "ROOM_USERS";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);  
}


std::string Procesador_Servidor::write_message_room_message_new(std::string roomname,
					   std::string username,
					   std::string message) {
  vacia_json();	    
  parsed_message["type"] = "ROOM_MESSAGE_FROM";
  parsed_message["roomname"] = roomname;
  parsed_message["username"] = username;
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_room_message_failure_existence(std::string roomname) {
  write_message_warning("El cuarto '" + roomname + "' no existe");
  parsed_message["operation"] = "ROOM_MESSAGE";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_room_message_failure_invite(std::string roomname) {
  write_message_warning("El usuario no se ha unido al cuarto '" + roomname + "'");
  parsed_message["operation"] = "ROOM_MESSAGE";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_leave_room_success(std::string roomname) {
  write_message_info("success");
  parsed_message["operation"] = "LEAVE_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_leave_room_new(std::string roomname,
					 std::string username) {
  vacia_json();
  parsed_message["type"] = "LEFT_ROOM";
  parsed_message["roomname"] = roomname;
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_leave_room_failure_existence(std::string roomname) {
  write_message_warning("El cuarto '" + roomname + "' no existe");
  parsed_message["operation"] = "LEAVE_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_leave_room_failure_invite(std::string roomname) {
  write_message_warning("El usuario no se ha unido al cuarto '" + roomname + "'");
  parsed_message["operation"] = "LEAVE_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}


std::string Procesador_Servidor::write_message_disconnect_new_users(std::string username) {
  vacia_json();
  parsed_message["type"] = "DISCONNECTED";
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}

std::string Procesador_Servidor::write_message_disconnect_new_rooms(std::string username,
								    std::string roomname) {
  vacia_json();
  parsed_message["type"] = "LEFT_ROOM";
  parsed_message["roomname"] = roomname;
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}


void Procesador_Servidor::verifica_protocolo(Sintaxis miembro, Protocolo llave) {
  std::string str_miembro = table_sintaxis.at(miembro);
  if (!parsed_message.isMember(str_miembro))
    error(("Error: no se recibió un json válido.\n" 
	   "(Ausencia de llave \"" + str_miembro + "\")").c_str());
  
  std::string str_llave = table_protocolo.at(llave);
  if (strcmp(parsed_message[str_miembro].asString().c_str(),
	     str_llave.c_str()) != 0)
    error(("Error: no se recibió un json de " + str_llave + " válido.").c_str());
}
