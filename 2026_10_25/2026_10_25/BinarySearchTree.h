#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

template <class K>
struct BSTNode {
	//构造函数
	BSTNode(const K& key)
		:_right(nullptr)
		,_left(nullptr)
		,_key(key)
	{}

	BSTNode<K>* _right;
	BSTNode<K>* _left;
	K _key;
};

template <class K>
class BSTree {
public:
	typedef BSTNode<K> Node;
	bool InsertR(const K& key) {
		return _InsertR(_root, key);
	}

	bool _InsertR(Node*& node, const K& key) {
		if (node == nullptr) {
			node = new Node(key);
			return true;
		}

		if (node->_key < key)
			return _InsertR(node->_right, key);
		else
			return _InsertR(node->_left, key);
	}

	bool Insert(const K& key);

	bool Find(const K& key);
	
	bool _FindR(Node* node , const K& key);
	bool FindR(const K& key) {
		return _FindR(_root , key);
	}

	bool Erase(const K& key);

	//由于我们访问不到根节点，所以我们可以采取子函数的方式（套一层）获取
	void Inorder() {
		_InOrder(_root);
		cout << endl;
	}

private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	//默认为空树
	Node* _root = nullptr; //存放的是根节点的位置
};

template <class K>
bool BSTree<K>::Insert(const K& key) {
	if (_root == nullptr) {
		_root = new Node(key);
		return true;
	}
	else {
		Node* cur = _root;
		Node* parent = nullptr;
		//当前结点不为空
		while (cur) {
			if (cur->_key > key) {
				//当前结点关键字比插入节点关键字大，向左走
				parent = cur; //保证链接关系
				cur = cur->_left;
			}
			else if (cur->_key < key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				//不允许插入相等的值
				return false;
			}
		}

		cur = new Node(key);
		//将插入节点与当前树进行链接
		if (parent->_key < key) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		return true;
	}
}

template <class K>
bool BSTree<K>::Find(const K& key) {
	Node* cur = _root;
	//当前结点不为空
	while (cur) {
		if (cur->_key > key) {
			//当前结点关键字比插入节点关键字大，向左走
			cur = cur->_left;
		}
		else if (cur->_key < key) {
			cur = cur->_right;
		}
		else {
			return true;
		}
	}
	return false;
}

template <class K>
bool BSTree<K>::Erase(const K& key) {
	Node* parent = nullptr;
	Node* cur = _root;
	while (cur) {
		if (cur->_key < key) {
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_key > key) {
			parent = cur;
			cur = cur->_left;
		}
		else {
			// 准备删除
			if (cur->_left == nullptr) { // 左为空
				if (cur == _root) {
					_root = cur->_right;
				}
				else {
					if (cur == parent->_left)
						parent->_left = cur->_right;
					else
						parent->_right = cur->_right;
				}

				delete cur;
			}
			else if (cur->_right == nullptr) { // 右为空
				if (cur == _root) {
					_root = cur->_left;
				}
				else {
					if (cur == parent->_left)
						parent->_left = cur->_left;
					else
						parent->_right = cur->_left;
				}

				delete cur;
			}
			else { // 左右均不为空
				Node* replaceParent = cur;
				Node* replace = cur->_right;
				while (replace->_left) {
					replaceParent = replace;
					replace = replace->_left;
				}

				std::swap(cur->_key, replace->_key);
				if (replace == replaceParent->_left) {
					replaceParent->_left = replace->_right;
				}
				else {
					replaceParent->_right = replace->_right;
				}

				delete replace;
			}

			return true;
		}
	}

	return false;
}

template <class K>
bool BSTree<K>::_FindR(Node* node , const K& key) {
	if (node == nullptr)
		return false;

	if (node->_key < key) {
		return _FindR(node->_right, key);
	}
	else if(node->_key > key){
		return _FindR(node->_left, key);
	}
	else {
		return true;
	}

}
