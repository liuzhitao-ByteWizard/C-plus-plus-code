#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//class A
//{
//public:
//	A(int a = 0)
//		:_a(a)
//	{
//		cout << "A(int a)" << endl;
//	}
//
//	~A()
//	{
//		cout << "~A()" << endl;
//	}
//private:
//	int _a;
//};
//
//class Solution {
//public:
//	int Sum_Solution(int n) {
//		//...
//		return n;
//	}
//};
//
//void PushBack(A aa) {
//	//...
//}
//
//int main() {
//	A aa1;
//	A aa2(2);
//
//	// 匿名对象,生命周期只在当前这一行
//	A();
//	A(2);
//
//	Solution  so;
//	so.Sum_Solution(1);
//
//	//创建匿名对象，通过匿名对象来进行调用成员函数
//	Solution().Sum_Solution(2);
//
//	A aa3(3);
//	PushBack(aa3);
//
//	PushBack(A(3));
//
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//    A(int a = 0)
//        : _a1(a)
//    {
//        cout << "A(int a)" << endl;
//    }
//
//    A(const A& aa)
//        : _a1(aa._a1)
//    {
//        cout << "A(const A& aa)" << endl;
//    }
//
//    A& operator=(const A& aa)
//    {
//        cout << "A& operator=(const A& aa)" << endl;
//
//        if (this != &aa)
//        {
//            _a1 = aa._a1;
//        }
//
//        return *this;
//    }
//
//    ~A()
//    {
//        cout << "~A()" << endl;
//    }
//
//private:
//    int _a1 = 1;
//};
//
//void f1(A aa)
//{
//}
//
//A f2()
//{
//    A aa;
//    return aa;
//}
//
//int main()
//{
//    // 传值传参
//    // 构造+拷贝构造
//    A aa1;
//    f1(aa1);
//    cout << endl;
//
//    // 隐式类型，连续构造+拷贝构造->优化为直接构造
//    f1(1);
//
//    // 一个表达式中，连续构造+拷贝构造->优化为一个构造
//    f1(A(2));
//    cout << endl;
//
//    cout << "********************************************" << endl;
//
//    // 传值返回
//    // 不优化的情况下传值返回，编译器会生成一个拷贝返回对象的临时对象作为函数调用表达式的返回值
//
//    // 无优化（vs2019 debug）
//    // 一些编译器会优化得更厉害，将构造的局部对象和拷贝构造的临时对象优化为直接构造
//    //（vs2022 debug）
//    f2();
//    cout << endl;
//
//    // 返回时一个表达式中，连续拷贝构造+拷贝构造->优化一个拷贝构造（vs2019 debug）
//    // 一些编译器会优化得更厉害，进行跨行合并优化，将构造的局部对象aa和拷贝的临时对象
//    // 和接收返回值对象aa2优化为一个直接构造。（vs2022 debug）
//    A aa2 = f2();
//    cout << endl;
//
//    // 一个表达式中，开始构造、中间拷贝构造+赋值重载->无法优化（vs2019 debug）
//
//    // 一些编译器会优化得更厉害，进行跨行合并优化，将构造的局部对象aa和拷贝临时对象合
//    // 并为一个直接构造（vs2022 debug）
//    aa1 = f2();
//    cout << endl;
//
//    return 0;
//}

//int main() {
//	int* ptr1 = new int;
//
//	int* ptr2 = new int(2);
//
//	int* ptr3 = new int[10];
//
//	int* ptr4 = new int[5] {1, 2, 3, 4, 5};
//
//	delete ptr1;
//	delete ptr2;
//	delete[] ptr3;
//	delete[] ptr4;
//	return 0;
//}

//class A
//{
//public:
//	A(int a = 0)
//		: _a(a)
//	{
//		cout << "A():" << this << endl;
//	}
//	~A()
//	{
//		cout << "~A():" << this << endl;
//	}
//private:
//	int _a;
//};
//
//int main()
//{
//	// 动态开空间,并没有初始化
//	A* p1 = (A*)malloc(sizeof(A));
//	//p1->_a = 1; err
//
//	// 动态开空间+1次构造
//	A* p2 = new A(1);
//	free(p1);
//	// 1次析构+释放动态空间
//	delete p2;
//
//	A* p5 = (A*)malloc(sizeof(A) * 10);
//	// 动态开空间+10次构造
//	A* p6 = new A[10];
//	//只是释放了动态空间，没有执行析构
//	free(p5);
//	// 10次析构+释放动态空间
//	delete[] p6;
//
//	// 语法逻辑要自洽
//	//A* p7 = new A[10]{A(1), A(2), A(3)}; //匿名对象
//	A* p7 = new A[10]{ 1,2,3}; //隐式类型转换
//	// 10次析构+释放动态空间
//	delete[] p7;
//
//	return 0;
//}

//void func(){
//	for (int i = 0; i < 10000; i++) {
//		if (i == 5119) {
//			int x = 0;
//		}
//
//		int* p1 = new int[1024 * 1000]; // 400KB
//		cout << i << ":" << p1 << endl;
//	}
//}
//
//int main(){
//	try {
//		func();
//	}
//	catch (const exception& e) {
//		cout << e.what() << endl;
//	}
//
//	return 0;
//}

#include <iostream>
using namespace std;

int GetMonthDay(int year, int month) {
    int MonthArr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
        return 29;
    }
    return MonthArr[month];
}

int main() {
    int n = 1;
    while (n--) {
        int month = 1;
        int year = 0, day = 0;
        cin >> year >> day;
        if (day <= 31) {
            if (day < 10) {
                printf("%d-0%d-0%d\n", year, month, day);
                continue;
            }
            printf("%d-0%d-%d\n", year, month, day);
            continue;
        }
        while (day > GetMonthDay(year, month)) {
            day -= GetMonthDay(year, month);
            month += 1;
            if (month == 13) {
                year += 1;
                month = 1;
            }
        }
        if (month < 10 && day >= 10) {
            printf("%d-0%d-%d\n", year, month, day);
            continue;
        }

        if (month < 10 && day < 10) {
            printf("%d-0%d-0%d\n", year, month, day);
            continue;
        }
        if (month >= 10 && day < 10) {
            printf("%d-%d-0%d\n", year, month, day);
            continue;
        }

        printf("%d-%d-%d\n", year, month, day);
    }

    
}
// 64 位输出请用 printf("%lld")
