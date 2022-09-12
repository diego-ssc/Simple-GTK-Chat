#include "inc/Chat.h"
#include "inc/Controlador.h"

#include "../vista/inc/Vista.h"

int inicializaInterfaz(int argc, char **argv) {
return defineAplicacion(argc, argv);
}

int inicio(int argc, char **argv) {
  return inicializaInterfaz(argc, argv);
}
