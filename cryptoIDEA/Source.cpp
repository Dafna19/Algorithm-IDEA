#include<iostream>
#include <time.h>
#include "IDEA.h"
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
������� 128 ��� ����(256 ��� ��� ������)
������� 4� ��������(��� 9�� ������)
������� ������
���������� �� ����� ��������(?)
��������� ������ �����: ����� ������ + �����*����� ������ % ������� = ������ ������
*/

void main(int argc, char* argv[]) {
	IDEA idea;
	srand(time(NULL));
	int mas[SIZE];//��� ����
	for (int i = 0; i < SIZE; i++) {
		mas[i] = rand() % 2;
		//cout << mas[i];
		//if (i % 4 == 3) cout << " ";
		//��������� ����� � ����������
		//a = a << 1;
		//a = a + mas[i];
		//if (i % 16 == 15) {//������� 16 ���
		//	cout << "a = " << a << endl;
		//	a = 0;
		//}
	}
	idea.coding("text.txt", "out.bin", mas);
	cout << endl;




	system("PAUSE");
}
