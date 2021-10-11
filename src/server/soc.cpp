#include "soc.h"
#pragma comment(lib, "Ws2_32.lib")


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              soc.cpp/soc.h                                                     //             //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////




namespace Sockets
{
	bool Start()
	{
#ifdef _WIN32
		WSAData wsaData;
		return WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
#else
		return true;
#endif
	}
	void Release()
	{
#ifdef _WIN32
		WSACleanup();
#endif
	}
	int GetError()
	{
#ifdef _WIN32
		return WSAGetLastError();
#else
		return errno;
#endif
	}
	bool CloseSocket(SOCKET s)
	{
#ifdef _WIN32
		closesocket(s);
#else
		close(s);
#endif
		return true;
	}
	std::string GetAddress(const sockaddr_in& addr)
	{
		char buff[INET6_ADDRSTRLEN] = { 0 };
		return inet_ntop(addr.sin_family, (void*)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
	}
}
