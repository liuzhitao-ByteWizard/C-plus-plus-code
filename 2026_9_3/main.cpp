#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;

//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	void Print()
//	{
//		cout << _year << "/" << _month << "/" << _day << endl;
//	}
//
//	~Date() {
//		cout << this <<"~Date()" << endl;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//
//int main() {
//	//后构造的对象先执行析构
//	Date d1;
//	Date d2;
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//typedef int STDataType;
//class Stack
//{
//public:
//    Stack(int n = 4) //全缺省的默认构造函数
//    {
//        _a = (STDataType*)malloc(sizeof(STDataType) * n); 
//        if (nullptr == _a)
//        {
//            perror("malloc申请空间失败");
//            return;
//        }
//
//        _capacity = n;
//        _top = 0;
//    }
//
//    ~Stack() {  //析构函数
//        cout << this <<"~Stack()" << endl;
//        free(_a);
//        _a = nullptr; //建议在C++不要使用NULL
//        _top = _capacity = 0;
//    }
//
//private:
//    STDataType* _a;
//    size_t _capacity;
//    size_t _top;
//};
//
//// 两个Stack实现队列
//class MyQueue
//{
//public:
//    // 编译器默认生成MyQueue的析构函数调用了Stack的析构，释放的Stack内部的资源
//
//    // 显示写析构，也会自动调用Stack的析构
//    /*~MyQueue()
//    {}*/
//
//private:
//    Stack pushst;
//    Stack popst;
//};
//
//int main()
//{
//    Stack st;
//
//    MyQueue mq;
//    return 0;
//}

//// 用最新加了构造和析构的C++版本Stack实现
//bool isValid(const char* s) {
//    Stack st;
//
//    while (*s) {
//        if (*s == '(' || *s == '[' || *s == '{') {
//            // 左括号入栈
//            st.Push(
//            );
//        }
//        else {
//            // 栈为空，说明右括号多于左括号
//            if (st.Empty()) {
//                return false;
//            }
//
//            int top = st.Pop();
//
//            // 判断左右括号的类型是否匹配
//            if ((top == '(' && *s != ')')
//                || (top == '[' && *s != ']')
//                || (top == '{' && *s != '}')) {
//                return false;
//            }
//        }
//
//        ++s;
//    }
//
//    // 栈不为空，说明存在未匹配的左括号
//    return st.Empty();
//}
//
//int main()
//{
//    cout << isValid("[()][]") << endl;
//    cout << isValid("[(])[]") << endl;
//
//    return 0;
//}

//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
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
//};
//
//int main() {
//	Date d1;
//	//调用拷贝构造函数
//	Date d2(d1);
//	d2.Print();
//	return 0;
//}

