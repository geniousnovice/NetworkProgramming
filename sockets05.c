#pragma comment(lib, "ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>

int main(int argc, char* argv[])
{
	WSADATA windowsSocketsAPIData;
	SOCKET serverSocket;
	SOCKET clientSocket;
	struct sockaddr_in serverSocketInformation;
	struct sockaddr_in clientSocketInformation;
	int clientSocketInformationSize;
	char message[100] = "";

	// Start socket programming
	if (WSAStartup(MAKEWORD(2, 2), &windowsSocketsAPIData) != 0)
	{
		printf("STATE = FAILURE from WSAStartup() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from WSAStartup()\n");

	// Create a server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		printf("STATE = FAILURE from socket() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from socket()\n");

	// Define a server socket information
	memset(&serverSocketInformation, 0, sizeof(serverSocketInformation));
	serverSocketInformation.sin_family = AF_INET;
	serverSocketInformation.sin_port = htons(1234);
	serverSocketInformation.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind the server socket with the server socket information
	if (bind(serverSocket, (SOCKADDR *)&serverSocketInformation, sizeof(serverSocketInformation)) == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from bind() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from bind()\n");

	// Make the server listen
	if (listen(serverSocket, 5) == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from listen() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from listen()\n");

	// Make the server socket accept a client socket
	clientSocketInformationSize = sizeof(clientSocketInformation);
	while (clientSocket = accept(serverSocket, (SOCKADDR*)&clientSocketInformation, &clientSocketInformationSize))
	{
		if (clientSocket == INVALID_SOCKET)
		{
			printf("STATE = FAILURE from accept() : %d\n", WSAGetLastError());
			return 1;
		}
		printf("STATE : SUCCESS from accept()\n"); // 여기까지 왔군.

		// Make the server socket receive a message from the client socket
		while (recv(clientSocket, message, sizeof(message) - 1, 0) != SOCKET_ERROR)
		{
			printf("STATE : SUCCESS from recv()\n");
			printf("Mesage from the server socket: %s\n", message);

			// Make the server socket send a message to the client socket
			if (send(clientSocket, message, (int)strlen(message), 0) == SOCKET_ERROR)
			{
				printf("STATE = FAILURE from send() : %d\n", WSAGetLastError());
				return 1;
			}
			printf("STATE : SUCCESS from send()\n");
		}
		printf("STATE = FAILURE from recv() : %d\n", WSAGetLastError());
		return 1;


	}

	// Close the client socket
	if (closesocket(clientSocket) == SOCKET_ERROR)
	{
		printf("STATE = FAILURE from closesocket() : %d\n", WSAGetLastError());
		return 1;
	}
	printf("STATE : SUCCESS from closesocket()\n");

	// Close the server socket
	if (closesocket(serverSocket) == SOCKET_ERROR)
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
