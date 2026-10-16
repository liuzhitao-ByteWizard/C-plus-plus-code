#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>

using namespace std;

namespace byte {

	template<class T , class Container = std::vector<T> , class Compare = std::less<T>>
	class priority_queue {
    public:
        void Adjustup(std::size_t child)
        {
            while (child > 0)
            {
                std::size_t parent = (child - 1) / 2;
                Compare comare;
                if (comare(_con[parent],_con[child]))
                {
                    std::swap(_con[parent], _con[child]);

                    child = parent;
                }
                else
                {
                    break;
                }
            }
        }

        void AjustDown(int parent) {
            int child = parent * 2 + 1;
            while (child < _con.size()) {
                Compare compare;
                if (child + 1 < _con.size() && compare(_con[child] , _con[child + 1]))
                    ++child;

                if (compare(_con[parent] , _con[child])) {
                    std::swap(_con[parent], _con[child]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else {
                    break;
                }
            }
        }

        void pop() {
            std::swap(_con[0], _con[_con.size() - 1]);
            _con.pop_back();
            AjustDown(0);
        }

        const T& top() const  { return _con[0]; }

        bool empty() const { return _con.size() == 0; }

        void push(const T& x)
        {
            _con.push_back(x);

            Adjustup(_con.size() - 1);
        }

        priority_queue(){}

        //迭代器区间初始化
        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last) 
            :_con(first , last)
        {

            //向下调整算法
            for (int i = (_con.size() - 1 - 1) / 2; i >= 0; i--) {

                AjustDown(i);
            }

        }

	private:
		Container _con; //用Container进行访问，它是一个支持方括号访问的容器
	};
}