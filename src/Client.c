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

bool Client_send_flag(Client* self, Uint8 flag)
{
    if(SDLNet_TCP_Send(self->socket, &flag, 1) < 1)
    {
        return false;
    }
    return true;
}

bool Client_send_data(Client* self, Uint8* data, int size)
{
    if(SDLNet_TCP_Send(self->socket, data, size) < size)
    {
        return false;
    }
    return true;
}

Uint8 Client_recv_flag(Client* self)
{
    Uint8 flag;
    if(SDLNet_TCP_Recv(self->socket, &flag, 1) < 1)
    {
        return TCP_ERROR;
    }
    return flag;
}

bool Client_recv_data(Client* self, Uint8* buffer, int size)
{
    if(SDLNet_TCP_Recv(self->socket, buffer, size) < size)
    {
        return false;
    }
    return true;
}


void Client_print(Client* self)
{
    printf("%d.%d.%d.%d:%u",
        (self->ip & 0xFF000000) >> 24,
        (self->ip & 0x00FF0000) >> 16,
        (self->ip & 0x0000FF00) >> 8,
        (self->ip & 0x000000FF),
        self->port
    );
}

Uint16 Client_get_port(Client* self)
{
    return self->port;
}

Uint32 Client_get_ip(Client* self)
{
    return self->ip;
}

TCPsocket Client_get_socket(Client* self)
{
    return self->socket;
}
