#pragma once
#include <stdio.h>

/*
сделать 128 бит ключ(256 бит для сдвига)
функцию 4х операций(для 9го раунда)
функцию раунда
*/
class IDEA {
private:
	wchar_t key[9][6];
	//составляет подключи из ключа
	void makeKeys(wchar_t keys[][6], int *bigKey);
	//читает блок из 16 бит
	wchar_t readBlock(FILE *input);
public:
	void coding(char *source, char *out, int *bigKey);
	void decoding(char *source, char *out, int *bigKey);

};