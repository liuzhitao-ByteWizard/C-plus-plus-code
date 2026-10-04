#include "vector.h"

void testvector1() {
	byte::vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	v1.push_back(6);
	v1.push_back(7);
	for (auto e : v1) {
		cout << e << ' ';
	}
	cout << endl;
}

void testvector2() {
	byte::vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v2.push_back(4);
	v2.push_back(5);
	v2.push_back(6);
	v2.push_back(7);
	v2.pop_back();
	v2.pop_back();
	v2.pop_back();
	v2.pop_back();
	for (auto e : v2) {
		cout << e << ' ';
	}
	cout << endl;
}

void testvector3() {
	byte::vector<int> v3;
	v3.push_back(1); //1 + 0
	v3.push_back(1); // 1 + 1
	v3.push_back(1); // 1 + 2
	v3.push_back(1); // 1 + 3
	v3.push_back(1);
	v3.push_back(1);
	for (int i = 0; i < v3.size(); i++) {
		v3[i] += i;
	}
	for (auto e : v3) {
		cout << e << ' ';
	}
	cout << endl;
}

int main() {
	//testvector1();
	//testvector2();
	testvector3();
}