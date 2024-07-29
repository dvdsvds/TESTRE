#include <iostream>
#include <Windows.h>
#include <stdlib.h>

using namespace std;

void setColor(int color) {
	// Get the console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the text color
	SetConsoleTextAttribute(hConsole, color);
}

int main() {
	/*
	[00] [00] [00] [00] [00]

	[00] [00] [00] [00] [00]

	[00] [00] [00] [00] [00]

	[00] [00] [00] [00] [00]

	[00] [00] [00] [00] [00]
	*/

	/*
	int j = 1;
	for (int i = 0; i < 100; i++) {
		if (j < 10) {
			cout << " [00" << j << "]";
		}
		else if (j > 9 && j < 100) {
		    cout << " [0" << j << "]";
			if (j % 10 == 0) {
				cout << endl << endl;
			}
		}
		else {
			cout << " [" << j << "]";
			cout << endl;
		}
		j++;
		
	}
	*/

	int c;
	cin >> c;

	int a = 1;
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			if (a == c) {
				setColor(4);
			}
			else {
				setColor(2);
			}

			if (a < 10) {
				cout << "[0" << a <<  "] ";
			}
			else {
				cout << "[" << a <<  "] ";
			}
			a++;
			setColor(7);
			
		}
		cout << endl << endl;
	}

	system("pause");
	return 0;
}
