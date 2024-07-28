/*
0 = Black
1 = Blue
2 = Green
3 = Aqua
4 = Red
5 = Purple
6 = Yellow
7 = White
8 = Gray
9 = Light Blue
10 = Light Green
11 = Light Aqua
12 = Light Red
13 = Light Purple
14 = Light Yellow
15 = Bright White
*/
#include <iostream>
#include <Windows.h>

using namespace std;

void setColor(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
}

int main() {
	for (int i = 0; i < 10; i++) {
		cout << i << endl;
		if (i == 5) {
			setColor(5);
		}
		else {
			setColor(7);
		}
	}
	return 0;
}
