#define _CRT_SECURE_NO_WARNINGS

//class A
//{
//public:
//	void func()
//	{
//		cout << "A::func()" << endl;
//	}
//};
//
////指定类域，表示它是A这个类的成员函数的指针
//typedef void (A::*PF)();
//
//
//void sortFunc(PF pf) {
//	A a;
//	//对象回调成员函数的函数指针
//	(a.*pf)();
//}
//
//int main() {
//	//普通函数的函数名就代表函数指针，成员函数的函数指针呢，要加个取地址
//	sortFunc(&A::func);
//	return 0;
//}

//class Date {
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	void Print() {
//		cout << _year << "-" << _month << "-" << _day << endl; 
//	}
//	//前置++
//	//出作用域之后this指针指向的对象没有销毁（不是局部对象），可以使用引用
//	Date& operator++() {
//		this->_day += 1;
//		return *this;
//
//	}
//	//后置++
//	Date operator++(int) {
//		Date tmp(*this); //拷贝构造
//		this->_day += 1;
//		return tmp;
//	}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main() {
//	Date d1(2026, 9, 6);
//	Date tmp = d1++; //拷贝构造
//	tmp.Print();
//	d1.Print();
//	++d1;
//	d1.Print();
//	return 0;
//}

//class Date {
//public:
//	Date(int year = 1, int month = 1, int day = 1) {
//		_year = year;
//		_month = month;
//		_day = day;
//	}
//
//	void Print() {
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//	//前置++
//	//出作用域之后this指针指向的对象没有销毁（不是局部对象），可以使用引用
//	Date& operator++() {
//		this->_day += 1;
//		return *this;
//
//	}
//
//	//必须重载为成员函数
//	Date& operator=(const Date& d) {
//		//处理自己给自己赋值的场景，在深拷贝的场景下的代价是非常大的
//		if (this != &d) {
//			_year = d._year;
//			_month = d._month;
//			_day = d._day;
//		}
//		return *this;
//	}
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main() {
//	Date d1(2025, 9, 6);
//	Date d2(2026, 9, 6);
//	Date d3(2027, 9, 6);
//	d2 = d1 = d3; 
//	d2.Print();
//	return 0;
//}

#include "Date.h"
Date::Date(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
}

// 获取指定年份、月份的天数
int GetMonthDay(int month, int year)
{
	// 下标与月份保持一致，因此0号位置不使用
	static const int MonthArr[13] =
	{
		0, 31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	// 闰年的2月有29天
	if (month == 2 &&
		((year % 4 == 0 && year % 100 != 0) ||
			year % 400 == 0))
	{
		return 29;
	}

	return MonthArr[month];
}

bool Date::operator>(const Date& d) const  {
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

bool Date::operator>=(const Date& d)const  {
	return (*this) > d || (*this) == d;
}

bool Date::operator<(const Date& d) const {
	//1. 复用大于等于运算符，然后取反
	//return !((*this) >= d);
	//2. *this < d -> d > *this
	return d > (*this);
}

bool Date::operator<=(const Date& d) const {
	return *this < d || *this == d;
}

bool Date::operator!=(const Date& d) const {
	return !(*this == d);
}

Date Date::operator+(int day)
{
	// 加上负数等价于减去它的绝对值
	// 例如：date + (-5) 等价于 date - 5
	if (day < 0)
	{
		return *this - (-day);
	}

	// 确定需要执行当前加法逻辑后再创建临时对象，避免无用拷贝
	Date tmp(*this);
	assert(tmp._month > 0 && tmp._month < 13);

	tmp._day += day;
	while (tmp._day > GetMonthDay(tmp._month, tmp._year))
	{
		tmp._day -= GetMonthDay(tmp._month, tmp._year);

		++tmp._month;
		if (tmp._month == 13)
		{
			tmp._month = 1;
			++tmp._year;
		}
	}
	return tmp;
}

Date& Date::operator+=(int day)
{
	*this = *this + day;
	return *this;
}

bool Date::operator==(const Date& d) const {
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}
// 前置++：日期增加一天
Date& Date::operator++()
{
	++_day;

	// 超过当月天数时进入下个月
	if (_day > GetMonthDay(_month, _year))
	{
		_day = 1;
		++_month;

		// 超过12月时进入下一年
		if (_month == 13)
		{
			_month = 1;
			++_year;
		}
	}

	return *this;
}

// 后置++：返回增加前的日期
Date Date::operator++(int)
{
	Date tmp(*this);

	// 复用前置++
	++(*this);

	return tmp;
}

Date Date::operator-(int day) {
	// 减去负数等价于加上它的绝对值
	// 例如：date - (-5) 等价于 date + 5	
	if (day < 0)
	{
		return *this + (-day);
	}
	// 确定需要执行当前减法逻辑后再创建临时对象，避免无用拷贝
	Date tmp(*this);
	tmp._day -= day;
	//处理不合法的天数
	while (tmp._day <= 0) {
		tmp._month -= 1;
		if (tmp._month == 0) {
			tmp._month = 12;
			tmp._year -= 1;
		}
		tmp._day += GetMonthDay(tmp._month, tmp._year);
	}
	return tmp;
}

Date& Date::operator-=(int day) {
	*this = *this - day;
	return *this; 
}

//前置--
Date& Date::operator--() {
	*this -= 1;
	return *this;
}

//后置--
Date Date::operator--(int) {
	Date tmp(*this);
	*this -= 1;
	return tmp;
}

//// 获取指定年份的总天数
//int GetYearDay(int year)
//{
//	int sum = 0;
//
//	// 使用1～12作为月份下标，0号位置不使用
//	int MonthArr[13] =
//	{
//		0, 31, 28, 31, 30, 31, 30,
//		31, 31, 30, 31, 30, 31
//	};
//
//	// 闰年的2月有29天
//	if ((year % 4 == 0 && year % 100 != 0) ||
//		year % 400 == 0)
//	{
//		MonthArr[2] = 29;
//	}
//
//	// 累加12个月的天数
//	for (int month = 1; month < 13; ++month)
//	{
//		sum += MonthArr[month];
//	}
//
//	return sum;
//}
//
//// 日期减日期，返回有符号的天数差：
//// 当前日期较晚时返回正数，较早时返回负数
//int Date::operator-(const Date& d)
//{
//	// 计算当前日期是本年度的第几天
//	int leftDayOfYear = 0;
//
//	// 累加当前月份之前各月的天数
//	for (int month = 1; month < _month; ++month)
//	{
//		leftDayOfYear += GetMonthDay(month, _year);
//	}
//
//	leftDayOfYear += _day;
//
//	// 计算右侧日期是本年度的第几天
//	int rightDayOfYear = 0;
//
//	// 累加右侧日期当前月份之前各月的天数
//	for (int month = 1; month < d._month; ++month)
//	{
//		rightDayOfYear += GetMonthDay(month, d._year);
//	}
//
//	rightDayOfYear += d._day;
//
//	// 先计算两个日期在各自年份中的位置差
//	// 如果年份相同，这个结果就是最终的日期差
//	int difference = leftDayOfYear - rightDayOfYear;
//
//	if (_year > d._year)
//	{
//		// 当前日期的年份较大：
//		// 累加右侧年份到当前年份之间所有完整年份的天数
//		for (int year = d._year; year < _year; ++year)
//		{
//			difference += GetYearDay(year);
//		}
//	}
//	else if (_year < d._year)
//	{
//		// 当前日期的年份较小：
//		// 减去当前年份到右侧年份之间所有完整年份的天数
//		for (int year = _year; year < d._year; ++year)
//		{
//			difference -= GetYearDay(year);
//		}
//	}
//
//	// 返回带正负号的日期差
//	return difference;
//}
//

int Date::operator-(const Date& d)const {
	Date max = *this;
	Date min = d;
	int flag = 1;
	if (*this < d) {
		min = *this;
		max = d;
		flag = -1;
	}
	int count = 0;
	while (min != max) {
		++min;
		++count;
	}
	return count * flag;
}

void operator<<(ostream& _cout, const Date& d) {
	_cout << d._year << '/' << d._month << '/' << d._day << endl;
}




