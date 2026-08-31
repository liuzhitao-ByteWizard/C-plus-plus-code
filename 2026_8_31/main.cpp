#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//using namespace std;
//
//// 1、参数类型不同
//int Add(int left, int right)
//{
//    cout << "int Add(int left, int right)" << endl;
//
//    return left + right;
//}
//
//double Add(double left, double right)
//{
//    cout << "double Add(double left, double right)" << endl;
//
//    return left + right;
//}
//
//// 2、参数个数不同
//void f()
//{
//    cout << "f()" << endl;
//}
//
//void f(int a)
//{
//    cout << "f(int a)" << endl;
//}
//
//// 3、参数类型顺序不同
//void f(int a, char b)
//{
//    cout << "f(int a,char b)" << endl;
//}
//
//void f(char b, int a)
//{
//    cout << "f(char b, int a)" << endl;
//}

// 返回值不同不能作为重载条件，因为调用时也无法区分
// void fxx()
// {
// }
//
// int fxx()
// {
//     return 0;
// }

// 下面两个函数构成重载
// f()但是调用时，会报错，存在歧义，编译器不知道调用谁
//void f1()
//{
//    cout << "f()" << endl;
//}
//
//void f1(int a = 10)
//{
//    cout << "f(int a)" << endl;
//}

//int main()
//{
//    Add(10, 20);
//    Add(10.1, 20.2);
//
//    f();
//    f(10);
//
//    f(10, 'a');
//    f('a', 10);
//
//    return 0;
//}

//#include <iostream>
//using  namespace std;
//
//int main() {
//	//cout底层使用了函数重载
//	cout << 1 << endl;
//	cout << "hello world" << endl;
//	cout << 1.11 << endl;
//}

//#include <stdio.h>
//
//int main() {
//    int a = 0;
//    int f = 2;
//
//    // 引用：b和c是a的别名（一个变量可以有多个别名）
//    int& b = a;
//    int& c = a;
//
//    // 也可以给别名b取别名，d相当于还是a的别名
//    int& d = b;
//
//    b = f; //本质上是赋值
//
//    //++d;
//
//    // 这里取地址我们看到是一样的
//    //printf("%p\n", &a);
//    //printf("%p\n", &b);
//    //printf("%p\n", &c);
//    //printf("%p\n", &d);
//    printf("%d\n", a);
//    printf("%d\n", b);
//    printf("%d\n", c);
//    printf("%d\n", d);
//
//    return 0;
//}

//void Swap(int& x1, int& x2) {
//	int tmp = x1;
//	x1 = x2;
//	x2 = tmp;
//}
//
//
//int main() {
//	int a = 10, b = 20;
//	Swap(a, b); //使用引用之后传值就行，不需要传地址
//
//
//	return 0;
//}
//

//#include <stdio.h>
//void Swap(int* rx, int* ry)
//{
//    int tmp = *rx;
//    *rx = *ry;
//    *ry = tmp;
//}
//
//int main()
//{
//    int x = 0, y = 1;
//    printf("%d %d ", x, y);
//    Swap(&x, &y);
//    printf("%d %d", x, y);
//    return 0;
//}

//int Add(int x, int y) {
//	return x + y;
//}
//
//int main() {
//	Add(2, 3) += 2; //error C2106 : '+=' : 左操作数必须为左值
//	return 0;
//}


//#include <iostream>
//#include <assert.h>
//using namespace std;
//
//typedef int STDataType;
//typedef struct Stack
//{
//    STDataType* a;
//    int top;
//    int capacity;
//} ST;
//
//void STInit(ST& rs, int n = 4)
//{
//    rs.a = (STDataType*)malloc(n * sizeof(STDataType));
//    rs.top = 0;
//    rs.capacity = n;
//}
//
//// 入栈（压栈）
//void STPush(ST& rs, STDataType x)
//{
//    // 满了，扩容
//    if (rs.top == rs.capacity)
//    {
//        printf("扩容\n");
//        int newcapacity = rs.capacity == 0 ? 4 : rs.capacity * 2;
//        STDataType* tmp =
//            (STDataType*)realloc(rs.a, newcapacity * sizeof(STDataType));
//
//        if (tmp == NULL)
//        {
//            perror("realloc fail");
//            return;
//        }
//
//        rs.a = tmp;
//        rs.capacity = newcapacity;
//    }
//
//    rs.a[rs.top] = x;
//    rs.top++;
//}
//
//// 按值返回不能作为左值修改；这里按引用返回，使栈顶元素可以被修改
//int& STTop(ST& rs)
//{
//    assert(rs.top > 0);
//    // 返回栈顶元素的引用；该元素位于动态分配的数组中
//    return rs.a[rs.top - 1];
//}
//
//int main()
//{
//    // 创建局部栈对象，并调用全局函数进行操作
//    ST st1;
//    STInit(st1);
//    STPush(st1, 1);
//    STPush(st1, 2);
//
//    STTop(st1) += 10;
//
//    cout << STTop(st1) << endl;
//
//    return 0;
//}

//#include <stdio.h>
//
//int main() {
//	const int a = 10;
//
//	int& b = a; //权限放大
//	return 0;
//}

//#include <iostream>
//#include<list>
//#include<string>
//
//using namespace std;
//
//typedef string Type;
//
////void push_back(const value_type& val);
//int main() {
//
//	list<string> lt;
//	string s1("张三");
//	lt.push_back(s1); 
//
//	const string s2("李四");
//	lt.push_back(s2);
//
//	lt.push_back("王五");
//
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//inline int Add(int x, int y) {
//	return x + y;
//}
//
//int main() {
//	int a = 10, b = 20;
//	int c = Add(a, b);
//	return 0;
//}

#include <iostream>
using namespace std;

void f(int x)
{
    cout << "f(int x)" << endl;
}

void f(int* ptr)
{
    cout << "f(int* ptr)" << endl;
}

int main()
{
    f(0);

    // 本想通过 f(NULL) 调用指针版本的 f(int*) 函数，
    // 但是由于 NULL 被定义成 0，实际调用了 f(int x)，
    // 因此与程序的初衷相悖。
    f(NULL);

    f((int*)NULL);

    // 编译报错：error C2665：“f”：
    // 2 个重载中没有一个可以转换所有参数类型
    // f((void*)NULL);

    f(nullptr);

    return 0;
}



