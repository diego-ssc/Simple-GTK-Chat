#ifndef PROCESADOR_CLIENTE_H_
#define PROCESADOR_CLIENTE_H_

#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"
#include "Procesador.h"
#include "Protocolo.h"
#include <list>

class Procesador_Cliente : public Procesador {

  /** Diccionario que mapea cadenas equivalentes al enum
      Protocolo */
  static std::unordered_map<Protocolo, std::string, EnumClassHash>
  const table_protocolo;
  
 public:
  /** Métodos de conversión de json a cadena */
  std::list<std::string> parse_message_new_user(std::string message); 
  std::list<std::string> parse_message_new_status(std::string message);
  std::list<std::string> parse_message_user_list(std::string message);
  std::list<std::string> parse_message_private_message_from(std::string message);
  std::list<std::string> parse_message_public_message_from(std::string message);
  std::list<std::string> parse_message_invitation(std::string message);
  std::list<std::string> parse_message_joined_room(std::string message);
  std::list<std::string> parse_message_room_user_list(std::string message);
  std::list<std::string> parse_message_room_message_from(std::string message);
  std::list<std::string> parse_message_left_room(std::string message);
  std::list<std::string> parse_message_disconnected(std::string message);
  /** Métodos de creación de json */
  std::string write_message_new_user(std::string username);
  std::string write_message_new_status(std::string status);
  std::string write_message_user_list();
  std::string write_message_private_message_to(std::string username,
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

  /** Método que ayuda a garantizar el formato correcto de json recibidos  */
  void verifica_protocolo(Sintaxis miembro, Protocolo llave);
  
};

#endif
