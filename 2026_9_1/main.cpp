#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

//class Date {
//public:
//	void init(int year, int month, int day) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//	void print() {
//		cout << _year << '/' << _month << '/' << _day << endl;
//	}
//	
//private:
//	int _year;
//	int _month;
//	int _day;
//}; //分号不要丢
//
//int main() {
//	Date d1;
//	d1.init(2026, 9, 1);
//	d1.print();
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//class Stack
//{
//public:
//    // 成员函数
//    void Init(int n = 4);
//
//private:
//    // 成员变量
//    int* array;
//    size_t capacity;
//    size_t top;
//};
//
//// 声明和定义分离，需要指定类域
//void Stack::Init(int n)
//{
//    array = (int*)malloc(sizeof(int) * n);
//    if (nullptr == array)
//    {
//        perror("malloc申请空间失败");
//        return;
//    }
//
//    capacity = n;
//    top = 0;
//}
//
//int main()
//{
//    Stack st;
//    st.Init();
//
//    return 0;
//}

//#include<iostream>
//using namespace std;
//
//class Date
//{
//public:
//    void Init(int year, int month, int day)
//    {
//        //成员变量的命名如果不加上下划线，还可以通过指定类域的方式实现，但是并不推荐这种写法
//        //Date::year = year
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//
//    void Print()
//    {
//        cout << _year << "/" << _month << "/" << _day << endl;
//    }
//
//private:
//    // 这里只是声明，没有开空间
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    // Date类实例化出对象d1和d2
//    Date d1;
//    Date d2;
//
//    d1.Init(2024, 3, 31);
//    d1.Print();
//
//    d2.Init(2024, 7, 5);
//    d2.Print();
//
//    return 0;
//}

//#include<iostream>
//using namespace std;
//
//// 计算一下A/B/C实例化的对象是多大？
//class A
//{
//public:
//    void Print()
//    {
//        cout << _ch << endl;
//    }
//
//private:
//    char _ch;
//    int _i;
//};
//
//class B
//{
//public:
//    void Print()
//    {
//        //...
//    }
//};
//
//class C
//{
//};
//
//int main()
//{
//    A a;
//    B b;
//    C c;
//
//    cout << sizeof(a) << endl;
//    cout << sizeof(b) << endl;
//    cout << sizeof(c) << endl;
//
//    return 0;
//}

//#include<iostream>
//using namespace std;
//
//class Date
//{
//public:
//    // void Init(Date* const this, int year, int month, int day)
//    void Init(int year, int month, int day)
//    {
//        // 编译报错：error C2106：“=”：左操作数必须为左值
//        // this = nullptr;
//
//        // this->_year = year;
//        _year = year;
//        this->_month = month;
//        this->_day = day;
//    }
//
//    void Print()
//    {
//        cout << _year << "/" << _month << "/" << _day << endl;
//    }
//
//private:
//    // 这里只是声明，没有开空间
//    int _year;
//    int _month;
//    int _day;
//};
//
//int main()
//{
//    // Date类实例化出对象d1和d2
//    Date d1;
//    Date d2;
//
//    // d1.Init(&d1, 2024, 3, 31);
//    d1.Init(2024, 3, 31);
//    d1.Print();
//
//    d2.Init(2024, 7, 5);
//    d2.Print();
//
//    return 0;
//}

//#include<iostream>
//using namespace std;
//
//class A
//{
//public:
//    void Print()
//    {
//        cout << "A::Print()" << endl;
//    }
//
//private:
//    int _a;
//};
//
//int main()
//{
//    A* p = nullptr;
//    p->Print();
//
//    return 0;
//}
//

