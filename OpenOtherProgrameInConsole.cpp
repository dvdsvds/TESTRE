#include <iostream>
#include <cstdlib>  // system 함수 사용을 위해 필요
#include <windows.h>
#include <string>

using namespace std;

int main() {
    std::wcout << L"Current console program running..." << std::endl;
  
    const wchar_t* programPath = L"C:\\Users\\source\\repos\\Test\\x64\\Release\\TEST.exe";

    std::wstring commandLine = L"cmd.exe /C start \"\" \"" + std::wstring(programPath) + L"\"";

    // STARTUPINFO 구조체 초기화
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);

    // PROCESS_INFORMATION 구조체 초기화
    PROCESS_INFORMATION pi;
    ZeroMemory(&pi, sizeof(pi));

    // CreateProcess 함수 호출
    if (CreateProcess(
        NULL,            // 애플리케이션 이름
        const_cast<wchar_t*>(commandLine.c_str()), // 명령줄 문자열
        NULL,            // 프로세스 보안 속성
        NULL,            // 스레드 보안 속성
        FALSE,           // 자식 프로세스가 핸들을 상속받지 않음
        CREATE_NEW_CONSOLE, // 새로운 콘솔 창 생성
        NULL,            // 새로운 환경 변수
        NULL,            // 현재 디렉터리
        &si,             // STARTUPINFO 포인터
        &pi              // PROCESS_INFORMATION 포인터
    )) {
        std::wcout << L"Another console program has been launched." << std::endl;
        // 프로세스와 스레드 핸들을 닫음.
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else {
        std::wcerr << L"Failed to launch another console program. Error: " << GetLastError() << std::endl;
    }

    return 0;
}
