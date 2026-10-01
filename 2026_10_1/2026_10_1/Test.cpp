#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//// 打印 vector 中的元素
//void printVector(const char* name, const vector<int>& v)
//{
//    cout << name << ": [ ";
//    for (int value : v)
//        cout << value << " ";
//    cout << "]\n";
//}
//
//void testvector1(){
//
//    // 1. 无参构造：创建一个空 vector
//    vector<int> v1;
//    printVector("v1", v1);       // [ ]
//    cout << "v1.size() = " << v1.size() << "\n"; // 0
//
//    // 2. 指定元素数量和初始值
//    vector<int> v2(5, 10);       // 5 个元素，每个都是 10
//    printVector("v2", v2);       // [ 10 10 10 10 10 ]
//
//    // 只指定数量：对于 int，元素初始化为 0
//    vector<int> v3(5);
//    printVector("v3", v3);       // [ 0 0 0 0 0 ]
//
//    // 3. 拷贝构造：用已有 vector 创建一个新 vector
//    vector<int> v4(v2);
//    printVector("v4", v4);       // [ 10 10 10 10 10 ]
//
//    // 修改副本中的元素，不影响原 vector
//    v4[0] = 99;
//    cout << "v2[0] = " << v2[0] << "\n"; // 10
//    cout << "v4[0] = " << v4[0] << "\n"; // 99
//
//    // 4. 迭代器区间构造：复制指定范围中的元素
//    int arr[] = { 1, 2, 3, 4, 5 };
//    vector<int> v5(arr, arr + 5);
//    printVector("v5", v5);       // [ 1 2 3 4 5 ]
//
//    // 也可以使用另一个 vector 的迭代器
//    vector<int> v6(v5.begin() + 1, v5.begin() + 4);
//    printVector("v6", v6);       // [ 2 3 4 ]
//}

//iterator
void  testvector2() {
    vector<int> v1(10, 1);
    vector<int>::iterator it = v1.begin();
    while (it != v1.end()) {
        cout << *it << ' ';
        it++;
    }
}

//// 测试vector的默认扩容机制
//void TestVectorExpand()
//{
//    size_t sz;
//    vector<int> v;
//    sz = v.capacity();
//
//    cout << "making v grow:\n";
//    for (int i = 0; i < 100; ++i)
//    {
//        v.push_back(i);
//        if (sz != v.capacity())
//        {
//            sz = v.capacity();
//            cout << "capacity changed: " << sz << '\n';
//        }
//    }
//}

void PrintVector(vector<int>& v) {
    for (auto x : v) {
        cout << x << " ";
    }
    cout << endl;
}

void testvector3() {
    vector<int> v1(10, 2);
    v1.resize(1);
    PrintVector(v1);
    v1.resize(20, 10);
    PrintVector(v1);
    v1.resize(30);
    PrintVector(v1);
}

void testvector4() {
    vector<int> v2(12, 1);
    v2.push_back(2);
    v2.push_back(3);
    PrintVector(v2);
    v2.pop_back();
    v2.pop_back();
    PrintVector(v2);
}

void testvector5() {
    vector<int> v(12, 1);

    //头插
    v.insert(v.begin(), 0);
    PrintVector(v);

    //中间位置插入
    v.insert(v.begin() + 5, 0);
    v.insert(v.begin() + 4, 0);
    v.insert(v.begin() + 3, 0);
    v.insert(v.begin() + 2, 0);
    //v.insert(v.begin() + 100, 0); err 越界就会报错
    PrintVector(v);
}

void testvector6() {
    vector<int> v(10, 1);
    v.push_back(11);
    //v.erase(v.begin()); //头删
    //PrintVector(v);
    //v.erase(v.end() - 1); //尾删
    //PrintVector(v);
    //删除迭代器区间
    v.erase(v.begin(), v.end());
    PrintVector(v);
}

void testvector7() {
    vector<int> v1(10, 2);
    vector<int> v2(11, 2);
    cout << (v1 < v2) << endl;
    vector<int> v3(10, 2);
    vector<int> v4(10, 3);
    cout << (v3 > v4) << endl;
    vector<int> v5(10, 2);
    vector<int> v6(10, 2);
    cout << (v5 == v6) << endl;
}

void testvector8() {
    vector<int> v8;
    v8.resize(3,0);
    for (int i = 0; i < 3; i++) {
        cin >> v8[i];
    }
    for (auto e : v8) {
        cout << e << ' ';
    }
    cout << endl;
}

void testvector9() {
    vector<string> v1;
    v1.push_back("张三");
    v1.push_back("李四");
    v1.push_back("xxxxxxxxxxxxxxxxx");

    for (const auto& e : v1) { //加上引用，减少深拷贝
        cout << e << " "; //既可以遍历，又可以修改
    }
    cout << endl;
}

int main() {
    testvector9();
    return 0;
}
