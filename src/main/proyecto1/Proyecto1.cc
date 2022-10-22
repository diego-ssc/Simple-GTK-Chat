#include <string.h>
#include <iostream>
#include "controlador/inc/Chat.h"
#include <strings.h>

int main(int argc, char **argv) {		   
  Chat* chat = chat->get_instance(argc, (const char **)argv);
  int status = chat->inicio();

  return status;
}
