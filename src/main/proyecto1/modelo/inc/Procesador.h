#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"

class Procesador {

protected:
  Json::Value parsed_message;
  Json::Reader reader;
  Json::FastWriter writer;

  /** Mensajes que reciben el servidor
      y el cliente */
  enum Protocolo_general {
    /** Mensajes de error, advertencia e información. */
    ERROR, WARNING, INFO
  };

  enum Sintaxis {
    /** Llaves permitidas en json */
    type, message, operation, username, status, usernames,
    roomname
  };
  
  /** Diccionario que mapea cadenas equivalentes al enum
      Protocolo_general */
  static std::unordered_map<Protocolo_general, std::string, EnumClassHash>
  const table_general; 

  /** Diccionario que mapea cadenas equivalentes al enum
      Sintaxis */
  static std::unordered_map<Sintaxis, std::string, EnumClassHash>
  const table_sintaxis;
    
  void error(const char *message);
  void verifica_protocolo(Sintaxis miembro, Protocolo_general llave);
  void verifica_miembro(Sintaxis miembro);
  void parse_message(std::string message);
  void vacia_json();
  
 public:
  Procesador();
  std::string parse_message_error(std::string message);
  std::string parse_message_warning(std::string message);
  std::string parse_message_info(std::string message);
  
  void write_message_error(std::string message);  
  void write_message_warning(std::string message);
  void write_message_info(std::string message);

  
  virtual ~Procesador(); 
  
};
