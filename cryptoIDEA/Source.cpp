#include<iostream>
#include <time.h>
#include "IDEA.h"
using namespace std;
#pragma warning(2:4235)
#define SIZE 128

/*
сделать 128 бит ключ(256 бит дл€ сдвига)
функцию 4х операций(дл€ 9го раунда)
функцию раунда
считывание из файла побитово(?)
обработка сдвига влево: новый индекс + сдвиг*номер сдвига % размера = старый индекс
коррел€ци€ = 1/N SUM( (2xi-1)(2yi-1) ) ~ 0
*/

wchar_t evclid(int a, wchar_t b) {
	//a*x + b*y = 1
	wchar_t buf = a;
	int q, r, x, x1, x2, y, y1, y2;
	x2 = 1, x1 = 0, y2 = 0, y1 = 1;
	while (b > 0) {
		q = a / b;//
		r = a - q * b;//
		x = x2 - q * x1;//
		y = y2 - q * y1;//
		a = b;//
		b = r;//
		x2 = x1;//
		x1 = x;//
		y2 = y1;//
		y1 = y;//
			   //std::cout << " a= " << a << " b= " << b << " q= " << q << " x= " << x << " y= " << y << " r= " << r << " x2= " << x2 << " y2= " << y2 << std::endl;
	}
	if (y2 < 0) y2 = y2 + buf;
	return y2;//
}

void main(int argc, char* argv[]) {
	IDEA idea;
	srand(time(NULL));
	int mas[SIZE];//наш ключ
	cout << "key: ";
	for (int i = 0; i < SIZE; i++) {
		mas[i] = rand() % 2;
		cout << mas[i];
		if (i % 4 == 3) cout << " ";
		//переводит число в дес€тичное
		//a = a << 1;
		//a = a + mas[i];
		//if (i % 16 == 15) {//считали 16 бит
		//	cout << "a = " << a << endl;
		//	a = 0;
		//}
	}
	cout << endl;

	idea.coding(argv[1], argv[2], mas);

	idea.decoding(argv[2], argv[3], mas);

	//unsigned int abc = 65002 * 40950;
//	abc = abc % 65537;
	wchar_t abc = 2550 ;
	cout << abc << endl;
	cout << hex << (wchar_t)abc << endl;
	cout << hex << abc << endl;
	/*FILE *f;
	fopen_s(&f, "testInt.txt", "wb");
	fwrite(&abc, sizeof(wchar_t), 1, f);
	fclose(f);
	abc = 0;
	fopen_s(&f, "testInt.txt", "rb");
	fread(&abc, sizeof(unsigned char), 1, f);
	cout << abc << endl;
	fclose(f);*/




	system("PAUSE");
}

