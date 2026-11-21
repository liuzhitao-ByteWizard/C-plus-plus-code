#pragma once
#include "HashTable.h"

namespace byte {

	template<class K , class hash = HashFunc<K>>
	class myunordered_set {
		struct setKeyOfT {
			const K& operator()(const K& k) const {
				return k;
			}
		};
	public:
		typedef typename link_address::HashTable<K, const K, setKeyOfT, hash>::iterator iterator;
		typedef typename link_address::HashTable<K, const K, setKeyOfT, hash>::const_iterator const_iterator;
		std::pair<iterator, bool> insert(const K& k) {
			return _ht.Insert(k);
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


	private:
		link_address::HashTable<K, const K , setKeyOfT, hash> _ht;
	};
}
