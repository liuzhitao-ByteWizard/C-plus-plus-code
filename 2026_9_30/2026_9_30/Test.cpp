#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>

using namespace std;

void testvector1() {
	vector<int> s1;
	vector<int> s2(10, 1);
	vector<int> s4(s2);
	for (auto e : s4) {
		cout << e << ' ';
	}
	cout << endl;
}

int main() {
	testvector1();
	return 0;
}
