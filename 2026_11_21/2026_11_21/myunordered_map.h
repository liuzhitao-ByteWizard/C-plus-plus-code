#pragma once
#include "HashTable.h"

namespace byte {
	template <class K, class V , class hash = HashFunc<K>>
	class myunordered_map {
		struct mapKeyOfT {
			const K& operator()(const std::pair<const K,V>& kv) const {
				return kv.first;
			}
		};
	public:
		typedef typename link_address::HashTable<K, std::pair<const K, V>, mapKeyOfT, hash>::iterator iterator;
		typedef typename link_address::HashTable<K, std::pair<const K,V>, mapKeyOfT, hash>::const_iterator const_iterator;
		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)  {
			return _ht.Insert(kv);
		}

		bool Erase(const K& k) {
			return _ht.Erase(k);
		}

		iterator begin() {
			return _ht.begin();
		}

		iterator end() {
			return _ht.end();
		}

		const_iterator begin() const {
			return _ht.begin();
		}

		const_iterator end() const {
			return _ht.end();
		}

		iterator find(const K& k) {
			return _ht.Find(k);
		}

		bool erase(const K& k) {
			return _ht.Erase(k);
		}

		V& operator[](const K& key) {
			//key在的话，就相当于查找
			//key不在的话，相当于进行插入
			auto it = _ht.Insert({ key , V() });
			//it.first -> iterator it
			//it->second == it->()->second
			//调用operator->()
			return it.first->second;
		}

	private:
		link_address::HashTable<K, std::pair<const K,V> , mapKeyOfT , hash> _ht;
	};
}
