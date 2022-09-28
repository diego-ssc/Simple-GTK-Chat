#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"
#include "Procesador.h"
#include <list>

class Procesador_Servidor : public Procesador {

  enum Protocolo {
    /** Mensajes que recibe el servidor */
    IDENTIFY, STATUS, USERS, MESSAGE, PUBLIC_MESSAGE,
    NEW_ROOM, INVITE, JOIN_ROOM, ROOM_USERS, ROOM_MESSAGE,
    LEAVE_ROOM, DISCONNECT
  };

  /** Diccionario que mapea cadenas equivalentes al enum
      Protocolo */
  static std::unordered_map<Protocolo, std::string, EnumClassHash>
  const table_protocolo; 

  void verifica_protocolo(Sintaxis miembro, Protocolo llave);
  
 public:
  std::string parse_message_id(std::string message); 
  std::string parse_message_status(std::string message);
  void parse_message_users(std::string message);
  std::list<std::string> parse_message_private_message(std::string message);
  std::list<std::string> parse_message_public_message(std::string message);
  std::string parse_message_new_room(std::string message);
  std::list<std::string> parse_message_invite(std::string message);
  std::string parse_message_join_room(std::string message);
  std::string parse_message_room_users(std::string message);
  std::list<std::string> parse_message_room_message(std::string message);
  std::string parse_message_leave_room(std::string message);
  void parse_message_disconnect(std::string message);

  std::string write_message_id_success(); 
  std::string write_message_id_new_user(std::string username);
  std::string write_message_id_failure(std::string username); 

  std::string write_message_status_success();
  std::string write_message_status_new_status(std::string message,
					      std::string status);
  std::string write_message_status_failure(std::string status);
  
  std::string write_message_users(std::list<std::string> usernames);
  
  std::string write_message_private_message_new(std::string username,
						std::string message);
  std::string write_message_private_message_failure(std::string username);

  std::string write_message_public_message_new(std::string message,
					       std::string username);
  
  std::string write_message_new_room_success();
  std::string write_message_new_room_failure(std::string sala);
  
  std::string write_message_invite_success(std::string message);
  std::string write_message_invite_new(std::string message,
				       std::string username);
  std::string write_message_invite_failure_room(std::string roomname);
  std::string write_message_invite_failure_users(std::string username);
  
  std::string write_message_join_room_success(std::string roomname);
  std::string write_message_join_room_new(std::string roomname,
					  std::string username);
  std::string write_message_join_room_failure_existence(std::string roomname);
  std::string write_message_join_room_failure_invite(std::string roomname);
  std::string write_message_join_room_failure_joined(std::string roomname);
  
  
  std::string write_message_room_users_new(std::list<std::string> usernames);
  std::string write_message_room_users_failure_existence(std::string roomname);
  std::string write_message_room_users_failure_invite(std::string roomname);
  
  std::string write_message_room_message_new(std::string roomname,
					     std::string username,
					     std::string message);
  std::string write_message_room_message_failure_existence(std::string roomname);
  std::string write_message_room_message_failure_invite(std::string roomname);
  

  std::string write_message_leave_room_success(std::string roomname);
  std::string write_message_leave_room_new(std::string roomname,
					   std::string username);
  std::string write_message_leave_room_failure_existence(std::string roomname);
  std::string write_message_leave_room_failure_invite(std::string roomname);
  
  
  std::string write_message_disconnect_new_users(std::string username);
  std::string write_message_disconnect_new_rooms(std::string username,
						 std::string roomname);
  
};
