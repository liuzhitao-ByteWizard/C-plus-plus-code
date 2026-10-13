#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <deque>

using namespace std;


namespace byte {
	//模板中容器参数给缺省值，这样如果不指定容器，自动使用deque
	template <class T , class Container = std::deque<T>>
	class stack {
	public:
		void push(const T& x) {
			_con.push_back(x);
		}

		size_t size() {
			return _con.size();
		}

		T& top() {
			//不要使用[],list是不支持[]的
			//list和vector都有back，直接使用back来返回进行
			return _con.back();
		}

		void pop() {
			_con.pop_back();
		}

		bool empty() { return _con.empty(); }


	private:
		Container _con;
	};

}

