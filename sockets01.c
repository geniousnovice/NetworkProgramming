#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	WSADATA windowsSocketsAPIData;
	
	// Start socket programming
	if (WSAStartup(MAKEWORD(2, 2), &windowsSocketsAPIData) != 0)
	{
		printf("STATE = FAILURE from WSAStartup() : %d", WSAGetLastError());
		return 1;
	}

	printf("STATE : SUCCESS from WSAStartup()");

	// Finish socket programming
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from WSACleanup() : %d", WSAGetLastError());
		return 1;
	}
}
