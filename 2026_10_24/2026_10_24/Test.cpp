#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;
//
//class A {};
//class B : public A {};
//
//class Person
//{
//public:
//
//    virtual A* BuyTicket()
//    {
//        cout << "买票-全价" << endl;
//        return nullptr;
//    }
//};
//
//class Student : public Person
//{
//public:
//    virtual B* BuyTicket()
//    {
//        cout << "买票-打折" << endl;
//        return nullptr;
//    }
//};
//
//void Func(Person* ptr)
//{
//    ptr->BuyTicket();
//}
//
//int main()
//{
//    Person ps;
//    Student st;
//
//    Func(&ps);
//    Func(&st);
//
//    return 0;
//}

//class A
//{
//public:
//    virtual ~A()
//    {
//        cout << "~A()" << endl;
//    }
//};
//
//class B : public A
//{
//public:
//    ~B()
//    {
//        cout << "~B()->delete:" << _p << endl;
//        delete _p;
//    }
//
//protected:
//    int* _p = new int[10];
//};
//
//int main()
//{
//    A* p1 = new A;
//    A* p2 = new B;
//
//    delete p1;
//    delete p2;
//
//    return 0;
//}


// error C3668: “Benz::Drive”: 包含重写说明符“override”的方法没有重写任何基类方法
//class Car
//{
//public:
//    virtual void Dirve() final
//    {
//        cout << "Car" << endl;
//    }
//};
//
//class Benz : public Car
//{
//public:
//    void Dirve() 
//    {
//        cout << "Benz-舒适" << endl;
//    }
//};
//
//void Func(Car* c) {
//    c->Dirve();
//}
//
//int main()
//{
//    Car c1;
//    Benz b1;
//    Func(&c1);
//    Func(&b1);
//
//    return 0;
//}

//// 抽象类
//class Car
//{
//public:
//	//纯虚函数
//	virtual void Drive() const = 0;
//};
//
//class Benz :public Car
//{
//public:
//	virtual void Drive() const
//	{
//		cout << "Benz-舒适" << endl;
//	}
//};
//
//class BMW :public Car
//{
//public:
//	virtual void Drive() const
//	{
//		cout << "BMW-操控" << endl;
//	}
//};
//
//class WENJIE :public Car
//{
//public:
//	virtual void Drive() const
//	{
//		cout << "BMW-智能化" << endl;
//	}
//};
//
//void Func(const Car& p) {
//	p.Drive();
//}
//
//int main()
//{
//	// 编译报错：error C2259: “Car”: 无法实例化抽象类
//	// Car car;
//	//用匿名对象当参数
//	Func(Benz());
//	Func(BMW());
//	Func(WENJIE());
//
//	return 0;
//}

class Base
{
public:
    virtual void Func1()
    {
        cout << "Func1()" << endl;
    }

protected:
    int _b = 1;
    char _ch = 'x';
};

int main()
{
    Base b;
    cout << sizeof(b) << endl;

    return 0;
}





