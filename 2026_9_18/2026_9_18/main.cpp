#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <assert.h>
#include <list>
using namespace std;

//// 简化示意：展示下标访问的实现，不是完整的string类
//class MyString
//{
//public:
//    char& operator[](size_t pos)
//    {
//        assert(pos < _size); // 检查下标，越界就报断言错误
//        return _str[pos];    // 返回引用，允许修改字符
//    }
//
//private:
//    char* _str;        // 指向字符存储区
//    size_t _size;     // 有效字符数
//    size_t _capacity; // 可容纳的字符数
//};
//
//// 编译器检查语法和类型，并将代码翻译为目标代码
//void test_string1()
//{
//    string s1("12345"); // 使用std::string，长度为5
//
//    s1[0]++;     // '1'变为'2'
//    s1[2] = '4'; // s1变为"22445"
//
//    // cout << s1[30] << endl; // 越界：未定义行为，部分实现会触发断言
//
//    cout << s1[3] << endl; // 输出'4'
//    cout << s1 << endl;    // 输出"22445"
//
//    char arr[] = "12345"; // 共6个元素，包含'\0'
//    arr[0]++;            // 等价于(*(arr + 0))++，变为"22345"
//
//    // cout << arr[30] << endl; // 越界：未定义行为，不保证报错
//
//    s1 += "xxxxxx";     // 追加6个'x'
//    cout << s1 << endl; // 输出"22445xxxxxx"
//}
//
//
//void test_string2() {
//    string s1("hello world");
//    cout <<s1.size() << endl; //11 不包含'\0'
//    cout << s1.capacity() << endl << endl; //15
//
//    s1 += "12345";
//    cout << s1.size() << endl; //16
//    cout << s1.capacity() << endl; //31
//
//}
//
//void test_string3() {
//    string s2("hello ");
//    cout << s2.size() << endl; 
//    s2 += "world";
//    s2.clear();
//    cout << s2.size() << endl;
//}
//
//int main() {
//    //test_string2();
//    test_string3();
//	return 0;
//}

//class Solution
//{
//public:
//    // 判断字符是否为英文字母
//    bool isLetter(char ch)
//    {
//        if (ch >= 'a' && ch <= 'z') // 小写字母
//            return true;
//
//        if (ch >= 'A' && ch <= 'Z') // 大写字母
//            return true;
//
//        return false;
//    }
//
//    // 仅反转英文字母，其他字符的位置保持不变
//    string reverseOnlyLetters(string s)
//    {
//        if (s.empty())
//            return s; // 空串直接返回，避免size() - 1下溢
//
//        size_t begin = 0, end = s.size() - 1; // 左右下标
//
//        while (begin < end)
//        {
//            // 从左向右跳过非字母字符
//            while (begin < end && !isLetter(s[begin]))
//                ++begin;
//
//            // 从右向左跳过非字母字符
//            while (begin < end && !isLetter(s[end]))
//                --end;
//
//            if (begin >= end)
//                break; // 下标相遇，结束遍历
//
//            swap(s[begin], s[end]); // 交换两端的字母
//            ++begin;               // 左下标右移
//            --end;                 // 右下标左移
//        }
//
//        return s;
//    }
//};

//int main() {
//	string s("hello world");
//	string::iterator it = s.begin();
//	while (it != s.end()) {
//		cout << *it;
//		it++;
//	}
//	return 0;
//}

int main() {
	string s;
	cin >> s;
	string s2;
}