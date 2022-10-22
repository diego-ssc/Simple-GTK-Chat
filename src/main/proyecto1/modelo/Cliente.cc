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

char* Cliente::get_buffer_recv() {
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

void Cliente::set_room_list(std::list<GtkWidget*> list) {
  this->room_list = list;
}

int Cliente::get_response() {
  return this->response;
}

std::string Cliente::get_str_response() {
  return this->response_str;
}

void Cliente::set_text_buffer(GtkTextBuffer* text_buffer) {
  this->text_buffer = text_buffer;
}

void Cliente::set_list_store(GtkListStore* list_store) {
  this->store = list_store;
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
  gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					   ("You: " + message + "\n").c_str(),
					   -1, NULL, "lmarg",  NULL);
  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

int Cliente::cliente_write_private_message(std::string username,
					   std::string message) {
  if (message.empty())
    return -1;
  std::string str_message = procesador.write_message_private_message_to(username,
									message);
  std::list<GtkWidget*>::iterator i;
  GtkTextBuffer* text_buffer;
  std::string widget_name;
  for (i = room_list.begin(); i != room_list.end(); ++i) {
    widget_name = gtk_widget_get_name(*i);
    if (widget_name.rfind("Private", 0) == 0) {
      if ((widget_name.substr(10)).compare(username) == 0) {
	text_buffer = gtk_text_view_get_buffer
	  (GTK_TEXT_VIEW(*i));
      }
    }
  }

  gtk_text_buffer_get_iter_at_offset(text_buffer, &iter, 0);
  gtk_text_buffer_create_tag(text_buffer, "lmarg", 
			     "left_margin", 5, NULL);
  gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					   ("You: " + message + "\n").c_str(),
					   -1, NULL, "lmarg",  NULL);
  
  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

int Cliente::cliente_write_room_message(std::string roomname,
					std::string message) {
  if (message.empty())
    return -1;
  
  std::string str_message = procesador.write_message_room_message(roomname,
								  message);
  std::list<GtkWidget*>::iterator i;
  GtkTextBuffer* text_buffer;
  std::string widget_name;
  for (i = room_list.begin(); i != room_list.end(); ++i) {
    widget_name = gtk_widget_get_name(*i);
    if (widget_name.compare(roomname) == 0)
      text_buffer = gtk_text_view_get_buffer
	(GTK_TEXT_VIEW(*i));
  }

  gtk_text_buffer_get_iter_at_offset(text_buffer, &iter, 0);
  gtk_text_buffer_create_tag(text_buffer, "lmarg", 
			     "left_margin", 5, NULL);
  gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					   ("You: " + message + "\n").c_str(),
					   -1, NULL, "lmarg",  NULL);

  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

void Cliente::cliente_disconnect() {
  std::string message = procesador.write_message_disconnected();
  write(m_socket, message.c_str(),
	strlen(message.c_str()));
}

int Cliente::cliente_write_identify(char * message) {
  std::string str_message = procesador.write_message_new_user(message);
  return write(m_socket, str_message.c_str(),
	       strlen(str_message.c_str()));
}

int Cliente::cliente_write_new_room(std::string roomname) {
  std::string(Procesador::*procesador_write)(std::string) =
    Fabrica_Procesadores::send_protocol_one(Protocolo::NEW_ROOM);
  std::string message = (procesador.*procesador_write)
    (roomname);
  return write(m_socket, message.c_str(),
	       strlen(message.c_str()));
}

int Cliente::cliente_write_user_list() {
  std::string(Procesador::*procesador_write)() =
    Fabrica_Procesadores::send_protocol(Protocolo::USER_LIST);
  std::string message = (procesador.*procesador_write)();
  return write(m_socket, message.c_str(),
	       strlen(message.c_str()));
}

int Cliente::cliente_write_room_user_list(std::string roomname) {
  std::string(Procesador::*procesador_write)(std::string) =
    Fabrica_Procesadores::send_protocol_one(Protocolo::ROOM_USER_LIST);
  std::string message = (procesador.*procesador_write)
    (roomname);
  return write(m_socket, message.c_str(),
	       strlen(message.c_str()));
}

int Cliente::cliente_send_invitation(std::list<std::string> usernames, std::string roomname) {
  
  std::string message = procesador.write_message_invite(roomname, usernames);
  return write(m_socket, message.c_str(),
	       strlen(message.c_str()));
}

int Cliente::cliente_change_status(std::string status) {
  std::string(Procesador::*procesador_write)(std::string) =
    Fabrica_Procesadores::send_protocol_one(Protocolo::NEW_STATUS);
  std::string message = (procesador.*procesador_write)
    (status);
  return write(m_socket, message.c_str(),
	       strlen(message.c_str()));
}

int Cliente::cliente_write_join_room(std::string roomname) {
  std::string message = procesador.write_message_join_room(roomname);
  return write(m_socket, message.c_str(),
	       strlen(message.c_str()));
}

int Cliente::cliente_read() {
  bzero(buffer_recv, sizeof(buffer_recv));
  return recv(m_socket, buffer_recv, sizeof(buffer_recv), 0);
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
  std::string message;
  std::string username;
  std::string status;
  std::string roomname;
  
  std::list<std::string>::iterator i;
  
  cv.wait(lk, [this]{return interface;});
  gtk_text_buffer_get_iter_at_offset(text_buffer, &iter, 0);
  gtk_text_buffer_create_tag(text_buffer, "lmarg", 
			     "left_margin", 5, NULL);
  lk.unlock();
  Chat *chat;
  
  while (true) {
    if (cliente_read() <= 0)
      continue;
    Protocolo protocolo = procesador.get_type(get_buffer_recv());
    std::list<std::string>(Procesador::*parse)(std::string) =
      Fabrica_Procesadores::recv_protocol(protocolo);
    std::list<std::string> recvd_message = (procesador.*parse)
      (std::string(get_buffer_recv()));
  
    switch (protocolo) {
    case NEW_USER:
      username = recvd_message.front();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + " se ha conectado\n").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case NEW_STATUS:
      username = recvd_message.front();
      status = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + " ha cambiado su estado a "
						+ status).c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case USER_LIST:
      for (i = recvd_message.begin(); i != recvd_message.end(); ++i) {
	gtk_list_store_append(store, &tree_iter);
	gtk_list_store_set(store, &tree_iter, 0, (*i).c_str(), -1);
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
      username = recvd_message.front();
      message = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + ": " + message + "\n").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case INVITATION:
      message = recvd_message.front();
      i = recvd_message.begin();
      i++; i++;
      roomname = *i;
      chat = Chat::get_instance();
      chat->invitation_dialog(message, roomname);
      break;
    case JOINED_ROOM:
      roomname = recvd_message.front(); 
      username = recvd_message.back();
      
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + " se ha unido\n").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case ROOM_USER_LIST:
      for (i = recvd_message.begin(); i != recvd_message.end(); ++i) {
	gtk_list_store_append(store, &tree_iter);
	gtk_list_store_set(store, &tree_iter, 0, (*i).c_str(), -1);
      }
      break;
    case ROOM_MESSAGE_FROM:
      roomname = recvd_message.front();
      i = recvd_message.begin();
      username = *++i;
      message = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter,
					       (username + ": " + message).c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case LEFT_ROOM:
      roomname = recvd_message.front(); 
      username = recvd_message.back();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + "se ha desconectado").c_str(),
					       -1, NULL, "lmarg",  NULL);

      break;
    case DISCONNECTED:
      username = recvd_message.front();
      gtk_text_buffer_insert_with_tags_by_name(text_buffer, &iter, 
					       (username + "se ha desconectado").c_str(),
					       -1, NULL, "lmarg",  NULL);
      break;
    case INFO:
      response = 0;
      response_str = recvd_message.front();
      response_str[0] = toupper(response_str[0]);
      break;
    case WARNING:
      response = 1;
      response_str = recvd_message.front();
      response_str[0] = toupper(response_str[0]);
      break;
    case ERROR:
      response = 2;
      response_str = recvd_message.front();
      response_str[0] = toupper(response_str[0]);
      break;
    }
     
    
  }
}

Cliente::~Cliente() {}
