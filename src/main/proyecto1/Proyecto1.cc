#include <stdio.h>
#include "controlador/inc/Chat.h"

int main(int argc, char **argv) {
    if(argc != 1) {
        printf("%s no recibe argumentos.\n", argv[0]);
        return 1;
    }

    Chat* chat = chat->get_instancia(argc, (const char **)argv);
    chat->inicio();
    

    return 0;
}
