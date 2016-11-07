#include<iostream>
#include <time.h>
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
сделать 128 бит ключ(256 бит для сдвига)
функцию 4х операций(для 9го раунда)
функцию раунда
считывание из файла побитово(?)
*/

void makeKeys(wchar_t keys[][6], int *bigKey);

void main(int argc, char* argv[]) {
	FILE *f;
	fopen_s(&f, "text.txt", "rb");
	//------------считывание по 16 бит
	wchar_t ch = 0, bufc = 0;
	int sum = 0;
	while (!feof(f)) {
		fread(&bufc, sizeof(unsigned char), 1, f);//1 байт	
		sum++;
		if (sum == 2) //считался 2й байт числа
			bufc = bufc << 8;
		ch += bufc;
		if (sum == 2) {
			cout << ch << " ";
			sum = 0;
			ch = bufc = 0;
		}
	}
	//------------------------------
	cout << endl;
	srand(time(NULL));
	int mas[SIZE];
	wchar_t a = 0;
	for (int i = 0; i < SIZE; i++) {//переводит число в десятичное
		mas[i] = rand() % 2;
		cout << mas[i];
		if (i % 4 == 3) cout << " ";

		a = a << 1;
		a = a + mas[i];
		if (i % 16 == 15) {//считали 16 бит
			cout << "a = " << a << endl;
			a = 0;
		}
	}
	cout << endl;
	//обработка сдвига влево: новый индекс + сдвиг*номер сдвига % размера = старый индекс
	//-------------------

	wchar_t key[9][6];	
	makeKeys(key, mas);
	//проверка
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			cout << key[i][j] << "\t";
		}
		cout << endl;
	}

	system("PAUSE");
}
//составляет подключи из ключа
void makeKeys(wchar_t keys[][6], int *bigKey) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 6; j++)
			keys[i][j] = 0;
	int k = 0;//номер подключа
	for (int j = 0; j < 7; j++) {//кол-во сдвигов
		for (int i = 0; i < SIZE; i++) {//проход по 128-битному ключу
			keys[k / 6][k % 6] = keys[k / 6][k % 6] << 1;
			keys[k / 6][k % 6] = keys[k / 6][k % 6] + bigKey[(i + 25 * j) % SIZE];
			if (i % 16 == 15) k++;
			if (k == 52) break;
		}
		if (k == 52) break;
	}
}