#include <iostream>
//using namespace std;

//class Stack {
//public:
//	Stack(int n = 4)
//	:_n(n)
//	{
//
//	}
//private:
//	int _n;
//	int _size;
//	int _capacity;
//};
//
//class MyQueue {
//public:
//	//默认构造函数
//	MyQueue(int n = 4)
//		:_n(n)
//	{
//
//	}
//private:
//	int _n;
//	Stack _n1;
//	Stack _n2;
//};
//
//int main() {
//	MyQueue q;
//	return 0;
//}

//class Time
//{
//public:
//    Time(int hour)
//        : _hour(hour)
//    {
//        cout << "Time()" << endl;
//    }
//
//private:
//    int _hour;
//};
//
//class Date
//{
//public:
//    Date()
//        : _month(2)
//    {
//        cout << "Date()" << endl;
//    }
//
//    void Print() const
//    {
//        cout << _year << "-" << _month << "-" << _day << endl;
//    }
//
//private:
//    // 注意这里不是初始化，这里给的是缺省值，这个缺省值是给初始化列表的
//    // 如果初始化列表没有显式初始化，默认就会用这个缺省值初始化
//    int _year = 1;
//    int _month = 1;
//    int _day;
//
//    Time _t = 1;
//    const int _n = 1;
//    int* _ptr = (int*)malloc(12);
//};
//
//int main()
//{
//    Date d1;
//    d1.Print();
//
//    return 0;
//}

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//    A(int a)
//        : _a1(a),
//        _a2(_a1)
//    {
//    }
//
//    void Print()
//    {
//        cout << _a1 << " " << _a2 << endl;
//    }
//
//private:
//    int _a2 = 2;
//    int _a1 = 2;
//};
//
//int main()
//{
//    A aa(1);
//    aa.Print();
//}

//int main() {
//	// C 相近类型之间转换 隐式(接近) 显示(不那么接近，有一定的关联) 无关(不能)
//	// int/unsigned int/char/double 隐式 类型意义:表示数据大小
//	int i = 0;
//	char ch = i;
//	double d = i;
//
//	int* p1 = (int*)i; //报警告，这里面存在着整型提升
//	int j = 0x01020304;
//	// int* p2 = (int*)d; // error C2440: “类型强制转换”: 无法从“double”转换为“int *”
//	//地址本质上来看，其实就是一个整型
//
//	return 0;
//}
//class A
//{
//public:
//	A(int a1)
//		:_a1(a1)
//	{
//		cout << "A(int a1)" << endl;
//	}
//
//	//显示化定义，就跟缺省值没有关系了
//	 A(int a1, int a2)
//		:_a1(a1)
//		,_a2(a2)
//	{
//		cout << "A(int a1, int a2)" << endl;
//	}
//
//	A(const A& a) {
//		_a1 = a._a1;
//		_a2 = a._a2;
//	}
//
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//
//class Array {
//public:
//	void PushBack(const A& a) {	
//	}
//};
//
//
//
//int main() {
//	// 构造
//	A aa1(1);
//	// 类型转换
//	// 构造+拷贝构造+优化->构造
//	A aa2 = 1;
//
//	const A& aa3 = 1;
//
//	Array a;
//	//c++11
//	a.PushBack(aa2);
//}

//class A
//{
//public:
//	 A(int a1)
//		:_a1(a1)
//	{
//		cout << "A(int a1)" << endl;
//	}
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//
//class Array {
//public:
//	void PushBack(const A& a) {
//	}
//};
//
//int main() {
//	A aa1 = 1;
//
//	Array a;
//
//	a.PushBack(aa1);
//	a.PushBack(1);
//}

