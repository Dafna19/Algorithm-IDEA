#include "IDEA.h"
#include<iostream>
#define SIZE 128

void IDEA::countCorrelation(wchar_t buf, int block) {
	for (int i = 0; i < 16; i++) {
		corr += (2 * (buf % 2) - 1)*(2 * (block % 2) - 1);

		//считаем кол-во 0 и 1 в выходном потоке
		if ((block % 2) == 1) ones++;
		else zeros++;

		buf = buf >> 1;
		block = block >> 1;
	}
}

void IDEA::makeKeys(wchar_t keys[][6], int * bigKey) {
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

wchar_t IDEA::readBlock(FILE * input) {
	wchar_t buffer = 0, block = 0;
	for (int i = 0; i < 2; i++) {
		fread(&buffer, sizeof(unsigned char), 1, input);//1 байт
		if (feof(input) && i == 0) return NULL;//достигнут конец в самом начале
		if (feof(input) && i == 1) return block;//достигнут конец при считывании второго байта
		if (i == 1) //считался 2й байт числа
			buffer = buffer << 8;
		block += buffer;
	}
	if (block == 0) block = 65536;
	return block;
}

void IDEA::inverseKey() {
	wchar_t buffer[9][6];
	for (int i = 0; i < 9; i++) {
		buffer[i][0] = evclid(65537, key[8 - i][0]);
		unsigned int test = buffer[i][0] * key[8 - i][0];
		if (test % 65537 != 1) std::cout << "incorrect evclid(1) " << key[8 - i][0] << " -> " << buffer[i][0] << " test = " << test << " res = " << (buffer[i][0] * key[8 - i][0]) % 65537 << "\n";
		if (i == 0 || i == 8) {
			buffer[i][1] = (0 - key[8 - i][1]) + 65536;///
			if ((key[8 - i][1] + buffer[i][1]) % 65536 != 0) std::cout << "incorrect inverse\n";

			buffer[i][2] = (0 - key[8 - i][2]) + 65536;///
			if ((key[8 - i][2] + buffer[i][2]) % 65536 != 0) std::cout << "incorrect inverse\n";
		}
		else {
			buffer[i][1] = (0 - key[8 - i][2]) + 65536;///
			if ((key[8 - i][2] + buffer[i][1]) % 65536 != 0) std::cout << "incorrect inverse\n";

			buffer[i][2] = (0 - key[8 - i][1]) + 65536;///
			if ((key[8 - i][1] + buffer[i][2]) % 65536 != 0) std::cout << "incorrect inverse\n";
		}

		buffer[i][3] = evclid(65537, key[8 - i][3]);
		test = buffer[i][3] * key[8 - i][3];
		if (test % 65537 != 1) std::cout << "incorrect evclid " << key[8 - i][3] << " -> " << buffer[i][3] << " test = " << test << " res = " << (buffer[i][3] * key[8 - i][3]) % 65537 << "\n";

		buffer[i][4] = key[7 - i][4];
		buffer[i][5] = key[7 - i][5];
	}
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 6; j++)
			key[i][j] = buffer[i][j];

}

wchar_t IDEA::evclid(int a, wchar_t b) {
	//a*x + b*y = 1
	//std::cout << " a = " << a << " b = " << b;
	int buf = a;
	//std::cout << " buf = " << buf;
	int q, r, x, x1, x2, y, y1, y2;
	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0) {
		q = a / b;
		r = a - q * b;
		x = x2 - q * x1;
		y = y2 - q * y1;
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;//
		//std::cout << " a= " << a << " b= " << b << " q= " << q << " x= " << x << " y= " << y << " r= " << r << " x2= " << x2 << " y2= " << y2 << std::endl;
	}
	//std::cout << "  y2 = " << y2;
	if (y2 < 0) {
		//std::cout << "  y2%buf = " << y2%buf << " y2%buf + buf = " << y2%buf + buf;
		y2 = y2%buf + buf;
	}
	//std::cout << "  return y2 = " << y2%buf << "\n";
	return y2%buf;//
}

void IDEA::code(char * source, char * out, int * bigKey, bool decode) {

	FILE *input, *output;
	unsigned int blockA, blockB, blockC, blockD;
	corr = 0;
	allBits = 0;
	zeros = 0;
	ones = 0;

	makeKeys(key, bigKey);
	if (decode) inverseKey();

	/****************
	std::cout << "\nkeys\n";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++)
			std::cout << key[i][j] << " ";
		std::cout << "\n";
	}
	/****************/

	fopen_s(&input, source, "rb");
	fopen_s(&output, out, "wb");

	while (!feof(input)) {
		blockA = readBlock(input);
		if (feof(input)) break;

		blockB = readBlock(input);
		if (feof(input)) {//до кратности
			blockB = blockC = blockD = 65536;
		}

		blockC = readBlock(input);
		if (feof(input)) {
			blockC = blockD = 65536;
		}

		blockD = readBlock(input);
		if (feof(input)) {
			blockD = 65536;
		}

		//для корреляции
		wchar_t bufA = blockA, bufB = blockB, bufC = blockC, bufD = blockD;
		allBits += 64;

		for (int round = 0; round < 8; round++) {
			blockA = (blockA * key[round][0]) % 65537;
			blockB = (blockB + key[round][1]) % 65536;
			blockC = (blockC + key[round][2]) % 65536;
			blockD = (blockD * key[round][3]) % 65537;

			unsigned int t1, t2;
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
		blockC = (blockC + key[8][2]) % 65536;
		blockD = (blockD * key[8][3]) % 65537;

		//вот здесь корреляция
		countCorrelation(bufA, blockA);
		countCorrelation(bufB, blockB);
		countCorrelation(bufC, blockC);
		countCorrelation(bufD, blockD);


		fwrite(&blockA, sizeof(wchar_t), 1, output);
		if (decode && blockB == 65536) //т.е. это добавлено про кодировании
			break;

		fwrite(&blockB, sizeof(wchar_t), 1, output);
		if (decode && blockC == 65536)
			break;

		fwrite(&blockC, sizeof(wchar_t), 1, output);
		if (decode && blockD == 65536)
			break;

		fwrite(&blockD, sizeof(wchar_t), 1, output);
	}

	if (!decode) {
		corr = corr / allBits;
		std::cout << "\ncorrelation = " << corr << std::endl;
		std::cout << "probability(0) = " << zeros / allBits << std::endl;
		std::cout << "probability(1) = " << ones / allBits << std::endl;
	}

	fclose(input);
	fclose(output);
}

void IDEA::coding(char * source, char * out, int * bigKey) {
	code(source, out, bigKey, false);
	std::cout << "\ncoded\n";
}

void IDEA::decoding(char * source, char * out, int * bigKey) {
	code(source, out, bigKey, true);
	std::cout << "\ndecoded\n";
}
