//#include "priority_queue.h"
//void testpriority_queue1() {
//	vector<int> v{ 3,2,7,6,0,4,1,9,8,5,2,2,3 };
//	//1.构造无参队列
//	priority_queue<int> q1(v.begin() , v.end());
//
//	while (!q1.empty()) {
//		cout << q1.top() << ' ';
//		q1.pop();
//	}
//	cout << endl;
//}
//
//void testpriority_queue2() {
//	vector<int> v{ 3,2,7,6,0,4,1,9,8,5,2,2,3 };
//	//1.构造无参队列
//	priority_queue<int  , vector<int> , greater<int>> q1(v.begin(), v.end());
//
//	while (!q1.empty()) {
//		cout << q1.top() << ' ';
//		q1.pop();
//	}
//	cout << endl;
//}
//
//void testbytequeue1() {
//	byte::priority_queue<int> q1;
//	q1.push(99);
//	q1.push(22);
//	q1.push(77);
//	q1.push(66);
//	q1.push(44);
//	q1.push(11);
//	q1.push(33);
//	q1.push(78);
//
//
//	int k = 0; cin >> k;
//	while (!q1.empty() && k--) {
//		cout << q1.top() << ' ';
//		q1.pop();
//	}
//	cout << endl;
//
//}

template<class T>
class Less {
	public:
		bool operator()(const T& x , const T& y) {
			return x < y;
		}
};

template<class T>
class Greater {
public:
	bool operator()(const T& x, const T& y) {
		return x > y;
	}
};

#include "priority_queue.h"


//void testbytequeue3() {
//	byte::priority_queue<int, vector<int>, Greater<int>> q1; //使用仿函数Greater
//	byte::priority_queue<int, vector<int>, Less<int>> q2; //使用仿函数Less
//	byte::priority_queue<int, vector<int>> q3; //调用缺省值less仿函数
//	q2.push(1);
//	q2.push(4);
//	q2.push(3);
//	q2.push(5);
//	while (!q2.empty()) {
//		cout << q2.top() << ' ';
//		q2.pop();
//	}
//	cout << endl;
//}
//
//template<class T>
//class Func {
//public:
//	bool operator()(const T& x, const T& y) {
//		return x < y;
//	}
//};

//void test() {
//	Func<int> x1;
//	cout << Func<int>()(1, 2) << endl; //匿名对象
//	cout << x1(1, 2) << endl; //运算符重载
//	cout << x1.operator()(1, 2) << endl; //调用成员函数
//}

void testbytequeue4() {
	vector<int> v1 = { 100,20,33,22,88,6,2 };
	byte::priority_queue<int, vector<int>, Greater<int>> q1(v1.begin(),v1.end()); 
		while (!q1.empty()) {
		cout << q1.top() << ' ';
		q1.pop();
	}
	cout << endl;
	
}

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
	}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}

	friend ostream& operator<<(ostream& _cout, const Date& d);

	int _year;
	int _month;
	int _day;
};

//如果类中没有写比较函数，我们就可以写仿函数进行比较，日期类支持比较了我们就不需要写了，编译器会自动调用比较函数
//class LessDate {
//public:
//	bool operator()(const Date& x, const Date& y) {
//		return (x._year < y._year) ||
//			(x._year == y._year && x._month < y._month) ||
//			(x._year == y._year && x._month == y._month && x._day < y._day);
//	}
//};

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}
//
//void testbytequeue5() {
//	byte::priority_queue<Date, vector<Date>, Less<Date>> d1;
//	d1.push(Date(2026,10,13));
//	d1.push(Date(2026,10,16));
//	d1.push(Date(2026,10,15));
//	d1.push(Date(2026,10,14));
//	d1.push(Date(2026,1,30));
//	d1.push(Date(2026,2,1));
//
//	int k = 0;
//	cin >> k;
//	while (!d1.empty() && k--) {
//		cout << d1.top() << endl;
//		d1.pop();
//	}
//	cout << endl;
//}
//
////存放函数函数指针，我们需要的是日期与日期比较，不是比较地址
////那我们就自己写仿函数来满足我们想要的比较
//
class LessPDate {
public:
	bool operator()(const Date* x, const Date* y) {
		return (x->_year < y->_year) ||
			(x->_year == y->_year && x->_month < y->_month) ||
			(x->_year == y->_year && x->_month == y->_month && x->_day < y->_day);
	}
};
//
//void testbytequeue6() {
//	byte::priority_queue<Date*, vector<Date*>, LessPDate> q1;
//	Date d1(2026, 10, 23);
//	Date d2(2026, 10, 14);
//	Date d3(2026, 10, 29);
//	Date d4(2026, 10, 10);
//	q1.push(&d1);
//	q1.push(&d2);
//	q1.push(&d3);
//	q1.push(&d4);
//
//	while (!q1.empty()) {
//		cout << *q1.top() << endl;
//		q1.pop();
//	}
//	cout << endl;
//}

