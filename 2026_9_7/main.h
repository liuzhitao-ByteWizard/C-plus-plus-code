#pragma once

#include <iostream>
using namespace std;

// 日期类
class Date
{
    // 将operator<<声明为友元函数，
    // 使其能够访问Date类的私有成员
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);

public:
    // 构造函数
    Date(int year = 1, int month = 1, int day = 1);

    // 输出当前日期
    void Print() const
    {
        cout << _year << "/"
            << _month << "/"
            << _day << endl;
    }

private:
    int _year;  // 年
    int _month; // 月
    int _day;   // 日
};