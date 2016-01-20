#ifndef CLIENT_H
#define CLIENT_H

#include "../include/SDL2/SDL_net.h"
#include <string>
class Client
{
private:
    TCPsocket socket;
    std::string ip;
    Uint16 port;

    void get_ip();
	void get_port();

public:
    Client(TCPsocket socket);
    ~Client();

    void print();
    TCPsocket get_socket();
};

#endif
