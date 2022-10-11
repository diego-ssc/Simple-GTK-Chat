#include <string.h>
#include <iostream>
#include "controlador/inc/Chat.h"
#include <strings.h>

void uso() {
  std::cerr << "Uso" << std::endl;
  std::cerr << "./proyecto1 Servidor Puerto" << std::endl;
  std::cerr << "./proyecto1 Cliente Puerto Ip" << std::endl;
  exit(1);
}

int main(int argc, char **argv) {
  // if (argc < 2)
  //   uso();
  
  // int ejecutable;
  
  // if (strcasecmp(argv[1], "Servidor") == 0)
  //   ejecutable = 0;
  // else
  //   ejecutable = 1;

  // if (ejecutable == 0 && argc != 3)
  //   uso();
  
  // if (ejecutable == 1 && argc != 4)
  //   uso();
		   
  Chat* chat = chat->get_instance(argc, (const char **)argv);
  int status = chat->inicio();

  return status;
}
