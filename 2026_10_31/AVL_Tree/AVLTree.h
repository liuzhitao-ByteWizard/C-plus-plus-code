#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <map>

// AVL 树节点：K 为键的类型，V 为值的类型
template<class K, class V>
struct AVLTreeNode
{
    pair<K, V> _kv;
    AVLTreeNode<K, V>* _left;
    AVLTreeNode<K, V>* _right;
    AVLTreeNode<K, V>* _parent;    // 父节点，便于向上更新平衡因子和调整结构

    // 平衡因子 = 右子树高度 - 左子树高度
    // 节点处于平衡状态时，值为 -1、0 或 1
    int _bf;

    // 创建新节点：保存键值对，并初始化指针和平衡因子
    AVLTreeNode(const pair<K, V>& kv)
        : _kv(kv)
        , _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
        , _bf(0)                   // 新节点没有左右孩子，平衡因子为 0
    {
    }
};

template<class K, class V>
class AVLTree
{
    // 为当前键值类型对应的节点定义简短的类型名
    typedef AVLTreeNode<K, V> Node;
public:
    void Insert(const pair<K, V>& kv) {
        // 空树直接创建根结点。
        if (_root == nullptr)
        {
            _root = new Node(kv);
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
            cur->_parent = parent;

            //更新平衡因子
            while (parent) {
                if (cur == parent->_left)
                    cur->_bf -= 1;
                else
                    cur->_bf += 1;

                if (cur->_bf == 0)
                    break;
                else if (cur->_bf == 1 || cur->_bf == -1) {
                    //向上更新平衡因子
                    cur = parent;
                    parent = cur->_parent;
                }
                else if(cur->_bf == 2 || cur->_bf == -2){
                    //旋转
                    break;
                }
                else {
                    assert(false);
                }
            }

            return true;
        }
    }
private:
    Node* _root = nullptr;
};
