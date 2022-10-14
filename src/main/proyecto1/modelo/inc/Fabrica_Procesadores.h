#ifndef FABRICA_PROCESADORES_H_
#define FABRICA_PROCESADORES_H_
#include "Protocolo.h"
#include "Procesador.h"
#include "Procesador_Servidor.h"
#include "Procesador_Cliente.h"

typedef std::string(Procesador::*procesador_write)();
typedef std::string(Procesador::*procesador_write_one)(std::string);
typedef std::string(Procesador::*procesador_write_two)(std::string, std::string);

typedef std::list<std::string>(Procesador::*procesador_parse)(std::string);

/**
 * Clase para fabricar procesadores.
 */
class Fabrica_Procesadores {
  /** Constructor privado para evitar instanciación. */
  Fabrica_Procesadores() {};
  
 public:

  /**
   * Regresa una instancia de Procesador (o subclases)
   * para enviar json.
   * @param protocolo El tipo de mensaje que se procesará.
   * @return Una instancia de Procesador.
   *
   */
  static procesador_write
  send_protocol(Protocolo protocolo) {
    switch (protocolo) {
      /** Mensajes que escribe el cliente */
    case USER_LIST:
      return static_cast<procesador_write>
	(&Procesador_Cliente::write_message_user_list);
    case DISCONNECTED:
      return static_cast<procesador_write>
	(&Procesador_Cliente::write_message_disconnected);
    default:
      return nullptr;
    }
  }

  /**
   * Regresa una instancia de Procesador (o subclases)
   * para enviar json.
   * @param protocolo El tipo de mensaje que se procesará.
   * @return Una instancia de Procesador.
   *
   */
  static procesador_write_one
  send_protocol_one(Protocolo protocolo) {
    switch (protocolo) {
      /** Mensajes de error, advertencia e información. */
    case ERROR:
      return &Procesador::write_message_error;
    case WARNING:
      return &Procesador::write_message_warning;
    case INFO:
      return &Procesador::write_message_info;
      /** Mensajes que escribe el cliente */
    case NEW_USER:
      return static_cast<procesador_write_one>
	(&Procesador_Cliente::write_message_new_user);
    case NEW_STATUS:
      return static_cast<procesador_write_one>
	(&Procesador_Cliente::write_message_new_status);
    case JOINED_ROOM:
      return static_cast<procesador_write_one>
	(&Procesador_Cliente::write_message_join_room);
    case ROOM_USER_LIST:
      return static_cast<procesador_write_one>
	(&Procesador_Cliente::write_message_room_user_list);
    case LEFT_ROOM:
      return static_cast<procesador_write_one>
	(&Procesador_Cliente::write_message_leave_room);
      /** Mensajes que escribe el servidor */
    case IDENTIFY:
      return static_cast<procesador_write_one>
	(&Procesador_Servidor::write_message_id_new_user);
    case DISCONNECT:
      return static_cast<procesador_write_one>
	(&Procesador_Servidor::write_message_disconnect_new_users);
    default:
      return nullptr;
    }
  }

  /**
   * Regresa una instancia de Procesador (o subclases)
   * para enviar json.
   * @param protocolo El tipo de mensaje que se procesará.
   * @return Una instancia de Procesador.
   *
   */
  static procesador_write_two
  send_protocol_two(Protocolo protocolo) {
    switch (protocolo) {
      /** Mensajes que escribe el cliente */
    case MESSAGE_FROM:
      return static_cast<procesador_write_two>
	(&Procesador_Cliente::write_message_private_message_to);
    case PUBLIC_MESSAGE_FROM:
      return static_cast<procesador_write_two>
	(&Procesador_Cliente::write_message_public_message);
    case ROOM_MESSAGE_FROM:
      return static_cast<procesador_write_two>
	(&Procesador_Cliente::write_message_room_message);
      /** Mensajes que escribe el servidor */
    case STATUS:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_status_new_status);
    case MESSAGE:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_private_message_new);
    case PUBLIC_MESSAGE:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_public_message_new);
    case INVITE:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_invite_new);
    case JOIN_ROOM:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_join_room_new);
    case LEAVE_ROOM:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_leave_room_new);
    case DISCONNECT:
      return static_cast<procesador_write_two>
	(&Procesador_Servidor::write_message_disconnect_new_rooms);
    default:
      return nullptr;
    }
  }
  
  /**
   * Regresa una instancia de Procesador (o subclases)
   * para recibir json.
   * @param protocolo El tipo de mensaje que se procesará.
   * @return Una instancia de Procesador.
   *
   */
  static procesador_parse
  recv_protocol(Protocolo protocolo) {
    switch (protocolo) {
      /** Mensajes de error, advertencia e información. */
    case ERROR:
      return &Procesador::parse_message_response;
    case WARNING:
      return &Procesador::parse_message_response;
    case INFO:
      return &Procesador::parse_message_response;
      /** Mensajes que recibe el cliente */
    case NEW_USER:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_new_user);
    case NEW_STATUS:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_new_status);
    case USER_LIST:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_user_list);
    case MESSAGE_FROM:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_private_message_from);
    case PUBLIC_MESSAGE_FROM:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_public_message_from);
    case INVITATION:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_invitation);      
    case JOINED_ROOM:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_joined_room);
    case ROOM_USER_LIST:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_room_user_list);
    case ROOM_MESSAGE_FROM:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_room_message_from);
    case LEFT_ROOM:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_left_room);
    case DISCONNECTED:
      return static_cast<procesador_parse>
	(&Procesador_Cliente::parse_message_disconnected);
      /** Mensajes que recibe el servidor */
    case IDENTIFY:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_id);
    case STATUS:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_status);
    case USERS:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_users);
    case MESSAGE:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_private_message);
    case PUBLIC_MESSAGE:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_public_message);
    case NEW_ROOM:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_new_room);
    case INVITE:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_invite);
    case JOIN_ROOM:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_join_room);
    case ROOM_USERS:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_room_users);
    case ROOM_MESSAGE:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_room_message);
    case LEAVE_ROOM:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_leave_room);
    case DISCONNECT:
      return static_cast<procesador_parse>
	(&Procesador_Servidor::parse_message_disconnect);
    default:
      return nullptr;
    }
  }
  
};

#endif
