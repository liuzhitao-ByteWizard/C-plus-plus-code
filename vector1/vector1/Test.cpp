#include "string.h"
#include <vector>
using namespace std;

void teststring1() {
	byte::string s1("hello world");
	byte::string s2("hello C++");
	byte::string s3(s2);
	cout << s3 << endl;
}

void teststring2() {
	byte::string s4("hello world");
	byte::string s5("welcome");
	s5 = s4;
	cout << s5 << endl;
	s4 = s4;
	cout << s4 << endl;
}

void teststring3() {
	byte::string s1;
	//cin >> s1;
	//cout << s1 << endl;

	//cin >> s1;
	//cout << s1 << endl;
	getline(cin, s1, '\n');
	cout << s1 << endl;
}

void teststring4() {
	std::string s10;
	std::string s11("hello worldxxxxxxxxxxxxxxxxxxx");
	cout << sizeof(s10) << endl;
	cout << sizeof(s11) << endl;
}

void teststring5() {
	std::string s11("hello world");
	std::string s12(s11);
	cout << (const void*)s11.c_str() << endl;
	cout << (const void*)s12.c_str() << endl;
}


int main() {
	teststring5();
	return 0;
}

