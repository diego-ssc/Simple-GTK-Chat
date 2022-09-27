#include<json/json.h>
#include<string.h>

class Procesador_Cliente : public Procesador {

  enum Protocolo : std::string {
    /** Mensajes que recibe el cliente */
    NEW_USER, NEW_STATUS, USER_LIST, MESSAGE_FROM, PUBLIC_MESSAGE_FROM,
    JOINED_ROOM, ROOM_USER_LIST, ROOM_MESSAGE_FROM, LEFT_ROOM, DISCONNECTED
  }
  
 public:
  std::string parse_message_new_user(); 
  std::string parse_message_new_status();
  std::string parse_message_user_list();
  std::string parse_message_message_from();
  std::string parse_message_public_message_from();
  std::string parse_message_joined_room();
  std::string parse_message_room_user_list();
  std::string parse_message_room_message_from();
  std::string parse_message_left_room();
  std::string parse_message_disconnected();

  std::string write_message_new_user(); 
  std::string write_message_new_status();
  std::string write_message_user_list();
  std::string write_message_message_from();
  std::string write_message_public_message_from();
  std::string write_message_joined_room();
  std::string write_message_room_user_list();
  std::string write_message_room_message_from();
  std::string write_message_left_room();
  std::string write_message_disconnected();

};
