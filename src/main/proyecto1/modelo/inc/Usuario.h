#ifndef USUARIO_H_
#define USUARIO_H_


#include <thread>
#include <mutex>

/**
 * Clase que abstrae los objetos cliente y procesador_cliente.
 * Simula el comportamiento de un usuario dentro de la aplicación.
 *
 */
class Usuario {

  /** El identificador del usuario */
  int id;
  /** El nombre del usuario */
  std::string nombre;
  /** El estado del usuario */  
  std::string estado;
  /** El socket asociado al usuario */  
  int socket;
  /** El hilo asociado al usuario */
  std::thread th;
  
 public:
  /** Constructor por omisión */
  Usuario();

  /** Eliminar el constructor copia */
  Usuario(const Usuario&) = delete;
  
  /** Eliminar el operador de asignación */
  Usuario& operator=(const Usuario&) = delete;

  Usuario(Usuario && user);

  Usuario & operator=(Usuario && user);
  
  
  /**
   * Método contructor de la clase Usuario.
   * @param id el identificador del usuario
   * @param nombre el nombre asociado al usuario
   * @param socket el socket asociado al usuario
   * @param th el hilo asociado al usuario
   *
   */
  Usuario(int id, std::string nombre,
	  int socket, std::thread th);

  /**
   * Método contructor de la clase Usuario.
   * @param id el identificador del usuario
   * @param socket el socket asociado al usuario
   *
   */  
  Usuario(int id, int socket);
  
  /**
   * Redefine el estado del usuario.
   * @param status El nuevo estado del usuario
   *
   */
  void set_thread(std::thread th);
  
  /**
   * Redefine el estado del usuario.
   * @param status El nuevo estado del usuario
   *
   */
  void set_status(std::string status);

  /**
   * Redefine el nombre del usuario.
   * @param status El nuevo nombre del usuario
   *
   */
  void set_name(std::string name);

  /**
   * Devuelve el identificador del usuario.
   * @return El identificador del usuario
   *
   */
  int get_id();

  /**
   * Devuelve el nombre del usuario.
   * @return El nombre del usuario
   *
   */  
  std::string get_nombre();

  /**
   * Devuelve el estado del usuario.
   * @return El estado del usuario
   *
   */  
  std::string get_estado();
  
  /**
   * Devuelve el socket del usuario.
   * @return El socket del usuario
   *
   */  
  int get_socket();

  /**
   * Devuelve el hilo del usuario.
   * @return El hilo del usuario
   *
   */  
  std::thread get_thread();
  
};

#endif
