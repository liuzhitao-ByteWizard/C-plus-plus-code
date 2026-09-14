#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
//class A
//{
//public:
//	A(int a = 0)
//		: _a(a)
//	{
//		cout << "A():" << this << endl;
//	}
//
//	// A(const A& a);
//
//	~A()
//	{
//		cout << "~A():" << this << endl;
//	}
//private:
//	int _a;
//};
//
//// 一定不要错配使用
//int main() {
//	A* p1 = new A;
//	free(p1); //程序不会崩溃
//
//    // msvc
// 	//48
//	A* p2 = new A[10];
//	free(p2 - 1); //程序崩溃：本质上free的位置不对
//	//delete[] p2;
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
//
//	// A(const A& a);
//
//	~A()
//	{
//		cout << "~A():" << this << endl;
//	}
//	private:
//		int _a;
//};
//
//int main() {
//
//	//A* p4 = (A*)malloc(sizeof(A));
//	//A* p4 = (A*)operator new(sizeof(A));
//	//replacement new，对指针指向的空间，显示调用构造函数初始化
//	//new(p4)A; //显示
//	// 等价于A* p4 = new A(1);
//	
//	//等价于 A* p4 = new A(1)
//	A* p4 = (A*)operator new(sizeof(A));  //malloc
//	p4->A(1);  // 规定构造只能通过replacement new显示调用
//	//new(p4)A(1);
//
//	// 等价于delete p4;
//	p4->~A();
//	operator delete(p4); //free
//	return 0;
//}
//#include <iostream>
//
//using namespace std;
////template <class T>
//template <typename T>
//
//void Swap(T& left, T& right)
//{
//    T temp = left;
//    left = right;
//    right = temp;
//}
//
//int main() {
//    int a = 1, b = 2;
//    Swap(a, b);
//    double c = 1.1, d = 2.2;
//    Swap(c, d);
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
//
//	// A(const A& a);
//
//	~A()
//	{
//		cout << "~A():" << this << endl;
//	}
//	private:
//		int _a;
//};
//
//template<class T>
//T Add(const T& left, const T& right)
//{
//    return left + right;
//}
//
//template<class T>
//T* poolNew(int n) {
//    //...
//    return new T[n];
//}
//
//int main()
//{
//    int a1 = 10, a2 = 20;
//    float d1 = 10.0, d2 = 20.0;
//
//    Add(a1, a2);
//    Add(d1, d2);
//    Add<int>(a1, d1);
//
//	A* p1 = poolNew<A>(3); //显式实例化
//
//    return 0;
//}
//

//// 专门处理 int 的加法函数
//int Add(int left, int right)
//{
//    return left + right;
//}
//
//// 通用加法函数
//template<class T1, class T2>
//T1 Add(T1 left, T2 right)
//{
//    return left + right;
//}
//
//int main()
//{
//    // 普通函数和函数模板都能精确匹配；
//    // 匹配程度相同时，优先调用普通函数 Add(int, int)
//    Add(1, 2);
//
//    // 普通函数需要把 double 转换成 int；
//    // 函数模板可推导出 T1=int、T2=double，两个参数均精确匹配，
//    // 因此函数模板匹配程度更高，调用 Add<int, double>(int, double)
//    Add(1, 2.0);
//}
template<typename T>
class Stack {
public:
	Stack()
		:_top(0) {
	}

	void Push(const T& x); 
private:
	T* _a;
	int _top;
	int _capacity;
};

// 模版不建议声明和定义分离到两个文件.h 和.cpp会出现链接错误
template<typename T>
void Stack<T>::Push(const T& x) {

}

class A {
public:
	A(int n = 10)
		:_n(n)
	{
		//....
	}
	//...
private:
	int _n;
};

int main() {
	//一个类模板实例化出不同的类型
	Stack<int> st1; //int
	Stack<double> st2; //double
	Stack<A> st3;

	A aa1(1);
	st3.Push(aa1);
	st3.Push(2);
	st3.Push(A(3));	
	return 0;
}