//静态栈的大小空间写入就固定住了
//#define N1 100
//
//template<class T>
//class Stack {
//private:
//	T _a[N1];
//	int _top;
//};

////非类型模板参数实现静态栈
//namespace byte {
//	//N就是非类型模板参数
//	template <class T, int N2 = 100>
//	class stack {
//	private:
//		T _arr[N2];
//		int size;
//	};
//}
// 主模板必须先声明或定义。
//template<class T>
//bool Func(T left, T right)
//{
//	return left < right;
//}

////调用特化过后的版本
//template<>
//bool Func<Date*>(Date* left,Date* right)
//{
//	return *left < *right;
//}

//int main()
//{
//	Date d1(2022, 7, 7);
//	Date d2(2022, 7, 8);
//
//	Date* p2 = &d2;
//	Date* p1 = &d1;
//	cout << Func(p1, p2) << endl; 
//
//	return 0;
//}
//
//template<class T>
//class Func {
//public:
//	bool operator()(const T& x, const T& y) {
//		return x < y;
//	}
//};
//
//template<>
//class Func<Date*> {
//	
//	bool operator()(const Date* x, const Date* y) {
//		return *x < *y;
//	}
//};


template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }

private:
	T1 _d1;
	T2 _d2;
};

////全特化
//template<>
//class Data<int, char>
//{
//public:
//	Data() { cout << "Data<int, char>" << endl; }
//
//private:
//	int _d1;
//	char _d2;
//};
//
////偏特化
//template<class T>
//class Data<T, char> {
//public:
//	Data() { cout << "Data<T, char>" << endl; }
//
//private:
//};
//
//template<typename T1 ,  typename T2>
//class Data<T1*, T2*> {
//public:
//	Data() { cout << "Data<T1*, T2*>" << endl; }
//private:
//};
//
//template <typename T1, typename T2>
//class Data <T1&, T2&>
//{
//public:
//	Data()
//	{
//		cout << "Data<T1&, T2&>" << endl;
//	}
//private:
//};
//
//template <typename T1, typename T2>
//class Data <T1&, T2*>
//{
//public:
//	Data()
//	{
//		cout << "Data<T1&, T2*>" << endl;
//	}
//private:
//};

//void TestVector()
//{
//	Data<int, int> d1;
//	Data<int, char> d2;
//	Data<char, char> d3;
//	Data<char*, int*> d4;
//}
//template<class T>
//class Less {
//public:
//	bool operator()(const T& x, const T& y) {
//		return x < y;
//	}
//};

template<>
class Less<Date*> {
public:
	//const Date*& x, const Date*& y err //const在T&修饰的是引用，这里修饰的是指针，是const Data*
	bool operator()(Date* const & x, Date* const & y) {
		return *x < *y;
	}
};


class Conditional {
public:
	bool operator()(int x) {
		return x % 2 && x % 11 == 0;
	}
};

void testbytequeue7() {

	std::vector<int> myvector;

	myvector.push_back(10);
	myvector.push_back(25);
	myvector.push_back(40);
	myvector.push_back(55);
	std::vector<int>::iterator it = std::find_if(myvector.begin(), myvector.end(), Conditional());
	std::cout << "The first odd value is " << *it << '\n';
}

int main() {
	testbytequeue7();
}


//void test8() {
//	vector<int> v1 = { 1,7,4,3,9,6,7,0,10 };
//	sort(v1.begin(),  v1.end()); //默认的比较器是less,升序
//	for (auto& e : v1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//	sort(v1.begin(), v1.end(), greater<int>());
//	for (auto& e : v1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//	
//}
//priority_queue<int , vector<int> , greater<int>> q1;
//int main() {
//	test8();
//	return 0;
//}




//int main() {
//	//array对标的是C语言的数组
//	array<int, 10> arr1 = {1,2,3,4,5};
//	array<int, 100> arr2; //未初始化
//	arr1[5] = 1;
//	for (auto& e : arr1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//	//如果想初始化，用fill
//	arr2.fill(0);
//	for (auto& e : arr2) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//	//更好的检查数组的越界
//	int arr3[10] = { 0 };
//	//arr1[100] = 1; //报断言错误
//	arr3[9] = 1; //有些情况下不会报错
//	return 0;
//}