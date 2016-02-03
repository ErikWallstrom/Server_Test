#ifndef CLIENT_H
#define CLIENT_H

#include "../include/SDL2/SDL_net.h"
#include <stdbool.h>

#define TCP_ERROR        0
#define TCP_CONNECTED    1
#define TCP_DISCONNECTED 2
#define TCP_FULL         3
#define TCP_POSITION     4

typedef struct Client Client;

Client*     Client_create       (TCPsocket socket);
void        Client_destroy      (Client** client);

bool        Client_send_flag    (Client* self, Uint8 flag);
bool        Client_send_data    (Client* self, Uint8* data, int size);
Uint8       Client_recv_flag    (Client* self);
bool        Client_recv_data    (Client* self, Uint8* buffer, int size);

void        Client_print        (Client* self);
Uint16      Client_get_port     (Client* self);
Uint32      Client_get_ip       (Client* self);
TCPsocket   Client_get_socket   (Client* self);

#endif
