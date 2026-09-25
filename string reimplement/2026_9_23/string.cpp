#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

void test_string1() {
	string filename("string.cpp");
	FILE* ptf = fopen(filename.c_str(), "r");
	if (ptf == NULL) {
		perror("fopen fail");
		return;
	}
	char ch = fgetc(ptf);
	while (ch != EOF) {
		cout << ch;
		ch = fgetc(ptf);
	}

}

void test_string2() {
	string s2("hello world");
	size_t pos = s2.find("bs");
	cout << pos << endl;
}

//void test_string3() {
//	string s3("https://www.csgraduates.com/study_methods/408quiz/");
//	size_t pos1 = s3.find(':'); //截取协议
//	string s4 = s3.substr(0 , pos1);
//
//	size_t pos2 = s3.find('/', pos1 + 3); //截取域名
//	string s5 = s3.substr(pos1 + 3, pos2 - (pos1 + 3));
//	
//	string s6 = s3.substr(pos2 + 1); //截取资源
//	//cout << s4 << endl;
//	//cout << s5 << endl;
//	//cout << s6 << endl;
//
//	//我现在需要找到最后一个后缀，zip
//	string s7("string.tar.zip");
//	size_t pos4 = s7.rfind('.');
//	cout << s7.substr(pos4 + 1) << endl;
//	
//}

//void test_string4() {
//	//我现在需要找到最后一个后缀，zip
//	string s7("string.tar.zip");
//
//	// 从右向左查找最后一个 '.'，pos4 是它在字符串中的位置。
//	size_t pos4 = s7.rfind('.');
//
//	// 从 '.' 的下一位截取到末尾，输出最终后缀 zip。
//	cout << s7.substr(pos4 + 1) << endl;
//
//}
//
//int main() {
//	//test_string1();
//	//test_string2();
//	//test_string3();
//	test_string4();
//	return 0;
//}

//int main()
//{
//	//str中所有出现的aeiou变成*
//	std::string str("Please, replace the vowels in this sentence by asterisks.");
//	std::size_t found = str.find_first_of("aeiou");
//	while (found != std::string::npos)
//	{
//		str[found] = '*';
//		found = str.find_first_of("aeiou", found + 1);
//	}
//
//	std::cout << str << '\n';
//
//	return 0;
//}

//void SplitFilename(const std::string& str)
//{
//	std::cout << "Splitting: " << str << '\n';
//	std::size_t found = str.find_last_of("/\\");
//	std::cout << " path: " << str.substr(0, found) << '\n';
//	std::cout << " file: " << str.substr(found + 1) << '\n';
//}
//
//int main()
//{
//	std::string str1("/usr/bin/man");
//	std::string str2("c:\\windows\\winhelp.exe");
//
//	SplitFilename(str1);
//	SplitFilename(str2);
//
//	return 0;
//}


