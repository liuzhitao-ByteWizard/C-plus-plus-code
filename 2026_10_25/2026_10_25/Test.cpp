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

#include <iostream>
#include <string>
//#include "BinarySearchTree.h"
//
//int main()
//{
//    // 创建词典：英文单词作为 key，中文释义作为 value。
//    keyvalue::BSTree<std::string, std::string> dict;
//
//    // 插入词条；二叉搜索树根据英文单词进行比较和排序。
//    dict.Insert("left", "左边");
//    dict.Insert("right", "右边");
//    dict.Insert("insert", "插入");
//    dict.Insert("string", "字符串");
//
//    std::string str;
//
//    // 每次读取一个以空白分隔的单词，读取成功则继续循环。
//    // 遇到 EOF 或输入错误时退出循环。
//    // Windows 控制台：按 Ctrl+Z 后回车；Linux/macOS：在空行处按 Ctrl+D。
//    while (std::cin >> str)
//    {
//        // 查找单词：存在则返回对应结点的指针，不存在则返回 nullptr。
//        auto ret = dict.Find(str);
//
//        if (ret)
//        {
//            // 通过结点的 _value 成员取得并输出中文释义。
//            std::cout << "->" << ret->_value << std::endl;
//        }
//        else
//        {
//            // 词典中没有该单词，提示后继续读取下一次输入。
//            std::cout << "无此单词，请重新输入" << std::endl;
//        }
//    }
//
//    return 0;
//}

int main()
{
    string arr[] = {
        "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果",
        "西瓜", "苹果", "香蕉", "苹果", "香蕉"
    };

    keyvalue::BSTree<string, int> countTree1;

    for (auto& str : arr) {
        //没有，就插入到树中
        if (countTree1.Find(str) == nullptr) {
            countTree1.Insert(str, 1);
        }
        else {
            auto it = countTree1.Find(str);
            it->_value++;
        }
    }

    countTree1.Inorder();

    string arr1[] = {
    "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "10", "11"
    };

    //浅拷贝，两个对象指向同一块空间
    keyvalue::BSTree<string, int> countTree2;


    for (auto& str : arr1) {
        //没有，就插入到树中
        if (countTree2.Find(str) == nullptr) {
            countTree2.Insert(str, 1);
        }
        else {
            auto it = countTree2.Find(str);
            it->_value++;
        }
    }


    countTree1 = countTree2;


    countTree1.Inorder();
    countTree2.Inorder();


    return 0;
}
