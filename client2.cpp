#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define PORT 8080
#define ADDRESS "127.0.0.1"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
	cout << "CLIENT" << endl;
#ifdef _WIN32
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		cerr << "WSAstartup failed : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	else {
		cout << "WSAStartup was successful" << endl;
	}
#endif

	int sock = 0;
	struct sockaddr_in server_addr;
	char buffer[1024] = { 0 };

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		cerr << "Failed to create socket : " << WSAGetLastError() << endl;
		return -1;
	}
	else {
		cout << "Creating the socket was successful." << endl;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
		cerr << "Invalid address/ Address not supported : " << ADDRESS << endl;
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
		cerr << "Failed connect to server : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	else {
		cout << "connecting to server was successful." << endl;
	}

	const char* message = "hi, server";
	send(sock, message, strlen(message), 0);
	cout << "Sent to server : " << message << endl;

	recv(sock, buffer, sizeof(buffer), 0);
	cout << "Receved to server : " << buffer << endl;
	
#ifdef _WIN32
	closesocket(sock);
	WSACleanup();
#endif

	return 0;
}
