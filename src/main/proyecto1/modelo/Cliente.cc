#include "inc/Cliente.h"

bool Cliente::bandera_salida = false;

/**
 * Método constructor de la clase Cliente.
 * @param puerto El puerto al que se conectará el socket del
 * cliente.
 * 
 */
Cliente::Cliente(int puerto, const char * ip) {
  this->puerto = puerto;
  this->direccion_servidor.sin_family = AF_INET;
  this->direccion_servidor.sin_port = htons(puerto);
  this->direccion_servidor.sin_addr.s_addr = inet_addr(ip);
  bzero(&this->direccion_servidor.sin_zero,0);//
  getnameinfo((struct sockaddr *) &this->direccion_servidor,
	      sizeof(direccion_servidor),
	      host_buffer,
	      sizeof(host_buffer),
	      NULL, 0, 0);
  this->servidor = gethostbyname((char *)host_buffer);
  std::cout<<"[Cliente] Nombre host: "<<(char *)host_buffer<<std::endl;
  Cliente::verifica_servidor();
  
  // bcopy((char *)&this->servidor->h_addr,
  // 	(char *)&this->direccion_servidor.sin_addr.s_addr,
  // 	this->servidor->h_length);
}

/**
 * Define el servidor al que se conectará el socket del cliente.
 * @param host_buffer Arreglo para guardar el nombre del host.
 * @return El servidor.
 * 
 */
struct hostent * Cliente::get_server_hostname(void *host_buffer) {
  int hostname = gethostname((char *)host_buffer, sizeof(host_buffer));
  if (hostname == -1) {
    Cliente::error("[Cliente] Error al obtener el nombre del host.");
    exit(1);
  }

  struct hostent *host_entry = gethostbyname((char *)host_buffer);
  if (host_entry == NULL) {
    Cliente::error("[Cliente] Error al obtener host_entry.");
  }

  std::cout<<"[Cliente] Nombre host: "<<(char *)host_buffer<<std::endl;
  
  return host_entry;
}

/**
 * Verifica que el servidor asociado esté bien definido.
 * 
 */
void Cliente::verifica_servidor() {
  if (this->servidor == NULL)
    Cliente::error("[Cliente] No existe este host.");
}

/**
 * Devuelve el entero generado al crear el socket del cliente.
 * @return El entero generado al crear el socket.
 * 
 */
int Cliente::get_file_descriptor() {
  return this->file_descriptor;
}

/**
 * Define mensajes de error lanzados por el cliente.
 * @param mensaje El mensaje de error.
 * 
 */
void Cliente::error(const char *mensaje) {
  std::cerr << mensaje << " : " << strerror(errno)<< std::endl;
  exit(1);
}

/**
 * Crea el socket del cliente.
 * 
 */
void Cliente::cliente_socket() {
  int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_file_descriptor < 0)
    Cliente::error("[Cliente] Error al abrir el socket.");

  this->file_descriptor = socket_file_descriptor;
}

/**
 * Conecta el socket del cliente al socket del servidor.
 * 
 */
void Cliente::cliente_connect() {
  std::cout<<"[Cliente] Conectando..."<<std::endl;
  int status = connect(file_descriptor,
		       (struct sockaddr *) &direccion_servidor,
		       sizeof(direccion_servidor));
  if (status < 0)
    Cliente::error("[Cliente] Error al conectar con el servidor.");
  std::cout<<"[Cliente] Socket conectado."<<std::endl;
}

/**
 * Escribe los datos a enviar al socket servidor.
 * 
 */
void Cliente::cliente_write() {
  std::cout<<"[Cliente] Ingrese su mensaje:"<<std::endl;
  bzero(this->buffer_send, 1024);
  fgets(this->buffer_send, 1024, stdin);
  std::string message = procesador.write_message_new_user(buffer_send);
  std::cout<< "message: "<< message<<std::endl;
  std::cout<< "message:c_Str "<< message.c_str()<<std::endl;
  int status = write(file_descriptor, message.c_str(),
		     strlen(message.c_str()));
  if (status < 0)
    Cliente::error("[Cliente] Error al escribir al socket.");
  
  bzero(this->buffer_send, 1024);
}

/**
 * Lee los datos recibidos en el socket del cliente.
 * 
 */
void Cliente::cliente_read() {
  int status = read(file_descriptor, this->buffer_recv, 1024);
  if (status < 0)
    Cliente::error("[Cliente] Error al leer del socket.");
}

/**
 * Cierra el socket del cliente.
 * 
 */
void Cliente::cliente_close() {
  close(file_descriptor);
}

/**
 * Envía mensaje a todos los clientes..
 *
 */
void Cliente::send_message() {

  	while(1) {
	  //cout<<"You : "<<def_col;
	  std::cin.getline(buffer_send, 1024);
	  send(file_descriptor, buffer_send, sizeof(buffer_send),0);
	  // if(strcmp(str,"#exit")==0) {
	  //   exit_flag=true;
	  //   t_recv.detach();	
	  // 		close(client_socket);
	  // 		return;
	  // }	
	}
	
}

/**
 * Método para recepción de mensajes del cliente.
 *
 */
void Cliente::recv_message() {
  while(1) {
    if(bandera_salida)
      return;
    int bytes_recibidos = recv(file_descriptor,nombre,sizeof(nombre),0);
    if(bytes_recibidos <= 0)
      continue;
    recv(file_descriptor, buffer_recv, sizeof(buffer_recv), 0);
    // if(strcmp(name,"#NULL")!=0)
    //   cout<<color(color_code)<<name<<" : "<<def_col<<str<<endl;
    // else
    //   cout<<color(color_code)<<str<<endl;
    // cout<<colors[1]<<"You : "<<def_col;
    // fflush(stdout);
  }
  
}

Cliente::~Cliente() {
  delete(servidor);
}
