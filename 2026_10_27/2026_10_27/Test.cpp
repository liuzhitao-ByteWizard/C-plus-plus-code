#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <map>

using namespace std;


//void testset1() {
//	set<int> t1; //空初始化
//	t1.insert(1);
//	t1.insert(2);
//	t1.insert(3);
//	t1.insert(4);
//
//	set<int> t2(t1.begin(), t1.end()); //迭代器区间初始化
//
//	//initializer list初始化
//	set<int> t3 = { 1,10,4,5,6,8,7,9 };
//
//}

void testset2() {
    // 去重+升序排序
    set<int> s;
    // 去重+降序排序（给一个大于的仿函数）
    //set<int, greater<int>> s;
    s.insert(5);
    s.insert(2);
    s.insert(7);
    s.insert(5);

    //set<int>::iterator it = s.begin();
    auto it = s.begin();
    while (it != s.end())
    {
        // error C3892: “it”: 不能给常量赋值
         //*it = 1;
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    // 插入一段initializer_list列表值，已经存在的值插入失败
    s.insert({ 2, 8, 3, 9 });
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    set<string> strset = { "sort", "insert", "add" };
    // 遍历string比较ascll码大小顺序遍历的
    for (auto& e : strset)
    {
        cout << e << " ";
    }
    cout << endl;
}

void testset3() {
    set<int> s = { 4, 2, 7, 2, 8, 5, 9 };
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    // 删除最小值
    s.erase(s.begin());
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    // 直接删除x
    int x;
    cin >> x;
    int num = s.erase(x);//返回成功删除的个数
    if (num == 0)
    {
        cout << x << "不存在! " << endl;
    }

    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    // 直接查找在利用迭代器删除x
    cin >> x;
    auto pos = s.find(x);
    if (pos != s.end())
    {
        s.erase(pos);
    }
    else
    {
        cout << x << "不存在! " << endl;
    }

    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;

    // 算法库的查找 O(N)
    auto pos1 = find(s.begin(), s.end(), x);
    // set自身实现的查找 O(logN)
    auto pos2 = s.find(x);

    // 利用count间接实现快速查找
    cin >> x;
    if (s.count(x))
    {
        cout << x << "在! " << endl;
    }
    else
    {
        cout << x << "不存在! " << endl;
    }
}

void testset4() {
    set<int> s1;
    s1.insert(4);
    s1.insert(2);
    s1.insert(6);
    s1.insert(7);
    s1.insert(9);
    s1.insert(10);

    s1.insert({ 3,4,2,4,2,1 });

    for (auto e : s1) {
        cout << e << " ";
    }
    cout << endl;

    // 删除[2,7]
    // 删除[3,8]
    // >=2，左闭区间位置
    auto it1 = s1.lower_bound(2);
    // > 7  右开区间位置
    auto it2 = s1.upper_bound(7);
    s1.erase(it1, it2); //迭代器区间删除
    for (auto e : s1) {
        cout << e << " ";
    }
    cout << endl;
}

//multiset也包含在set的头文件中
void testmultiset5() {
    // 相比set不同的是，multiset是排序，但是不去重
    multiset<int> s = { 2,2,7,2,4,8,4,2,4,9 };
    auto it = s.begin();
    while (it != s.end())
    {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    // 相比set不同的是，x可能会存在多个，find查找中序的第一个
    int x;
    cin >> x;
    auto pos = s.find(x);
    while (pos != s.end() && *pos == x)
    {
        cout << *pos << " ";
        ++pos;
    }
    cout << endl;
    // 相比set不同的是，count会返回x的实际个数
    cout << s.count(x) << endl;
    // 相比set不同的是，erase给值时会删除所有的x
    s.erase(x);
    for (auto e : s)
    {
        cout << e << " ";
    }
    cout << endl;
}

void testmap1() {
    map<string, string> dict;
    dict.insert(pair<string, string>("sort", "排序"));
    dict.insert(pair<string, string>("insert", "插入"));
    dict.insert({ "string", "字符串" });
    pair<string, string> kv1 = { "string", "字符串" };

    for (auto& str : dict) {
        cout << str.first << " " << str.second << endl;
    }
    cout << endl;

    map<string, string>::iterator it = dict.begin(); //迭代器里面存放的是键值对的地址
    while (it != dict.end()) {
        //(*it).first  (*it).second
        //it.operator->()->first //编译器为了可读性，省略一个->
        cout << it->first << " " <<  it->second << endl;
        //it->first = "x"; key不能修改
        it->second = "x"; //value可以修改
        it++;
    }
    cout << endl;

    string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
    map<string, int> countMap;

    for (auto& e : arr) {
        auto it = countMap.find(e);
        if (countMap.count(e) == 0)
            countMap.insert({ e,1 });
        else
            it->second++;
        
    }
    for (auto& e : countMap) {
        cout << e.first << " " << e.second << endl;
    }
    cout << endl;
}


int main(){
    testmap1();
}


