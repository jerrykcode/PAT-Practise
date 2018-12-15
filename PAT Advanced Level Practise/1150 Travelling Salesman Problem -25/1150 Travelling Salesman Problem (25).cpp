#include <stdio.h>
#include <iostream>
#define INF 101

int **graph;

int pathDist(int *path, int nCities, int n) {
	int dist = 0;
	bool *visited = new bool[n];
	for (int i = 0; i < n; i++) visited[i] = false;
	bool simple = true, ts = true;
	for (int i = 0; i < nCities - 1; i++) {
		if (graph[path[i]][path[i + 1]] == INF) {
			printf("NA");
			printf(" (Not a TS cycle)\n");
			free(visited);
			return -1;
		}
		dist += graph[path[i]][path[i + 1]];
		if (visited[path[i]]) {
			simple = false;
		}
		visited[path[i]] = true;
	}
	printf("%d", dist);
	for (int i = 0; i < n; i++)
		if (!visited[i])
			ts = false;
	if (path[0] != path[nCities - 1]) ts = false;
	if (ts) {
		if (simple) printf(" (TS simple cycle)\n");
		else printf(" (TS cycle)\n");
	} else printf(" (Not a TS cycle)\n");
	free(visited);
	return ts ? dist : -1;
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	graph = new int*[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
		for (int j = 0; j < n; j++)
			graph[i][j] = INF;
	}
	int c1, c2, dist;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &c1, &c2, &dist);
		c1--; c2--;
		graph[c1][c2] = graph[c2][c1] = dist;
	}
	int k;
	scanf("%d", &k);
	int *path, nCities, minDist = -1, minIndex = 0;
	for (int i = 0; i < k; i++) {
		scanf("%d", &nCities);
		path = new int[nCities];
		for (int j = 0; j < nCities; j++) {
			scanf("%d", path + j);
			path[j]--;
		}
		printf("Path %d: ", i + 1);
		int d = pathDist(path, nCities, n);
		if ((d != -1) && (minDist == -1 || d < minDist)) {
			minDist = d;
			minIndex = i + 1;
		}
		free(path);
	}
	printf("Shortest Dist(%d) = %d\n", minIndex, minDist);
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	return 0;
}
