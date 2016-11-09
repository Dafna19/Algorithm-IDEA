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

wchar_t IDEA::readBlock(FILE * input){
	wchar_t buffer = 0, block = 0;
	for (int i = 0; i < 2; i++) {
		fread(&buffer, sizeof(unsigned char), 1, input);//1 байт
		if (feof(input)) return NULL;//достигнут конец
		if (i == 1) //считался 2й байт числа
			buffer = buffer << 8;
		block += buffer;
	}
	if (block == 0) block = 65536;
	return block;
}

void IDEA::coding(char * source, char * out, int * bigKey){
	FILE *input, *output;
	wchar_t blockA, blockB, blockC, blockD;

	makeKeys(key, bigKey);

	fopen_s(&input, source, "rb");
	fopen_s(&output, out, "wb");

	while (!feof(input)) {
		blockA = readBlock(input);
		blockB = readBlock(input);
		blockC = readBlock(input);
		blockD = readBlock(input);
		if (feof(input)) break;

		for (int round = 0; round < 8; round++) {
			blockA = (blockA * key[round][0]) % 65537;
			blockB = (blockB + key[round][1]) % 65536;
			blockC = (blockC + key[round][2]) % 65536;
			blockD = (blockD * key[round][3]) % 65537;

			wchar_t t1, t2;
			t1 = blockA^blockC;
			t2 = blockB^blockD;

			t1 = (t1 * key[round][4]) % 65537;
			t2 = (t2 + t1) % 65536;

			t2 = (t2 * key[round][5]) % 65537;
			t1 = (t1 + t2) % 65536;

			blockA = blockA^t2;
			blockB = blockB^t1;
			blockC = blockC^t2;
			blockD = blockD^t1;

			if (round != 7) {
				wchar_t buf = blockB;
				blockB = blockC;
				blockC = buf;
			}
		}
		//9й раунд - окончательное преобразование
		blockA = (blockA * key[8][0]) % 65537;
		blockB = (blockB + key[8][1]) % 65536;
		blockC = (blockC * key[8][2]) % 65536;
		blockD = (blockD * key[8][3]) % 65537;

		fwrite(&blockA, 2, 1, output);
		fwrite(&blockB, 2, 1, output);
		fwrite(&blockC, 2, 1, output);
		fwrite(&blockD, 2, 1, output);
	}


	fclose(input);
	fclose(output);
}

void IDEA::decoding(char * source, char * out, int * bigKey){
}
