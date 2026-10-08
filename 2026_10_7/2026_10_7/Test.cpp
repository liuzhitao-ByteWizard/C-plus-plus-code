#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//#include <list>
//#include <vector>
#include <algorithm>

//using namespace std;
//
//void testlist1() {
//	list<int> lt1; //无参构造
//	list<int> lt2(10, 1); //带参构造
//	list<int> lt3(lt2.begin(), lt2.end()); //迭代器构造 
//	list<int> lt4 = { 1,2,2,3,4,5 }; //使用initializer_list来构造
//
//	////减少拷贝：底层使用迭代器的方式实现（遍历list只能使用迭代器，不能随机访问）
//	//for (auto& e : lt4) {
//	//	cout << e << ' ';
//	//}
//	//cout << endl;
//
//	list<int>::iterator it = lt3.begin();
//	while (it != lt3.end()) {
//		cout << *it << ' ';
//		++it;
//	}
//	cout << endl;
//}
//
//void testlist2() {
//	list<int> lt1;
//	lt1.push_back(1);
//	lt1.push_back(1);
//	lt1.push_back(1);
//	lt1.push_back(1);
//	lt1.push_back(1);
//	lt1.push_front(2); //头插
//	lt1.push_front(3);
//	lt1.push_front(4);
//	for (auto& e : lt1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//	lt1.pop_front(); //头删
//	lt1.pop_front(); //头删
//	lt1.pop_front(); //头删
//	lt1.pop_front(); //头删
//
//	//在第i个位置删除或插入（假设i = 3）
//	auto it = lt1.begin();
//	size_t n = 3;
//	while (n--)
//		++it;
//	lt1.insert(it, 3);
//	for (auto& e : lt1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//}
//
//
//
//void testlist3() {
//	list<int> lt1;
//	lt1.push_back(1);
//	lt1.push_back(1);
//	lt1.push_back(1);
//	lt1.push_front(2); //头插
//	lt1.push_front(3);
//	lt1.push_front(4);
//	for (auto& e : lt1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//	auto it = find(lt1.begin(), lt1.end(), 3);
//	//find查找失败，返回last（end）
//	if (it != lt1.end()) {
//		lt1.erase(it);
//	}
//
//	for (auto& e : lt1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//}
//
//void testlist4() {
//	list<int> lt2;
//	lt2.push_back(1);
//	lt2.push_back(2);
//	lt2.push_back(3);
//	lt2.push_back(4);
//	lt2.push_back(5);
//
//	////将4移动到头部
//	//auto it = find(lt2.begin(), lt2.end() , 4);
//	//if (it != lt2.end()) {
//	//	lt2.splice(lt2.begin(), lt2, it);
//	//}
//
//	lt2.remove(1);
//	lt2.remove(3);
//	lt2.remove(4);
//	lt2.remove(5);
//
//	for (auto& e : lt2) {
//		cout << e << ' ';
//	}
//	cout << endl;
//}
//
//bool single_digit(const int& value) { return (value % 2 == 0); }
//
//struct is_odd {
//	bool operator() (const int& value) { return (value % 2) == 1; }
//};
//
//void testlist5() {
//	int myints[] = { 15,36,7,17,20,39,4,1 };
//	list<int> myint(myints, myints + 8);
//	//myint.remove_if(single_digit);
//	myint.remove_if(is_odd());
//	for (auto& e : myint) {
//		cout << e << ' ';
//	}
//	cout << endl;
//
//}
//
//void testlist6() {
//	list<int> v1;
//	v1.push_back(1);
//	v1.push_back(5);
//	v1.push_back(9);
//	v1.push_back(7);
//	v1.push_back(2);
//	v1.push_back(4);
//	v1.push_back(3);
//	//v1.unique();
//	for (auto& e : v1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//	v1.sort();
//	for (auto& e : v1) {
//		cout << e << ' ';
//	}
//	cout << endl;
//}
//
//void test_op1()
//{
//	srand(time(0));
//	const int N = 1000000;
//
//	list<int> lt1;
//	vector<int> v;
//
//	for (int i = 0; i < N; ++i)
//	{
//		auto e = rand() + i;
//		lt1.push_back(e);
//		v.push_back(e);
//	}
//
//	int begin1 = clock();
//	// 排序
//	sort(v.begin(), v.end());
//	int end1 = clock();
//
//	int begin2 = clock();
//	lt1.sort();
//	int end2 = clock();
//
//	printf("vector sort:%d\n", end1 - begin1);
//	printf("list sort:%d\n", end2 - begin2);
//}
//
//void test_op2()
//{
//	srand(time(0));
//	const int N = 1000000;
//
//	list<int> lt1;
//	list<int> lt2;
//
//	for (int i = 0; i < N; ++i)
//	{
//		auto e = rand() + i;
//		lt1.push_back(e);
//		lt2.push_back(e);
//	}
//
//	int begin1 = clock();
//	// 拷贝vector
//	vector<int> v(lt2.begin(), lt2.end());
//	// 排序
//	sort(v.begin(), v.end());
//
//	// 拷贝回lt2
//	lt2.assign(v.begin(), v.end());
//
//	int end1 = clock();
//
//	int begin2 = clock();
//	lt1.sort();
//	int end2 = clock();
//
//	printf("list copy vector sort copy list sort:%d\n", end1 - begin1);
//	printf("list sort:%d\n", end2 - begin2);
//}
//
//
//int main() {
//	//testlist6();
//	//test_op1();
//	test_op2();
//	return 0;
//}
//

#include "list.h"

void testbytelist1() {
	byte::list<int> lt1;
	lt1.push_back(1);
	lt1.push_back(2);
	lt1.push_back(3);
	lt1.push_back(4);
	lt1.push_back(5);
	lt1.push_back(6);
}

void testbytelist2() {
	byte::list<int> lt1;
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	lt1.push_back(1);
	byte::list<int>::iterator it = lt1.begin();
	while (it != lt1.end()) {
		std::cout << *it << ' ';
		it++;
	}
	std::cout << std::endl;
}

int main() {
	//testbytelist1();
	testbytelist2();
	return 0;
}










