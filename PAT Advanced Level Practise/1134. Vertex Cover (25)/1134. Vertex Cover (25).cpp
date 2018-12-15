#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n, m, k;
	cin >> n >> m;
	vector<pair<int, int>> edges;
	for (int i = 0; i < m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		edges.push_back({v1, v2});
	}
	cin >> k;
	int *collected = new int[n];
	for (int i = 0; i < k; i++) {
		fill(collected, collected + n, 0);
		int nv, v, flag = 0;
		cin >> nv;
		for (int j = 0; j < nv; j++) {
			cin >> v;
			collected[v] = 1;
		}
		for (auto it = edges.begin(); it != edges.end(); it++) 
			if (!collected[it->first] && !collected[it->second]) {
				cout << "No" << endl;
				flag = 1;
				break;
			}
		if (flag == 0)
			cout << "Yes" << endl;
	}
	return 0;
}