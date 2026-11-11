#pragma once

// 枚举值表示颜色
enum Colour
{
    RED,
    BLACK
};

// 这里我们默认按key/value结构实现
template<class T>
struct RBTreeNode
{
    // 这里更新控制平衡也要加入parent指针
    T _data; //数据域
    RBTreeNode<T>* _left;
    RBTreeNode<T>* _right;
    RBTreeNode<T>* _parent;
    Colour _col;

    RBTreeNode(const T& data)
        : _data(data)
        , _left(nullptr)
        , _right(nullptr)
        , _parent(nullptr)
    {
    }
};

template<class T , class Ref , class Ptr>
struct RBTreeiterator {
    typedef RBTreeNode<T> Node;
    typedef RBTreeiterator<T, Ref, Ptr> Self;
    RBTreeiterator(Node* node)
    :_node(node){}
    Ref operator*() {
        return _node->_data;
    }

    Self operator++() {
        Node* parent = _node->_parent;
        Node* cur = _node;
        if (cur->_right) {
            //访问右子树中中序的第一个
            //这时候就不需要判断cur是否为空
            cur = cur->_right;
            while (cur->_left) {
                cur = cur->_left;
            }
            _node = cur;
        }
        else {
            //右子树为空，代表当前子树已经访问完了
            while (parent && parent->_right == cur) {
                cur = parent;
                parent = cur->_parent;
            }
            _node = parent;
        }
        return *this;
    }

    Ptr operator->() {
        return &_node->_data;
    }

    bool operator!=(const Self& it) const  {
        return _node != it._node;
    }

    bool operator==(const Self& it) const {
        return _node == it._node;
    }
private:
    Node* _node;
};



//当tree是set的时候，T->K
//当tree是map的时候，T->pair<const K, V>
template<class K, class T , class KeyofT>
class RBTree
{
public:
    typedef RBTreeNode<T> Node;
    typedef RBTreeiterator<T, T&, T*> iterator;
    typedef RBTreeiterator<T, const T&, const T*> const_iterator;

    iterator end() {
        return iterator(nullptr);
    }

    iterator begin() {
        //找最左节点
        Node* cur = _root;
        while (cur && cur->_left) {
            cur = cur->_left;
        }
        return iterator(cur);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    const_iterator begin() const  {
        //找最左节点
        Node* cur = _root;
        while (cur && cur->_left) {
            cur = cur->_left;
        }
        return const_iterator(cur);
    }

    bool Insert(const T& data)
    {
        // KeyofT 是模板参数，表示“从 T 类型数据中提取 key”的仿函数类型。
        // set：T 是键类型 K，SetKeyOfT 返回数据本身。
        // map：T 是键值对类型，MapKeyOfT 返回键值对中的 first。
        //
        // kot 是 KeyofT 类型的仿函数对象。
        // kot(data) 会调用该对象的 operator()，提取 data 中的 key。
        // KeyofT 只负责提取 key，大小关系仍由后面的 > 和 < 判断。
        KeyofT kot;

        if (_root == nullptr)
        {
            _root = new Node(data);
            _root->_col = BLACK;
            return true;
        }
        else
        {
            Node* cur = _root;

            // 记录父结点，便于找到插入位置后链接新结点。
            Node* parent = nullptr;

            // 通过仿函数提取 key，使 set 和 map 能复用同一套查找逻辑。
            // kot(cur->_data)：当前结点的 key。
            // kot(data)：待插入数据的 key。
            // 对于 map，这里只比较 key，不比较键值对中的 value。
            while (cur)
            {
                if (kot(cur->_data) > kot(data))
                {
                    // 待插入的 key 较小，向左子树查找。
                    parent = cur;
                    cur = cur->_left;
                }
                else if (kot(cur->_data) < kot(data))
                {
                    parent = cur;
                    cur = cur->_right;
                }
                else
                {
                    return false;
                }
            }

            // 结点仍然存储完整的 T 类型数据，仿函数仅用于提取比较所需的 key。
            // 因此，map 的结点中保存的是完整键值对，而不只是 key。
            cur = new Node(data);
            cur->_col = RED;

            // 链接新结点时，同样通过仿函数提取 key，判断应插入哪一侧。
            if (kot(parent->_data) < kot(data))
            {
                parent->_right = cur;
            }
            else
            {
                parent->_left = cur;
            }
            cur->_parent = parent;

            // 父结点为红色时出现连续红结点，需要通过变色或旋转进行修复。
            while (parent && parent->_col == RED)
            {
                Node* grandparent = parent->_parent;
                Node* uncle = nullptr;

                // 根据父结点的位置，确定叔叔结点。
                if (grandparent->_left == parent)
                    uncle = grandparent->_right;
                else
                    uncle = grandparent->_left;

                // 父结点是祖父结点的左孩子。
                if (grandparent->_left == parent)
                {
                    if (uncle && uncle->_col == RED)
                    {
                        // 叔叔存在且为红色：父、叔变黑，祖父变红，
                        // 再将祖父作为当前结点，继续向上检查。
                        parent->_col = uncle->_col = BLACK;
                        grandparent->_col = RED;

                        cur = grandparent;
                        parent = cur->_parent;
                    }
                    else if (cur == parent->_right)
                    {
                        // 叔叔为黑色或不存在，且当前为左右结构：
                        // 先对父结点左旋，再对祖父结点右旋。
                        RotateL(parent);
                        RotateR(grandparent);

                        cur->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                    else
                    {
                        // 叔叔为黑色或不存在，且当前为左左结构：
                        // 对祖父结点右旋，并调整颜色。
                        RotateR(grandparent);

                        parent->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                }
                else
                {
                    // 父结点是祖父结点的右孩子，与上面的处理对称。
                    if (uncle && uncle->_col == RED)
                    {
                        // 叔叔存在且为红色：变色后继续向上检查。
                        parent->_col = uncle->_col = BLACK;
                        grandparent->_col = RED;

                        cur = grandparent;
                        parent = cur->_parent;
                    }
                    else if (cur == parent->_left)
                    {
                        // 叔叔为黑色或不存在，且当前为右左结构：
                        // 先对父结点右旋，再对祖父结点左旋。
                        RotateR(parent);
                        RotateL(grandparent);

                        cur->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                    else
                    {
                        // 叔叔为黑色或不存在，且当前为右右结构：
                        // 对祖父结点左旋，并调整颜色。
                        RotateL(grandparent);

                        parent->_col = BLACK;
                        grandparent->_col = RED;
                        break;
                    }
                }
            }

            // 修复过程中根结点可能发生变化或被染红，最后统一设为黑色。
            _root->_col = BLACK;

            return true;
        }
    }


    Node* Find(const K& key)
    {
        Node* cur = _root;
        while (cur)
        {
            if (cur->_data.first < key)
            {
                cur = cur->_right;
            }
            else if (cur->_data.first > key)
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
private:
    Node* _root = nullptr;
};