#include "inc/Procesador.h"

Procesador::Procesador() {}

/** Diccionario que mapea elementos del Protocolo
    a cadenas */
std::unordered_map<std::string, Protocolo>
const Procesador::protocolo_str = { {"ERROR", Protocolo::ERROR},
				    {"WARNING", Protocolo::WARNING},
				    {"INFO", Protocolo::INFO},  
				    {"NEW_USER", Protocolo::NEW_USER},
				    {"NEW_STATUS", Protocolo::NEW_STATUS},
				    {"USER_LIST", Protocolo::USER_LIST},
				    {"MESSAGE_FROM", Protocolo::MESSAGE_FROM},
				    {"PUBLIC_MESSAGE_FROM", Protocolo::PUBLIC_MESSAGE_FROM},
				    {"JOINED_ROOM", Protocolo::JOINED_ROOM},
				    {"ROOM_USER_LIST", Protocolo::ROOM_USER_LIST},
				    {"ROOM_MESSAGE_FROM", Protocolo::ROOM_MESSAGE_FROM},
				    {"LEFT_ROOM", Protocolo::LEFT_ROOM},
				    {"DISCONNECTED", Protocolo::DISCONNECTED},
				    {"IDENTIFY", Protocolo::IDENTIFY},
				    {"STATUS", Protocolo::STATUS},
				    {"USERS", Protocolo::USERS},
				    {"MESSAGE", Protocolo::MESSAGE},
				    {"PUBLIC_MESSAGE", Protocolo::PUBLIC_MESSAGE},
				    {"NEW_ROOM", Protocolo::NEW_ROOM},
				    {"INVITE", Protocolo::INVITE},
				    {"JOIN_ROOM", Protocolo::JOIN_ROOM},
				    {"ROOM_USERS", Protocolo::ROOM_USERS},
				    {"ROOM_MESSAGE", Protocolo::ROOM_MESSAGE},
				    {"LEAVE_ROOM", Protocolo::LEAVE_ROOM},
				    {"DISCONNECT", Protocolo::DISCONNECT}};

/** Diccionario que mapea cadenas equivalentes al enum
    Protocolo */
std::unordered_map<Protocolo, std::string, EnumClassHash>
const Procesador::table_general = { {Protocolo::ERROR, "ERROR"},
				    {Protocolo::WARNING, "WARNING"},
				    {Protocolo::INFO, "INFO"}};

/** Diccionario que mapea cadenas equivalentes al enum
    Sintaxis */
std::unordered_map<Procesador::Sintaxis, std::string, EnumClassHash>
const Procesador::table_sintaxis = { {Sintaxis::type, "type"},
				     {Sintaxis::message, "message"},
				     {Sintaxis::operation, "operation"},
				     {Sintaxis::username, "username"},
				     {Sintaxis::status, "status"},
				     {Sintaxis::usernames, "usernames"},
				     {Sintaxis::roomname, "roomname"}};


Protocolo Procesador::get_type(std::string message) {
  parse_message(message);
  std::string type = parsed_message[table_sintaxis.at(Sintaxis::type)].asString();
  return protocolo_str.at(type);
}

void Procesador::parse_message(std::string message) {
  vacia_json();
  std::cout<<message<<std::endl;
  if(!this->reader.parse(message, this->parsed_message))
    error("Error: No se ha recibido un json válido.");
}

std::list<std::string> Procesador::parse_message_response(std::string message) {
  parse_message(message);
  verifica_miembro(Sintaxis::type);
  verifica_miembro(Sintaxis::message);
  std::list<std::string> lista;
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::type)].asString());
  lista.push_back(parsed_message[table_sintaxis.at(Sintaxis::message)].asString());  
  return lista;
}


std::string Procesador::write_message_error(std::string message) {
  vacia_json();
  parsed_message["type"] = "ERROR";
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}

std::string Procesador::write_message_warning(std::string message) {
  vacia_json();
  parsed_message["type"] = "WARNING";
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}

std::string Procesador::write_message_info(std::string message) {
  vacia_json();
  parsed_message["type"] = "INFO";
  parsed_message["message"] = message;
  return writer.write(parsed_message);
}
  

void Procesador::error(const char *mensaje) {
  std::cerr << mensaje << " : " << strerror(errno)<< std::endl;
  exit(1);
}

void Procesador::verifica_protocolo(Sintaxis miembro, Protocolo llave) {
  std::string str_miembro = table_sintaxis.at(miembro);
  if (!parsed_message.isMember(str_miembro))
    error(("Error: no se recibió un json válido.\n" 
	   "(Ausencia de llave \"" + str_miembro + "\")").c_str());
  
  std::string str_llave = table_general.at(llave);
  if (strcmp(parsed_message[str_miembro].asString().c_str(),
	     str_llave.c_str()) != 0)
    error(("Error: no se recibió un json de " + str_llave + " válido.").c_str());
}

void Procesador::verifica_miembro(Sintaxis miembro) {
  std::string llave = table_sintaxis.at(miembro);
  if (!parsed_message.isMember(llave))
    error(("Error: no se recibió un json válido.\n" 
	   "(Ausencia de llave \"" + llave + "\")").c_str());
}

void Procesador::vacia_json() {
  if (!this-> parsed_message.empty())
    this->parsed_message.clear();
}

Procesador::~Procesador() {}


