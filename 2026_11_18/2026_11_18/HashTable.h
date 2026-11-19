#pragma once 

namespace open_address{
    //标记三种状态
    enum State
    {
        EXIST,
        EMPTY,
        DELETE
    };

    template<class K, class V>
    struct HashData
    {
        std::pair<K, V> _kv;
        State _state = EMPTY;
    };

    template<class K, class V>
    class HashTable
    {
    public:
        inline unsigned long __stl_next_prime(unsigned long n)
        {
            // Note: assumes long is at least 32 bits.
            static const int __stl_num_primes = 28;
            static const unsigned long __stl_prime_list[__stl_num_primes] =
            {
                53,         97,         193,       389,       769,
                1543,       3079,       6151,      12289,     24593,
                49157,      98317,      196613,    393241,    786433,
                1572869,    3145739,    6291469,   12582917,  25165843,
                50331653,   100663319,  201326611, 402653189, 805306457,
                1610612741, 3221225473, 4294967291
            };

            const unsigned long* first = __stl_prime_list;
            const unsigned long* last = __stl_prime_list + __stl_num_primes;
            const unsigned long* pos = std::lower_bound(first, last, n);
            return pos == last ? *(last - 1) : *pos;
        }

        HashTable() {

        }

        HashTable(int n)
            :_tables(n)
            , _n(0) {

        }

        bool Insert(const std::pair<K, V>& kv) {
            if (Find(kv.first)) {
                return false;
            }

            // 负载因子最大0.7
            if ((double)_n / _tables.size() >= 0.7) {
                // 扩容
                // 拷贝数据 + 重新映射
                HashTable<K, V> _newht(__stl_next_prime(_tables.size() + 1));
                //扩容之后的表的大小还要是质数

                //旧表插入新表
                for (int i = 0; i < _tables.size(); i++) {
                    if (_tables[i]._state == EXIST)
                        _newht.Insert(_tables[i]._kv);
                }
                //将旧空间与新空间进行交换
                _tables.swap(_newht._tables);
            }

            size_t hash0 = kv.first % _tables.size();
            size_t hashi = hash0;
            //kv.first -> key
            size_t hash2 = kv.first % (_tables.size() - 1) + 1;
            size_t i = 1;
            while (_tables[hashi]._state == EXIST) {
                //线性探测
                //hashi = (hash0 + i) % _tables.size();
                //双散列法
                hashi = (hash0 + i * hash2) % _tables.size();
                ++i;
            }

            _tables[hashi]._kv = kv;
            _tables[hashi]._state = EXIST;
            _n++;

            return true;
        }

        HashData<K, V>* Find(const K& key) {
            size_t hash0 = key % _tables.size();
            size_t hashi = hash0;
            size_t hash2 = key % (_tables.size() - 1) + 1;
            size_t i = 1;
            while (_tables[hashi]._state != EMPTY) {
                if (_tables[hashi]._kv.first == key) {
                    return &_tables[hashi];
                }

                //// 继续探测
                //hashi = (hash0 + i) % _tables.size();
                //双散列法
                hashi = (hash0 + i * hash2) % _tables.size();
                ++i;
            }

            return nullptr;
        }

        bool Erase(const K& key) {
            auto* ret = Find(key);
            if (ret == nullptr) {
                return false;
            }
            else {
                ret->_state = DELETE;
                --_n;
                return true;
            }
        }


    private:
        std::vector<HashData<K, V>> _tables;
        size_t _n = 0;  // 表中存储数据个数
    };
}

namespace link_address {

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

    template<class K, class V>
    struct HashNode
    {
        std::pair<K, V> _kv;         // 存储键值对 <key, value>
        HashNode<K, V>* _next;  // 指向同一桶中下一个冲突节点的指针
        // 构造函数：初始化键值对，后继指针置空
        HashNode(const std::pair<K, V>& kv)
            :_kv(kv)
            , _next(nullptr)
        {
        }
    };

    template<class K, class V , class hash = HashFunc<K>>
    class HashTable
    {
    public:

        typedef HashNode<K, V> Node;

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


        bool Insert(const std::pair<K, V>& kv) {
            if (Find(kv.first)) {
                return false;
            }
            hash hs;
            //负载因子为1，扩容
            if (_n / _tables.size() == 1) {
                std::vector<Node*> newtable(_tables.size() * 2);
                //将旧表数据插入到新表中
                for (size_t i = 0; i < _tables.size(); i++) {
                    Node* cur = _tables[i];
                    while (cur) {
                        Node* next = cur->_next; //保存原链表中结点的下一个
                        size_t hashi = hs(cur->_kv.first) % newtable.size();
                        cur->_next = newtable[hashi];
                        newtable[hashi] = cur;
                        cur = next;
                    }
                    _tables[i] = nullptr;
                }
                _tables.swap(newtable);
            }

            size_t hashi = hs(kv.first) % _tables.size();
            Node* newnode = new Node(kv);
            newnode->_next = _tables[hashi];
            _tables[hashi] = newnode; //变为新的头节点
            _n++; //有效元素+1
            return true;
        }

        Node* Find(const K& key) {
            hash hs;
            size_t hashi = hs(key) % _tables.size();
            Node* cur = _tables[hashi];
            while (cur) {
                if (cur->_kv.first == key)
                    return cur;
                cur = cur->_next;
            }
            return nullptr;
        }

        bool Erase(const K& key) {
            hash hs;
            size_t hashi = hs(key) % _tables.size();
            Node* cur = _tables[hashi];
            Node* prev = nullptr;
            while (cur) {
                //我们需要默认支持等于的比较
                if (cur->_kv.first == key) {
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
        ,_n(0){
        }

    private:
        //指针数组
        std::vector<Node*> _tables;
        size_t _n = 0;  // 表中存储数据个数
    };
}

