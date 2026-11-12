#include <iostream>
#include <vector>

using namespace std;

//int main() {
//	vector<int> v;
//	int n, m;
//	cin >> n >> m;
//	int x;
//	for (int i = 0; i < n; i++) {
//		cin >> x;
//		v.push_back(x);
//	}
//	int h;
//	while (m--) {
//		cin >> h;
//		cout << v[h - 1] << endl;
//	}
//	cout << endl;
//}

const int N = 1e5 + 10;
int main() {
	vector<vector<int>> v;

	v.resize(N);
	int n, q; cin >> n >> q;
	//q次操作
	while (q--) {
		int m; cin >> m;
		int i, j; cin >> i >> j;
		if (m == 1) {
			int k; cin >> k;
			if (v[i].size() < j) {
				v[i].resize(j + 1);
			}
			v[i][j] = k;
		}
		else {

			//查询操作
			cout << v[i][j] << endl;
		}
	}
	return 0;
}