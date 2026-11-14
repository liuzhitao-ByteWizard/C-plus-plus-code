#pragma once 
#include <iostream>
#include <vector>

using namespace std;


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
    pair<K, V> _kv;
    State _state = EMPTY;
};

template<class K, class V>
class HashTable
{
    bool Insert(const pair<K, V>& kv) {
        if (Find(kv.first)) {
            return false;
        }

        // 负载因子最大0.7
        if ((double)_n / _tables.size() >= 0.7) {
            // 扩容
        }

        size_t hash0 = kv.first % _tables.size();
        size_t hashi = hash0;
        size_t i = 1;
        while (_tables[hashi]._state == EXIST) {
            // 继续探测
            hashi = (hash0 + i) % _tables.size();
            ++i;
        }

        _tables[hashi]._kv = kv;
        _tables[hashi]._state = EXIST;
        _n++;

        return true;
    }

    HashData<K, V>* Find(const K& key) {
        size_t hash0 = kv.first % _tables.size();
        size_t hashi = hash0;
        size_t i = 1;
        while (_tables[hashi]._state != EMPTY) {
            if (_tables[hashi]._kv.first == key) {
                return &_tables[hashi];
            }

            // 继续探测
            hashi = (hash0 + i) % _tables.size();
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
    vector<HashData<K, V>> _tables;
    size_t _n = 0;  // 表中存储数据个数
};