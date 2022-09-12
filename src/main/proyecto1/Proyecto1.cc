#include <stdio.h>
#include "controlador/inc/Chat.h"

int main(int argc, char **argv) {
    if(argc != 1) {
        printf("%s takes no arguments.\n", argv[0]);
        return 1;
    }

    int status = inicio(argc, argv);

    return status;
}
