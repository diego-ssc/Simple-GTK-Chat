#ifndef VISTA_CLIENTE_H
#define VISTA_CLIENTE_H

#include <gtk/gtk.h>
#include <stdio.h>
#include "../../controlador/inc/Chat.h"

class Vista_Cliente {
  /** La ventana de bienvenida del cliente */
  GtkWidget *welcome;
  /** La ventana principal del cliente */
  GtkWidget *window;
  /** Administador de xml generado para la interfaz */
  GtkBuilder *builder;
  /** Variable para errores ocurridos al inicializar la interfaz */
  GError * err = NULL;
  /** Objeto de registro de ip */
  GtkEntry *ip;
  /** Objeto de registro de puerto */
  GtkEntry *port;
  /** Objeto de registro de mensajes */
  GtkEntry *message_box;
  /** Objeto de registro de nombre de sala */
  GtkEntry *room_creation_entry;
  /** Objeto de registro de nombre de usuario */
  GtkEntry *name_entry;
  /** Botón de envío de información para la ventana de bienvenida */
  GtkButton *welcome_button;
  /** La lista de usuarios mostrada en cada sala */
  GtkWidget *user_list;
  /** El contenedor de la lista de usuarios mostrada en cada sala */
  GtkWidget *user_list_container;
  /** Ventana de creación de sala */
  GtkWidget *room_dialog;
  /** Ventana de creación de sala */
  GtkWidget *name_dialog;
  /** IP registrada por el usuario */
  const char* ip_data;
  /** Puerto registrada por el usuario */
  const char* port_data;
  /** Nombre de la sala a crear */
  std::string room_name;
  /** Nombre del usuario */
  std::string username;
  /** Única instancia de la interfaz del cliente*/
  static Vista_Cliente* vista_cliente;
  /** El widget de registro de mensajes */
  GtkWidget *text_box;
  
  /**
   * Constructor de la clase Vista_Cliente.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   *
   */
  Vista_Cliente(int argc, char ** argv);

  /**
   * Método auxiliar que define la ventanas de error para la
   * interfaz del cliente.
   * @param error_message El mensaje de error.
   * @param parent La ventana padre.
   *
   */
  void window_error(const char * error_message, GtkWidget* parent);

  /**
   * Método auxiliar que define la ventanas de advertencia para la
   * interfaz del cliente.
   * @param error_message El mensaje de advertencia.
   * @param parent La ventana padre.
   *
   */
  void window_warning(const char * warning_message, GtkWidget* parent);

  /**
   * Método auxiliar que define la ventanas de información para la
   * interfaz del cliente.
   * @param error_message El mensaje de información.
   * @param parent La ventana padre.
   *
   */
  void window_info(const char * info_message, GtkWidget* parent);
  
public:

  /**
   * Elimina el constructor copia de la clase.
   *
   */
  Vista_Cliente(Vista_Cliente &other) = delete;

  /**
   * Elimina el operador de asignación.
   *
   */
  void operator=(const Vista_Cliente &) = delete;

  /**
   * Devuelve la única instancia de la vista del cliente.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   * @return La única instancia de la vista del cliente
   *
   */
  static Vista_Cliente *get_instance(int argc, char **argv) {
    if (vista_cliente == nullptr) {
      vista_cliente = new Vista_Cliente(argc, argv);
    }
  
    return vista_cliente;
  }

  /**
   * Devuelve la única instancia de la vista del cliente.
   * @return La única instancia de la vista del cliente
   *
   */
  static Vista_Cliente *get_instance() {    
    return vista_cliente;
  }
  
  /**
   * Define el ip del cliente.
   * @param ip_data El IP al que se conectará el cliente
   *
   */
  void set_ip_data(const char* ip_data);

  /**
   * Define el puerto del cliente.
   * @param port_data El puerto al que se conectará el cliente
   *
   */
  void set_port_data(const char* port_data);

  /**
   * Define el nombre de sala registrado del cliente.
   * @param room_name El nombre de sala 
   *
   */  
  void set_room_name(std::string room_name);

  /**
   * Define el nombre del usuario conectado.
   * @param username El nombre del usuario 
   *
   */  
  void set_username(std::string username);
  
