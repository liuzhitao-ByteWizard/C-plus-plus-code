#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

namespace byte {
	template<class T>
	//不要使用class，要频繁访问成员变量
	struct list_node {
		list_node<T>* _prev;
		list_node<T>* _next;
		T _val;

		//匿名对象做缺省参数
		list_node(const T& val = T())
			:_prev(nullptr)
			, _next(nullptr)
			, _val(val)
		{

		}
	};

	template <class T>
	class list_iterator {
	public:
		typedef list_node<T> Node;

		list_iterator(Node* node)
		:_node(node){
		}

		list_iterator<T>& operator++(int) {
			_node = _node->_next;
			return *this;
		}

		//解引用，访问的是当前节点中的值，不是节点
		T& operator*() {
			return _node->_val;
		}

		bool operator!=(const list_iterator<T>& lt) const {
			return _node != lt._node;
		}
	private:
		Node* _node;

	};

	

	template <class T>
	class list {
	public:
		typedef list_node<T> Node;
		typedef list_iterator<T> iterator;
		//typedef Node* iterator; 不支持的
		list() {
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		void push_back(const T& val);

		iterator begin() { return _head->_next; }
		iterator end() { return _head; } //哨兵位充当开区间位置
	private:
		Node* _head;
	};

	template <class T>
	void list<T>::push_back(const T& val) {
		Node* newnode = new Node(val);
		_head->_prev->_next = newnode;
		newnode->_prev = _head;
		//更新尾节点
		_head->_prev = newnode;
		newnode->_next = _head;
	}

}



