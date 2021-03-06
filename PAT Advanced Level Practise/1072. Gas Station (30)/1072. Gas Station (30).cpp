// 1072. Gas Station (30).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#define INF 100000

int get_id(string s, int n)
{	/* 返回城市在图中的编号 */
	if (s[0] == 'G') {
		s.erase(s.begin());
		return atoi(s.c_str()) + n - 1;
	}
	return atoi(s.c_str()) - 1;
}

int findMin(int *dist, int *collected, int n)
{	/* 返回未受录的顶点中dist值最小的 */
	int min = INF, minV = -1;
	for (int v = 0; v < n; v++) 
		if (!collected[v] && dist[v] < min) {
			min = dist[v];
			minV = v;
		}
	return minV;
}

int * dijkstra(int **graph, int s, int n)
{	/* 最短路径 */
	int *collected = new int[n]; /* 是否被收录过 */
	int *dist = new int[n]; /* 当前最短距离 */
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		dist[i] = graph[s][i];
	}
	collected[s] = 1;
	dist[s] = 0;
	while (1) {
		int min = findMin(dist, collected, n);
		if (min == -1) break;
		collected[min] = 1;
		for (int v = 0; v < n; v ++) /* 遍历每个顶点 */
			if (!collected[v] && graph[min][v] < INF) /* 未收录&&与min相邻 */
				if (dist[min] + graph[min][v] < dist[v]) /* 若通过min使路径更短 */
					dist[v] = dist[min] + graph[min][v]; /* 更新 */
	}
	return dist;
}

int main()
{
	int n, m, k, d;
	cin >> n >> m >> k >> d;
	int nVertexes = n + m; //图的顶点数
	int **graph = new int *[nVertexes];
	for (int i = 0; i < nVertexes; i++) {
		graph[i] = new int[nVertexes];
		for (int j = 0; j < nVertexes; j++)
			graph[i][j] = INF;
	}
	for (int i = 0; i < k; i++) {
		string v, w;
		int len, v_id, w_id;
		cin >> v >> w >> len;
		v_id = get_id(v, n);
		w_id = get_id(w, n);
		graph[v_id][w_id] = graph[w_id][v_id] = len;
	}
	int max_min = 0; //max_min是最远的最短距离
	int min_sum = INF;
	int best = -1;
	for (int i = 0; i < m; i++) { /* G1 ~ Gm (n ~ n + m - 1) */
		int *dist = dijkstra(graph, n + i, nVertexes);
		int minDist = INF, sum = 0, flag = 0;
		for (int v = 0; v < n; v++) { //0 ~ n-1
			if (dist[v] > d) { flag = 1;  break; }
			if (dist[v] < minDist) minDist = dist[v];
			sum += dist[v];
		}
		if (flag == 1) continue;
		if (minDist > max_min) { //minDist更大
			max_min = minDist;
			min_sum = sum;
			best = i;
		}
		else if (minDist == max_min && sum < min_sum) { //minDist相同但sum更小，故平均值更小
			min_sum = sum;
			best = i;
		}
	}
	if (best == -1) {
		cout << "No Solution" << endl;
		return 0;
	}
	printf("G%d\n%.1f %.1f\n", best + 1, max_min*1.0, (min_sum*1.0)/n);
    return 0;
}