//int main() {
//	// 构造
//	A aa1(1);
//	// 类型转换
//	// 构造+拷贝构造+优化->构造
//	A aa2 = 1;
//
//	const A& aa3 = 1;
//
//	Array a;
//	//c++11
//	a.PushBack(aa2);
//}

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//    explicit A(int a1)
//        : _a1(a1)
//    {
//        cout << "A(int a1)" << endl;
//    }
//    explicit A(int a1, int a2)
//        : _a1(a1),
//        _a2(a2)
//    {
//        cout << "A(int a1, int a2)" << endl;
//    }
//
//    A(const A& a)
//    {
//        _a1 = a._a1;
//        _a2 = a._a2;
//    }
//
//private:
//    int _a1 = 1;
//    int _a2 = 2;
//};
//
//int main()
//{
//    A aa2 = 1;
//
//    const A& aa3 = 1;
//    return 0;
//}

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//    A(int a1, int a2)
//        : _a1(a1),
//        _a2(a2)
//    {
//    }
//
//    int Get() const
//    {
//        return _a1 + _a2;
//    }
//
//private:
//    int _a1 = 1;
//    int _a2 = 2;
//};
//
//class B
//{
//public:
//    B(const A& a)
//        : _b(a.Get())
//    {
//    }
//
//private:
//    int _b = 0;
//};
//
//int main()
//{
//    // C++11 之后才支持多参数转换
//    A aa3 = { 2, 2 };
//
//    // aa3 隐式类型转换为 B 对象
//    B b = aa3;
//    const B& rb = aa3;
//
//    return 0;
//}

/*class A {
public:
	//err
	//A(int n)
	//	:_a(n)
	//	,_b(n)
	//{

	//}
private:
	int _a = 1;
	//static int _b = 4; err
	static int _b;
};

//静态成员变量必须在类外进行初始化
int A::_b = 0;

int main() {
	A a;
	return 0;
}*/
//using std::endl;
//using std::cout;
//using std::cin;
//
//class A {
//public:
//	A(int a = 1)
//		:_a(a)
//	{
//		++_scount;
//	}
//
//	A(const A& aa)
//		:_a(aa._a)
//	{
//		++_scount;
//	}
//
//	// static成员函数，没有this指针
//	static int GetCount() {
//		// _a++; // 对非静态成员“A::_a”的非法引用, 没有this
//		return _scount;
//	}
//private:
//	int _a;
//	static int _scount; // 声明
//};
//
//int A::_scount = 0;
//
//int main() {
//	A aa1(1);
//	A aa2 = 2;
//
//	// public
//	//cout << A::_scount << endl;
//	//cout << aa1._scount << endl;
//
//	// private
//	cout << aa1.GetCount() << endl;
//	cout << A::GetCount() << endl;
//
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//class B;
//
//class A
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//
//class B
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _b1 = 3;
//	int _b2 = 4;
//};
//
//void func(const A& aa, const B& bb)
//{
//	cout << aa._a1 << endl;
//	cout << bb._b1 << endl;
//}
//
//int main()
//{
//	A aa;
//	B bb;
//	func(aa, bb);
//
//	return 0;
//}
//
//#include <iostream>
//using namespace std;
//
//class A
//{
//    friend class B;
//private:
//    int _a1 = 1;
//    int _a2 = 2;
//};
//
//class B
//{
//public:
//    void func1(const A& aa)
//    {
//        cout << aa._a1 << endl;
//        cout << _b1 << endl;
//    }
//
//    void func2(const A& aa)
//    {
//        cout << aa._a2 << endl;
//        cout << _b2 << endl;
//    }
//
//private:
//    int _b1 = 3;
//    int _b2 = 4;
//};
//
//int main()
//{
//    A aa;
//    B bb;
//
//    bb.func1(aa);  // 输出 1、3
//    bb.func2(aa); // 输出 2、4
//    return 0;
//}

//#include <iostream>
//using namespace std;
//
//class B;
//
//class A
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//
//class B
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _b1 = 3;
//	int _b2 = 4;
//};
//
//void func(const A& aa, const B& bb)
//{
//	cout << aa._a1 << endl;
//	cout << bb._b1 << endl;
//}
//
//int main()
//{
//	A aa;
//	B bb;
//	func(aa, bb);
//
//	return 0;
//}
//
#include <iostream>
using namespace std;

class A
{
public:
	class B
	{
	public:
		void func2(const A& aa) {
			cout << aa._a1 << endl;
			cout << aa._a2 << endl;
		}
	private:
		int _b1 = 3;
		int _b2 = 4;
	};
private:
    int _a1 = 1;
    int _a2 = 2;
};

int main()
{
	A aa;
	A::B bb;
	bb.func2(aa);

    return 0;
}




