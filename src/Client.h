#ifndef CLIENT_H
#define CLIENT_H

#include "../include/SDL2/SDL_net.h"
typedef struct Client Client;

Client*     Client_create     (TCPsocket socket);
void        Client_destroy    (Client** client);

void        Client_print      (const Client* self);
Uint16      Client_get_port   (const Client* self);
Uint32      Client_get_ip     (const Client* self);
TCPsocket   Client_get_socket (const Client* self);

#endif
