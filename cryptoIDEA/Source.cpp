#include<iostream>
#include <time.h>
#include "IDEA.h"
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
сделать 128 бит ключ(256 бит для сдвига)
функцию 4х операций(для 9го раунда)
функцию раунда
считывание из файла побитово(?)
обработка сдвига влево: новый индекс + сдвиг*номер сдвига % размера = старый индекс
*/

void main(int argc, char* argv[]) {
	IDEA idea;
	srand(time(NULL));
	int mas[SIZE];//наш ключ
	for (int i = 0; i < SIZE; i++) {
		mas[i] = rand() % 2;
		//cout << mas[i];
		//if (i % 4 == 3) cout << " ";
		//переводит число в десятичное
		//a = a << 1;
		//a = a + mas[i];
		//if (i % 16 == 15) {//считали 16 бит
		//	cout << "a = " << a << endl;
		//	a = 0;
		//}
	}
	idea.coding("text.txt", "out.bin", mas);
	cout << endl;




	system("PAUSE");
}
