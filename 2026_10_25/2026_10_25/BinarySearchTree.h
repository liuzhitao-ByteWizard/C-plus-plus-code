#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

namespace key {
	template <class K>
	struct BSTNode {
		//构造函数
		BSTNode(const K& key)
			:_right(nullptr)
			, _left(nullptr)
			, _key(key)
		{
		}

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

		bool _FindR(Node* node, const K& key);
		bool FindR(const K& key) {
			return _FindR(_root, key);
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
	bool BSTree<K>::_FindR(Node* node, const K& key) {
		if (node == nullptr)
			return false;

		if (node->_key < key) {
			return _FindR(node->_right, key);
		}
		else if (node->_key > key) {
			return _FindR(node->_left, key);
		}
		else {
			return true;
		}

	}
}

namespace keyvalue
{
    // K 表示关键码类型，V 表示关联值类型。
    // 搜索树仅根据 key 确定结点的位置，value 不参与比较。
    template<class K, class V>
    struct BSTNode
    {
        // 创建结点，初始化键值对，左右孩子均为空。
        BSTNode(const K& key, const V& val)
            : _right(nullptr)
            , _left(nullptr)
            , _key(key)
            , _value(val)
        {
        }

        BSTNode<K, V>* _right;
        BSTNode<K, V>* _left;
        K _key;
        V _value;
    };

    template<class K, class V>
    class BSTree
    {
    public:
        typedef BSTNode<K, V> Node;

        // 插入键值对；key 已存在时返回 false，不覆盖原 value。
        bool Insert(const K& key, const V& val);

        // 找到时返回结点指针，否则返回 nullptr。
        // 可通过指针修改 _value；直接修改 _key 可能破坏搜索树性质。
        Node* Find(const K& key);

        // 删除 key 对应的整个结点。
        // 删除成功返回 true，key 不存在则返回 false。
        bool Erase(const K& key);

        // 对外提供无参接口，内部从根结点开始递归遍历。
        void Inorder()
        {
            _InOrder(_root);
            std::cout << std::endl;
        }
    

        ~BSTree() {
            _Destroy(_root);
            _root = nullptr;
        }
        BSTree(){} //写了拷贝构造函数，编译器就不会生成默认构造函数，我们就需要显示写默认构造函数
        //C++11之后，在类中类名就是类型
        //BSTree<K,V>(const BSTree<K,V>& node)
        BSTree(const BSTree& node) {
            //先拷贝根节点，再拷贝左子树和右子树
            _root = _Copy(node._root);
        }

        //T1 = T3
        BSTree& operator=(BSTree node)   {
                std::swap(_root, node._root);
                return *this;
        }



    private:

        Node* _Copy(const Node* node) {
            //先拷贝根节点
            if (node == nullptr)
                return nullptr;
            Node* _copy = new Node(node->_key, node->_value);
            //在拷贝左子树和右子树
            _copy->_left = _Copy(node->_left);
            _copy->_right = _Copy(node->_right);
            return _copy;
        }

        void _Destroy(Node* node) {
            if (node == nullptr)
                return;
            //后序遍历
            _Destroy(node->_left);
            _Destroy(node->_right);
            delete node;
        }

        // 中序遍历：左子树 -> 当前结点 -> 右子树。
        // 对二叉搜索树进行中序遍历，可按 key 升序输出键值对。
        void _InOrder(Node* root)
        {
            if (root == nullptr)
            {
                return;
            }

            _InOrder(root->_left);
            std::cout << root->_key << " "
                << root->_value << " " << std::endl;
            _InOrder(root->_right);
        }

        // 保存根结点地址，初始为空树。
        Node* _root = nullptr;
    };

