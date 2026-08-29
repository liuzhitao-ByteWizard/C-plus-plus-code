#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
//int main() {
//	printf("hello world\n");
//	return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//
//namespace byte {
//    int rand = 10;
//}
//
//int main()
//{
//    printf("%p\n", rand);  // rand 是函数名，在此退化为函数指针
//    printf("%d\n", byte::rand); // 输出命名空间 byte 中的变量 rand
//    return 0;
//}

//#include <stdio.h>
//
//int rand = 10;
//
//int main()
//{
//    int rand = 1;
//    printf("%d\n", rand); // 访问的是局部的rand
//    // ::域作用限定符
//    printf("%d\n", ::rand);
//    return 0;
//}

//#include <stdio.h>
//
//namespace byte
//{
//    namespace h1
//    {
//        int rand = 1;
//
//        int Add(int left, int right)
//        {
//            return left + right;
//        }
//
//        struct Node {
//            struct Node* next;
//            int val;
//        };
//    }
//
//    namespace h2
//    {
//        int rand = 2;
//
//        int Add(int left, int right)
//        {
//            return (left + right) * 10;
//        }
//
//        struct Node {
//            struct Node* next;
//            int val;
//        };
//    }
//}
//
//int main()
//{
//    struct byte::h1::Node;
//    struct byte::h2::Node;
//    printf("%d\n", byte::h1::rand);
//    printf("%d\n", byte::h2::rand);
//
//    printf("%d\n", byte::h1::Add(1, 2));
//    printf("%d\n", byte::h2::Add(1, 2));
//
//    return 0;
//}

// Stack.cpp
#include "Stack.h"

// 缺省参数不能声明和定义同时给
void STInit(ST* ps, int n)
{
    assert(ps && n > 0);

    ps->a = (STDataType*)malloc(n * sizeof(STDataType));
    ps->top = 0;
    ps->capacity = n;
}

