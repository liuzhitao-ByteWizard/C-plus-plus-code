#include "Date.h"
using namespace std;

bool Date::operator>(Date& d) {
	if (_year > d._year) {
		return true;
	}
	else if (_year == d._year) {
		//两个属性的年份相等，就比较月份
		if (_month > d._month) {
			return true;
		}
		else if (_month == d._month) {
			//月份相等，就比较天数
			if (_day > d._day) {
				return true;
			}
		}
	}
	return false;
}

Date::Date(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
}

int GetMonthDay(int month,int year) {
	int MonthArr[13] = { 0 , 31  , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };
	if (year == 2 && (year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
		return 29;
	}

	return MonthArr[month];
}

Date Date::operator+(int day) {
	Date tmp(*this); //拷贝构造
	assert(tmp._month > 0 && tmp._month < 13); //保证传过来的month是有效的
	tmp._day += day;
	//处理无效的day
	while (tmp._day > GetMonthDay(tmp._month,tmp._year)) {
		if (tmp._month == 13) {
			tmp._month = 1;
			tmp._year += 1;
		}
		tmp._day -= GetMonthDay(tmp._month,tmp._year);
		tmp._month += 1;
	}
	return tmp; //传值返回，调用拷贝构造函数
}

int main() {
	Date d1(2026, 10, 4);
	Date d2(2026, 9, 4);
	d1 = d2 + 200;
	d1.Print();
	return 0;
}