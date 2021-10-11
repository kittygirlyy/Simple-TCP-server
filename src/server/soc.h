#ifdef _WIN32
#if _MSC_VER >= 1800
#include <WS2tcpip.h>
#include <vector>
#else
#define inet_pton(FAMILY, IP, PTR_STRUCT_SOCKADDR) (*(PTR_STRUCT_SOCKADDR)) = inet_addr((IP))
typedef int socklen_t;
#endif
#include <WinSock2.h>
#include <thread>
#include <mutex>
#include <string>
#ifdef _MSC_VER
#if _WIN32_WINNT >= _WIN32_WINNT_WINBLUE

#pragma comment(lib, "Ws2_32.lib")
#else
#pragma comment(lib, "wsock32.lib")
#endif
#endif
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>
#define SOCKET int
#define INVALID_SOCKET ((int)-1)
#endif

namespace Sockets
{
	bool Start();
	void Release();
	int GetError();
	bool CloseSocket(SOCKET socket);
	std::string GetAddress(const sockaddr_in& addr);
}
