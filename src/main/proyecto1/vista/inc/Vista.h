#ifndef VISTA_H_
#define VISTA_H_

#include <gtk/gtk.h>
#include <stdio.h>

class Vista {
  /** La ventana principal de la aplicación */
  GtkWidget *window;
  /** Etiqueta que contiene el nombre de la apliación */
  GtkLabel *label;
  /** Administador de xml generado para la interfaz */
  GtkBuilder *builder;
  /** Variable para errores ocurridos al inicializar la interfaz */
  GError * err = NULL;
  /** Única instancia de clase Vista */
  static Vista* vista;
  
  /**
   * Constructor de la clase Vista.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   *
   */
  Vista(int argc, char ** argv);
  
public:
  /**
   * Elimina el constructor copia de la clase.
   *
   */
  Vista(Vista &other) = delete;

  /**
   * Elimina el operador de asignación.
   *
   */
  void operator=(const Vista &) = delete;

    /**
   * Devuelve la única instancia de la vista general.
   * @param argc El número de argumentos pasados a la aplicación
   * @param argv Los argumentos pasados a la aplicación
   * @return La única instancia de la vista general
   *
   */
  static Vista *get_instance(int argc, char **argv) {
    if (vista == nullptr) {
      vista = new Vista(argc, argv);
    }
  		 
    return vista;
  }

  /**
   * Devuelve la única instancia de la vista general.
   * @return La única instancia de la vista general
   *
   */
  static Vista *get_instance() {    
    return vista;
  }

  /**
   * Devuelve la ventana principal de la aplicación.
   * @return La ventana principal de la aplicación.
   *
   */
  GtkWidget* get_window();
  
  /**
   * Muestra la ventana principal de la aplicación.
   *
   */
  void main_window();

};

#endif
