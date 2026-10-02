#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testvector1()
{
    vector<string> v1;
    v1.push_back("张三");
    v1.push_back("李四");
    v1.push_back("xxxxxxxxxxxxxxxxx");

    //修改对象
    v1[0] = "张三来";
    //v1[2][0] = 'y';
    v1.operator[](2).operator[](0) = 'y';

    for (const auto& e : v1)
    {
        cout << e << " "; // 输出当前字符串
    }
    cout << endl;
}

//规则
void testvector2() {
    vector<vector<int>> v2;
    v2.resize(10); //开10个vector int的对象数组
    for (int i = 0; i < v2.size(); i++) {
        v2[i].resize(5 , 0); //为每个vector int 开辟空间
    }
    for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j < v2[i].size(); j++) {
            //cout << v2[i][j] << ' ';
            cout << v2.operator[](i).operator[](j) << ' ';
        }
        cout << endl;
    }

}

//不规则：访问时小心越界
void testvector3() {
    vector<vector<int>> v2;
    v2.resize(10); //开10个vector int的对象数组
    for (int i = 0; i < v2.size(); i++) {
        v2[i].resize(i + 1, 0); //为每个vector int 开辟空间
    }
    for (int i = 0; i < v2.size(); i++) {
        for (int j = 0; j < v2[i].size(); j++) {
            cout << v2[i][j] << ' ';
        }
        cout << endl;
    }

}
//杨辉三角
//class Solution {
//public:
//    vector<vector<int>> generate(int numRows) {
//        vector<vector<int>> v;
//        v.resize(numRows); //开n个vector int对象
//        for (int i = 0; i < numRows; i++) {
//            v[i].resize(i + 1, 1); //第i个对象数组开i + 1个空间,默认全部初始化为1
//            for (int j = 1; j < v[i].size() - 1; j++) {
//                v[i][j] = v[i - 1][j] + v[i - 1][j - 1];
//            }
//        }
//        return v;
//    }
//};

int main()
{
    //testvector3();
    testvector2();
    return 0;
}