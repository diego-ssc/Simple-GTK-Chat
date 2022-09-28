#include <stdio.h>
#include "controlador/inc/Chat.h"
#include <strings.h>


int main(int argc, char **argv) {
    if(argc != 4) {
      printf("Uso:\n");
      printf("./proyecto1 Servidor Puerto\n");
      printf("./proyecto1 Cliente Puerto\n");
      return 1;
    }

    Chat* chat = chat->get_instancia(argc, (const char **)argv);
    int ejecutable;

    
    
    if (strcasecmp(argv[1], "Servidor") == 0)
      ejecutable = 0;
    else
      ejecutable = 1;
      
    int status = chat->inicio(ejecutable,  atoi(argv[2]), argv[3]);
    

    return status;
}
