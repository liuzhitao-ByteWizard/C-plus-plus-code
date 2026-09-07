#pragma once

#include <iosfwd>

class Date
{
	friend std::ostream& operator<<(std::ostream& output, const Date& date);

public:
	// 仅接受公历 1/1/1 至 INT_MAX/12/31；非法年月日抛出 std::invalid_argument。
	Date(int year = 1, int month = 1, int day = 1);

	// 按“年/月/日”的格式输出日期，并在末尾换行。
	void Print() const;

	bool operator>(const Date& date) const noexcept;
	bool operator>=(const Date& date) const noexcept;
	bool operator<(const Date& date) const noexcept;
	bool operator<=(const Date& date) const noexcept;
	bool operator==(const Date& date) const noexcept;
	bool operator!=(const Date& date) const noexcept;

	// 日期加减越过支持范围时抛出 std::out_of_range。
	Date& operator+=(int day);
	Date operator+(int day) const;

	Date& operator-=(int day);
	Date operator-(int day) const;

	Date& operator++();
	Date operator++(int);

	Date& operator--();
	Date operator--(int);

	// 返回两个日期之间的有符号天数差；结果超出 int 范围时抛出异常。
	int operator-(const Date& date) const;

private:
	int _year;
	int _month;
	int _day;
};

// 流输出不附加换行，以便支持 output << date1 << " " << date2 的链式写法。
std::ostream& operator<<(std::ostream& output, const Date& date);
