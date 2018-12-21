#include <iostream>
#include <stack>
using namespace std;

#define INF 249501

int findMin(int *dist, bool *collected, int n) {
	int minV = -1, min = INF;
	for (int i = 0; i < n; i++) 
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	return minV;
}

void printPath(int *path, int src, int des) {
	stack<int> s;
	int v = des;
	while (v != src) {
		s.push(v);
		v = path[v];
	}
	printf("%d", src);
	while (!s.empty()) {
		printf(" %d", s.top());
		s.pop();
	}
}

void dijkstra(int **graph, int *weight, int n, int src, int des) {
	int *dist = new int[n]; 
	int *nTeams = new int[n];
	int *path = new int[n];
	int *nPaths = new int[n];
	bool *collected = new bool[n];
	for (int i = 0; i < n; i++) {
		dist[i] = graph[src][i];
		nTeams[i] = dist[i] < INF ? weight[src] + weight[i] : 0;
		path[i] = dist[i] < INF ? src : -1;
		nPaths[i] = dist[i] < INF ? 1 : 0;
		collected[i] = false;
	}
	dist[src] = 0;
	nTeams[src] = weight[src];
	path[src] = src;
	nPaths[src] = 1;
	collected[src] = true;
	while (true) {
		int minV = findMin(dist, collected, n);
		if (minV == -1) break;
		if (minV == des) break;
		collected[minV] = true;	
		for (int v = 0; v < n; v++)
			if (!collected[v] && graph[minV][v] < INF) {
				if (dist[minV] + graph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + graph[minV][v];
					nTeams[v] = nTeams[minV] + weight[v];
					path[v] = minV;
					nPaths[v] = nPaths[minV];
				}
				else if (dist[minV] + graph[minV][v] == dist[v]) {
					nPaths[v] += nPaths[minV];
					if (nTeams[minV] + weight[v] > nTeams[v]) {
						nTeams[v] = nTeams[minV] + weight[v];
						path[v] = minV;
					}
				}
			}
	}
	printf("%d %d\n", nPaths[des], nTeams[des]);
	printPath(path, src, des);
	free(dist);
	free(nTeams);
	free(path);
	free(nPaths);
	free(collected);
}

int main() {
	int n, m, s, d;
	scanf("%d %d %d %d", &n,&m, &s, &d);
	int **graph = new int*[n];
	int *weight = new int[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
		fill(graph[i], graph[i] + n, INF);
	}
	for (int i = 0; i < n; i++)
		scanf("%d", weight + i);
	int c1, c2, len;
	for (int i = 0; i < m; i++) {		
		scanf("%d %d %d", &c1, &c2, &len);		
		graph[c1][c2] = graph[c2][c1] = len;
	}		
	dijkstra(graph, weight, n, s, d);
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	free(weight);	
	return 0;
}
