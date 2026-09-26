#include "string.h"

void teststring1() {
	std::string s3;
	cout << s3.c_str() << endl;

	byte::string s2;
	cout << s2.c_str() << endl;

	//如果你在传字符串初始化时将字符串初始化为空，当你访问c_str时就会造成空指针的解引用，程序崩溃
	byte::string s1("hello world");
	cout << s1.c_str() << endl;
}

void teststring2() {
	string s("hello chatgpt");
	for (int i = 0; i < s.size(); i++)
		cout << s[i];
	cout << endl;
}

void func(const byte::string& s) {
	byte::string::const_iterator it = s.begin();
	while (it != s.end()) {
		cout << *it;
		it++;
	}
	cout << endl;
	//范围for在底层上就是使用迭代器的方式来实现的
	for (auto ch : s) //前提是你模拟实现的名字必须得跟库里面这些保持一致，不然范围for无法实现
		cout << ch;
}

void teststring3() {
	/*std::string s1("hello");
	s1.append("xxxxxxxxxxxx");

	cout << s1.c_str() << endl;

	s1 += ' ';
	s1 += "yyyyyyyyyyyyyy";
	cout << s1.c_str() << endl;*/

	string s1("string.cpp");
	string s2("aaaa");
	const char* p1 = "bb";
	//cout << (s1 < s2) << endl;
	//cout << (s2 < p1) << endl;
	//cout << (p1 < s2) << endl;

	cout << s1 + p1 << endl;
	cout << p1 + s1 << endl;
	cout << s1 + p1 + s2 + p1 << endl;
}

void teststring4() {
	byte::string s4;
	s4.insert(0, 'x');
	cout << s4.c_str() << endl;
	byte::string s5("hello world");
	s5.insert(0, 'x');
	cout << s5.c_str() << endl;
	byte::string s6("hello world");
	s6.insert(0, "xxxxxxxxxxxxxxxxx");
	cout << s6.c_str() << endl;
	byte::string s7("hello world");
	s7.insert(5, "xxxxxxxxxxxxxxxxx");
	cout << s7.c_str() << endl;
}

void teststring5() {
	byte::string s6("helloxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	s6.erase(5);
	cout << s6.c_str() << endl;
	byte::string s7("helloxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	s7.erase(0, 5);
	cout << s7.c_str() << endl;
}

void teststring6() {
	byte::string s8("hello C++");
	cout << s8.find('C') << endl;
	cout << s8.find('+' , 5) << endl;
	cout << s8.find("C++") << endl;

}

void teststring7() {
	byte::string s1("hello world");
	byte::string s2 = s1.substr(6);
	byte::string s3(s2);
	s3 = s2;
	s3 = s3;
	cout << s2.c_str() << endl;
}

void teststring8() {
	byte::string s1;
	//cin >> s1;
	//cout << s1 << endl;
	byte::string s2;
	getline(cin , s2);
	cout << s2 << endl;
}

int main() {
	//teststring1();
	//teststring2();
	//byte::string s1("i like C++");
	//func(s1);
	//teststring4();
	//teststring5();
	//teststring6();
	//teststring7();
	teststring8();
	return 0;
}

