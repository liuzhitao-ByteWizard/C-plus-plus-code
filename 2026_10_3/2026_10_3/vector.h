#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

namespace byte {
	template <class T>
	class vector {
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		//短小的函数默认定义为内联函数inline
		iterator begin()  { return _start; }
		iterator end()   { return _finish; }
		const_iterator begin() const { return _start; }
		const_iterator end() const { return _finish; }

		size_t size() const  { return _finish - _start; }
		size_t capacity() const { return _end_of_storage - _start; }

		bool empty() const { return _start == _finish; }

		//可读可写
		T& operator[](size_t n) {
			assert(!empty());
			assert(n >= 0 && n < size());
			return *(_start + n);
		}

		const T& operator[](size_t n) const {
			assert(!empty());
			assert(n >= 0 && n < size());
			return *(_start + n);
		}

		vector()
		:_start(nullptr)
		,_finish(nullptr)
		,_end_of_storage(nullptr)
		{

		}

		//加上引用，减少拷贝
		void push_back(const T& x);
		void pop_back();

	private:
		iterator _start;
		iterator _finish;
		iterator _end_of_storage;
	};
	
	template <class T>
	void vector<T>::push_back(const T& x) {
		//考虑扩容的问题
		if (_finish == _end_of_storage) {
			//1.开辟新空间（这里，我们不使用内存池来申请）
			size_t oldSize = size();
			size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
			T* tmp = new T[newcapacity];
			//2.拷贝旧数据 + 释放旧空间
			memcpy(tmp, _start, size() * sizeof(T));
			delete[] _start;
			//3.指向新空间
			_start = tmp;
			_finish = _start + oldSize;
			_end_of_storage = _start + newcapacity; //更新
		}

		//尾插元素
		*_finish = x;
		++_finish; //有效元素+1
	}

	template <class T>
	void vector<T>::pop_back() {
		assert(!empty()); //vector不能为空
		--_finish; //逻辑上删除数据
	}



};




