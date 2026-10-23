#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>

using namespace std;

//class Person
//{
//public:
//    Person(const char* name)
//        : _name(name)
//    {
//    }
//
//    string _name; // 姓名
//};
//
//class Student : virtual public Person
//{
//public:
//    Student(const char* name, int num)
//        : Person(name)
//        , _num(num)
//    {
//    }
//
//protected:
//    int _num; // 学号
//};
//
//class Teacher : virtual public Person
//{
//public:
//    Teacher(const char* name, int id)
//        : Person(name)
//        , _id(id)
//    {
//    }
//
//protected:
//    int _id; // 职工编号
//};
//
//// 不要去玩菱形继承
//class Assistant : public Student, public Teacher
//{
//public:
//    //菱形继承的正确使用方式
//    Assistant(const char* name3)
//        : Person(name3)
//        , Student("", 1)
//        , Teacher("", 2)
//    {
//    }
//};
//
//int main()
//{
//    Assistant b("zhansan"); //现实使用菱形继承进行初始化（构造）
//
//    return 0;
//}

//class Base1 { public: int _b1; };
//class Base2 { public: int _b2; };
//class Derive : public Base1, public Base2 { public: int _d; };
//
//int main()
//{
//    Derive d;
//    Base1* p1 = &d;
//    Base2* p2 = &d;
//    Derive* p3 = &d;
//
//    return 0;
//}

////1.必须是继承状态下的基类或者派生类
//class Person
//{
//public:
//	//2.调用函数（行为）是虚函数，且需要完成重写
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//
//class Student : public Person {
//public:
//	// 重写基类的虚函数 - 重写虚函数的实现
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//};
//
////不仅仅是发生在基类与基类之间，它也有可能发生在两个派生类对象之间
//class Soldier : public Student {
//public:
//	virtual void BuyTicket() { cout << "买票-优先" << endl; }
//};
//
////同一个行为，调用不同类型的对象会产生不同的效果
////void Func(Person* p) 
//void Func(Person& p) {
//	p.BuyTicket();
//}
//
//int main() {
//	Person p1;
//	Student s1;
//	Soldier s2;
//	Func(p1);
//	Func(s1);
//	Func(s2);
//	return 0;
//}

//class Animal
//{
//public:
//    virtual void talk() const
//    {
//    }
//};
//
//class Dog : public Animal
//{
//public:
//    virtual void talk() const
//    {
//        std::cout << "汪汪" << std::endl;
//    }
//};
//
//class Cat : public Animal
//{
//public:
//    virtual void talk() const
//    {
//        std::cout << "(>^ω^<)喵" << std::endl;
//    }
//};
//
//void letsHear(Animal& animal)
//{
//    animal.talk();
//}
//
//int main()
//{
//    Cat cat;
//    Dog dog;
//
//    letsHear(cat);
//    letsHear(dog);
//
//    return 0;
//}

class A
{
public:
    virtual void func(int val = 1)
    {
        std::cout << "A->" << val << std::endl;
    }
    virtual void test()
    {
        func();
    }

};

class B : public A
{
public:
    void func(int val = 0)
    {
        std::cout << "B->" << val << std::endl;
    }

};

int main(int argc, char* argv[])
{
    B* p = new B;
    p->test();

    return 0;
}


