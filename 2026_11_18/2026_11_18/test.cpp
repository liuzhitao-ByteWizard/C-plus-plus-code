#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include "HashTable.h"

using namespace std;

int main() {
	//open_address::HashTable<int, int> ht(11);
	//int a[] = { 19, 30, 52, 74 };
	//for (auto& e : a) {
	//	ht.Insert({ e,e });
	//}
	//cout << endl;

	//ht.Insert({1,1});
	//ht.Insert({10,1});
	//ht.Insert({20,1});
	//ht.Insert({40,1});
	//ht.Insert({50,1});

	link_address::HashTable<int, int> ht1(11);
	int arr[] = { 19,30,5,36,13,20,21,12,24,96 };
	for (auto& e : arr) {
		ht1.Insert({ e,e });
	}
	ht1.Insert({ rand(),1 });
	ht1.Insert({ rand(),1 });
	ht1.Insert({ rand(),1 });
	ht1.Insert({ rand(),1 });

	cout << ht1.Find(19) << endl;
	cout << ht1.Erase(19) << endl;
	cout << ht1.Find(19) << endl;

	link_address::HashTable<string, int> ht2(11);
	ht2.Insert({ "zhangsan",11 });
	ht2.Insert({ "lisi",11 });
	ht2.Insert({ "wangsu",11 });
	return 0;
}


