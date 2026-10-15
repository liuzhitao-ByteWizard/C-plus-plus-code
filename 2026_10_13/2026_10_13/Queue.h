#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <deque>


using namespace std;

namespace byte {
	template<class T, class Container = std::deque<T>>
	class queue {
	public:
		void push(const T& x) { _con.push_back(x); }
		//void pop() { _con.erase(_con.begin()); }  // 工程场景
		void pop() { _con.pop_front(); }  // 工程场景
		size_t size() { return _con.size(); }
		bool empty() { return _con.empty(); }
		T& front() { return _con.front(); }
		T& back() { return _con.back(); }
	private:
		Container _con;
	};

}