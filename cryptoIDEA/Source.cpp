#include<iostream>
#include <time.h>
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
������� 128 ��� ����(256 ��� ��� ������)
������� 4� ��������(��� 9�� ������)
������� ������
���������� �� ����� ��������(?)
*/

void makeKeys(wchar_t keys[][6], int *bigKey);

void main(int argc, char* argv[]) {
	FILE *f;
	fopen_s(&f, "text.txt", "rb");
	//------------���������� �� 16 ���
	wchar_t ch = 0, bufc = 0;
	int sum = 0;
	while (!feof(f)) {
		fread(&bufc, sizeof(unsigned char), 1, f);//1 ����	
		sum++;
		if (sum == 2) //�������� 2� ���� �����
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
	for (int i = 0; i < SIZE; i++) {//��������� ����� � ����������
		mas[i] = rand() % 2;
		cout << mas[i];
		if (i % 4 == 3) cout << " ";

		a = a << 1;
		a = a + mas[i];
		if (i % 16 == 15) {//������� 16 ���
			cout << "a = " << a << endl;
			a = 0;
		}
	}
	cout << endl;
	//��������� ������ �����: ����� ������ + �����*����� ������ % ������� = ������ ������
	//-------------------

	wchar_t key[9][6];	
	makeKeys(key, mas);
	//��������
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 6; j++) {
			cout << key[i][j] << "\t";
		}
		cout << endl;
	}

	system("PAUSE");
}
//���������� �������� �� �����
void makeKeys(wchar_t keys[][6], int *bigKey) {
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 6; j++)
			keys[i][j] = 0;
	int k = 0;//����� ��������
	for (int j = 0; j < 7; j++) {//���-�� �������
		for (int i = 0; i < SIZE; i++) {//������ �� 128-������� �����
			keys[k / 6][k % 6] = keys[k / 6][k % 6] << 1;
			keys[k / 6][k % 6] = keys[k / 6][k % 6] + bigKey[(i + 25 * j) % SIZE];
			if (i % 16 == 15) k++;
			if (k == 52) break;
		}
		if (k == 52) break;
	}
}