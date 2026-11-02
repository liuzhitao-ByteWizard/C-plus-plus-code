#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
#include <vector>
#include <map>

using namespace std;

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
    //右单旋
    void RotateR(Node* parent) {
        //更新节点
        Node* subL = parent->_left;
        Node* subLR = subL->_right;

        //旋转
        Node* parentParent =  parent->_parent;
        parent->_left = subLR;
        parent->_parent = subL; //更新父节点
        subL->_right = parent;
        //subLR不为空时，才能更新父节点，不然默认为空
        if(subLR)
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

        //更新平衡因子
        subL->_bf = 0;
        parent->_bf = 0;

    }

    // 以 parent 为旋转点进行左单旋。
    // 前提：parent 及其右孩子均不为空。
    void RotateL(Node* parent)
    {
        Node* subR = parent->_right; // 原右孩子，旋转后成为这棵子树的新根。
        Node* subRL = subR->_left;   // 原右孩子的左子树，需要重新连接。

        // 将 subRL 转接为 parent 的右子树，保持二叉搜索树的大小关系。
        parent->_right = subRL;
        if (subRL)
            subRL->_parent = parent; // 子树非空时，同步更新其父指针。

        // 保存旋转点的原父节点，便于将旋转后的子树接回原树。
        Node* parentParent = parent->_parent;

        // parent 下移，成为 subR 的左孩子，并更新其父指针。
        subR->_left = parent;
        parent->_parent = subR;

        if (parentParent == nullptr)
        {
            // 旋转点原本是整棵树的根，需要更新根指针。
            _root = subR;
            subR->_parent = nullptr;
        }
        else
        {
            // 旋转点不是整棵树的根：
            // 用 subR 替换 parent 在原父节点下的位置。
            if (parent == parentParent->_left)
            {
                parentParent->_left = subR;
            }
            else
            {
                parentParent->_right = subR;
            }

            // 新子树根指向原来的上层父节点。
            subR->_parent = parentParent;
        }

        // 对于 AVL 插入导致的 RR 型失衡，
        // 左单旋后，两个节点的左右子树分别等高，平衡因子均为 0。
        parent->_bf = subR->_bf = 0;
    }

    // 对以 parent 为根的子树进行左右双旋。
// 前提：parent 的左孩子 subL 和 subL 的右孩子 subLR 均不为空。
    void RotateLR(Node* parent) {
        Node* subL = parent->_left;    // 旋转前 parent 的左孩子。
        Node* subLR = subL->_right;    // 双旋后这棵子树的新根。

        // 保存 subLR 旋转前的平衡因子：
        // RotateL 和 RotateR 会修改平衡因子，后续需要用原值判断如何更新。
        // 平衡因子定义为：右子树高度 - 左子树高度。
        int bf = subLR->_bf;

        // 第一步：以 subL 为旋转点左旋，使 subLR 上移。
        RotateL(parent->_left);

        // 第二步：以 parent 为旋转点右旋，使 subLR 成为子树根。
        RotateR(parent);

        if (bf == 0) {
            // 典型情况：subLR 是新插入的叶节点。
            // 双旋后，三个节点的平衡因子均为 0。
            parent->_bf = 0;
            subL->_bf = 0;
            subLR->_bf = 0;
        }
        else if (bf == 1) {
            // 插入发生在 subLR 的右子树。
            // 双旋后，subL 的左子树比右子树高 1。
            parent->_bf = 0;
            subL->_bf = -1;
            subLR->_bf = 0;
        }
        else if (bf == -1) {
            // 插入发生在 subLR 的左子树。
            // 双旋后，parent 的右子树比左子树高 1。
            parent->_bf = 1;
            subL->_bf = 0;
            subLR->_bf = 0;
        }
        else {
            // 插入前是合法 AVL 树且平衡因子维护正确时，不应出现其他值。
            assert(false);
        }
    }

    void RotateRL(Node* parent)
    {
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        int bf = subRL->_bf;

        RotateR(parent->_right);
        RotateL(parent);

        if (bf == 0)
        {
            subR->_bf = 0;
            subRL->_bf = 0;
            parent->_bf = 0;
        }
        else if (bf == 1)
        {
            subR->_bf = 0;
            subRL->_bf = 0;
            parent->_bf = -1;
        }
        else if (bf == -1)
        {
            subR->_bf = 1;
            subRL->_bf = 0;
            parent->_bf = 0;
        }
        else
        {
            assert(false);
        }
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

    int Size() {
        return _Size(_root);
    }

    bool Insert(const pair<K, V>& kv) {
        // 空树直接创建根结点。
        if (_root == nullptr)
        {
            _root = new Node(kv);
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

            if (parent->_kv.first < kv.first)
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
                    parent->_bf -= 1;
                else
                    parent->_bf += 1;

                if (parent->_bf == 0)
                    break;
                else if (parent->_bf == 1 || parent->_bf == -1) {
                    //向上更新平衡因子
                    cur = parent;
                    parent = parent->_parent;
                }
                else if (parent->_bf == 2 || parent->_bf == -2) {
                    //旋转：四种情况
                    if (parent->_bf == -2 && cur->_bf == 1) {
                        RotateLR(parent);
                    }
                    else if (parent->_bf == -2 && cur->_bf == -1) {
                        RotateR(parent);
                    }
                    else if (parent->_bf == 2 && cur->_bf == -1) {
                        RotateRL(parent);
                    }
                    else if (parent->_bf == 2 && cur->_bf == 1) {
                        RotateL(parent);
                    }
                    break;
                }
                else {
                    assert(false);
                }
            }

            return true;
        }
    }

    int Height() {
        return _Height(_root);
    }

    bool IsBalanceTree() {
        return _IsBalanceTree(_root);
    }

    void InOrder() {
        _InOrder(_root);
        cout << endl;
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

        return max(leftHeight , rightHeight) + 1;
    }

    bool _IsBalanceTree(Node* root)
    {
        // 空树也是AVL树
        if (nullptr == root)
            return true;

        // 计算pRoot结点的平衡因子：即pRoot左右子树的高度差
        int leftHeight = _Height(root->_left);
        int rightHeight = _Height(root->_right);
        int diff = rightHeight - leftHeight;

        // 如果计算出的平衡因子与pRoot的平衡因子不相等，或者
        // pRoot平衡因子的绝对值超过1，则一定不是AVL树
        if (abs(diff) >= 2)
        {
            cout << root->_kv.first << "高度差异常" << endl;
            return false;
        }

        if (root->_bf != diff)
        {
            cout << root->_kv.first << "平衡因子异常" << endl;
            return false;
        }

        // pRoot的左和右如果都是AVL树，则该树一定是AVL树
        return _IsBalanceTree(root->_left) && _IsBalanceTree(root->_right);
    }


    Node* _root = nullptr;
};
