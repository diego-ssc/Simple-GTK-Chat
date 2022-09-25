#include "../../modelo/inc/Servidor.h"
#include "../../modelo/inc/Cliente.h"

class Chat {  

protected:
  Chat(const int argc, const char **argv) : argc(argc), argv(argv) {}
  static Chat* chat;
  const int argc;
  const char **argv;
  
 public:

  Chat(Chat &other) = delete;
  void operator=(const Chat &) = delete;
  static Chat *get_instancia(const int argc, const char **argv) {
    if (chat == nullptr) {
      chat = new Chat(argc, argv);
    }
  
    return chat;
  }
  void interfaz();
  void inicio();
  Servidor* inicia_servidor(int puerto);
  Cliente* inicia_cliente(int puerto, void *buffer); 
  
};