  /**
   * Define la lista de usuarios del cliente.
   * @param user_list La lista de usuarios
   *
   */  
  void set_user_list(std::list<std::string> user_list);
  
  /**
   * Devuelve el ip del cliente.
   * @return El IP del cliente
   *
   */
  const char* get_ip_data();

  /**
   * Devuelve el puerto del cliente.
   * @return El puerto del cliente
   *
   */
  const char* get_port_data();

  /**
   * Devuelve el nombre de sala registrado del cliente.
   * @return El nombre de sala
   *
   */ 
  std::string get_room_name();

  /**
   * Devuelve el nombre del usuario registrado.
   * @return El nombre de usuario registrado
   *
   */ 
  std::string get_username();
  
  /**
   * Devuelve el objeto que registró el IP del cliente.
   * @return El objeto que registró el IP del cliente
   *
   */
  GtkEntry* get_ip_entry();

  /**
   * Devuelve el objeto que registró el puerto del cliente.
   * @return El objeto que registró el puerto del cliente
   *
   */
  GtkEntry* get_port_entry();

  /**
   * Devuelve el objeto que registró el mensaje del cliente.
   * @return El objeto que registró el mensaje del cliente
   *
   */
  GtkEntry* get_message_entry();

  /**
   * Devuelve el objeto que guarda el nombre de la sala a crear.
   * @return El objeto que registró el nombre de la sala
   * a crear
   *
   */
  GtkEntry* get_room_creation_entry();

  /**
   * Devuelve el objeto que guarda el nombre usuario.
   * @return El objeto que registró el nombre de usuario.
   *
   */
  GtkEntry* get_name_entry();

  /**
   * Devuelve el objeto que registró la lista de usuarios.
   * @return El objeto que registró la lista de usuarios
   *
   */
  GtkWidget* get_user_list();

  /**
   * Devuelve el objeto contenedor de la lista de usuarios.
   * @return El objeto que contenedor de la lista de usuarios
   *
   */
  GtkWidget* get_user_list_container();
  
  /**
   * Devuelve el widget de la ventana de bienvenida.
   * @return El widget de la ventana de bienvenida
   *
   */
  GtkWidget * get_welcome_widget();

  /**
   * Devuelve el widget de la ventana del cliente.
   * @return El widget de la ventana del cliente
   *
   */
  GtkWidget * get_client_widget();

  /**
   * Devuelve el widget de la ventana de creación
   * de salas.
   * @return El widget de la ventana de creación
   * de salas
   *
   */
  GtkWidget * get_room_dialog();

  /**
   * Devuelve el widget de la ventana de registro
   * de nombre de usuario.
   * @return El widget de la ventana de registro
   * de nombre de usuario
   *
   */
  GtkWidget * get_name_dialog();

  /**
   * Devuelve el widget de registro de mensajes.
   * @return El widget de registro de mensajes
   *
   */
  GtkWidget* get_text_box();
  
  /**
   * Muestra la ventana de bienvenida del cliente.
   *
   */
  void welcome_window();

  /**
   * Muestra la ventana de introducción del nombre
   * del usuario.
   *
   */
  void client_name_window();
  
  /**
   * Muestra la ventana principal del cliente.
   *
   */
  void client_window(Cliente* cliente);

  /**
   * Muestra una ventana de diálogo en caso de
   * que el puerto registrado no sea válido.
   *
   */
  void window_port_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que el IP registrado no sea válido.
   *
   */
  void window_ip_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que el host registrado no exista.
   *
   */
  void window_null_server_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que el socket no haya podido abrirse.
   *
   */
  void window_socket_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que el cliente no haya podido establecer
   * una conexión con el servidor.
   *
   */
  void window_connection_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que no se haya podido escribir los datos
   * al socket.
   *
   */
  void window_write_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que no se haya podido leer los datos
   * del socket anfitrión.
   *
   */
  void window_read_error();

  /**
   * Método auxiliar que define la ventana de introducción del
   * nombre de la sala que se desea crear.
   *
   */
  void window_room_creation();

};

#endif

