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

// 以下为原课程示例实现，保留作学习参考；正式实现位于文件后半部分。
#if 0
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

#endif

#include <cstdint>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace
{
	const std::int64_t kDaysPer400Years = 146097;

	struct DateParts
	{
		int year;
		int month;
		int day;
	};

	bool IsLeapYear(int year) noexcept
	{
		return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	}

	int GetMonthDay(int year, int month) noexcept
	{
		static const int monthDays[12] =
		{
			31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31
		};

		return month == 2 && IsLeapYear(year) ? 29 : monthDays[month - 1];
	}

	bool IsValidDate(int year, int month, int day) noexcept
	{
		if (year < 1 || month < 1 || month > 12 || day < 1)
		{
			return false;
		}

		return day <= GetMonthDay(year, month);
	}

	// 计算指定年份之前共有多少天。使用 64 位整数，确保 INT_MAX 年仍可安全表示。
	std::int64_t DaysBeforeYear(int year) noexcept
	{
		const std::int64_t completedYears = static_cast<std::int64_t>(year) - 1;
		return completedYears * 365
			+ completedYears / 4
			- completedYears / 100
			+ completedYears / 400;
	}

	// 将日期转换为从 1/1/1 开始、以 0 为起点的日期序号。
	std::int64_t DateToSerial(int year, int month, int day) noexcept
	{
		static const int daysBeforeMonth[12] =
		{
			0, 31, 59, 90, 120, 151,
			181, 212, 243, 273, 304, 334
		};

		std::int64_t serial = DaysBeforeYear(year);
		serial += daysBeforeMonth[month - 1];
		if (month > 2 && IsLeapYear(year))
		{
			++serial;
		}
		return serial + day - 1;
	}

	const std::int64_t kMaximumSerial =
		DateToSerial((std::numeric_limits<int>::max)(), 12, 31);

	// 利用公历每 400 年重复一次（共 146097 天）的性质反向计算年份。
	// 年份确定后只按月检查，循环次数最多为 12，不会随日期跨度增长。
	DateParts SerialToDate(std::int64_t serial) noexcept
	{
		const std::int64_t fourHundredYearCycles = serial / kDaysPer400Years;
		std::int64_t dayInCycle = serial % kDaysPer400Years;

		std::int64_t hundredYearCycles = dayInCycle / 36524;
		if (hundredYearCycles == 4)
		{
			hundredYearCycles = 3;
		}
		dayInCycle -= hundredYearCycles * 36524;

		std::int64_t fourYearCycles = dayInCycle / 1461;
		if (fourYearCycles == 25)
		{
			fourYearCycles = 24;
		}
		dayInCycle -= fourYearCycles * 1461;

		std::int64_t oneYearCycles = dayInCycle / 365;
		if (oneYearCycles == 4)
		{
			oneYearCycles = 3;
		}
		dayInCycle -= oneYearCycles * 365;

		const std::int64_t year64 = fourHundredYearCycles * 400
			+ hundredYearCycles * 100
			+ fourYearCycles * 4
			+ oneYearCycles + 1;
		const int year = static_cast<int>(year64);

		int month = 1;
		while (dayInCycle >= GetMonthDay(year, month))
		{
			dayInCycle -= GetMonthDay(year, month);
			++month;
		}

		DateParts result = { year, month, static_cast<int>(dayInCycle) + 1 };
		return result;
	}

	Date DateFromSerial(std::int64_t serial)
	{
		const DateParts parts = SerialToDate(serial);
		return Date(parts.year, parts.month, parts.day);
	}
}

Date::Date(int year, int month, int day)
	: _year(year)
	, _month(month)
	, _day(day)
{
	if (!IsValidDate(year, month, day))
	{
		throw std::invalid_argument("invalid Gregorian date");
	}
}

void Date::Print() const
{
	std::cout << *this << '\n';
}

bool Date::operator>(const Date& date) const noexcept
{
	return date < *this;
}

bool Date::operator>=(const Date& date) const noexcept
{
	return !(*this < date);
}

bool Date::operator<(const Date& date) const noexcept
{
	if (_year != date._year)
	{
		return _year < date._year;
	}
	if (_month != date._month)
	{
		return _month < date._month;
	}
	return _day < date._day;
}

bool Date::operator<=(const Date& date) const noexcept
{
	return !(date < *this);
}

bool Date::operator==(const Date& date) const noexcept
{
	return _year == date._year
		&& _month == date._month
		&& _day == date._day;
}

bool Date::operator!=(const Date& date) const noexcept
{
	return !(*this == date);
}

Date Date::operator+(int day) const
{
	// 先提升为 int64_t 再参与运算，避免 day == INT_MIN 时对 int 取负溢出。
	const std::int64_t target = DateToSerial(_year, _month, _day)
		+ static_cast<std::int64_t>(day);
	if (target < 0 || target > kMaximumSerial)
	{
		throw std::out_of_range("date addition is outside the supported range");
	}
	return DateFromSerial(target);
}

Date& Date::operator+=(int day)
{
	// 先生成合法结果，再写回当前对象；若计算抛出异常，原对象保持不变。
	const Date result = *this + day;
	*this = result;
	return *this;
}

Date Date::operator-(int day) const
{
	// 直接在 64 位域中减去偏移，不对 INT_MIN 执行危险的 int 取负操作。
	const std::int64_t target = DateToSerial(_year, _month, _day)
		- static_cast<std::int64_t>(day);
	if (target < 0 || target > kMaximumSerial)
	{
		throw std::out_of_range("date subtraction is outside the supported range");
	}
	return DateFromSerial(target);
}

Date& Date::operator-=(int day)
{
	// 与 += 一样，采用“计算成功后再提交”的方式提供强异常保证。
	const Date result = *this - day;
	*this = result;
	return *this;
}

Date& Date::operator++()
{
	return *this += 1;
}

Date Date::operator++(int)
{
	const Date previous(*this);
	++(*this);
	return previous;
}

Date& Date::operator--()
{
	return *this -= 1;
}

Date Date::operator--(int)
{
	const Date previous(*this);
	--(*this);
	return previous;
}

int Date::operator-(const Date& date) const
{
	const std::int64_t difference = DateToSerial(_year, _month, _day)
		- DateToSerial(date._year, date._month, date._day);
	if (difference < (std::numeric_limits<int>::min)()
		|| difference > (std::numeric_limits<int>::max)())
	{
		throw std::overflow_error("date difference cannot be represented by int");
	}
	return static_cast<int>(difference);
}

std::ostream& operator<<(std::ostream& output, const Date& date)
{
	return output << date._year << '/' << date._month << '/' << date._day;
}




