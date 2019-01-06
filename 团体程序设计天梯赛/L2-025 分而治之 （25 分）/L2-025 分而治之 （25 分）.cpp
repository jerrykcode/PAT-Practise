#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> *graph = new vector<int>[n];
	for (int i = 0; i < m; i++) {
		int city1, city2;
		scanf("%d %d", &city1, &city2);
		city1--;
		city2--;
		graph[city1].push_back(city2);
		graph[city2].push_back(city1);
	}
	int k, nv, destroyedCity;
	scanf("%d", &k);
	bool *hasDestroyed = new bool[n];
	for (int i = 0; i < k; i++) {
		fill(hasDestroyed, hasDestroyed + n, false);
		scanf("%d", &nv);
		for (int j = 0; j < nv; j++) {
			scanf("%d", &destroyedCity);
			destroyedCity--;
			hasDestroyed[destroyedCity] = true;
		}
		bool flag = true;	
		for (int city = 0; city < n; city++) {
			if (hasDestroyed[city]) continue;
			if (graph[city].empty()) continue;
			for (int neighborCity : graph[city])
				if (!hasDestroyed[neighborCity]) {
					flag = false;
					break;
				}
			if (flag == false) break;
		}
		cout << (flag ? "YES" : "NO") << endl;
	}
	free(hasDestroyed);
	for (int i = 0; i < n; i++) {
		graph[i].clear();
		vector<int>().swap(graph[i]);
	}
	//free(graph); //patÃ·Ωªruntime error 
	return 0;
}
