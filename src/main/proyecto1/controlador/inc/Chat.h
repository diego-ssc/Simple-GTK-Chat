#ifndef CHAT_H_
#define CHAT_H_

#include "../../modelo/inc/Servidor.h"
#include "../../modelo/inc/Cliente.h"
#include <iostream>
#include <thread>
#include <future>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../../vista/inc/Vista.h"
#include "../../vista/inc/Vista_Cliente.h"
#include "../../vista/inc/Vista_Servidor.h"

/** "Forward declaration" de clases con dependencias circulares */
class Vista_Cliente;
class Vista_Servidor;

class Chat {  

protected:
  /**
   * Constructor de la clase Chat.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   *
   */
  Chat(const int argc, const char **argv) : argc(argc), argv(argv) {}
  /** Única instancia de la aplicación */
  static Chat* chat;
  /** El número de argumentos pasados a la aplicación */
  const int argc;
  /** Los argumentos pasados a la aplicación */
  const char **argv;
  /** La interfaz general de la aplicación */
  Vista *vista;
  /** La interfaz del servidor */
  Vista_Servidor *vista_servidor;
  /** La interfaz del cliente */
  Vista_Cliente *vista_cliente;
  /** Hilos de ejecución para la vista del servidor
   y la ejecución principal de este. */
  std::thread h;
  /** Hilos de ejecución para el envío
   y la recrpción de mensajes del cliente. */
  std::thread rcv;
  /** Servidor de la aplicación */
  Servidor* servidor;
  /** Cliente de la aplicación */
  Cliente* cliente;
  /** Nombre asociado al cliente */
  std::string client_name;
  
 public:
  
  /**
   * Elimina el constructor copia de la clase.
   *
   */
  Chat(Chat &other) = delete;

  /**
   * Elimina el operador de asignación.
   *
   */
  void operator=(const Chat &) = delete;

  /**
   * Devuelve la única instancia de la aplicación.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   * @return La única instancia de la aplicación
   *
   */
  static Chat *get_instance(const int argc, const char **argv) {
    if (chat == nullptr) {
      chat = new Chat(argc, argv);
    }
  
    return chat;
  }

  /**
   * Devuelve la única instancia de la aplicación.
   * @return La única instancia de la aplicación
   *
   */
  static Chat *get_instance() {
    return chat;
  }

  /**
   * Devuelve el número de argumentos pasados a la
   * aplicación.
   * @return El número de argumentos pasados a la
   * aplicación
   *
   */
  const int& get_argc();

  /**
   * Devuelve los argumentos pasados a la aplicación.
   * @return Los argumentos pasados a la aplicación
   *
   */
  char** get_argv();

  /**
   * Devuelve el hilo de ejecución de la ejecución principal
   * del servidor.
   * @return El hilo de ejecución de la ejecución principal
   * del servidor.
   *
   */   
  std::thread get_thread_h();

  /**
   * Devuelve el hilo de ejecución de recepción de mensajes
   * del cliente.
   * @return El hilo de ejecución de recepción de mensajes
   * del cliente.
   *
   */   
  std::thread get_thread_rcv();

  /**
   * Devuelve el servidor de la aplicación.
   * @return El servidor de la aplicación.
   *
   */
  Servidor* get_servidor();

  /**
   * Devuelve el cliente de la aplicación.
   * @return El cliente de la aplicación.
   *
   */
  Cliente* get_cliente();
  
  /**
   * Define la interfaz general de la aplicación.
   * @param vista La interfaz general de la aplicación
   *
   */
  void set_vista(Vista* vista);

  /**	       
   * Define la interfaz del servidor.
   * @param vista La interfaz del servidor.
   *
   */
  void set_vista_servidor(Vista_Servidor* vista);

  /**	       
   * Define la interfaz del cliente.
   * @param vista La interfaz del cliente.
   *
   */
  void set_vista_cliente(Vista_Cliente* vista);
  
  /**
   * Devuelve la interfaz general de la aplicación.
   * @return La interfaz general de la aplicación.
   *
   */
  Vista* get_vista();

  /**
   * Devuelve la interfaz del servidor.
   * @return La interfaz del servidor.
   *
   */
  Vista_Servidor* get_vista_servidor();

  /**
   * Devuelve la interfaz del cliente.
   * @return La interfaz del cliente.
   *
   */
  Vista_Cliente* get_vista_cliente();

  /**
   * Inicia la aplicación.
   * @return 0, si la ejecución terminó correctamente
   */
  int inicio();

  /**
   * Inicia el servidor.
   * @return 0, si la ejecución terminó correctamente
   */  
  int inicia_servidor(int puerto);

  /**
   * Hace que el servidor espere indefinidamente las
   * solicitudes de conexión.
   */  
  void ejecuta_servidor();

  /**
   * Cierra el socket del servidor y termina los hilos
   * creados por el mismo.
   *
   */
  void termina_servidor();
  
  /**
   * Inicia el cliente.
   * @return 0, si la ejecución terminó correctamente;
   * -1, en otro caso.
   */  
  int inicia_cliente(int puerto, const char * ip);

  /**
   * Envía un mensaje público desde el cliente.
   * @param message El mensaje a enviar.
   *
   */
  void cliente_envia_mensaje_publico(std::string message);
  
  /**
   * Asegura que el cliente creado sea una instancia
   * válida.
   * @param cliente El cliente a validar
   * @return true, si el cliente recibido es válido;
   * false, en otro caso
   *
   */
  bool valida_cliente(Cliente* cliente);
  
};

#endif
