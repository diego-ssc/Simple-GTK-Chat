#include "inc/Procesador_Servidor.h"

/** Diccionario que mapea cadenas equivalentes al enum
    Protocolo_general */
std::unordered_map<Procesador_Servidor::Protocolo, std::string, EnumClassHash>
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

std::string Procesador_Servidor::parse_message_id(std::string message) {
  parse_message(message);
  verifica_protocolo(Sintaxis::type, Protocolo::IDENTIFY);
  verifica_miembro(Sintaxis::username);
  return parsed_message[table_sintaxis.at(Sintaxis::username)].asString();
}

// std::string parse_message_status();
// std::string parse_message_users();
//   std::string parse_message_message();
//   std::string parse_message_public_message();
//   std::string parse_message_new_room();
//   std::string parse_message_invite();
//   std::string parse_message_join_room();
//   std::string parse_message_room_users();
//   std::string parse_message_room_message();
//   std::string parse_message_leave_room();
//   std::string parse_message_disconnect();

//   std::string write_message_id(); 
//   std::string write_message_status();
//   std::string write_message_users();
//   std::string write_message_message();
//   std::string write_message_public_message();
//   std::string write_message_new_room();
//   std::string write_message_invite();
//   std::string write_message_join_room();
//   std::string write_message_room_users();
//   std::string write_message_room_message();
//   std::string write_message_leave_room();
//   std::string write_message_disconnect();

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
