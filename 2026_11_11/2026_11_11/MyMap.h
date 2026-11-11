#pragma once
#include "RBTree.h"
#define _CRT_SECURE_NO_WARNINGS

namespace byte {
	template<class K,class V>
	class map {
		struct MapOfT {
			const K& operator()(const std::pair<K, V>& kv) {
				return kv.first;
			}
		};
	public:
		//告诉编译器是内嵌类型
		typedef typename RBTree<K, std::pair<const K,V>, MapOfT>::iterator iterator;
		typedef typename RBTree<K, std::pair<const K, V>, MapOfT>::const_iterator const_iterator;

		bool Insert(const std::pair<K,V>& kv) {
			return _t.Insert(kv);
		}

		iterator begin() {
			return _t.begin();
		}

		iterator end() {
			return _t.end();
		}

		const_iterator begin() const {
			return _t.begin();
		}

		const_iterator end() const {
			return _t.end();
		}

	private:
		RBTree<K, std::pair<const K,V> , MapOfT> _t;
	};
}

