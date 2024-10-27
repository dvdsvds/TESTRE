#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define PORT 8080
#define ADDRESS "127.0.0.1"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	cout << "CLIENT" << endl;
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "Failed WSAStartup : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else {
		cout << "1. Successfully" << endl;
	}

	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		cerr << "Failed to create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return 1;
	}
	else {
		cout << "2. Successfully" << endl;
	}

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, ADDRESS, &addr.sin_addr) <= 0) {
		cerr << "Invalid address/ Address not supported : " << ADDRESS << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	int connected = connect(clientSocket, (SOCKADDR*)&addr, sizeof(addr));
	if (connected != 0) {
		cerr << "Failed connect to server : " << WSAGetLastError() << endl;
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}
	else {
		cout << "3. Successfully" << endl;
	}

	char buf[1024];
	int recvd = recv(clientSocket, buf, sizeof(buf) - 1, 0);
	if (recvd < 0) {
		cerr << "Failed to receive data : " << WSAGetLastError() << endl;
	}
	else if (recvd == 0) {
		cerr << "Connetion closed by server" << endl;
	}
	else if (recvd > 0 && recvd < sizeof(buf)) {
		buf[recvd] = '\0';
		cout << "Received : " << buf << endl;
	}

	const char* message = "Hi, I'm choi's client";
	int sendd = send(clientSocket, message, strlen(message), 0);
	if (sendd < 0) {
		cerr << "Failed to send data : " << WSAGetLastError() << endl;
	}
	else if (sendd == 0) {
		cerr << "Connetion closed by server" << endl;
	}
	else if (sendd > 0) {
		cout << "sent : " << message << endl;
	}

	closesocket(clientSocket);
	WSACleanup();

	return 0;
}
