#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

// 枚举值表示颜色
enum Colour
{
    RED,
    BLACK
};

// 这里我们默认按key/value结构实现
template<class K, class V>
struct RBTreeNode
{
    // 这里更新控制平衡也要加入parent指针
    pair<K, V> _kv;
    RBTreeNode<K, V>* _left;
    RBTreeNode<K, V>* _right;
    RBTreeNode<K, V>* _parent;
    Colour _col;

    RBTreeNode(const pair<K, V>& kv)
        : _kv(kv)
        , _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
    {
    }
};

template<class K, class V>
class RBTree
{
    typedef RBTreeNode<K, V> Node;

public:
    //右单旋
    void RotateR(Node* parent) {
        //更新节点
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        //旋转
        Node* parentParent = parent->_parent;
        parent->_left = subLR;
        parent->_parent = subL; //更新父节点
        subL->_right = parent;
        //subLR不为空时，才能更新父节点，不然默认为空
        if (subLR)
            subLR->_parent = parent;
        //如果parent是根节点，旋转之后根节点需要更新
        if (parent == _root) {
            _root = subL;
            subL->_parent = nullptr;
        }
        else {
            //不是根节点，就需要进行向上链接
            subL->_parent = parentParent;
            //parentParent向下链接
            if (parentParent->_left == parent) {
                parentParent->_left = subL;
            }
            else {
                parentParent->_right = subL;
            }
        }
    }

    void RotateL(Node* parent)
    {
        Node* subR = parent->_right; // 原右孩子，旋转后成为这棵子树的新根。
        Node* subRL = subR->_left;   // 原右孩子的左子树，需要重新连接。

        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent; // 子树非空时，同步更新其父指针。

        Node* parentParent = parent->_parent;

        subR->_left = parent;
        parent->_parent = subR;

        if (parentParent == nullptr)
        {
            _root = subR;
            subR->_parent = nullptr;
        }
        else
        {
            if (parent == parentParent->_left)
            {
                parentParent->_left = subR;
            }
            else
            {
                parentParent->_right = subR;
            }

            subR->_parent = parentParent;
        }
    }

    void RotateLR(Node* parent) {
        Node* subL = parent->_left;    // 旋转前 parent 的左孩子。
        Node* subLR = subL->_right;    // 双旋后这棵子树的新根。

        RotateL(parent->_left);

        RotateR(parent);
    }

    void RotateRL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;

        RotateR(parent->_right);
        RotateL(parent);

    }

    int Size() {
        return _Size(_root);
    }

    bool Insert(const pair<K, V>& kv) {
        // 空树直接创建根结点。
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK; //根节点是黑色的
            return true;
        }
        else
        {
            Node* cur = _root;

            // 记录父结点，便于找到插入位置后链接新结点。
            Node* parent = nullptr;

            while (cur)
            {
                if (cur->_kv.first > kv.first)
                {
                    // 待插入的 key 较小，向左子树查找。
                    parent = cur;
                    cur = cur->_left;
                }
                else if (cur->_kv.first < kv.first)
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
            cur = new Node(kv);
            cur->_col = RED;
            if (parent->_kv.first < kv.first)
            {
                parent->_right = cur;
            }
            else
            {
                parent->_left = cur;
            }
            cur->_parent = parent;

            //需要进行处理
            while (parent && parent->_col == RED) {
                //uncle存在且为红色的时候
                Node* grandparent = parent->_parent;
                Node* uncle = nullptr;
                if (grandparent->_left == parent)
                    uncle = grandparent->_right;
                else
                    uncle = grandparent->_left;

                //父亲是爷爷的左边
                if (grandparent->_left == parent) {
                    if (uncle && uncle->_col == RED) {
                        parent->_col = uncle->_col = BLACK;
                        grandparent->_col = RED;
                        cur = grandparent; //向上更新
                        parent = cur->_parent;
                    }
                    else if (cur == parent->_right) {
                        //双旋+变色
                        RotateL(parent);
                        RotateR(grandparent);

                        cur->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                    else {
                        //不存在或者存在为黑色的情况
                        //右单旋+变色
                        RotateR(grandparent);
                        //变色
                        parent->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                }
                else {
                    if (uncle && uncle->_col == RED) {
                        parent->_col = uncle->_col = BLACK;
                        grandparent->_col = RED;
                        //向上更新
                        cur = grandparent; 
                        parent = cur->_parent;
                    }
                    else if (cur == parent->_left) {
                        //双旋+变色
                        RotateR(parent);
                        RotateL(grandparent);

                        cur->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                    else {
                        //不存在或者存在为黑色的情况
                        //左单旋+变色
                        RotateL(grandparent);
                        //变色
                        parent->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                }
            }
            _root->_col = BLACK; //确保根节点为黑

            return true;
        }
    }

    int Height() {
        return _Height(_root);
    }


    void InOrder() {
        _InOrder(_root);
        cout << endl;
    }
    Node* Find(const K& key)
    {
        Node* cur = _root;
        while (cur)
        {
            if (cur->_kv.first < key)
            {
                cur = cur->_right;
            }
            else if (cur->_kv.first > key)
            {
                cur = cur->_left;
            }
            else
            {
                return cur;
            }
        }

        return nullptr;
    }

    bool Check(Node* root, int blackNum, const int refNum)
    {
        if (root == nullptr)
        {
            // 前序遍历走到空时，意味着一条路径走完了
            //cout << blackNum << endl;
            if (refNum != blackNum)
            {
                cout << "存在黑色结点的数量不相等的路径" << endl;
                return false;
            }

            return true;
        }

        // 检查孩子不太方便，因为孩子有两个，且不一定存在，反过来检查父亲就方便多了
        if (root->_col == RED && root->_parent->_col == RED)
        {
            cout << root->_kv.first << "存在连续的红色结点" << endl;
            return false;
        }

        if (root->_col == BLACK)
        {
            blackNum++;
        }

        return Check(root->_left, blackNum, refNum)
            && Check(root->_right, blackNum, refNum);
    }


    bool IsBalanceTree()
    {
        if (_root == nullptr)
            return true;

        if (_root->_col == RED)
            return false;

        // 参考值
        int refNum = 0;
        Node* cur = _root;
        while (cur)
        {
            if (cur->_col == BLACK)
            {
                ++refNum;
            }

            cur = cur->_left;
        }

        return Check(_root, 0, refNum);
    }
private:

    int _Size(Node* _root) {
        if (_root == nullptr)
            return 0;
        return _Size(_root->_left) + _Size(_root->_right) + 1;
    }

    void _InOrder(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        _InOrder(root->_left);
        cout << root->_kv.first << " ";
        _InOrder(root->_right);
    }

    int _Height(Node* root)
    {
        if (root == nullptr)
            return 0;

        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);

        return max(leftHeight, rightHeight) + 1;
    }
    Node* _root = nullptr;
};