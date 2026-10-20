//#include "stack.h"
//int main()
//{
//    
//    Add(1, 2);
//    Add(1.0, 2.0);
//
//    return 0;
//}

/////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

////基类
//class Person
//{
//public:
//    // 进入校园/图书馆/实验室刷二维码等身份认证
//    void identity()
//    {
//        cout << "void identity()" << _name << endl;
//    }
//
//protected:
//    string _name = "张三"; // 姓名
//    string _address;      // 地址
//    string _tel;          // 电话
//    int _age = 18;        // 年龄
//};
//
////派生类
//class Student : public Person
//{
//public:
//    // 学习
//    void study()
//    {
//        // ...
//    }
//
//protected:
//    int _stuid; // 学号
//};
//
////派生类
//class Teacher : public Person
//{
//public:
//    // 授课
//    void teaching()
//    {
//        // ...
//    }
//
//protected:
//    string title; // 职称
//};
//
//int main()
//{
//    Student s;
//    Teacher t;
//
//    s.identity();
//    t.identity();
//
//    return 0;
//}
//class Person
//{
//	//1.声明为友元类
//	friend class Student;
//public:
//	void func() { cout << _age << endl; }
//private:
//	string _name = "张三"; // 姓名
//	string _address; // 地址
//	string _tel;     // 电话
//	int _age = 18; // 年龄 == 私房钱
//};
//
//class Student : public Person
//{
//
//public:
//	void study()
//	{
//		cout << _tel << endl;
//		cout << _age << endl; 
//		//2.调用基类函数间接访问
//		func();
//	}
//
//protected:
//	int _stuid; // 学号
//};
//
//int main() {
//	Student s;
//	s.study();
//	return 0;
//}

//namespace byte {
//	template<class T>
//	class Stack : public std::vector<T> {
//	public:
//		//int size() { return size(); } //需要指定类域
//		int size() { return vector<T>::size(); }
//	};
//}
//
//int main() {
//	byte::Stack<int> st1;
//	cout << st1.size() << endl;
//	return 0;
//}

//#include <iostream>
//#include <vector>
//
//namespace byte
//{
//    // 通过继承复用 vector 的尾部操作，实现“后进先出”的栈。
//    template<class T>
//    class stack : public std::vector<T>
//    {
//    public:
//        void push(const T& x)
//        {
//            // std::vector<T> 依赖于模板参数 T，属于依赖基类。
//            // 模板定义阶段，普通的未限定名称查找不会搜索依赖基类。
//            // 因此显式指定基类作用域，也可以写 this->push_back(x)。
//            std::vector<T>::push_back(x);
//        }
//
//        void pop()
//        {
//            std::vector<T>::pop_back();
//        }
//
//        const T& top()
//        {
//            return std::vector<T>::back();
//        }
//
//        bool empty()
//        {
//            // 明确调用基类的 empty()。
//            // 如果写成 this->empty()，会递归调用当前函数。
//            return vector<T>::empty();
//        }
//    };
//}
//
//int main()
//{
//    byte::stack<int> st;
//
//    st.push(1);
//    st.push(2);
//    st.push(3);
//
//    while (!st.empty())
//    {
//        std::cout << st.top() << " ";
//        st.pop();
//    }
//
//    return 0;
//}
//
////基类
//class Person
//{
//public:
//    // 进入校园/图书馆/实验室刷二维码等身份认证
//    void identity()
//    {
//        cout << "void identity()" << _name << endl;
//    }
//
//protected:
//    string _name = "张三"; // 姓名
//    string _address;      // 地址
//    string _tel;          // 电话
//    int _age = 18;        // 年龄
//};
//
////派生类
//class Student : public Person
//{
//public:
//    // 学习
//    void study()
//    {
//        // ...
//    }
//
//protected:
//    int _stuid; // 学号
//};
//
////派生类
//class Teacher : public Person
//{
//public:
//    // 授课
//    void teaching()
//    {
//        // ...
//    }
//
//protected:
//    string title; // 职称
//};
//
//void test() {
//    Student s;
//    Person& a = s; //a就是s中基类的别名 ， 引用的是派生类当中基类的那一部分
//    Person* b = &s;
//    //Person d;
//    //Student& b = d; 需要拷贝构造或赋值重载
//    // Person p;
//    //Student* st = &p; 不一定err
//
//}
//
//int main() {
//	double a = 2;
//	const int& b = a; //存在类型转换时（赋值给某一个对象的指针或者引用）时
//	//临时对象具有常性，需要加上const
//
//	return 0;
//}

