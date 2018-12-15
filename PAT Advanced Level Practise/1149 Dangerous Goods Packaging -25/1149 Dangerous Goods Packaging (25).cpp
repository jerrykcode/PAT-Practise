#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[100000];

bool incompatible(int a, int b) {
	for (int g : graph[a])
		if (g == b) return true;
	return false;
}

bool isOk(int *list, int k) {
	for (int i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) 
			if (incompatible(list[i], list[j])) {
				return false;
			}
	}
	return true;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int g0, g1;
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &g0, &g1);
		graph[g0].push_back(g1);
		graph[g1].push_back(g0);
	}
	int *list, k;
	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		list = new int[k];
		for (int j = 0; j < k; j++) {
			scanf("%d", list + j);
		}
		printf(isOk(list, k) ? "Yes\n" : "No\n");
		free(list);
	}
	return 0;
}
