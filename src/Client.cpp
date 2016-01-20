#include "Client.h"
#include <iostream>

Client::Client(TCPsocket socket)
{
    this->socket = socket;
    get_ip();
    get_port();
}

Client::~Client()
{
    SDLNet_TCP_Close(socket);
}

void Client::get_ip()
{
	IPaddress* client_ip = SDLNet_TCP_GetPeerAddress(socket);
	Uint32 ip = SDLNet_Read32(&client_ip->host);

	this->ip = std::to_string((ip & 0xFF000000) >> 24) + "." +
		       std::to_string((ip & 0x00FF0000) >> 16) + "." +
		       std::to_string((ip & 0x0000FF00) >> 8)  + "." +
		       std::to_string((ip & 0x000000FF));
}

void Client::get_port()
{
	IPaddress* client_ip = SDLNet_TCP_GetPeerAddress(socket);
	port = SDLNet_Read16(&client_ip->port);
}

void Client::print()
{
    std::cout << "Client: " << ip << ":" << port;
    std::cout.flush();
}

TCPsocket Client::get_socket()
{
    return socket;
}
