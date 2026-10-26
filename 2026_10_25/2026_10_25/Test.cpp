//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//private:
//	string _name;
//};
//
//class Student : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//	virtual void Func2()
//	{
//		cout << "Func2()" << endl;
//	}
//private:
//	string _id;
//};
//
//void Func(Person& ptr)
//{
//	ptr.BuyTicket();
//}
//
//
//int main() {
//	Person p1;
//	Student s1;
//	Func(p1);
//	Func(s1);
//	return 0;
//}


//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//private:
//	string _name;
//};
// 
// 


//int main() {
//	Person p1;
//	Person p2;
//	Person p3;
//	Person p4;
//	Student s1;
//	Func(p1);
//	Func(s1);
//	return 0;
//}

//class Base {
//public:
//    virtual void func1() { cout << "Base::func1" << endl; }
//    virtual void func2() { cout << "Base::func2" << endl; }
//
//    void func5() { cout << "Base::func5" << endl; }
//
//protected:
//    int a = 1;
//};
//
//class Derive : public Base
//{
//public:
//    // 重写基类的func1
//    virtual void func1() { cout << "Derive::func1" << endl; }
//    virtual void func3() { cout << "Derive::func1" << endl; }
//
//    void func4() { cout << "Derive::func4" << endl; }
//
//protected:
//    int b = 2;
//};
//
//
//int main()
//{
//    int i = 0;
//    static int j = 1;
//    int* p1 = new int;
//    const char* p2 = "xxxxxxxx";
//
//    printf("栈:%p\n", &i);
//    printf("静态区:%p\n", &j);
//    printf("堆:%p\n", p1);
//    printf("常量区:%p\n", p2);
//
//    Base b;
//    Derive d;
//    Base* p3 = &b;
//    Derive* p4 = &d;
//
//    //取虚函数表指针在64位环境下
//    printf("Person虚表地址:%p\n", *(long long*)p3);
//    printf("Student虚表地址:%p\n", *(long long*)p4);
//
//    return 0;
//}

//class Base {
//public:
//    virtual void func1() { cout << "Base::func1" << endl; }
//    virtual void func2() { cout << "Base::func2" << endl; }
//
//    void func5() { cout << "Base::func5" << endl; }
//
//protected:
//    int a = 1;
//};
//
//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//private:
//	string _name;
//};
//
//class Derive : public Base ,  public Person
//{
//public:
//    // 重写基类的func1
//    virtual void func1() { cout << "Derive::func1" << endl; }
//    virtual void func3() { cout << "Derive::func1" << endl; }
//
//    void func4() { cout << "Derive::func4" << endl; }
//
//protected:
//    int b = 2;
//};
//
//int main() {
//    Derive d1;
//
//    return 0;
//}

////////////////////////////////////////////////
#include "BinarySearchTree.h"

int main() {
	BSTree<int> t;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a) {
		t.InsertR(e);
	}
	t.Inorder();
	cout << t.FindR(1) << endl;
}