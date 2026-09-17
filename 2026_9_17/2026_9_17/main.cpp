#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

//int main() {
//	char arr1[] = "abcd01";
//	char arr2[] = "比特abcd01";
//	arr2[2]++;
//	arr2[2]++;
//	arr2[2]++;
//	arr2[2]++;
//	
//	arr2[5]--;
//	arr2[5]--;
//	arr2[5]--;
//	arr2[5]--;
//	arr2[5]--;
//	return 0;
//}
void Teststring1()
{
	string s1;              // 构造空的string类对象s1
	string s2("hello world");  // 用C格式字符串构造string类对象s2
	s2 = "hello world"; //拷贝构造
	string s3(s2);          // 拷贝构造s3

}

void Teststring2() {
	string s1;
	//string s1("hello"); //6个 hello\0
	//cout << s1.size() << endl; //不包含'\0'
	cin >> s1; //底层上重载了 >> 运算符
	cout << s1 << endl;
}

void Teststring3() {
	string s1("hello world");
	string s2(s1, 6); //拷贝到末尾
	string s3(s1, 100 ,3); //从第一个位置开始拷贝，拷贝3个字节
}

void Teststring4() {
	string s4(5, 'x');
	cout << s4 << endl;
}

void Teststring5() {
	string s5("hello");
	string s6("world");
	s6 = s5; //赋值
	s6 = "world"; //赋值 构造 + 拷贝构造 -> 构造

}


int main() {
	Teststring5();
	return 0;
}