#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "MyMap.h"
#include "MySet.h"
#include <vector>

using namespace std;

void testmap1() {
	byte::map<int, int> s1;
	s1.Insert({ 1,1 });
	s1.Insert({ 9,1 });
	s1.Insert({ 5,1 });
	s1.Insert({ 3,1 });
	s1.Insert({ 7,1 });

	byte::map<int,int>::iterator it = s1.begin();
	while (it != s1.end()) {
		//it->first = rand(); //这个不能进行修改
		//it->second = rand(); //这个可以修改
		cout << it->first << " "<<  it->second << endl;
		++it;
	}
	cout << endl;

}

void Print(const byte::set<int>& cs) {
	byte::set<int>::const_iterator sit = cs.begin();
	while (sit != cs.end()) {
		//*sit = 5; //不能修改
		cout << *sit << " ";
		++sit;
	}
	cout << endl;
}

//void Print(const byte::map<int, int>& cs) {
//	byte::map<int , int>::const_iterator sit = cs.begin();
//	while (sit != cs.end()) {
//		sit->first = 1;
//		sit->second = rand();
//		cout << sit->first << " " << sit->second << endl;;
//		++sit;
//	}
//	cout << endl;
//}

void Print(byte::map<int, int>& cs) {
	byte::map<int, int>::iterator sit = cs.begin();
	while (sit != cs.end()) {
		//sit->first = 1;
		sit->second = rand();
		cout << sit->first << " " << sit->second << endl;;
		++sit;
	}
	cout << endl;
}


void testmap() {
	byte::map<int,int> s1;
	s1.Insert({ 1,1 });
	s1.Insert({ 9,1 });
	s1.Insert({ 5,1 });
	s1.Insert({ 3,1 });
	s1.Insert({ 7,1 });
	Print(s1);
}

void testset() {
	byte::set<int> t1;
	t1.Insert(1);
	t1.Insert(6);
	t1.Insert(4);
	t1.Insert(8);
	t1.Insert(2);
	Print(t1);
}

void test() {
	byte::map<int, int> m;
	m.Insert({ 1,1 });
	m.Insert({ 5,1 });
	m.Insert({ 2,1 });
	m.Insert({ 9,1 });

	byte::set<int> s;
	s.Insert(1);
	s.Insert(4);
	s.Insert(1);
	s.Insert(2);
	s.Insert(5);
	s.Insert(6);

	byte::set<int>::iterator sit = s.begin();
	while (sit != s.end()) {
		// *sit = rand(); //不能修改
		cout << *sit << " ";
		++sit;
	}
	cout << endl;

	byte::map<int, int>::iterator mit = m.begin();
	while (mit != m.end()) {
		// mit->first = rand(); //不能修改
		mit->second = rand(); // 可以修改

		cout << mit->first << ":" << mit->second << endl;
		++mit;
	}
	cout << endl;

	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜","苹果", "香蕉", "苹果", "香蕉" };
	byte::map<string, int> countMap;
	for (const auto& str : arr) {
		countMap[str]++;
	}

	for (const auto& e : countMap)
	{
		cout << e.first << ":" << e.second << endl;
	}
	cout << endl;
}

void test_map()
{
	byte::map<string, string> dict;
	dict.Insert({ "sort", "排序" });
	dict.Insert({ "left", "左边" });
	dict.Insert({ "right", "右边" });

	dict["left"] = "左边，剩余";

	dict["insert"] = "插入";

	dict["string"];

	byte::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{

		it->second += 'x';

		cout << it->first << ":" << it->second << endl;
		++it;
	}

	cout << endl;
}

int main() {
	test_map();
	return 0;
}
