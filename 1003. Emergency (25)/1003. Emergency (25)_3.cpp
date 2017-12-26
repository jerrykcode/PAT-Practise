// 1003. Emergency (25)_3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define INFINITY 99999999
#define ERROR -1

int findMin(int *dist, int *collected, int N)
{
	int minV = 0, min = INFINITY;
	for (int i = 0; i < N; i++)
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	if (min == INFINITY)
		return ERROR;
	return minV;
}

void dijkstra(int s, int des, int *nTeams, int **graph, int N)
{
	int *dist = new int[N]; //dist[i] = the current shortest distance between S and i
	int *num = new int[N]; //num[i] = the current number of shortest paths between S and i
	int *weight = new int[N]; //weight[i] = the current total weight of all the vetexes on the path from S to i
	int *collected = new int[N]; //collected[i] = 1 if a vertex had been collected or 0 if not
	for (int i = 0; i < N; i++) {
		dist[i] = graph[s][i];
		if (graph[s][i] != INFINITY) { //an edge between s & i exists, that is, there is a road between the city s and i
			num[i] = 1;
			weight[i] = nTeams[s] + nTeams[i];
		}
		else
			num[i] = weight[i] = 0;
		collected[i] = 0;
	}
	//collects s
	dist[s] = 0;
	num[s] = 1;
	weight[s] = nTeams[s];
	collected[s] = 1;
	for (int i = 0; i < N; i++) {
		int min = findMin(dist, collected, N);
		if (min == ERROR)
			break;
		if (min == des) {
			cout << num[des] << " " << weight[des] << "\n";
			return;
		}
		collected[min] = 1;
		for (int v = 0; v < N; v++)
			if (graph[min][v] < INFINITY && !collected[v]) {
				if (dist[min] + graph[min][v] < dist[v]) {
					dist[v] = dist[min] + graph[min][v];
					num[v] = num[min];
					weight[v] = weight[min] + nTeams[v];
				}
				else if (dist[min] + graph[min][v] == dist[v]) {
					num[v] += num[min];
					if (weight[min] + nTeams[v] > weight[v])
						weight[v] = weight[min] + nTeams[v];
				}
			}
	}
	cout << num[des] << " " << weight[des] << "\n";
}

int main()
{
	int N, M, S, Des;
	cin >> N >> M >> S >> Des;
	int * nTeams = new int[N];
	for (int i = 0; i < N; i++)
		cin >> nTeams[i];
	int **graph = new int*[N];
	for (int i = 0; i < N; i++) {
		graph[i] = new int[N];
		for (int j = 0; j < N; j++)
			graph[i][j] = INFINITY;
	}
	for (int i = 0; i < M; i++) {
		int c1, c2, l;
		cin >> c1 >> c2 >> l;
		graph[c1][c2] = graph[c2][c1] = l;
	}
	dijkstra(S, Des, nTeams, graph, N);
	return 0;
}
