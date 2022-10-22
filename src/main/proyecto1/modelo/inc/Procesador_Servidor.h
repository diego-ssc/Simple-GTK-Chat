#ifndef PROCESADOR_SERVIDOR_H_
#define PROCESADOR_SERVIDOR_H_

#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"
#include "Procesador.h"
#include "Protocolo.h"
#include <list>

class Procesador_Servidor : public Procesador {

  /** Diccionario que mapea cadenas equivalentes al enum
      Protocolo */
  static std::unordered_map<Protocolo, std::string, EnumClassHash>
  const table_protocolo; 

  
 public:
  
  /**
   * Recibe json de identificación del cliente y
   * filtra el nombre del usuario registrado.
   * @param message Json a leer
   * @return El nombre del usuario registrado
   *
   */
  std::list<std::string> parse_message_id(std::string message);

  /**
   * Recibe json de identificación del cliente y
   * filtra el estado del usuario registrado.
   * @param message Json a leer
   * @return El estado del usuario registrado
   *
   */  
  std::list<std::string> parse_message_status(std::string message);

  /**
   * Recibe json de petición que espera la lista
   * de usuarios conectados al servidor y verifica
   * su sintaxis.
   * @param message Json a leer
   * @return La señal para pedir la lista de usuarios
   *
   */
  std::list<std::string> parse_message_users(std::string message);

  /**
   * Recibe json de envío de mensaje privado.
   * @param message Json a leer
   * @return Una lista que contiene el usuario origen
   * y el mensaje
   *
   */  
  std::list<std::string> parse_message_private_message(std::string message);

  /**
   * Recibe json de envío de mensaje público.
   * @param message Json a leer
   * @return Una lista que contiene el usuario origen
   * y el mensaje
   *
   */  
  std::list<std::string> parse_message_public_message(std::string message);
  
  /**
   * Recibe json de creación de sala.
   * @param message Json a leer
   * @return El nombre de la nueva sala.
   *
   */  
  std::list<std::string> parse_message_new_room(std::string message);

  /**
   * Recibe json de invitación de usuario.
   * @param message Json a leer
   * @return Una lista que contiene el nombre de la sala
   * y el nombre de los integrantes que fueron invitados.
   *
   */ 
  std::list<std::string> parse_message_invite(std::string message);

  /**
   * Recibe json de petición de entrada a un cuarto.
   * @param message Json a leer
   * @return El nombre del cuarto al que se solicita entrar
   *
   */ 
  std::list<std::string> parse_message_join_room(std::string message);

  /**
   * Recibe json de petición de que espera la lista
   * de usuarios conectados al cuarto parámetro
   * y verifica su sintaxis.
   * @param message Json a leer
   * @return El nombre del cuarto del que se solicita
   * la lista de usuarios
   *
   */ 
  std::list<std::string> parse_message_room_users(std::string message);

  /**
   * Recibe json de envío de mensaje a cuarto.
   * @param message Json a leer
   * @return Una lista que contiene el nombre del cuarto al
   * que se enviará el mensage y el mensaje
   *
   */ 
  std::list<std::string> parse_message_room_message(std::string message);

  /**
   * Recibe json de desconexión de cuarto.
   * @param message Json a leer
   * @return El nombre del cuarto del que se desconectará
   * el usuario
   *
   */ 
  std::list<std::string> parse_message_leave_room(std::string message);

    /**
   * Recibe json de desconexión del chat, incluyendo todos
   * los cuartos donde el usuario se haya unido.
   * @param message Json a leer
   * @return La señal para desconectar al usuario.
   *
   */ 
  std::list<std::string> parse_message_disconnect(std::string message);

  /** Métodos de escrutura de json */
  std::string write_message_id_success(); 
  std::string write_message_id_new_user(std::string username);
  std::string write_message_id_failure(std::string username); 

  std::string write_message_status_success();
  std::string write_message_status_new_status(std::string username,
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

#endif
