#include "Server.h"
#include <iostream>
#undef main
int main()
{
	std::cout << "EW_AH Server V_1.0\n" << std::endl;

	Uint16 port = 0;
	std::cout << "Port: ";
	std::cout.flush();
	std::cin >> port;

	Uint16 max_clients;
	std::cout << "Max users: ";
	std::cout.flush();
	std::cin >> max_clients;

	int success_flag;
	try
	{
		Server server(port, max_clients);
		success_flag = !server.start();
	}
	catch (const char* msg)
	{
		std::cout << "Exception: " << msg << std::endl;
		return EXIT_FAILURE;
	}

	return success_flag;
}
