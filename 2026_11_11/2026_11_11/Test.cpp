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
		sit->first = 1;
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

int main() {

	//byte::set<int>::iterator it = t1.begin();
	//while (it != t1.end()) {
	//	cout << *it << " ";
	//	++it;
	//}
	//cout << endl;
	//testmap();
	testmap();
	return 0;
}
