#pragma once 
#include <vector>
#include <string>

template<class K>
struct HashFunc {
    size_t operator()(const K& k) {
        return (size_t)k;
    }
};
//string不能进行强制类型转换：模板特化
template <>
struct HashFunc<std::string> {
    size_t operator()(const std::string& str) {
        size_t hash = 0;
        for (auto& e : str) {
            hash += e;
            hash *= 131;
        }
        return hash;
    }
};

namespace link_address {

    inline static size_t __stl_next_prime(size_t n)
    {
        // Note: assumes long is at least 32 bits.
        static const int __stl_num_primes = 28;
        static const size_t __stl_prime_list[__stl_num_primes] =
        { 53, 97, 193, 389, 769,
            1543, 3079, 6151, 12289, 24593,
            49157, 98317, 196613, 393241, 786433,
            1572869, 3145739, 6291469, 12582917, 25165843,
            50331653, 100663319, 201326611, 402653189, 805306457,
            1610612741, 3221225473, 4294967291
        };

        const size_t* first = __stl_prime_list;
        const size_t* last = __stl_prime_list + __stl_num_primes;
        const size_t* pos = std::lower_bound(first, last, n);

        return pos == last ? *(last - 1) : *pos;
    }

    template<class T>
    struct HashNode
    {
        T _data;         // 存储键值对 <key, value>
        HashNode<T>* _next;  // 指向同一桶中下一个冲突节点的指针
        // 构造函数：初始化键值对，后继指针置空
        HashNode(const T& data)
            :_data(data)
            , _next(nullptr)
        {
        }
    };

    //前置声明
    template<class K, class T, class KeyOfT, class hash>
    class HashTable;

    template<class K, class T, class Ref , class Ptr , class KeyOfT, class hash>
    struct HTIterator {
        typedef HashNode<T> Node;
        typedef HashTable<K, T, KeyOfT, hash> HT;
        typedef HTIterator<K, T, Ref, Ptr, KeyOfT, hash> Self; 
        //封装节点的指针
        Node* _node;
        //需要传递的是哈希表的指针（减少拷贝）
        const HT* _pht; //不变

        HTIterator(Node* node, const HT* pht)
            :_node(node)
            , _pht(pht) {
        }

        Self& operator++() {
            if (_node->_next) {
                //1.如果当前桶没有走完，继续走
                _node = _node->_next;
            }
            else {
                hash hs;
                KeyOfT kot;
                //计算出当前桶所对应的下标
                size_t hashi = hs(kot(_node->_data)) % _pht->_tables.size();
                ++hashi; //往后走
                while (hashi < _pht->_tables.size()) {
                    if (_pht->_tables[hashi])
                        break;
                    else
                        ++hashi;
                }
                if (hashi == _pht->_tables.size())
                    _node = nullptr;
                else
                    _node = _pht->_tables[hashi];
            }
            return *this;
        }

        bool operator==(const Self& s) const {
            return this->_node == s._node;
        }

        bool operator!=(const Self& s) const {
            return this->_node != s._node;
        }

        Ref operator*() const {
            return this->_node->_data;
        }

        Ptr operator->() const {
            return &this->_node->_data;
        }
    };
    template<class K, class T, class KeyOfT , class hash>
    class HashTable
    {
        template<class K, class T, class Ref, class Ptr, class KeyOfT, class hash>
        friend struct HTIterator;
    public:
        typedef HashNode<T> Node;
        typedef HTIterator<K, T, T&, T*, KeyOfT, hash> iterator;
        typedef HTIterator<K, T, const T& , const T* ,KeyOfT, hash> const_iterator;

        iterator begin() {
            for (size_t i = 0; i < _tables.size(); i++) {
                if (_tables[i]) {
                    //this代表的是指向对应类对象(哈希表的地址)
                    return iterator(_tables[i], this);
                }
            }
            return iterator(nullptr, this);
        }
        iterator end() {
            return iterator(nullptr, this);
        }

        const_iterator begin() const {
            for (size_t i = 0; i < _tables.size(); i++) {
                if (_tables[i]) {
                    //this代表的是指向对应类对象(哈希表的地址)
                    return const_iterator(_tables[i], this);
                }
            }
            return const_iterator(nullptr, this);
        }
        const_iterator end() const  {
            return const_iterator(nullptr, this);
        }
        
        ~HashTable() {
            for (size_t i = 0; i < _tables.size(); i++) {
                Node* cur = _tables[i];
                while (cur) {
                    Node* next = cur->_next;
                    delete cur;
                    cur = next;
                }
                _tables[i] = nullptr;
            }
        }

        std::pair<iterator , bool> Insert(const T& data) {
            KeyOfT kot;
            hash hs;    
            if (Find(kot(data)) != end()) {
                return { Find(kot(data)) ,false };
            }
            if (_n == _tables.size()) {
                std::vector<Node*> newtable(__stl_next_prime(_tables.size() + 1));
                for (size_t i = 0; i < _tables.size(); i++) {
                    Node* cur = _tables[i];
                    while (cur) {
                        Node* next = cur->_next; // 保存原链表中的下一个节点，防止断链
                        size_t hashi = hs(kot(cur->_data)) % newtable.size();
                        cur->_next = newtable[hashi];
                        newtable[hashi] = cur;
                        cur = next;
                    }
                    _tables[i] = nullptr;
                }
                _tables.swap(newtable); 
            }
            size_t hashi = hs(kot(data)) % _tables.size();
            Node* newnode = new Node(data);
            newnode->_next = _tables[hashi]; 
            _tables[hashi] = newnode;        
            _n++;
            return { iterator(newnode , this) , true};
        }

        iterator Find(const K& key) {
            hash hs;
            KeyOfT kot;
            size_t hashi = hs(key) % _tables.size();
            Node* cur = _tables[hashi];
            while (cur) {
                if (kot(cur->_data) == key)
                    return iterator(cur , this);
                cur = cur->_next;
            }
            return iterator(nullptr , this);
        }

        bool Erase(const K& key) {
            hash hs;
            KeyOfT kot;
            size_t hashi = hs(key) % _tables.size();
            Node* cur = _tables[hashi];
            Node* prev = nullptr;
            while (cur) {
                //我们需要默认支持等于的比较
                if (kot(cur->_data) == key) {
                    if (prev) {
                        prev->_next = cur->_next;
                    }
                    else {
                        //头删
                        _tables[hashi] = cur->_next;
                    }
                    delete cur;
                    _n--;
                    return true;
                }
                prev = cur;
                cur = cur->_next;
            }
            return false;
        }

        HashTable(int n = 11)
            :_tables(n)
            , _n(0) {
        }

    private:
        //指针数组
        std::vector<Node*> _tables;
        size_t _n = 0;  // 表中存储数据个数
    };
}

