#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "soc.h"
#include <string>
#include <fstream>
#include <vector>
#include <Ws2tcpip.h>
#include <WinSock2.h>
#include "tcpsoc.h"
#include "env.h"

#pragma comment(lib, "Ws2_32.lib")


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              CLIENT.cpp/CLIENT.h                                               //             //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{


	const unsigned char buff[258] = "ceci est un test";

	std::vector<unsigned char> buf;

	std::cout <<"donnees envoyer: "<< buff << "\n";

	if (!Sockets::Start())
	{
		std::cout << "Erreur initialisation : " << Sockets::GetError() << std::endl;
		return 0;
	}

	{
		TCPSocket socket;
		if (!socket.Connect("127.0.0.1", 8989))
		{
			std::cout << "Erreur connection : " << Sockets::GetError() << std::endl;
			return 0;
		}
		std::cout << "Socket connecte !" << std::endl;
		

		socket.Send(buff, sizeof(buff));
		std::cout << "donnees envoyer avec succes\n";
		socket.Receive(buf);
		std::cout << "donnees recu: ";
		for (auto const& it : buf)
		{
			std::cout <<it;
		}

		std::cin.ignore();
		
	}
	Sockets::Release();
}

