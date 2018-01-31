#include<iostream>
#include <time.h>
#include "IDEA.h"
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
обработка сдвига влево: новый индекс + сдвиг*номер сдвига % размера = старый индекс
корреляция = 1/N SUM( (2xi-1)(2yi-1) ) ~ 0
*/


void main(int argc, char* argv[]) {
	IDEA idea;
	srand(time(NULL));
	int mas[SIZE];//наш ключ
	char c;

	cout << "Do you want to enter the key? (y/n)\n";
	c = getchar();
	if (c == 'y') {
		int i = 0;
		printf("Enter 16 characters:\n");
		for (int r = 0; r < 16; r++) {
			c = getchar();
			for (int k = 0; k < 8; k++, i++) {
				mas[i] = c % 2;
				c = c >> 1;
			}
		}
	}
	else {
		for (int i = 0; i < SIZE; i++) {
			mas[i] = rand() % 2;
		}
	}
	cout << "\nkey: ";
	for (int i = 0; i < SIZE; i++) {
		cout << mas[i];
		if (i % 4 == 3) cout << " ";
	}
	cout << endl;

	idea.coding(argv[1], argv[2], mas);

	idea.decoding(argv[2], argv[3], mas);


	system("PAUSE");
}

