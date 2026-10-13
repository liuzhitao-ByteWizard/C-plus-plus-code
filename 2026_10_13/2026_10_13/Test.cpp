#include "Stack.h"

void testbytestack() {

	byte::stack<int> st1; //默认使用deque容器
	//指定使用容器
	byte::stack<int, vector<int>> st2; 
	byte::stack<int, list<int>> st3;
	st1.push(1);
	st1.push(2);
	st1.push(3);
	st1.push(4);
	st1.push(5);

	while (!st1.empty()) {
		cout << st1.top() << ' ';
		st1.pop();
	}
}

int main() {
	testbytestack();
	return 0;
}