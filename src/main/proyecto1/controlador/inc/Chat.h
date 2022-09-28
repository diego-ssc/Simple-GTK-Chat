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
  int inicio(int ejecutable, int puerto, const char * ip);
  int inicia_servidor(int puerto, const char * ip);
  int inicia_cliente(int puerto, const char * ip); 
};

