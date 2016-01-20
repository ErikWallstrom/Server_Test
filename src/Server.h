#ifndef SERVER_H
#define SERVER_H

#include "Client.h"
#include <vector>
class Server
{
private:
	enum Message : char
	{
		CONNECTED = 0,
		FULL,
		DATA
	};

	IPaddress server_ip;
	TCPsocket server_socket;
	SDLNet_SocketSet socket_set;

	std::vector<Client*> clients;

	Uint16 port;
	Uint16 max_clients;

	void add_client(Client* client);
	void remove_client(Client* client);
	void handle_data(Client* client);

public:

	Server(Uint16 port, Uint16 max_clients);
	~Server();

	int start();
};

#endif
