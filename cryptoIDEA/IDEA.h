#pragma once
#include <stdio.h>

/*
������� 128 ��� ����(256 ��� ��� ������)
������� 4� ��������(��� 9�� ������)
������� ������
*/
class IDEA {
private:
	float corr;
	int allBits;

	void countCorrelation(wchar_t buf, int block);

	wchar_t key[9][6];

	//���������� �������� �� �����
	void makeKeys(wchar_t keys[][6], int *bigKey);

	//������ ���� �� 16 ���
	wchar_t readBlock(FILE *input);

	//��� ����������
	void inverseKey();

	//�������� �������
	wchar_t evclid(int a, wchar_t mod);

	void code(char *source, char *out, int *bigKey, bool decode);

public:
	void coding(char *source, char *out, int *bigKey);
	void decoding(char *source, char *out, int *bigKey);

};