//#include<iostream>
//using namespace std;
//
//typedef int STDataType;
//
//class Stack
//{
//public:
//    Stack(int n = 4)
//    {
//        _a = (STDataType*)malloc(sizeof(STDataType) * n);
//        if (nullptr == _a)
//        {
//            perror("malloc申请空间失败");
//            return;
//        }
//
//        _capacity = n;
//        _top = 0;
//    }
//
//    //深拷贝
//    Stack(const Stack& st) {
//        _a = (STDataType*)malloc(sizeof(STDataType) * st._capacity); //开辟跟它一样大小的空间
//        if (nullptr == _a)
//        {
//            perror("malloc申请空间失败");
//            return;
//        }
//        memcpy(_a, st._a, sizeof(STDataType) * st._top);  //st._top代表当前栈中有效元素的大小
//        _capacity = st._capacity;
//        _top = st._top;
//
//    }
//
//    void Push(STDataType x)
//    {
//        if (_top == _capacity)
//        {
//            int newcapacity = _capacity * 2;
//            STDataType* tmp =
//                (STDataType*)realloc(_a, newcapacity * sizeof(STDataType));
//
//            if (tmp == NULL)
//            {
//                perror("realloc fail");
//                return;
//            }
//
//            _a = tmp;
//            _capacity = newcapacity;
//        }
//
//        _a[_top++] = x;
//    }
//
//    ~Stack()
//    {
//        cout << "~Stack()" << endl;
//
//        free(_a);
//        _a = nullptr;
//        _top = _capacity = 0;
//    }
//
//private:
//    STDataType* _a;
//    size_t _capacity;
//    size_t _top; //栈顶的下一个位置
//};
//
//// 两个Stack实现队列
//class MyQueue
//{
//public:
//private:
//    Stack pushst;
//    Stack popst;
//};
//
//int main()
//{
//    Stack st1;
//    st1.Push(1);
//    st1.Push(2);
//
//    // Stack不显示实现拷贝构造，用自动生成的拷贝构造完成浅拷贝
//    // 会导致st1和st2里面的_a指针指向同一块资源，析构时会析构两次，程序崩溃
//    Stack st2 = st1;
//
//    MyQueue mq1;
//
//    // MyQueue自动生成的拷贝构造，会自动调用Stack拷贝构造完成pushst/popst
//    // 的拷贝，只要Stack拷贝构造自己实现了深拷贝，他就没问题
//    MyQueue mq2 = mq1;
//
//    return 0;
//}

//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	// Date d3(d2);
//	Date(const Date& d) {
//		_year = d._year;
//		_month = d._month;
//		_day = d._day;
//	}
//
//	void Print()
//	{
//		cout << _year << "/" << _month << "/" << _day << endl;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//class Stack
//{
//public:
//	Stack(int n = 4)
//	{
//		_a = (int*)malloc(sizeof(int) * n);
//		if (nullptr == _a)
//		{
//			perror("malloc申请空间失败");
//			return;
//		}
//		_capacity = n;
//		_top = 0;
//	}
//
//	~Stack() {
//		cout << this << "~Stack()" << endl;
//
//		if (_a) {
//			free(_a);
//			_a = nullptr;
//			_top = _capacity = 0;
//		}
//	}
//
//private:
//	int* _a;
//	size_t _capacity;
//	size_t _top;
//};
//
//class MyQueue {
//public:
//private:
//	Stack _st1;
//	Stack _st2;
//};
//

//#include<iostream>
//using namespace std;
//
//class Date
//{
//public:
//    Date(int year = 1, int month = 1, int day = 1)
//    {
//        _year = year;
//        _month = month;
//        _day = day;
//    }
//
//
//    Date(const Date& d)
//    {
//        _year = d._year;
//        _month = d._month;
//        _day = d._day;
//    }
//
//    void Print()
//    {
//        cout << _year << "-" << _month << "-" << _day << endl;
//    }
//
//    bool operator==(Date& d2) {
//        return _year == d2._year
//            && _month == d2._month
//            && _day == d2._day;
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
//    Date d1(2024, 7, 5); //调用构造函数
//    Date d2(2024, 7, 5); //调用构造函数
//
//    
//
//    cout << (d1 == d2) << endl; // d1 == d2 会自动调用重载函数，没有重载函数，则编译报错
//    return 0;
//}

#include<iostream>
using namespace std;

class Date
{
public:
    Date(int year = 1, int month = 1, int day = 1)
    {
        _year = year;
        _month = month;
        _day = day;
    }

    void Print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }

    bool operator==(const Date& d)
    {
        return _year == d._year
            && _month == d._month
            && _day == d._day;
    }

private:
    int _year;
    int _month;
    int _day;
};

int main()
{
    Date d1(2024, 7, 5);
    Date d2(2024, 7, 6);

    // 运算符重载函数可以显示调用
    d1.operator==(d2);

    // 编译器会转换成 d1.operator==(d2);
    d1 == d2;

    //cout << d1 == d2 << endl; err  流插入运算符的优先级高于等于符号的优先级
    cout << (d1 == d2) << endl;

    return 0;
}
