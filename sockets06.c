#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main(int argc, char* argv[])
{
	WSADATA windowsSocketsAPIData;
	SOCKET clientSocket;
	struct sockaddr_in serverSocketInformation;
	char message[100] = "";

	// Check the command line arguments
	if (argc != 3)
	{
		printf("Usage : %s <IP> <PORT> \n", argv[0]);
		return 1;
	}
	printf("STATE : SUCCESS from command line check\n");

	// Start socket programming
	if (WSAStartup(MAKEWORD(2, 2), &windowsSocketsAPIData) != 0)
	{
		printf("STATE = FAILURE from WSAStartup() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from WSAStartup()\n");

	// Create a client socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		printf("STATE = FAILURE from socket() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from socket()\n");

	// Define a server socket information
	memset(&serverSocketInformation, 0, sizeof(serverSocketInformation));
	serverSocketInformation.sin_family = AF_INET;
	serverSocketInformation.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &serverSocketInformation.sin_addr.s_addr);

	// Make the client socket connect to the server socket
	if (connect(clientSocket, (SOCKADDR*)&serverSocketInformation, sizeof(serverSocketInformation)) == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from connect() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from connect()\n");

	while (1)
	{
		printf("Enter a message: ");
		fgets(message, 100, stdin);		
		// Make the client socket send a message to the server socket
		if (send(clientSocket, message, (int)strlen(message), 0) == SOCKET_ERROR)
		{
			printf("STATE = FAILURE from send() : %d\n", WSAGetLastError());
			return 1;
		}
		printf("STATE : SUCCESS from send()\n");

		// Make the client socket receive a message from the server socket
		if (recv(clientSocket, message, sizeof(message) - 1, 0) == SOCKET_ERROR)
		{
			printf("STATE = FAILURE from recv() : %d\n", WSAGetLastError());
			return 1;
		}
		printf("STATE : SUCCESS from recv()\n");
		printf("Mesage from the server socket: %s\n", message);
	}

	// Close the client socket
	if (closesocket(clientSocket) == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from closesocket() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from closesocket()\n");

	// Finish socket programming
	if (WSACleanup() == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from WSACleanup() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from WSACleanup()\n");
	return 0;
}
