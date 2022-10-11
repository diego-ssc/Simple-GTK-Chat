#include "inc/Procesador_Cliente.h"

  std::unordered_map<Protocolo, std::string, EnumClassHash>
  const Procesador_Cliente::table_protocolo = { {Protocolo::NEW_USER, "IDENTIFY"},
						{Protocolo::NEW_STATUS, "STATUS"},
						{Protocolo::USER_LIST, "USERS"},
						{Protocolo::MESSAGE_FROM, "MESSAGE"},
						{Protocolo::PUBLIC_MESSAGE_FROM, "PUBLIC_MESSAGE"},
						{Protocolo::JOINED_ROOM, "NEW_ROOM"},
						{Protocolo::ROOM_USER_LIST, "INVITE"},
						{Protocolo::ROOM_MESSAGE_FROM, "JOIN_ROOM"},
						{Protocolo::LEFT_ROOM, "ROOM_USERS"},
						{Protocolo::DISCONNECTED, "ROOM_MESSAGE"}};

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Cliente::parse_message_new_user(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::NEW_USER);
  verifica_miembro(Sintaxis::username);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());
  return lista;
}

       
std::list<std::string> Procesador_Cliente::parse_message_new_status(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::NEW_STATUS);
  verifica_miembro(Sintaxis::username);
  verifica_miembro(Sintaxis::status);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());  
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::status)].asString());
  return lista;
}

std::list<std::string> Procesador_Cliente::parse_message_user_list(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::USER_LIST);
  verifica_miembro(Sintaxis::usernames);
  std::list<std::string> lista;
  Json::Value array = parsed_message[table_sintaxis.at(Sintaxis::usernames)];
  for (Json::Value::ArrayIndex i = 0; i != array.size(); i++)
      lista.push_back(array[i].asString());
  return lista;
}

std::list<std::string> Procesador_Cliente::parse_message_private_message_from(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::MESSAGE_FROM);
  verifica_miembro(Sintaxis::username);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());  
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());
  return lista;
}


std::list<std::string> Procesador_Cliente::parse_message_public_message_from(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::PUBLIC_MESSAGE_FROM);
  verifica_miembro(Sintaxis::username);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());  
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());
  return lista;
}

std::list<std::string> Procesador_Cliente::parse_message_joined_room(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::JOINED_ROOM);
  verifica_miembro(Sintaxis::roomname);
  verifica_miembro(Sintaxis::username);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());  
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());
  return lista;
}

std::list<std::string> Procesador_Cliente::parse_message_room_user_list(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::ROOM_USER_LIST);
  verifica_miembro(Sintaxis::roomname);
  verifica_miembro(Sintaxis::usernames);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString()); 
  Json::Value array = parsed_message[table_sintaxis.at(Sintaxis::usernames)];
  for (Json::Value::ArrayIndex i = 0; i != array.size(); i++)
      lista.push_back(array[i].asString());
  return lista;
}

std::list<std::string> Procesador_Cliente::parse_message_room_message_from(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::ROOM_MESSAGE_FROM);
  verifica_miembro(Sintaxis::roomname);
  verifica_miembro(Sintaxis::username);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());
  return lista;
}

std::list<std::string> Procesador_Cliente::parse_message_left_room(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::LEFT_ROOM);
  verifica_miembro(Sintaxis::roomname);
  verifica_miembro(Sintaxis::username);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::roomname)].asString());
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());
  return lista;
}

/**
 * Devolverá una lista para homogeneizar la el tipo devuelto en los métodos
 * de lectura.
 *
 */
std::list<std::string> Procesador_Cliente::parse_message_disconnected(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::DISCONNECTED);
  verifica_miembro(Sintaxis::username);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::username)].asString());
  return lista;
}


std::string Procesador_Cliente::write_message_new_user(std::string username) {
  vacia_json();
  parsed_message["type"] = "IDENTIFY";
  parsed_message["username"] = username;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_new_status(std::string status) {
  vacia_json();
  parsed_message["type"] = "STATUS";
  parsed_message["status"] = status;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_user_list() {
  vacia_json();
  parsed_message["type"] = "USERS";
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_private_message_to(std::string username,
							   std::string message) {
  vacia_json();
  parsed_message["type"] = "MESSAGE";
  parsed_message["username"] = username;
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_public_message(std::string username,
								  std::string message) {
  vacia_json();
  parsed_message["type"] = "PUBLIC_MESSAGE";
  parsed_message["username"] = username;
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}
			  
std::string Procesador_Cliente::write_message_new_room(std::string roomname) {
  vacia_json();
  parsed_message["type"] = "NEW_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_invite(std::string roomname,
				 std::list<std::string> usernames) {
  vacia_json();
  parsed_message["type"] = "INVITE";
  parsed_message["roomname"] = roomname;
  Json::Value array;
  std::list<std::string>::iterator i;
  for (i = usernames.begin(); i != usernames.end(); ++i)
    array.append(*i);
  parsed_message["usernames"] = array;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_join_room(std::string roomname) {
  vacia_json();
  parsed_message["type"] = "JOIN_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_room_user_list(std::string roomname) {
  vacia_json();
  parsed_message["type"] = "ROOM_USERS";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_room_message(std::string roomname,
							   std::string message) {
  vacia_json();
  parsed_message["type"] = "ROOM_MESSAGE";
  parsed_message["roomname"] = roomname;
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_leave_room(std::string roomname) {
  vacia_json();
  parsed_message["type"] = "LEAVE_ROOM";
  parsed_message["roomname"] = roomname;
  return writer.write(parsed_message);
}

std::string Procesador_Cliente::write_message_disconnected() {
  vacia_json();
  parsed_message["type"] = "LEAVE_ROOM";
  return writer.write(parsed_message);
}


void Procesador_Cliente::verifica_protocolo(Sintaxis miembro, Protocolo llave) {
  std::string str_miembro = table_sintaxis.at(miembro);
  if (!parsed_message.isMember(str_miembro))
    error(("Error: no se recibió un json válido.\n" 
	   "(Ausencia de llave \"" + str_miembro + "\")").c_str());
  
  std::string str_llave = table_protocolo.at(llave);
  if (strcmp(parsed_message[str_miembro].asString().c_str(),
	     str_llave.c_str()) != 0)
    error(("Error: no se recibió un json de " + str_llave + " válido.").c_str());
}
