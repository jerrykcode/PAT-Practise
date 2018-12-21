# L2-001 紧急救援 （25 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805073643683840)

> 作者: 陈越
> 单位: 浙江大学
> 时间限制: 200 ms
> 内存限制: 64 MB
> 代码长度限制: 16 KB

作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。在地图上显示有多个分散的城市和一些连接城市的快速道路。每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。当其他城市有紧急求助电话给你的时候，你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。

## 输入格式:

输入第一行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0 ~ (N?1)；M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号。

第二行给出N个正整数，其中第i个数是第i个城市的救援队的数目，数字间以空格分隔。随后的M行中，每行给出一条快速道路的信息，分别是：城市1、城市2、快速道路的长度，中间用空格分开，数字均为整数且不超过500。输入保证救援可行且最优解唯一。

## 输出格式:

第一行输出最短路径的条数和能够召集的最多的救援队数量。第二行输出从S到D的路径中经过的城市编号。数字间以空格分隔，输出结尾不能有多余空格。

## 输入样例:
4 5 0 3  
20 30 40 10  
0 1 1  
1 3 2  
0 3 3  
0 2 2  
2 3 2  


## 输出样例:
2 60  
0 1 3  

## 思路

dijkstra求最短路径，对每一个顶点，记录当前最短路径及距离，当前到达该顶点的路径上的救援队数量，当前到达该顶点的最短路径数量，及该顶点是否被收录过。

## 代码

[L2-001 紧急救援 （25 分）.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-001%20%E7%B4%A7%E6%80%A5%E6%95%91%E6%8F%B4%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-001%20%E7%B4%A7%E6%80%A5%E6%95%91%E6%8F%B4%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
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
```
