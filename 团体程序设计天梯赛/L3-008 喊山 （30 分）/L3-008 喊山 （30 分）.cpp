#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> *Graph;

int bfs(Graph graph, int src, int n) {
	queue<int>q;
	int last = src, tail = src;
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	q.push(src);
	collected[src] = true;
	int minV = -1;
	bool newLevel = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int w : graph[v]) {
			if (!collected[w]) {
				collected[w] = true;
				q.push(w);
				if (newLevel || w < minV) {
					if (newLevel) newLevel = false;
					minV = w;
				}
				last = w;
			}
		}
		if (v == tail) {
			tail = last;
			newLevel = true;
		}
	}
	free(collected);
	return minV;
}

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	Graph graph = new vector<int>[n];
	for (int i = 0; i < m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--; v2--;
		graph[v1].push_back(v2);
		graph[v2].push_back(v1);
	}
	for (int i = 0; i < k; i++) {
		int v;
		cin >> v;
		int minV = bfs(graph, v - 1, n);
		cout << (minV + 1) << endl;
	}
	return 0;
}