#pragma once
#include <stdio.h>

/*
������� 128 ��� ����(256 ��� ��� ������)
������� 4� ��������(��� 9�� ������)
������� ������
*/
class IDEA {
private:
	wchar_t key[9][6];
	//���������� �������� �� �����
	void makeKeys(wchar_t keys[][6], int *bigKey);
	//������ ���� �� 16 ���
	wchar_t readBlock(FILE *input);
public:
	void coding(char *source, char *out, int *bigKey);
	void decoding(char *source, char *out, int *bigKey);

};