//class Person
//{
//protected:
//	string _name = "小李子"; // 姓名
//	int _num = 111; // 身份证号
//};
//
//class Student : public Person
//{
//public:
//	void Print()
//	{
//		cout << " 姓名:" << _name << endl;
//		cout << " 身份证号:" << Person::_num << endl; //如果想访问基类成员的话，指定类域
//		cout << " 学号:" << _num << endl; //999
//	}
//protected:
//	int _num = 999; // 学号
//};
//
//int main() {
//	Student s1;
//	s1.Print();
//}
//
//class A
//{
//public:
//    void fun()
//    {
//        cout << "func()" << endl;
//    }
//};
//
//class B : public A
//{
//public:
//    void fun(int i)
//    {
//        cout << "func(int i)" << i << endl;
//    }
//};
//
//int main()
//{
//    B b;
//    b.fun(10);
//    b.A::fun();
//
//    return 0;
//};

//class Person final
//{
//public:
//
//	~Person()
//	{
//		cout << "~Person()" << endl;
//	}
//protected:
//	string _name; // 姓名
//};
//
//class Student : public Person
//{
//public:
//
//	~Student() {
//		//~Person(); 构成函数隐藏
//		Person::~Person();
//		cout << "~Student()" << endl;
//	}
//private:
//	int _num;
//};
////
////int main() {
////	Student s1("zhansan", 10);
////	Student s2("lisi", 20);
////	s2 = s1;
////
////	return 0;
////}
//int main() {
//	Student s;
//	return 0;
//}

////因为需要在student类前面使用友元声明，需要加上前置声明
//class Student;
//
//class Person
//{
//public:
//    friend void Display(const Person& p, const Student& s);
//
//protected:
//    string _name; // 姓名
//};
//
//class Student : public Person
//{
//    friend void Display(const Person& p, const Student& s);
//protected:
//    int _stuNum; // 学号
//};
//
//void Display(const Person& p, const Student& s)
//{
//    cout << p._name << endl;
//    cout << s._stuNum << endl;
//}
//
//int main() {
//    Student s;
//    Person p;
//    Display(p,s);
//    return 0;
//
//}

//#include <iostream>
//#include <string>
//using namespace std;
//
//class Person
//{
//public:
//    string _name;
//    static int _count;
//};
//
//int Person::_count = 0;
//
//class Student : public Person
//{
//protected:
//    int _stuNum;
//};
//
//int main()
//{
//    Person p;
//    Student s;
//
//    // 非静态成员 _name 的地址不同，
//    // 说明基类对象和派生类对象各自拥有一份 _name。
//    cout << &p._name << endl;
//    cout << &s._name << endl;
//
//    // 静态成员 _count 的地址相同，
//    // 说明派生类和基类共用同一份静态成员。
//    cout << &p._count << endl;
//    cout << &s._count << endl;
//
//    // 在公有继承且静态成员为 public 的情况下，
//    // 可以通过基类名或派生类名指定作用域，访问同一个静态成员。
//    cout << Person::_count << endl;
//    cout << Student::_count << endl;
//
//    return 0;
//}


class Person
{
public:
    string _name; // 姓名
};

class Student : virtual public Person
{
protected:
    int _num; // 学号
};

class Teacher : virtual public Person
{
protected:
    int _id; // 职工编号
};

class Assistant : public Student, public Teacher
{
protected:
    string _majorCourse; // 主修课程
};

int main()
{
    // 编译报错：error C2385：对“_name”的访问不明确
    Assistant a;
    //a._name = "peter";

    //// 显式指定访问哪个基类的成员，可以解决二义性问题，
    //// 但是无法解决数据冗余问题。
    //a.Student::_name = "xxx";
    //a.Teacher::_name = "yyy";

    a._name = "abc";
    return 0;
}




