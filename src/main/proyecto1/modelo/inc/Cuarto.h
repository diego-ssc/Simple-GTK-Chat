#ifndef CUARTO_H_
#define CUARTO_H_

#include <unordered_map>
#include <map>
#include <list>
#include <iostream>
#include "Usuario.h"

class Cuarto {

  /**
   * Árbol binario ordenenado que guarda los usuarios
   * integrantes del cuarto, ordenándolos por nombre.
   */
  std::map<std::string, Usuario> users;

  /**
   * Diccionario que registra los usuarios que han sido
   * invitados al cuarto.
   */
  std::unordered_map<std::string, Usuario> invited_users;

  /** El identificador del cuarto */
  int id;
  /** El nombre del cuarto */
  std::string nombre;

  /**
   * Verifica que el usuario parámetro esté en el
   * cuarto.
   * @param nombre_usuario El nombre del usuario que
   * se buscará en el cuarto
   * @return true, si el usuario es integrante del cuarto;
   * false, en otro caso
   *
   */
  bool is_in(std::string nombre_usuario);

  /**
   * Verifica que el usuario parámetro esté en el
   * diccionario de invitados.
   * @param nombre_usuario El nombre del usuario que
   * se buscará en el diccionario
   * @return true, si el usuario es integrante del diccionario;
   * false, en otro caso
   *
   */
  bool is_invited(std::string nombre_usuario);
  
 public:

  /**
   * Método constructor de la clase
   * @param id El identificador del cuarto
   *
   */
  Cuarto(int id);

  /**
   * Devuelve el identidicador del cuarto.
   * @return El identificador del cuarto
   *
   */
  int get_id();

  /**
   * Devuelve el nombre del cuarto.
   * @return El nombre del cuarto
   */
  std::string get_nombre();  
  
  /**
   * Devuelve lo usuarios integrantes del cuarto.
   * @return La lista de los usuarios
   *
   */
  std::list<std::string> get_room_usernames();

  /**
   * Agrega a un usuario al cuarto, si este ha sido
   * invitado previamente
   * @param username El nombre del usuario a agregar
   * @return 0, si se ejecutó correctamente; -1, 
   * si el usuario ya se encuentra dentro del cuarto;
   * o -2 si este no fue invitado
   *
   */
  int add_member(std::string username, Usuario &&user);

  /**
   * Agrega a un usuario al diccionario de invitados
   * @param username El nombre del usuario a invitar
   * @return 0, si se ejecutó correctamente; -1, 
   * si el usuario ya se encuentra dentro del cuarto;
   * o -2 si este ya fue invitado
   *
   */
  int invite_member(std::string username, Usuario &&user);

  /**
   * Elimina a un usuario del cuarto
   * @param username El nombre del usuario a eliminar
   * @return 0, si se ejecutó correctamente; o -1, 
   * si el usuario no se encuentra dentro del cuarto
   *
   */  
  int eliminate_member(std::string username);

  /**
   * Destructor de la clase
   *
   */
  ~Cuarto();
  
  
};

#endif
