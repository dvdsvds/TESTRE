#include <iostream>
#include <cstring>      // memset
#ifdef _WIN32           // Windows에서 Winsock 라이브러리 사용
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else                   // Unix 계열에서 POSIX 소켓 라이브러리 사용
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

int main() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

    int sock = 0;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // 소켓 생성
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "소켓 생성 실패" << std::endl;
        return -1;
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    // 서버 IP 주소 변환 및 할당
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        std::cerr << "잘못된 주소" << std::endl;
        return -1;
    }

    // 서버에 연결
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "서버 연결 실패" << std::endl;
        return -1;
    }

    // 서버로 데이터 전송
    const char *message = "안녕하세요, 서버!";
    send(sock, message, strlen(message), 0);
    std::cout << "서버로 전송: " << message << std::endl;

    // 서버로부터 데이터 수신
    recv(sock, buffer, sizeof(buffer), 0);  // read 대신 recv 사용
    std::cout << "서버로부터 수신: " << buffer << std::endl;

    // 소켓 종료
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif

    return 0;
}
