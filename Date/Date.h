#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;

#pragma once
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);

	// 类里面直接定义，默认是inline
	void Print() {
		cout << _year << "/" << _month << "/" << _day << endl;
	}

	bool operator>(Date& d);
	bool operator==(Date& d);
	bool operator>=(Date& d);
	bool operator<(Date& d);
	bool operator<=(Date& d);
	bool operator!=(Date& d);

	Date& operator+=(int day);
	Date operator+(int day);

	Date& operator-=(int day);
	Date operator-(int day);

private:
	int _year;
	int _month;
	int _day;
};