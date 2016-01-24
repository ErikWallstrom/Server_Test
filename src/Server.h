#ifndef SERVER_H
#define SERVER_H

#include "../include/SDL2/SDL_net.h"
#include <stdbool.h>

typedef struct Server Server;

Server* Server_create(Uint16 port, Uint16 max_clients);
void Server_destroy(Server** server);
bool Server_update(Server* self);

#endif
