#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>

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
	struct list_iterator {
		typedef list_node<T> Node;

		list_iterator(Node* node)
		:_node(node){
		}

		list_iterator<T>& operator++(int) {
			_node = _node->_next;
			return *this;
		}

		list_iterator<T>& operator++() {
			_node = _node->_next;
			return *this;
		}

		list_iterator<T>& operator--() {
			_node = _node->_prev;
			return *this;
		}

		bool operator!=(list_iterator<T> node) {
			return _node != node._node;
		}

		//解引用，访问的是当前节点中的值，不是节点
		T& operator*() {
			return _node->_val;
		}

		bool operator!=(const list_iterator<T>& lt) const {
			return _node != lt._node;
		}


		Node* _node;

	};

	template <class T>
	struct list_const_iterator {
		typedef list_node<T> Node;

		list_const_iterator(Node* node)
			:_node(node) {
		}

		list_const_iterator<T>& operator++(int) {
			_node = _node->_next;
			return *this;
		}

		list_const_iterator<T>& operator++() {
			_node = _node->_next;
			return *this;
		}

		list_const_iterator<T>& operator--() {
			_node = _node->_prev;
			return *this;
		}

		bool operator!=(list_iterator<T> node) {
			return _node != node._node;
		}

		//解引用，访问的是当前节点中的值，不是节点
		const T& operator*() {
			return _node->_val;
		}

		bool operator!=(const list_iterator<T>& lt) const {
			return _node != lt._node;
		}
		Node* _node;

	};


	template <class T>
	class list {
	public:
		typedef list_node<T> Node;
		typedef list_iterator<T> iterator;
		typedef list_const_iterator<T> const_iterator;
		//typedef const T* iterator;

		list() {
			empty_initialize();
		}

		iterator begin() { return _head->_next; }

		const_iterator begin() const  { return _head->_next; }
		
		iterator end() { return _head; } //哨兵位充当开区间位置
		
		const_iterator end() const { return _head; } //哨兵位充当开区间位置

		//在pos位置之前插入val值
		void insert(iterator pos, const T& val) {
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* newnode  = new Node(val);
			//修改节点之间的关系
			newnode->_next = cur;
			cur->_prev = newnode;
			newnode->_prev = prev;
			prev->_next = newnode;
			
			//增加有效元素的个数
			++_size;
		}

		//返回的是删除节点的下一个位置
		iterator erase(iterator pos) {
			//不能删除哨兵位
			assert(pos._node != _head);
			Node* del = pos._node;
			Node* next = del->_next;
			Node* prev = del->_prev;
			//1.改变链接关系
			prev->_next = next;
			next->_prev = prev;
			//2.释放节点
			delete del;
			//3.更新size
			--_size;
			return next;
		}

		void pop_front() {
			erase(begin());
		}

		void pop_back() {
			erase(--end());
		}

		//头插
		void push_front(const T& val) {
			insert(begin(), val);
		}

		void push_back(const T& val) {
			insert(end(), val);
		}

		~list() {
			clear(); //1.先将所有的节点删除
			delete _head; //2.删除哨兵节点
			_head = nullptr;
		}

		void clear() {
			iterator it = begin();
			//出哨兵位之外的所有元素都删除
			while (it != end()) {
				it = erase(it);
			}
		}
		//拷贝构造函数
		//lt1(lt2)
		list(list<T>& lt) {
			empty_initialize();
			auto it = lt.begin();
			//拷贝一样节点的个数，一样的值
			for (auto& e : lt) {
				push_back(e);
			}
		}

		void empty_initialize() {
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}
		//lt1 = lt2
		//调用拷贝构造，拷贝出一份临时对象，将this与这个对象进行交换
		list<T>& operator=(list<T> lt) {
			swap(lt);
			return *this;
		}

		void swap(list<T>& lt) {
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		//list(initializer_list<T> il) {
		//	//1.初始化链表结构
		//	empty_initialize();
		//	//2.插入数据
		//	for (auto& e : il) {
		//		push_back(e);
		//	}
		//}


	private:
		Node* _head;
		size_t _size;
	};

}



