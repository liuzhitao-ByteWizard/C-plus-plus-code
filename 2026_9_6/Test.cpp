#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

int main() {
	Date d1(2000,7, 1);
	Date d2(2300,7,2);
	int dif = d1 - d2;
	cout << dif << endl;
	//d1 << cout;


	return 0;
}

