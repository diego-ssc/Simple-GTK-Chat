#pragma GCC diagnostic ignored "-Wswitch" // No se usarán todos miembros del enum Protocolo
#include "inc/Cliente.h"
#include <condition_variable>

bool Cliente::bandera_salida = false;

Cliente::Cliente(int puerto, const char * ip) {
  this->puerto = puerto;
  this->direccion_servidor.sin_family = AF_INET;
  this->direccion_servidor.sin_port = htons(puerto);
  this->direccion_servidor.sin_addr.s_addr = inet_addr(ip);
  bzero(&this->direccion_servidor.sin_zero,0);
  getnameinfo((struct sockaddr *) &this->direccion_servidor,
	      sizeof(direccion_servidor),
	      host_buffer,
	      sizeof(host_buffer),
	      NULL, 0, 0);
  this->servidor = gethostbyname((char *)host_buffer);
  this->procesador = Procesador_Cliente();
  this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
}

Procesador_Cliente Cliente::get_procesador() {
  return this->procesador;
}

char * Cliente::get_buffer_recv() {
  return this->buffer_recv;
}

int Cliente::get_socket() {
  return this->m_socket;
}

struct hostent * Cliente::get_servidor() {
  return this->servidor; 
}

bool Cliente::get_bool_interface() {
  return this->interface;
}

void Cliente::set_text_buffer(GtkTextBuffer* text_buffer) {
  this->text_buffer = text_buffer;
}

void Cliente::set_bool_interface(bool interface) {
  this->interface = interface;
}

int Cliente::cliente_connect() {
  return connect(m_socket,
		 (struct sockaddr *) &direccion_servidor,
		 sizeof(direccion_servidor));
}

int Cliente::cliente_write_message(std::string username,
				   std::string message) {
  if (message.empty())
    return -1;
  std::string str_message = procesador.write_message_public_message(username,
								    message);
  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

int Cliente::cliente_write_identify(char * message) {
  std::string str_message = procesador.write_message_new_user(message);
  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

int Cliente::cliente_read() {
  bzero(buffer_recv, 1024);
  return read(m_socket, this->buffer_recv, 1024);
}

void Cliente::cliente_close() {
  close(m_socket);
}

std::thread Cliente::crea_hilo_recv() {
  std::thread t(&Cliente::recv_messages, this);
  return t;
}

void Cliente::recv_messages() {
  // Variables para usarse dentro de while
  std::cout<<"Recibiendo mensajes..."<<std::endl;
  std::string message;
  std::string username;
  std::string status;
  std::string roomname;
  
  std::list<std::string>::iterator i;
  
  GtkTextIter iter;


  std::unique_lock lk(m);
  
  cv.wait(lk, [this]{return interface;});
  gtk_text_buffer_get_iter_at_offset(text_buffer, &iter, 0);
  gtk_text_buffer_create_tag(text_buffer, "lmarg", 
			     "left_margin", 5, NULL);  
  lk.unlock();
      
  while (true) {
    if (cliente_read() <= 0)
      continue;
    
    Protocolo protocolo = procesador.get_type(get_buffer_recv());
    std::list<std::string>(Procesador::*parse)(std::string) =
      Fabrica_Procesadores::recv_protocol(protocolo);
    std::list<std::string> recvd_message = (procesador.*parse)
      (std::string(get_buffer_recv()));

    for (i = recvd_message.begin(); i != recvd_message.end(); ++i) {
      std::cout<<*i<<std::endl;
    }
    
    switch (protocolo) {
    case NEW_USER:
      username = recvd_message.front();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + " se ha conectado").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case NEW_STATUS:
      username = recvd_message.front();
      status = recvd_message.back();
      // cambiar status de lista mostrada
      break;
    case USER_LIST:
      for (i = recvd_message.begin(); i != recvd_message.end(); ++i) {
	std::cout<<*i<<std::endl;// Establecer como modelo de lista de usuarios
      }
      break;
    case MESSAGE_FROM:
      username = recvd_message.front();
      message = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       ("[Private]" + username + ": " + message).c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case PUBLIC_MESSAGE_FROM:
      std::cout<<"Se recibió mensaje público"<<std::endl;
      username = recvd_message.front();
      message = recvd_message.back();
      std::cout<<"Username: "<<std::endl<<username<<"Message: "<<message<<std::endl;
      std::cout<<"Username: "<<username<<std::endl<<"Message: "<<message<<std::endl;
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + ": " + message).c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case INVITATION:
      message = recvd_message.front();
      // como dialog
      break;
    case JOINED_ROOM:
      roomname = recvd_message.front(); //Acceder a stack de cuarto
      username = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, // en buffer correspondiente
					       (username + " se ha unido").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case ROOM_USER_LIST:
      for (i = recvd_message.begin(); i != recvd_message.end(); ++i) {
	std::cout<<*i<<std::endl;// Establecer como modelo de lista de usuarios del cuarto
      }
      break;
    case ROOM_MESSAGE_FROM:
      roomname = recvd_message.front(); //Acceder a stack de cuarto
      i = recvd_message.begin();
      username = *++i;
      message = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, // en buffer correspondiente
					       (username + ": " + message).c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case LEFT_ROOM:
      roomname = recvd_message.front(); //Acceder a stack de cuarto
      username = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, // en buffer correspondiente
					       (username + "se ha desconectado").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case DISCONNECTED:
      username = recvd_message.front();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + "se ha desconectado").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case INFO:// dialog con operación relacionada
      return;
    case WARNING:
      return;
    case ERROR:
      return;
    }
     
    
  }
}

Cliente::~Cliente() {}
