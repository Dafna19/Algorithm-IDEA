#pragma once
#include <stdio.h>

/*
сделать 128 бит ключ(256 бит для сдвига)
функцию 4х операций(для 9го раунда)
функцию раунда
*/
class IDEA {
private:
	float corr;
	int zeros, ones, allBits;
	wchar_t key[9][6];

	void countCorrelation(wchar_t buf, int block);	

	//составляет подключи из ключа
	void makeKeys(wchar_t keys[][6], int *bigKey);

	//читает блок из 16 бит
	wchar_t readBlock(FILE *input);

	//для дешифровки
	void inverseKey();

	//обратный элемент
	wchar_t evclid(int a, wchar_t b);

	void code(char *source, char *out, int *bigKey, bool decode);

public:
	void coding(char *source, char *out, int *bigKey);
	void decoding(char *source, char *out, int *bigKey);

};