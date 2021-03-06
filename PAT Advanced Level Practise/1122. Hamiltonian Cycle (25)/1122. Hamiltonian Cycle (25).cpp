// 1122. Hamiltonian Cycle (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int N, M, k;
	cin >> N >> M;
	int **graph = new int*[N];
	for (int i = 0; i < N; i++)
		graph[i] = new int[N];
	for (int i = 0; i < M; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--;
		v2--;
		graph[v1][v2] = graph[v2][v1] = 1;
	}
	cin >> k;
	int *collected = new int[N];
	for (int i = 0; i < k; i++) {
		fill(collected, collected + N, 0);
		int n, v, w;
		cin >> n >> v;
		v--;
		int start = v;
		collected[v] = 1;
		int sum = 1, flag = 0;
		for (int j = 1; j < n; j++) {
			cin >> w;
			w--;
			if (flag) continue;
			if (j == n - 1 && w != start) {
				flag = 1;
				continue;
			}
			if (graph[v][w] != 1) {
				flag = 1;
				continue;
			}
			if (!collected[w]) {
				collected[w] = 1;
				sum ++;
			}
			else if (j != n - 1) flag = 1;
			v = w;
		}
		if (flag) printf("NO\n");
		else if (sum != N) printf("NO\n");
		else printf("YES\n");
	}
    return 0;
}

