#include "Client.h"
#include <stdio.h>

struct Client
{
    TCPsocket socket;
    Uint32 ip;
    Uint16 port;
};

Client* Client_create(TCPsocket socket)
{
    Client* self = malloc(sizeof(Client));
    self->socket = socket;

    IPaddress* client_ip = SDLNet_TCP_GetPeerAddress(socket);
    self->ip = SDLNet_Read32(&client_ip->host);
    self->port = SDLNet_Read16(&client_ip->port);

    return self;
}

void Client_destroy(Client** client)
{
    Client* self = (*client);
    if(self)
    {
        if(self->socket)
        {
            SDLNet_TCP_Close(self->socket);
        }
        free(self);
    }
    *client = NULL;
}

void Client_print(const Client* self)
{
    printf("%d.%d.%d.%d:%u",
        (self->ip & 0xFF000000) >> 24,
        (self->ip & 0x00FF0000) >> 16,
        (self->ip & 0x0000FF00) >> 8,
        (self->ip & 0x000000FF),
        self->port
    );
}

Uint16 Client_get_port(const Client* self)
{
    return self->port;
}

Uint32 Client_get_ip(const Client* self)
{
    return self->ip;
}

TCPsocket Client_get_socket(const Client* self)
{
    return self->socket;
}
