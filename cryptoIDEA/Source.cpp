#include<iostream>
#include <time.h>
#include "IDEA.h"
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
сделать 128 бит ключ(256 бит дл€ сдвига)
функцию 4х операций(дл€ 9го раунда)
функцию раунда
считывание из файла побитово(?)
обработка сдвига влево: новый индекс + сдвиг*номер сдвига % размера = старый индекс
коррел€ци€ = 1/N SUM( (2xi-1)(2yi-1) ) ~ 0
*/


void main(int argc, char* argv[]) {
	IDEA idea;
	srand(time(NULL));
	int mas[SIZE];//наш ключ
	cout << "key: ";
	for (int i = 0; i < SIZE; i++) {
		mas[i] = rand() % 2;
		cout << mas[i];
		if (i % 4 == 3) cout << " ";
		//переводит число в дес€тичное
		//a = a << 1;
		//a = a + mas[i];
		//if (i % 16 == 15) {//считали 16 бит
		//	cout << "a = " << a << endl;
		//	a = 0;
		//}
	}
	cout << endl;

	idea.coding(argv[1], argv[2], mas);

	idea.decoding(argv[2], argv[3], mas);




	system("PAUSE");
}

