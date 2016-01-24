#include "Server.h"
#include "Array.h"
#include "Client.h"
#include "../include/SDL2/SDL_net.h"
#include <stdio.h>

#define CONNECTED    1
#define DISCONNECTED 2
#define FULL         3
#define POSITION     4

struct Server
{
    IPaddress ip;
    TCPsocket socket;
    SDLNet_SocketSet socket_set;

    Array* clients;
    Uint16 port;
    Uint16 max_clients;
};

Server* Server_create(Uint16 port, Uint16 max_clients)
{
    Server* self = calloc(1, sizeof(Server));
    if(!self)
    {
        return NULL;
    }

    if(SDLNet_ResolveHost(&self->ip, NULL, port) ||
       !(self->socket = SDLNet_TCP_Open(&self->ip)) ||
       !(self->socket_set = SDLNet_AllocSocketSet(max_clients + 1)) ||
       SDLNet_TCP_AddSocket(self->socket_set, self->socket) == -1
    )
    {
        Server_destroy(&self);
        return NULL;
    }

    self->clients = Array_create();
    self->port = port;
    self->max_clients = max_clients;

    printf("\nListening on port %u...\n", self->port);
    return self;
}

void Server_destroy(Server** server)
{
    Server* self = (*server);
    if(self)
    {
        if(self->socket)
        {
            SDLNet_TCP_Close(self->socket);
        }

        if(self->socket_set)
        {
            SDLNet_FreeSocketSet(self->socket_set);
        }

        Array_destroy(&self->clients);
        free(self);
    }
}

bool Server_add_client(Server* self, Client* client)
{
    TCPsocket socket = Client_get_socket(client);
    Uint8 message = CONNECTED;
    if(SDLNet_TCP_Send(socket, &message, 1) == 1)
    {
        if(SDLNet_TCP_AddSocket(self->socket_set, socket) == -1)
        {
            return false;
        }
        Client_print(client);
        printf(" connected\n");
        Array_insert(self->clients, 0, client);
    }
    return true;
}

void Server_remove_client(Server* self, Client* client)
{
    Uint8 message = DISCONNECTED;

    Uint8 buffer[6] = {0};
    SDLNet_Write32(Client_get_ip(client), buffer);
    SDLNet_Write16(Client_get_port(client), buffer + 4);

    foreach(i, self->clients)
    {
        Client* c = Array_get(self->clients, i);
        if(c == client)
        {
            Array_remove(self->clients, i);
        }
        else
        {
            if(SDLNet_TCP_Send(
                Client_get_socket(c), &message, 1) < 1 ||
               SDLNet_TCP_Send(
                Client_get_socket(c), &buffer, 6) < 6)
            {
                Server_remove_client(self, c);
            }
        }
    }
    Client_print(client);
    printf(" disconnected\n");

    Client_destroy(&client);
}

void Server_handle_position(Server* self, Client* client)
{
    Uint8 buffer_rec[4] = {0};
    if(SDLNet_TCP_Recv(Client_get_socket(client), buffer_rec, 4) < 4)
	{
		Server_remove_client(self, client);
	}

    Uint8 message = POSITION;
    Uint8 buffer_send[10] = {0};
    memcpy(buffer_send, buffer_rec, 4);

    SDLNet_Write32(Client_get_ip(client), buffer_send + 4);
    SDLNet_Write16(Client_get_port(client), buffer_send + 8);

    foreach(i, self->clients)
    {
        Client* c = Array_get(self->clients, i);
        if(c != client)
        {
            if(SDLNet_TCP_Send(
                Client_get_socket(c), &message, 1) < 1 ||
               SDLNet_TCP_Send(
                Client_get_socket(c), &buffer_send, 10) < 10)
            {
                Server_remove_client(self, c);
            }
        }
    }
}

bool Server_update(Server* self)
{
    int sockets_ready = SDLNet_CheckSockets(self->socket_set, 0);
    if(sockets_ready == -1)
    {
        return false;
    }
    else if(sockets_ready > 0)
    {
        if(SDLNet_SocketReady(self->socket))
        {
            TCPsocket socket = SDLNet_TCP_Accept(self->socket);
            if(socket)
            {
                if(Array_size(self->clients) < self->max_clients)
                {
                    Client* client = Client_create(socket);
                    Server_add_client(self, client);
                }
                else
                {
                    Uint8 message = FULL;
                    SDLNet_TCP_Send(socket, &message, 1);
                    SDLNet_TCP_Close(socket);
                }
            }
        }

        foreach(i, self->clients)
        {
            Client* client = Array_get(self->clients, i);
            if (SDLNet_SocketReady(Client_get_socket(client)))
            {
                Uint8 message;
                if(SDLNet_TCP_Recv(
                    Client_get_socket(client), &message, 1
                  ) < 1
                )
                {
                    Server_remove_client(self, client);
                }
                else
                {
                    switch (message)
                    {
                    case DISCONNECTED:
                        Server_remove_client(self, client);
                    break;

                    case POSITION:
                        Server_handle_position(self, client);
                    break;

                    default:
                        Client_print(client);
                        printf(" sent an unknown message\n");
                    break;
                    }
                }
            }
        }
    }
    return true;
}