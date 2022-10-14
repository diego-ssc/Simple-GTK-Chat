#ifndef PROTOCOLO_H_
#define PROTOCOLO_H_

/** Mensajes que reciben el servidor
    y el cliente */
enum Protocolo {
  /** Mensajes de error, advertencia e información. */
  ERROR, WARNING, INFO,

  /** Mensajes que recibe el cliente */
  NEW_USER, NEW_STATUS, USER_LIST, MESSAGE_FROM, PUBLIC_MESSAGE_FROM, JOINED_ROOM,
  ROOM_USER_LIST, ROOM_MESSAGE_FROM, LEFT_ROOM, DISCONNECTED, INVITATION,

  /** Mensajes que recibe el servidor */
  IDENTIFY, STATUS, USERS, MESSAGE, PUBLIC_MESSAGE,
  NEW_ROOM, INVITE, JOIN_ROOM, ROOM_USERS, ROOM_MESSAGE,
  LEAVE_ROOM, DISCONNECT
  
};

#endif
