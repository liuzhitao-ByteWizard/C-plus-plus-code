#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
//
//class Date {
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	//this指针默认是Date* const this,d1传进来，涉及权限的放大
//	void Print() const {
//		cout << _year << '/' << _month << '/' << _day << endl;
//	}
//	
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main() {
//	const Date d1(2026,8,29);
//	Date d(2026,9,9);
//	d1.Print(); //d1.Print(&d1) const Date*
//	d.Print(); //d.Print(&d) Date*
//	return 0;
//}

//class Date {
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	//两个函数，构成函数重载
//	Date* operator&() {
//		return nullptr;
//	}
//
//	//Date* const this
//	const Date* operator&() const {
//		return nullptr;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main() {
//	const Date d1(2026, 8, 29);
//	Date d(2026, 9, 9);
//	d1.operator&();
//	d.operator&();
//	return 0;
//}

//class Time
//{
//public:
//	Time(int hour)
//		:_hour(hour)
//	{
//		cout << "Time()" << endl;
//	}
//private:
//	int _hour;
//};
//
//class A {
//public:
//	//A(int a, int b) {
//	//	//函数体内这个变量已经定义出来了，我在这呢对它进行赋值修改,不是初始化
//	//	//由于有const成员变量，而const修饰的变量必须在定义时初始化，初始化完之后const变量是不能进行修改的
//	//	//_a = a;
//	//	//_b = b;
//	//}
//	A(Time t) {
//		_t = t;
//	}
//private:
//	//const int _a; //const成员变量
//	//int& _b; //引用成员变量
//	Time _t;
//};
//
//
//int main() {
//	int a = 1;
//	int b = 2;
//	//A _a(a , b);
//	A t(10);
//	return 0;
//}

//class Stack{
//public:
//	Stack(int n) {
//	}
//};
//
//class MyQueue {
//public:
//	MyQueue(int n = 4)
//		:_st1(n)
//		,_st2(n)
//	{}
//private:
//	Stack _st1;
//	Stack _st2;
//};
//
//int main() {
//	MyQueue q;
//	return 0;
//}

