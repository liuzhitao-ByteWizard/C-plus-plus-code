#pragma once
#include "RBTree.h"
#define _CRT_SECURE_NO_WARNINGS

namespace byte {
	template <class K>
	class set {
		struct SetOfT {
			const K& operator()(const K& k) {
				return k;
			}
		};
	public:
		typedef typename RBTree<K, const K, SetOfT>::const_iterator const_iterator;
		typedef typename RBTree<K, const K, SetOfT>::iterator iterator;

		bool Insert(const K& k) {
			return _t.Insert(k);
		}

		iterator begin() {
			return _t.begin();
		}

		iterator end() {
			return _t.end();
		}

		const_iterator begin() const  {
			return _t.begin();
		}

		const_iterator end() const {
			return _t.end();
		}
	private:
		RBTree<K, const K , SetOfT> _t;
	};
}

