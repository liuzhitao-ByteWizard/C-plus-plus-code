#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

void func() {
	string s1("hello world hello world hello world hello world hello world hello world"); // 把空格换成%%
	string s2;
	s2.reserve(100);
	for (auto& ch : s1) {
		if (ch == ' ') {
			s2 += "%%";
		}
		else if (ch != ' ') {
			s2 += ch;
		}
	}
	cout << s2 << endl;
}

int main() {
	func();
	return 0;
}
