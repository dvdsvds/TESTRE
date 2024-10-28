#include <iostream>
#include <cstring> // strlen
#include <cstdlib> // exit
#include <unistd.h> // close
#include <arpa/inet.h> // inet_pton, sockaddr_in
#include <sys/socket.h> // socket

#define PORT 8080
#define ADDRESS "127.0.0.1"

using namespace std;

int main() {
    cout << "CLIENT" << endl;

    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = { 0 };

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Failed to create socket" << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Creating the socket was successful." << endl;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ADDRESS, &server_addr.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported : " << ADDRESS << endl;
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        cerr << "Failed to connect to server" << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Connecting to server was successful." << endl;
    }

    const char* message = "hi, server";
    send(sock, message, strlen(message), 0);
    cout << "Sent to server : " << message << endl;

    recv(sock, buffer, sizeof(buffer), 0);
    cout << "Received from server : " << buffer << endl;

    close(sock); // 소켓 닫기

    return 0;
}
