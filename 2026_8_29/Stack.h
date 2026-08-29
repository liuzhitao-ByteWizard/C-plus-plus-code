#pragma once
//// 多文件中可以定义同名namespace，他们会默认合并到一起，就像同一个namespace一样
//// Stack.h
//#pragma once
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <assert.h>
//
//namespace bit
//{
//    typedef int STDataType;
//
//    typedef struct Stack
//    {
//        STDataType* a;
//        int top;
//        int capacity;
//    } ST;
//
//    void STInit(ST* ps);
//    void STDestroy(ST* ps);
//
//    void STPush(ST* ps, STDataType x);
//    void STPop(ST* ps);
//    STDataType STTop(ST* ps);
//    int STSize(ST* ps);
//    bool STEmpty(ST* ps);
//}

#include <iostream>
#include <assert.h>
using namespace std;

typedef int STDataType;

typedef struct Stack
{
    STDataType* a;
    int top;
    int capacity;
} ST;


//只能在函数声明中给缺省值
void STInit(ST* ps, int n = 4);