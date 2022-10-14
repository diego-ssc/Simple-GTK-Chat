#ifndef VISTA_SERVIDOR_H
#define VISTA_SERVIDOR_H

#include <gtk/gtk.h>
#include <stdio.h>
#include "../../controlador/inc/Chat.h"

class Vista_Servidor {
  /** La ventana de bienvenida del servidor */
  GtkWidget *welcome;
  /** La ventana principal del servidor */
  GtkWidget *window;
  /** El widget de registro de eventos */
  GtkWidget *text_box;
  /** Administador de xml generado para la interfaz */
  GtkBuilder *builder;
  /** Variable para errores ocurridos al inicializar la interfaz */
  GError * err = NULL;
  /** Objeto de registro de puerto */
  GtkEntry *port;
  /** Botón de envío de información para la ventana de bienvenida */
  GtkButton *welcome_button;
  /** La lista de usuarios mostrada en cada sala */
  GtkWidget *user_list;
  /** El contenedor de la lista de usuarios mostrada en cada sala */
  GtkWidget *user_list_container;
  /** Puerto registrada por el usuario */
  const char *port_data;
  /** Nombre de sala creada por cliente */
  const char *room_name;
  /** Única instancia de la interfaz del servidor */
  static Vista_Servidor* vista_servidor;
  
  /**
   * Constructor de la clase Vista_Servidor.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   *
   */
  Vista_Servidor(int argc, char ** argv);

  /**
   * Método auxiliar que define la ventanas de error para la
   * interfaz del servidor.
   * @param error_message El mensaje de error.
   * @param parent La ventana padre.
   *
   */
  void window_error(const char * error_message, GtkWidget* parent);

  /**
   * Método auxiliar que define la ventanas de advertencia para la
   * interfaz del servidor.
   * @param error_message El mensaje de advertencia.
   * @param parent La ventana padre.
   *
   */
  void window_warning(const char * warning_message, GtkWidget* parent);

  /**
   * Método auxiliar que define la ventanas de información para la
   * interfaz del servidor.
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
  Vista_Servidor(Vista_Servidor &other) = delete;

  /**
   * Elimina el operador de asignación.
   *
   */
  void operator=(const Vista_Servidor &) = delete;

  /**
   * Devuelve la única instancia de la vista del servidor.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   * @return La única instancia de la vista del servidor
   *
   */
  static Vista_Servidor *get_instance(int argc, char **argv) {
    if (vista_servidor == nullptr) {
      vista_servidor = new Vista_Servidor(argc, argv);
    }
  
    return vista_servidor;
  }

  /**
   * Devuelve la única instancia de la vista del servidor.
   * @return La única instancia de la vista del servidor
   *
   */
  static Vista_Servidor *get_instance() {    
    return vista_servidor;
  }

  /**
   * Define el puerto del servidor.
   * @param port_data El puerto al que se conectará al que se
   * enlazará el cliente
   *
   */
  void set_port_data(const char* port_data);

  /**
   * Define el nombre de sala registrado del cliente.
   * @param room_name El nombre de sala 
   *
   */  
  void set_room_name(const char* room_name);
  
  /**
   * Define la lista de usuarios del cliente.
   * @param user_list La lista de usuarios
   *
   */  
  void set_user_list(std::list<std::string> user_list);

  /**
   * Devuelve el puerto del servidor.
   * @return El puerto del servidor
   *
   */
  const char* get_port_data();

  /**
   * Devuelve el objeto que registró el puerto del servidor.
   * @return El objeto que registró el puerto del servidor
   *
   */
  GtkEntry* get_port_entry();

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
   * Devuelve el widget de la ventana del servidor.
   * @return El widget de la ventana del servidor
   *
   */
  GtkWidget * get_server_widget();

  /**
   * Devuelve el widget de registro de eventos.
   * @return El widget de registro de eventos.
   *
   */
  GtkWidget * get_text_box();
  
  /**
   * Muestra la ventana de bienvenida del servidor.
   *
   */
  void welcome_window();

  /**
   * Muestra la ventana principal del servidor.
   *
   */
  void server_window();

  /**
   * Muestra una ventana de diálogo en caso de
   * que el servidor no haya podido asociarse
   * al socket.
   *
   */ 
  void window_bind_error();

  /**
   * Muestra una ventana de diálogo en caso de
   * que el servidor no haya podido escuchar
   * a través del socket.
   *
   */ 
  void window_listen_error();

  /**
   * Muestra una ventana de diálogo en caso de
   * que el servidor no haya aceptar una conexión
   * a través del socket.
   *
   */  
  void window_accept_error();
  
  /**		      
   * Muestra una ventana de diálogo en caso de
   * que el socket no haya podido abrirse.
   *
   */
  void window_socket_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que no se haya podido escribir los datos
   * al socket.
   *
   */
  void window_send_error();

  /**		      
   * Muestra una ventana de diálogo en caso de
   * que no se haya podido leer los datos
   * del socket cliente.
   *
   */
  void window_read_error();

  /**
   * Muestra una ventana de diálogo en caso de
   * que se haya aceptado una conexión.
   * @param ip IP del cliente que se conecta.
   * @param puerto Puerto del cliente que se conecta.
   *
   */
  void servidor_accepted_message(int ip, int puerto);

};

#endif
