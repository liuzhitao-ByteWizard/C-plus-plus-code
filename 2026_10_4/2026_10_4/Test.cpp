#include "vector.h"

void testvector1() {
	byte::vector<int> v1;
	v1.reserve(100);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = 1;
	}
	for (auto e : v1) {
		cout << e << ' ';
	}
	cout << endl;
}

void testvector2() {
	byte::vector<int> v2;
	v2.push_back(1);
	v2.push_back(1);
	v2.push_back(1);
	//v2.push_back(1);
	//v2.push_back(1);
	//v2.push_back(1);
	//v2.push_back(1);
	v2.insert(v2.begin(), 0);
	v2.insert(v2.end(), 0);
	//v2.insert(v2.begin() + 2, 0);
	for (auto e : v2) {
		cout << e << ' ';
	}
}

void testvector3() {
	byte::vector<int> v3; //v3默认开4个空间
	v3.push_back(1);
	v3.push_back(2);
	v3.push_back(3);
	v3.push_back(4);
	auto it = v3.begin();
	v3.insert(it, 0); //it会失效（形参是实参的一份临时拷贝）
	for (auto e : v3) {
		cout << e << ' ';
	}
	cout << endl;
}

//void testvector4() {
//	byte::vector<int> v4;
//	v4.push_back(1);
//	v4.push_back(2);
//	v4.push_back(3);
//	v4.push_back(4);
//	v4.push_back(5);
//	v4.push_back(6);
//	v4.push_back(7);
//	//v4.push_back(8);
//	auto it = v4.begin();
//	while (it != v4.end()) {
//		if (*it % 2 == 0)
//			v4.erase(it);
//		else
//			it++;
//	}
//	for (auto e : v4) {
//		cout << e << ' ';
//	}
//	cout << endl;
//}

//void testvector5() {
//	byte::vector<int> v5;
//	v5.push_back(1);
//	v5.push_back(2);
//	v5.push_back(3);
//	v5.push_back(4);
//	v5.push_back(5);
//	v5.push_back(6);
//	v5.push_back(6);
//	v5.push_back(7);
//	auto it = v5.begin();
//	while (it != v5.end()) {
//		if (*it % 2 == 0)
//			v5.erase(it);
//		else
//			it++;
//	}
//	for (auto e : v5) {
//		cout << e << ' ';
//	}
//	cout << endl;
//}
void testvector6() {
	byte::vector<int> v6;
	v6.push_back(1);
	v6.push_back(2);
	v6.push_back(3);
	v6.push_back(4);
	v6.push_back(5);
	v6.push_back(6);
	v6.push_back(7);
	v6.push_back(8);
	auto it = v6.begin();
	while (it != v6.end()) {
		if (*it % 2 == 0)
			it = v6.erase(it);
		else
			it++;
	}
	for (auto e : v6) {
		cout << e << ' ';
	}
	cout << endl;
}



int main() {
	//testvector4();
	//testvector5();
	testvector6();
	return 0;
}