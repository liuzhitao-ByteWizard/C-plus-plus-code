#define _CRT_SECURE_NO_WARNINGS 1
//#pragma once
//// test.cpp
//#include "Stack.h"
//
//// 全局定义了一份单独的Stack
//typedef struct Stack
//{
//    int a[10];
//    int top;
//} ST;
//
//void STInit(ST* ps) {}
//void STPush(ST* ps, int x) {}
//
//int main()
//{
//    // 调用全局的
//    ST st1;
//    STInit(&st1);
//    STPush(&st1, 1);
//    STPush(&st1, 2);
//    printf("%d\n", sizeof(st1));
//
//    // 调用bit namespace的
//    bit::ST st2;
//    printf("%d\n", sizeof(st2));
//    bit::STInit(&st2);
//    bit::STPush(&st2, 1);
//    bit::STPush(&st2, 2);
//
//    return 0;
//}

//#include <iostream>
//
//int main() {
//	std::cout << "hello world" << std::endl;
//	return 0;
//}
//
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    int a = 0;
//    double b = 0.1;
//    char c = 'x';
//
//    cout << a << " " << b << " " << c << endl;  //这种写法在不展开命名空间下会报错
//    std::cout << a << " " << b << " " << c << std::endl;
//
//    scanf("%d%lf", &a, &b);
//    printf("%d %lf\n", a, b);
//
//    // 可以自动识别变量的类型
//    cin >> a;
//    cin >> b >> c;
//
//    cout << a << endl;
//    cout << b << " " << c << endl;
//
//    return 0;
//}

//#include <iostream>
//
//namespace byte {
//	int n = 10;
//
//	struct Node {
//		int nal;
//		struct Node* next;
//	};
//}
//
//using byte::n;
//

//#include <iostream>
//#include <assert.h>
//using namespace std;
//
//void Func(int a = 0)
//{
//    cout << a << endl;
//}
//
//int main()
//{
//    Func();    // 没有传参时，使用参数的默认值
//    Func(10);  // 传参时，使用指定的实参
//
//    return 0;
//}

//#include <iostream>
//using namespace std;
//
//// 全缺省
//void Func1(int a = 10, int b = 20, int c = 30)
//{
//    cout << "a = " << a << endl;
//    cout << "b = " << b << endl;
//    cout << "c = " << c << endl << endl;
//}
//
//// 半缺省
//void Func2(int a, int b = 10, int c = 20)
//{
//    cout << "a = " << a << endl;
//    cout << "b = " << b << endl;
//    cout << "c = " << c << endl << endl;
//}
//
//int main()
//{
//    Func1();
//    Func1(1);
//    Func1(1, 2);
//    Func1(1, 2, 3);
//
//    Func2(100);
//    Func2(100, 200);
//    Func2(100, 200, 300);
//
//    return 0;
//}

// test.cpp
#include "Stack.h"

int main()
{
    ST s1;
    STInit(&s1);

    // 确定知道要插入1000个数据，初始化时一把开好，避免扩容
    ST s2;
    STInit(&s2, 1000);

    return 0;
}