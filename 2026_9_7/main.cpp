#include "main.h"

// 流插入运算符：输出日期
ostream& operator<<(ostream& out, const Date& d)
{
    out << d._year << "/"
        << d._month << "/"
        << d._day;

    // 返回输出流，以支持连续输出
    return out;
}

// 流提取运算符：输入日期
istream& operator>>(istream& in, Date& d)
{
    // 输入格式：年 月 日，例如 2026 9 7
    in >> d._year
        >> d._month
        >> d._day;

    // 返回输入流，以支持连续输入
    return in;
}

Date::Date(int year, int month, int day) {
    _year = year;
    _month = month;
    _day = day;
}