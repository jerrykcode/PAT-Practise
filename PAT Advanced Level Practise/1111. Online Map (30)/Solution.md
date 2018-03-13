# 1111. Online Map (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1111)

* 时间限制 300 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Input our current position and a destination, an online map can recommend several paths. Now your job is to recommend two paths to your user: one is the shortest, and the other is the fastest. It is guaranteed that a path exists for any request. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives two positive integers N (2 <= N <= 500), and M, being the total number of streets intersections on a map, and the number of streets, respectively. Then M lines follow, each describes a street in the format:

*V1 V2 one-way length time*

where V1 and V2 are the indices (from 0 to N-1) of the two ends of the street; one-way is 1 if the street is one-way from V1 to V2, or 0 if not; length is the length of the street; and time is the time taken to pass the street. 

Finally a pair of source and destination is given.

## Output Specification: 

For each case, first print the shortest path from the source to the destination with distance D in the format: 

*Distance = D: source -> v1 -> ... -> destination* 

Then in the next line print the fastest path with total time T: 

*Time = T: source -> w1 -> ... -> destination* 

In case the shortest path is not unique, output the fastest one among the shortest paths, which is guaranteed to be unique. In case the fastest path is not unique, output the one that passes through the fewest intersections, which is guaranteed to be unique. 

In case the shortest and the fastest paths are identical, print them in one line in the format: 

*Distance = D; Time = T: source -> u1 -> ... -> destination*

## Sample Input 1:  
10 15  
0 1 0 1 1  
8 0 0 1 1  
4 8 1 1 1  
3 4 0 3 2  
3 9 1 4 1  
0 6 0 1 1  
7 5 1 2 1  
8 5 1 2 1  
2 3 0 2 2  
2 1 1 1 1  
1 3 0 3 1  
1 4 0 1 1  
9 7 1 3 1  
5 1 0 5 2  
6 5 1 1 2  
3 5  

## Sample Output 1:  
Distance = 6: 3 -> 4 -> 8 -> 5  
Time = 3: 3 -> 1 -> 5  

## Sample Input 2:  
7 9  
0 4 1 1 1  
1 6 1 1 3    
2 6 1 1 1  
2 5 1 2 2  
3 0 0 1 1  
3 1 1 1 3  
3 2 1 1 2  
4 5 0 2 2  
6 5 1 1 2  
3 5  

## Sample Output 2:  
Distance = 3; Time = 4: 3 -> 2 -> 5  


## 题意：

N个顶点，M条边，输入每条边的起点、终点，是否为有向边，边的长度，以及通过这条边需要的时间。给出一个源与终点，求从源到终点距离最短的路径，若有多条最短路径，则输出所需时间最少的路径。然后求从源到终点所需时间最少的路径，若有多条则输出经过的顶点数最少的路径。

## 思路：

用两次dijkstra，分别求距离最短与时间最短的路径。求距离最短时，同时要记录从源到每个顶点的时间，在更新时若经过一个dist最小的顶点，距离变小要更新，距离相同但时间减少也要更新。同理求最短时间时，也要记录从源到每个顶点经过的顶点数量。具体算法见以下代码。

## 代码：

[1111. Online Map (30).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1111.%20Online%20Map%20(30)/1111.%20Online%20Map%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

#define INF 100000

int **D, **T;
int minDist, minTime;

int findMin(int *dist, int *collected, int n)
{
	int minV = -1, min = INF;
	for (int i = 0; i < n; i ++)
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	return minV;
}

vector<int> getPath(int *path, int s, int des)
{
	vector<int> p;
	if (path[des] == s)
		p.push_back(s);
	else p = getPath(path, s, path[des]);
	p.push_back(des);
	return p;
}

vector<int> dijkstraDist(int n, int s, int des)
{
	int *collected = new int[n];
	int *dist = new int[n];
	int *time = new int[n];
	int *path = new int[n];
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		dist[i] = D[s][i];
		path[i] = dist[i] < INF ? s : -1;
		time[i] = T[s][i];
	}
	collected[s] = 1;
	dist[s] = time[s] = 0;
	path[s] = s;
	while (1) {
		int min = findMin(dist, collected, n);
		if (min == -1) break;
		if (min == des) break;
		collected[min] = 1;
		for (int v = 0; v < n; v++) 
			if (!collected[v] && D[min][v] < INF) {
				if (dist[min] + D[min][v] < dist[v]) {
					dist[v] = dist[min] + D[min][v];
					time[v] = time[min] + T[min][v];
					path[v] = min;
				}
				else if (dist[min] + D[min][v] == dist[v] && time[min] + T[min][v] < time[v]) {
					time[v] = time[min] + T[min][v];
					path[v] = min;
				}
			}
	}
	minDist = dist[des];
	return getPath(path, s, des);
}

vector<int> dijkstraTime(int n, int s, int des)
{
	int *collected = new int[n];
	int *time = new int[n];
	int *num = new int[n];
	int *path = new int[n];
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		time[i] = T[s][i];
		path[i] = time[i] < INF ? s : -1;
		num[i] = time[i] < INF ? 2 : 1;
	}
	collected[s] = 1;
	time[s] = 0;
	path[s] = s;
	while (1) {
		int min = findMin(time, collected, n);
		if (min == -1) break;
		if (min == des) break;
		collected[min] = 1;
		for (int v = 0; v < n; v ++)
			if (!collected[v] && T[min][v] < INF) {
				if (time[min] + T[min][v] < time[v]) {
					time[v] = time[min] + T[min][v];
					num[v] = num[min] + 1;
					path[v] = min;
				}
				else if (time[min] + T[min][v] == time[v] && num[min] + 1 < num[v]) {
					num[v] = num[min] + 1;
					path[v] = min;
				}
			}
	}
	minTime = time[des];
	return getPath(path, s, des);
}

void printVector(vector<int> v)
{
	for (auto it = v.begin(); it != v.end(); it++) {
		if (it != v.begin()) printf(" -> ");
		cout << *it;
	}
}

int main()
{
	int n, m;
	cin >> n >> m;
	D = new int*[n];
	T = new int*[n];
	for (int i = 0; i < n; i++) {
		D[i] = new int[n];
		T[i] = new int[n];
		for (int j = 0; j < n; j++)
			D[i][j] = T[i][j] = INF;
	}
	for (int i = 0; i < m; i++) {
		int v1, v2, flag, len, time;
		cin >> v1 >> v2 >> flag >> len >> time;
		D[v1][v2] = len;
		T[v1][v2] = time;
		if (!flag) {
			D[v2][v1] = len;
			T[v2][v1] = time;
		}
	}
	int s, des;
	cin >> s >> des;
	vector<int> shortest = dijkstraDist(n, s, des);
	vector<int>  fastest = dijkstraTime(n, s, des);
	int flag = 0;
	if (shortest.size() != fastest.size())
		flag = 1;
	else
		for (int i = 0; i < shortest.size(); i++)
			if (shortest[i] != fastest[i]) {
				flag = 1;
				break;
			}
	if (flag) {
		printf("Distance = %d: ", minDist);
		printVector(shortest);
		printf("\nTime = %d: ", minTime);
		printVector(fastest);
	}
	else {
		printf("Distance = %d; Time = %d: ", minDist, minTime);
		printVector(shortest);
	}
	return 0;
}
```
