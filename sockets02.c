#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	WSADATA windowsSocketsAPIData;
	SOCKET socketA;

	// Start socket programming
	if (WSAStartup(MAKEWORD(2, 2), &windowsSocketsAPIData) != 0)
	{
		printf("STATE = FAILURE from WSAStartup() : %d", WSAGetLastError());
	}
	printf("STATE : SUCCESS from WSAStartup()");

	// Create a socket
	socketA = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socketA == INVALID_SOCKET)
	{
		printf("STATE = FAILURE from socket() : %d", WSAGetLastError());
	}
	printf("STATE : SUCCESS from socket()");

	// Close the server socket
	if (closesocket(socketA) == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from closesocket() : %d", WSAGetLastError());
	}
	printf("STATE : SUCCESS from closesocket()");

	// Finish socket programming
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from WSACleanup() : %d", WSAGetLastError());
	}
}
