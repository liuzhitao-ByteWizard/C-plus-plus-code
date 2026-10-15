#include "priority_queue.h"

void TestPriorityQueue1() {
	// 默认情况下大的优先级高
	vector<int> v{ 3,2,7,6,0,4,1,9,8,5,2,2,3 };
	//支持push，也支持迭代器区间构造
	priority_queue<int> q1(v.begin() , v.end());


	//没有迭代器的，不支持遍历
	while (!q1.empty()) {
		cout << q1.top() << ' ';
		q1.pop();
	}
	cout << endl;


}

int main() {
	TestPriorityQueue1();
	return 0;
}