#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"
#include "Procesador.h"
#include <list>

class Procesador_Cliente : public Procesador {

  enum Protocolo {
    /** Mensajes que recibe el cliente */
    NEW_USER, NEW_STATUS, USER_LIST, MESSAGE_FROM, PUBLIC_MESSAGE_FROM,
    JOINED_ROOM, ROOM_USER_LIST, ROOM_MESSAGE_FROM, LEFT_ROOM, DISCONNECTED
  };

  /** Diccionario que mapea cadenas equivalentes al enum
      Protocolo */
  static std::unordered_map<Protocolo, std::string, EnumClassHash>
  const table_protocolo;
  
 public:
  std::string parse_message_new_user(std::string message); 
  std::list<std::string> parse_message_new_status(std::string message);
  std::list<std::string> parse_message_user_list(std::string message);
  std::list<std::string> parse_message_message_from(std::string message);
  std::list<std::string> parse_message_public_message_from(std::string message);
  std::list<std::string> parse_message_joined_room(std::string messagew);
  std::list<std::string> parse_message_room_user_list(std::string message);
  std::list<std::string> parse_message_room_message_from(std::string message);
  std::list<std::string> parse_message_left_room(std::string message);
  std::string parse_message_disconnected(std::string message);

  std::string write_message_new_user(std::string username);
  std::string write_message_new_status(std::string status);
  std::string write_message_user_list();
  std::string write_message_message(std::string username,
				    std::string message);
  std::string write_message_public_message(std::string username,
					   std::string message);
  std::string write_message_new_room(std::string roomname);
  std::string write_message_invite(std::string roomname,
				   std::list<std::string> usernames);
  std::string write_message_join_room(std::string roomname);
  std::string write_message_room_user_list(std::string roomname);
  std::string write_message_room_message(std::string roomname,
					 std::string message);  
  std::string write_message_leave_room(std::string roomname);
  std::string write_message_disconnected();

  void verifica_protocolo(Sintaxis miembro, Protocolo llave);
  
};
