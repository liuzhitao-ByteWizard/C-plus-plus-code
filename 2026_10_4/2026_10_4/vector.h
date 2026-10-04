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
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		const_iterator begin() const { return _start; }
		const_iterator end() const { return _finish; }

		size_t size() const { return _finish - _start; }
		size_t capacity() const { return _end_of_storage - _start; }

		bool empty() const { return _start == _finish; }

		void reserve(size_t n);

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

		void insert(iterator pos, const T& x);
		iterator erase(iterator pos);

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
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
			size_t newcapacity = capacity() == 0 ? 4 : capacity() * 2;
			reserve(newcapacity);
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

	template <class T>
	void vector<T>::reserve(size_t n) {
		if (n > capacity()) {
			//1.开辟新空间（这里，我们不使用内存池来申请）
			size_t oldSize = size();
			T* tmp = new T[n];
			//2.拷贝旧数据 + 释放旧空间
			memcpy(tmp, _start, size() * sizeof(T));
			delete[] _start;
			//3.指向新空间
			_start = tmp;
			_finish = _start + oldSize;
			_end_of_storage = _start + n; //更新
		}
	}

	template<class T>
	void vector<T>::insert(iterator pos, const T& x) {
		// 当前空间已满，需要先扩容
		if (_finish == _end_of_storage) {
			// 扩容会使原 pos 失效，先保存插入位置相对于起始位置的偏移量
			size_t offset = pos - _start;

			// 容量为 0 时分配 4 个元素的空间，否则扩为原来的 2 倍
			size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
			reserve(newCapacity);

			// 根据新的起始位置和原偏移量，恢复 pos 的插入位置
			pos = _start + offset;
		}

		// 将 [pos, _finish) 内的元素整体右移一位，为新元素腾出位置
		// 源区间与目标区间可能重叠，因此使用 memmove
		memmove(pos + 1, pos, sizeof(T) * (_finish - pos));

		// 将新元素写入插入位置
		*pos = x;

		// 更新有效元素的尾后位置，使 size 增加 1
		++_finish;
	}

	template <class T>
	typename vector<T>::iterator vector<T>::erase(iterator pos) {
		assert(pos >= _start && pos <= _finish); //用指针就不需要考虑头插那个下标挪动小于0的问题了
		iterator it = pos + 1;
		while (it != _finish) {
			*(it - 1) = *it;
			it++;
		}
		--_finish;
		return pos; //返回删除之后的下一个位置
	}



};





