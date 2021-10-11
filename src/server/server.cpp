#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <fstream>
#include <Ws2tcpip.h>
#include <vector>
#include <WinSock2.h>
#include "tcpsoc.h"
#include "soc.h"

#pragma comment(lib, "ws2_32.lib")




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              server.cpp/server.h                                               //             //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
	if (!Sockets::Start())
	{
		std::cout << "Erreur initialisation WinSock : " << Sockets::GetError();
		return -1;
	}

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket : " << Sockets::GetError();
		return -2;
	}

	const unsigned short port = 6666;
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int res = bind(server, (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
	{
		std::cout << "Erreur bind : " << Sockets::GetError();
		return -3;
	}

	res = listen(server, SOMAXCONN);
	if (res != 0)
	{
		std::cout << "Erreur listen : " << Sockets::GetError();
		return -4;
	}

	std::cout << "Serveur demarre sur le port " << port << std::endl;

	for (;;)
	{
		sockaddr_in from = { 0 };
		socklen_t addrlen = sizeof(from);
		SOCKET newClient = accept(server, (SOCKADDR*)(&from), &addrlen);
		if (newClient != INVALID_SOCKET)
		{
			std::thread([newClient, from]() {
				const std::string clientAddress = Sockets::GetAddress(from);
				const unsigned short clientPort = ntohs(from.sin_port);
				std::cout << "Connexion de " << clientAddress.c_str() << ":" << clientPort << std::endl;
				bool connected = true;
				for (;;)
				{
					char buffer[200] = { 0 };
					int ret = recv(newClient, buffer, 199, 0);
					if (ret == 0 || ret == SOCKET_ERROR)
						break;
					std::cout << "[" << clientAddress << ":" << clientPort << "]" << buffer << std::endl;
					ret = send(newClient, buffer, ret, 0);
					if (ret == 0 || ret == SOCKET_ERROR)
						break;
				}
				std::cout << "Deconnexion de [" << clientAddress << ":" << clientPort << "]" << std::endl;
				}).detach();
		}
		else
			break;
	}

	Sockets::CloseSocket(server);
	Sockets::Release();
	return 0;
}