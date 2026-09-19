#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
using namespace std;

void test_string1() {
	string s1("hello world");
	string::iterator it = s1.begin();
	//尽量不要用<=来替换!=，有些场景下<=是不能进行使用的
	while(it != s1.end()){
		cout << *it << ' ';
		it++;
	}
}

void test_string2() {
	string s1("hello world");
	//auto不加引用时，不会改变原有对象，想要改变的话，就加上引用
	for (auto& ch : s1) {
		ch++;
	}
	cout << s1;
}

void test_string3() {
	int x = 1;
	double y = 2.0;
	//auto z = x , c = y; “auto”必须始终推导为同一类型
	auto z = y; //自动推导迭代类型
	auto m = x;
	cout << typeid(z).name() << endl;
	cout << typeid(m).name() << endl;
	//auto arr[] = { 1,2,3,4 }; err

}



void test_string4() {
	int a = 0;
	auto p1 = &a;
	auto* p2 = &a;
	// auto* p3 = a; // 报错，因为auto*代表必须是指针初始化
	auto& r1 = a;  // r1是a的引用
	const auto& r2 = a;  // r2是a的const引用
	int array[] = { 1,2,3,4,5 };
	for (const auto& e : array) {
		cout << e << ' ';
	}
}

//int main()
//{
//	int a = 10;
//
//	// auto 根据初始化表达式推导变量类型。
//	auto b = a;       // b 为 int，是 a 的副本
//	auto c = 'a';     // c 为 char
//	auto d = func1(); // d 为 int，因为 func1 返回 int
//
//	// 错误：auto 变量必须有初始化表达式，否则无法推导类型。
//	// auto e;
//
//	// typeid(...).name() 返回类型名称，但具体字符串由编译器实现决定。
//	cout << typeid(b).name() << endl;
//	cout << typeid(c).name() << endl;
//	cout << typeid(d).name() << endl;
//
//	int x = 10;
//
//	// 初始化表达式为 int*，以下两种写法得到的变量类型均为 int*。
//	auto y = &x;  // auto 推导为 int*
//	auto* z = &x; // auto 推导为 int，z 的完整类型为 int*
//
//	// 声明引用时需要显式添加 &，m 是 x 的别名。
//	// 修改 m 就会修改 x；若写成 auto m = x，则得到的是副本。
//	auto& m = x;
//
//	cout << typeid(x).name() << endl;
//	cout << typeid(y).name() << endl;
//	cout << typeid(z).name() << endl;
//
//	// 同一条声明中的各个声明符必须推导出相同的 auto 类型。
//	auto aa = 1, bb = 2; // 两者均推导为 int
//
//	// 错误：cc 要求 auto 为 int，dd 要求 auto 为 double，推导结果不一致。
//	// auto cc = 3, dd = 4.0;
//
//	// 错误：不能使用 auto 推导内置数组的元素类型。
//	// auto array[] = { 4, 5, 6 };
//
//	// 正确：明确指定元素类型，数组长度可根据初始化列表推导。
//	int array[] = { 4, 5, 6 };
//
//	return 0;
//}

void test_string5() {
	string s5("12345");
	string::iterator it = s5.begin();
	string::const_iterator cit = s5.begin();
	//while (cit != s5.end()) {
	//	cout << *cit << endl;
	//	cit++;
	//}
	string::reverse_iterator rit = s5.rbegin();
	while (rit != s5.rend()) {
		cout << *rit;
		rit++;
	}
}

void func(const string& s) {
	// 遍历容器时，可读不可写
	string::const_iterator it = s.begin();
	while (it != s.end()) {
		// (*it)++;
		cout << *it << '%';
		++it;
	}
	cout << endl;

	//string::const_reverse_iterator rit = s.rbegin();
	auto rit = s.rbegin();
	while (rit != s.rend()) {
		cout << *rit << '%';
		++rit;
	}
	cout << endl;
}

void test_string6() {
	string s1("12345");
	// 遍历容器时，可读可写
	string::iterator it = s1.begin();
	while (it != s1.end()) {
		(*it)++;
		cout << *it << '%';
		++it;
	}
	cout << endl;

	// 从后往前遍历，可读可写
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend()) {
		(*rit)++;
		cout << *rit << '%';
		++rit;
	}
	cout << endl;

	func(s1);
}

void test_string7() {
	string s7;
	s7.push_back('a');
	s7.push_back('b');
	s7.push_back('c');
	s7.push_back('d');
	s7.push_back('e');
	s7.push_back('f');
	s7.push_back('g');
	s7.push_back('h'); //abcdef
}

void test_string8() {
	string s8("hello ");
	string s9("12234");
	s8.append("world");
	s8.append(s9);
	s8.append(5, 'x');
	s8.append(s9.begin() + 2, s9.end());
	s8.append("67890", 3);
	cout << s8 << endl;
}


void test_string10()
{
	string s1("world");
	s1.insert(0, "hello "); // 头插后：hello world

	// 1. 按下标删除：从下标 0 开始，删除 3 个字符。
	// 此重载返回当前字符串的引用。
	s1.erase(0, 3);
	cout << s1 << endl; // lo world

	// 以下每次重新赋值，便于独立观察各用法。

	// 2. 只传起始下标：从该位置一直删除到末尾。
	s1 = "hello world";
	s1.erase(5);
	cout << s1 << endl; // hello

	// 3. 不传参数：删除全部字符，字符串变为空。
	s1 = "hello world";
	s1.erase();
	cout << s1.size() << endl; // 0

	// 4. 删除数量超过剩余字符数时，只删除到末尾。
	s1 = "hello world";
	s1.erase(5, 100);
	cout << s1 << endl; // hello

	// 5. 删除最后一个字符时，返回 end()，不能解引用。
	s1 = "hello";
	string::iterator it = s1.erase(s1.end() - 1); // 要求字符串非空
	cout << s1 << endl; // hell
	if (it == s1.end())
	{
		cout << "已到达字符串末尾" << endl;
	}
}

void test_string11() {
	string s3("123456789");
	cout << s3 << endl;
	s3.replace(3, 3, "abc");
	cout << s3 << endl;
	// 谨慎使用，多替换少，或者少替换多，都涉及挪动数据
	s3.replace(3, 5, "xxx");
	cout << s3 << endl;
}


int main() {
	//test_string1();
	//test_string1();
	//test_string2();
	//test_string3();
	//test_string4();
	//test_string5();
	//test_string6();
	//test_string7();
	//test_string8();
	//test_string9();
	//test_string10();
	test_string11();
	return 0;
}
