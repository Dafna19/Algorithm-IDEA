#include "IDEA.h"
#define SIZE 128

void IDEA::makeKeys(wchar_t keys[][6], int * bigKey){
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

void IDEA::coding(char * source, char * out, int * bigKey){
	makeKeys(key, bigKey);

}

void IDEA::decoding(char * source, char * out, int * bigKey){
}
