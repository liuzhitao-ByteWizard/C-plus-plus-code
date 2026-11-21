#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "myunordered_map.h"
//#include "myunordered_set.h"

using namespace std;

////void Print(const byte::myunordered_map<int ,int>& mp) {
////	byte::myunordered_map<int,int>::const_iterator it = mp.begin();
////	while (it != mp.end()) {
////		//it->first = 1; //不能修改
////		it->second = 1; //可以修改
////		cout << it->first <<  " "<< it->second << endl;
////		++it;
////	}
////	cout << endl;
////}
//
//void Print1(byte::myunordered_map<int, int>& mp) {
//	byte::myunordered_map<int, int>::iterator it = mp.begin();
//	while (it != mp.end()) {
//		//it->first = 1; //不能修改
//		it->second = rand(); //可以修改
//		cout << it->first << " " << it->second << endl;
//		++it;
//	}
//	cout << endl;
//}
//
//void test() {
//	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜","苹果", "香蕉", "苹果", "香蕉" };
//	byte::myunordered_map<string, int> countMap;
//	for (const auto& str : arr) {
//		countMap[str]++;
//	}
//
//	for (const auto& e : countMap)
//	{
//		cout << e.first << ":" << e.second << endl;
//	}
//	cout << endl;
//}
//
//
//int main() {
//	test();
//	return 0;
//}

#include<iostream>
#include<vector>
#include <map>
#include <initializer_list>  // std::initializer_list
using namespace std;

struct Point
{
    int _x;
    int _y;
};

class Date
{
public:
    Date(int year = 1, int month = 1, int day = 1)
        :_year(year)
        , _month(month)
        , _day(day)
    {
        cout << "Date(int year, int month, int day)" << endl;
    }

    Date(const Date& d)
        :_year(d._year)
        , _month(d._month)
        , _day(d._day)
    {
        cout << "Date(const Date& d)" << endl;
    }
private:
    int _year;
    int _month;
    int _day;
};

int main() {
	int a1[] = { 1,2,3,4 };
	int a2[]{ 1,2,3,4 };
	int a3 = 1;
	int a4{ 1 };

    Date d1 = { 2025,1,1 };
    Date d2{ 2025,1,1 };
    //临时对象具有常性
    const Date& d3{ 2025,1,1 };
    Date d4{}; //默认构造

    vector<Date> v;
	v.push_back(d1);
	v.push_back(Date(2025, 1, 1));
	// 比起有名对象和匿名对象传参，这里{}更有性价比
	v.push_back({ 2025, 1, 1 });

    // 跟上面调的不是一个构造，用法也不同
	// 下面要实现{}中任意多个值去初始化
	vector<int> v1 = { 1,2,3,4,5,6};
	vector<int> v2 = { 1,2,3};
	vector<int> v3 { 1,2,3,4 };

    std::initializer_list<int> mylist;
    mylist = { 10, 20, 30 };
    cout << sizeof(mylist) << endl;

    
    map<int, int> it = { { 1,1 } ,{ 2,1 } ,{ 4,1 } ,{ 6,1 } };

    int a = 1;
    int b = a;

    const int c = 1;
    cout << &c << endl;

    char d = 'v';
    cout << (void*)d << endl;
    //cout << &'v' << endl;

	return 0;
}