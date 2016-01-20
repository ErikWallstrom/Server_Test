#include "Server.h"
#include <iostream>

Server::Server(Uint16 port, Uint16 max_clients)
{
	if(SDL_Init(0)) throw SDL_GetError();
	if (SDLNet_Init()) throw SDLNet_GetError();

	if (SDLNet_ResolveHost(&server_ip, nullptr, port))
	{
		throw "Invalid port";
	}

	if(!(server_socket = SDLNet_TCP_Open(&server_ip)))
	{
		throw SDLNet_GetError();
	}

	if (!(socket_set = SDLNet_AllocSocketSet(max_clients + 1)))
	{
		throw SDLNet_GetError();
	}

	if (SDLNet_TCP_AddSocket(socket_set, server_socket) == -1)
	{
		throw SDLNet_GetError();
	}

	this->port = port;
	this->max_clients = max_clients;
}

Server::~Server()
{
	for(auto client : clients)
	{
		delete client;
	}

	SDLNet_FreeSocketSet(socket_set);
	SDLNet_TCP_Close(server_socket);
	SDLNet_Quit();
	SDL_Quit();
}

void Server::add_client(Client* client)
{
	Message msg = CONNECTED;
	if (SDLNet_TCP_Send(client->get_socket(), &msg, 1) == 1)
	{
		if (SDLNet_TCP_AddSocket(socket_set, client->get_socket()) == -1)
		{
			throw SDLNet_GetError();
		}

		client->print();
		std::cout << " connected" << std::endl;
		clients.push_back(client);
	}
}

void Server::remove_client(Client* client)
{
	client->print();
	std::cout << " disconnected" << std::endl;
	SDLNet_TCP_DelSocket(socket_set, client->get_socket());

	int counter = 0;
	for(auto c : clients)
	{
		if(&c == &client)
		{
			clients.erase(clients.begin() + counter);
			delete client;
			break;
		}

		counter++;
	}
}

void Server::handle_data(Client* client)
{
	char buffer[1024] = {0};
	if(SDLNet_TCP_Recv(client->get_socket(), buffer, 1024) < 1024)
	{
		remove_client(client);
	}

	client->print();
	std::cout <<  " says: " << buffer << std::endl;
}

int Server::start()
{
	std::cout << "\nListening on port " << port << "..." << std::endl;
	while (true)
	{
		int sockets_ready = SDLNet_CheckSockets(socket_set, 0);
		if (sockets_ready == -1)
		{
			throw SDLNet_GetError();
		}
		else if (sockets_ready > 0)
		{
			if (SDLNet_SocketReady(server_socket))
			{
				if (clients.size() < max_clients)
				{
					TCPsocket socket = SDLNet_TCP_Accept(server_socket);
					if (socket)
					{
						Client* client = new Client(socket);
						add_client(client);
					}
				}
				else
				{
					TCPsocket client = SDLNet_TCP_Accept(server_socket);
					if (client)
					{
						Message msg = FULL;
						SDLNet_TCP_Send(client, &msg, 1);
						SDLNet_TCP_Close(client);
					}
				}
			}

			for (auto client : clients)
			{
				if (SDLNet_SocketReady(client->get_socket()))
				{
					Message msg;
					if (SDLNet_TCP_Recv(client->get_socket(), &msg, 1) < 1)
					{
						remove_client(client);
					}
					else
					{
						if(msg == DATA)
						{
							handle_data(client);
						}
					}
				}
			}
		}
	}
}
