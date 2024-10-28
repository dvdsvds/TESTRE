#include <iostream>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#endif
#define ADDRESS "127.0.0.1"
#define PORT 8080
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	cout << "SERVER" << endl;
#ifdef _WIN32
	WSADATA wsa;
	// WINSOCK 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) == -1) {
		cerr << "WSAstartup failed : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	else {
		cout << "WSAStartup was successful" << endl;
	}
#endif

	int serverSocket, clientSocket;
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024] = { 0 };

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		cerr << "Failed to create socket : " << WSAGetLastError() << endl;
		return -1;
	}
	else {
		cout << "Creating the socket was Successful." << endl;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT); 

	if (inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
		cerr << "Wrong address" << endl;
		return -1;
	}

	if (bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		cerr << "Failed to bind the socket : " << WSAGetLastError() << endl;
		return -1;
	}
	else {
		cerr << "Binding the socket was Successful." << endl;
	}

	if (listen(serverSocket, 2) < 0) {
		cerr << "Failed to listen on socket : " << WSAGetLastError() << endl;
		return -1;
	}
	else {
		cerr << "Listening was Successful." << endl;
	}

	cout << "Waiting client...." << endl;

	int addrLen = sizeof(client_addr);
	clientSocket = accept(serverSocket, (struct sockaddr*)&client_addr, &addrLen);
	if (clientSocket < 0) {
		cerr << "Failed to accept connection : " << WSAGetLastError() << endl;
		return -1;
	}
	else {
		cerr << "5. Successfully" << endl;
	}
	
	recv(clientSocket, buffer, sizeof(buffer), 0);
	cout << "Receved to client : " << buffer << endl;

	const char* message = "Welcome to choi's server!";
	send(clientSocket, message, strlen(message), 0);
	cout << "Sent to client" << message << endl;

#ifdef _WIN32
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
#endif
	return 0;
}
