#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP
#pragma once

#include "soc.h"
#pragma comment(lib, "Ws2_32.lib")
#include <string>

class TCPSocket
{
public:
	TCPSocket();
	~TCPSocket();

	bool Connect(const std::string& ipaddress, unsigned short port);

	bool Send(const unsigned char* data, unsigned short len);
	bool Receive(std::vector<unsigned char>& buffer);

private:
	SOCKET mSocket;
};

#endif