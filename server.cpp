#include <iostream>
#include <WinSock2.h>

#define PORT 8080
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	cout << "SERVER" << endl;
	WSADATA wsa;
	// WINSOCK 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "Failed WSAStartup : " << WSAGetLastError() << endl;
		return 1;
	}
	else {
		cerr << "1. Successfully" << endl;
	}

	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		cerr << "Failed to create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else {
		cerr << "2. Successfully" << endl;
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT); 

	if (bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		cerr << "Failed to bind the socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else {
		cerr << "3. Successfully" << endl;
	}

	if (listen(serverSocket, 2) != 0) {
		cerr << "Failed to listen on socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else {
		cerr << "4. Successfully" << endl;
	}

	int addrLen = sizeof(addr);
	SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&addr, &addrLen);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "Failed to accept connection : " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 1;
	}
	else {
		cerr << "5. Successfully" << endl;
	}
	
	char buf[1024];
	int recvd = recv(clientSocket, buf, sizeof(buf), 0);
	if (recvd < 0) {
		cerr << "Failed to receive data : " << WSAGetLastError() << endl;
	}
	else if (recvd == 0) {
		cerr << "Connetion closed by client" << endl;
	}
	else if(recvd > 0 && recvd < sizeof(buf)) {
		buf[recvd] = '\0';
		cout << "Received : " << buf << endl;
	}

	const char* message = "Welcome to choi's server!";
	int sendd = send(clientSocket, message, strlen(message), 0);
	if (sendd < 0) {
		cerr << "Failed to send data : " << WSAGetLastError() << endl;
	}
	else if (sendd == 0) {
		cerr << "Connetion closed by client" << endl;
	}
	else if(sendd > 0) {
			cout << "sent : " << message << endl;
	}
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
