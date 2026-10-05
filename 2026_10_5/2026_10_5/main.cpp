#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct Node {
    int data;
    struct Node* next;
} Node;


void mergeIncreasing(Node* A, Node* B)
{
    Node* p = A->next, * q = B->next;
    Node* tail = A, * s, * t;

    while (p && q) {
        if (p->data < q->data) {
            s = p;
            p = p->next;
        }
        else if (p->data > q->data) {
            s = q;
            q = q->next;
        }
        else {
            // 值相等：保留 A 的结点，释放 B 的结点
            s = p;
            p = p->next;

            t = q;
            q = q->next;
            free(t);
        }

        tail->next = s;
        tail = s;
    }

    tail->next = p ? p : q;
    B->next = NULL;
}

void mergeDecreasing(Node* A, Node* B)
{
    Node* p = A->next, * q = B->next, * s;
    A->next = NULL;

    while (p || q) {
        // B 已取完，或 A 当前结点的值较小
        if (!q || (p && p->data <= q->data)) {
            s = p;
            p = p->next;
        }
        else {
            s = q;
            q = q->next;
        }

        // 头插：先保存原后继，再修改 s->next
        s->next = A->next;
        A->next = s;
    }

    B->next = NULL;
}

void intersection(Node* A, Node* B)
{
    Node* pre = A;
    Node* p = A->next, * q = B->next, * s;

    while (p && q) {
        if (p->data < q->data) {
            s = p;
            p = p->next;
            pre->next = p;
            free(s);
        }
        else if (p->data > q->data) {
            q = q->next;
        }
        else {
            // 属于交集，保留 A 的结点
            pre = p;
            p = p->next;
            q = q->next;
        }
    }

    // A 剩余的结点均不属于交集
    while (p) {
        s = p;
        p = p->next;
        free(s);
    }
    pre->next = NULL;
}

void split(Node* A, Node* B, Node* C)
{
    Node* p = A->next;
    Node* tb = B, * tc = C;
    A->next = NULL;

    while (p != NULL) {
        Node* q = p->next;  // 保存原后继

        if (p->data < 0) {
            tb->next = p;
            tb = p;
        }
        else {           // 题目保证不存在 0
            tc->next = p;
            tc = p;
        }

        p = q;
    }

    tb->next = NULL;
    tc->next = NULL;
}

Node* findMax(Node* L)
{
    Node* best = L->next;
    if (best == NULL)
        return NULL;  // 空表

    Node* p = best->next;

    while (p != NULL) {
        if (p->data > best->data)
            best = p;
        p = p->next;
    }

    return best;
}

void reverse(Node* L)
{
    Node* p = L->next;
    L->next = NULL;

    while (p != NULL) {
        Node* q = p->next;  // 修改指针前保存后继

        p->next = L->next;
        L->next = p;

        p = q;
    }
}

void deleteRange(Node* L, int mink, int maxk)
{
    if (mink >= maxk)
        return;

    Node* pre = L;

    // 找到待删除区间的前驱
    while (pre->next != NULL &&
        pre->next->data <= mink) {
        pre = pre->next;
    }

    // 删除开区间 (mink, maxk) 内的结点
    while (pre->next != NULL &&
        pre->next->data < maxk) {
        Node* p = pre->next;
        pre->next = p->next;
        free(p);
    }
}

typedef struct DNode {
    int data;
    struct DNode* prior, * next;
} DNode;

void change(DNode* p)
{
    if (p == NULL)
        return;

    DNode* q = p->prior;

    // 先摘下 p
    q->next = p->next;
    p->next->prior = q;

    // 再把 p 插到 q 前面
    p->prior = q->prior;
    p->next = q;
    q->prior->next = p;
    q->prior = p;
}

// 返回删除后的新长度
int deleteItem(int A[], int n, int item)
{
    int k = 0;

    for (int i = 0; i < n; i++) {
        if (A[i] != item) {
            A[k] = A[i];
            k++;
        }
    }

    return k;
}


