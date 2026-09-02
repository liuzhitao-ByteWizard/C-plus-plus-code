#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

//using namespace std;
//
//class Date {
//public:
//	Date(int year, int month, int day) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	void Print() {
//		cout << _year << '/' << _month << '/' << _day << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//}; //分号不能丢
//
//int main() {
//	//Date d1(2026);
//	//d1.Print();
//	//Date d1; err
//	//Date d1(1, 2,3);
//	//Date d1(); 
//
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//class Date
//{
//public:
//    // 1.无参构造函数
//    Date()
//    {
//        _year = 1;
//        _month = 1;
//        _day = 1;
//    }
//
//    // 2.带参构造函数
//    Date(int year, int month, int day)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//
//    // 3.全缺省构造函数
//    /*
//    Date(int year = 1, int month = 1, int day = 1)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//    */
//
//    void Print()
//    {
//        cout << _year << "/" << _month << "/" << _day << endl;
//    }
//
//private:
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    // 如果留下三个构造中的第二个带参构造，第一个和第三个注释掉
//    // 编译报错：error C2512：“Date”：没有合适的默认构造函数可用
//    Date d1;              // 调用默认构造函数
//    Date d2(2025, 1, 1); // 调用带参的构造函数
//
//    // 注意：如果通过无参构造函数创建对象时，对象后面不用跟括号，否则编译器无法
//    // 区分这是函数声明还是实例化对象
//    // warning C4930：“Date d3(void)”：未调用原型函数（是否是有意用变量定义的？）
//    Date d3();
//
//    d1.Print();
//    d2.Print();
//
//    return 0;
//}

#include<iostream>
using namespace std;

class Date
{
public:
    // 1.无参构造函数
    Date()
    {
        _year = 1;
        _month = 1;
        _day = 1;
    }

    // 2.带参构造函数
    Date(int year, int month, int day)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    // 3.全缺省构造函数
    /*
    Date(int year = 1, int month = 1, int day = 1)
    {
        _year = year;
        _month = month;
        _day = day;
    }
    */

    void Print()
    {
        cout << _year << "/" << _month << "/" << _day << endl;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main()
{
    // 如果留下三个构造中的第二个带参构造，第一个和第三个注释掉
    // 编译报错：error C2512：“Date”：没有合适的默认构造函数可用
    Date d1;              // 调用默认构造函数
    Date d2(2025, 1, 1); // 调用带参的构造函数

    // 注意：如果通过无参构造函数创建对象时，对象后面不用跟括号，否则编译器无法
    // 区分这是函数声明还是实例化对象
    // warning C4930：“Date d3(void)”：未调用原型函数（是否是有意用变量定义的？）
    Date d3();

    d1.Print();
    d2.Print();

    return 0;
}
