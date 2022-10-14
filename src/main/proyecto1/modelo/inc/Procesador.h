#ifndef PROCESADOR_H_
#define PROCESADOR_H_

#include <json/json.h>
#include <string>
#include <unordered_map>
#include <iostream>
#include "EnumClassHash.h"
#include <list>
#include "Protocolo.h"

class Procesador {

protected:
  Json::Value parsed_message;
  Json::Reader reader;
  Json::FastWriter writer;

  enum Sintaxis {
    /** Llaves permitidas en json */
    type, message, operation, username, status, usernames,
    roomname
  };

/** Diccionario que mapea elementos del Protocolo
    a cadenas */
  static std::unordered_map<std::string, Protocolo>
  const protocolo_str; 
  
  /** Diccionario que mapea cadenas equivalentes al enum
      Protocolo */
  static std::unordered_map<Protocolo, std::string, EnumClassHash>
  const table_general; 

  /** Diccionario que mapea cadenas equivalentes al enum
      Sintaxis */
  static std::unordered_map<Sintaxis, std::string, EnumClassHash>
  const table_sintaxis;
  
  void error(const char *message);
  void verifica_protocolo(Sintaxis miembro, Protocolo llave);
  void verifica_miembro(Sintaxis miembro);
  void parse_message(std::string message);
  void vacia_json();
  
 public:
  /**
   * Devuelve el tipo del mensaje recibido.
   * (Correspondiente a uno de los definidos
   * en el protocolo).
   * @param message El mensaje recibido.
   * @return El tipo del mensaje recibido.
   *
   */
  Protocolo get_type(std::string message);
  
  Procesador();

  std::list<std::string> parse_message_response(std::string message);
  
  std::string write_message_error(std::string message);  
  std::string write_message_warning(std::string message);
  std::string write_message_info(std::string message);

  
  virtual ~Procesador(); 
  
};

#endif
