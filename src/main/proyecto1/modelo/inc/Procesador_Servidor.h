#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"
#include "Procesador.h"

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
  // std::string parse_message_status(std::string message);
  // std::string parse_message_users(std::string message);
  // std::string parse_message_message(std::string message);
  // std::string parse_message_public_message(std::string message);
  // std::string parse_message_new_room(std::string message);
  // std::string parse_message_invite(std::string message);
  // std::string parse_message_join_room(std::string message);
  // std::string parse_message_room_users(std::string message);
  // std::string parse_message_room_message(std::string message);
  // std::string parse_message_leave_room(std::string message);
  // std::string parse_message_disconnect(std::string message);

  // std::string write_message_id(std::string message); 
  // std::string write_message_status(std::string message);
  // std::string write_message_users(std::string message);
  // std::string write_message_message(std::string message);
  // std::string write_message_public_message(std::string message);
  // std::string write_message_new_room(std::string message);
  // std::string write_message_invite(std::string message);
  // std::string write_message_join_room(std::string message);
  // std::string write_message_room_users(std::string message);
  // std::string write_message_room_message(std::string message);
  // std::string write_message_leave_room(std::string message);
  // std::string write_message_disconnect(std::string message);
};