    template<class K, class V>
    bool BSTree<K, V>::Insert(const K& key, const V& val)
    {
        // 空树直接创建根结点。
        if (_root == nullptr)
        {
            _root = new Node(key, val);
            return true;
        }
        else
        {
            Node* cur = _root;

            // 记录父结点，便于找到插入位置后连接新结点。
            Node* parent = nullptr;

            while (cur)
            {
                if (cur->_key > key)
                {
                    // 待插入的 key 较小，向左子树查找。
                    parent = cur;
                    cur = cur->_left;
                }
                else if (cur->_key < key)
                {
                    // 待插入的 key 较大，向右子树查找。
                    parent = cur;
                    cur = cur->_right;
                }
                else
                {
                    // key 已存在，不允许插入重复的 key。
                    return false;
                }
            }

            // cur 为空时，parent 就是新结点应连接的父结点。
            cur = new Node(key, val);

            if (parent->_key < key)
            {
                parent->_right = cur;
            }
            else
            {
                parent->_left = cur;
            }

            return true;
        }
    }

    template<class K, class V>
    typename BSTree<K, V>::Node* BSTree<K, V>::Find(const K& key)
    {
        Node* cur = _root;

        while (cur)
        {
            if (cur->_key > key)
            {
                // 目标 key 较小，向左查找。
                cur = cur->_left;
            }
            else if (cur->_key < key)
            {
                // 目标 key 较大，向右查找。
                cur = cur->_right;
            }
            else
            {
                // key 匹配，返回结点，供调用者访问对应的 value。
                return cur;
            }
        }

        // 查找到空位置仍未匹配，说明 key 不存在。
        return nullptr;
    }

    template<class K, class V>
    bool BSTree<K, V>::Erase(const K& key)
    {
        Node* parent = nullptr;
        Node* cur = _root;

        // 查找待删除结点，同时记录它的父结点。
        while (cur)
        {
            if (cur->_key < key)
            {
                parent = cur;
                cur = cur->_right;
            }
            else if (cur->_key > key)
            {
                parent = cur;
                cur = cur->_left;
            }
            else
            {
                // 情况一：左子树为空，让右孩子接替当前结点。
                // 叶子结点也属于此情况，此时右孩子同样为空。
                if (cur->_left == nullptr)
                {
                    if (cur == _root)
                    {
                        // 根结点没有父结点，需要直接更新 _root。
                        _root = cur->_right;
                    }
                    else
                    {
                        // 根据当前结点的位置，更新父结点的对应指针。
                        if (cur == parent->_left)
                            parent->_left = cur->_right;
                        else
                            parent->_right = cur->_right;
                    }

                    delete cur;
                }
                // 情况二：右子树为空，让左孩子接替当前结点。
                else if (cur->_right == nullptr)
                {
                    if (cur == _root)
                    {
                        _root = cur->_left;
                    }
                    else
                    {
                        if (cur == parent->_left)
                            parent->_left = cur->_left;
                        else
                            parent->_right = cur->_left;
                    }

                    delete cur;
                }
                // 情况三：左右子树均非空，使用中序后继进行替换。
                else
                {
                    Node* replaceParent = cur;
                    Node* replace = cur->_right;

                    // 中序后继是右子树中 key 最小的结点，
                    // 即从右孩子开始一直向左找到的结点。
                    while (replace->_left)
                    {
                        replaceParent = replace;
                        replace = replace->_left;
                    }

                    // 同时交换 key 和 value，保持键值对应关系。
                    // 原待删除的键值对被移到后继结点，随后删除该结点。
                    std::swap(cur->_key, replace->_key);
                    std::swap(cur->_value, replace->_value);

                    // 后继没有左孩子，但可能有右孩子。
                    // 删除后继前，需要将它的右孩子连接到其父结点。
                    if (replace == replaceParent->_left)
                    {
                        replaceParent->_left = replace->_right;
                    }
                    else
                    {
                        // 后继就是 cur 的右孩子，此时 replaceParent == cur。
                        replaceParent->_right = replace->_right;
                    }

                    delete replace;
                }

                return true;
            }
        }

        // 空树或未找到目标 key，删除失败。
        return false;
    }
}


