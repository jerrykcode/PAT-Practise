## 1018. Public Bike Management (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1018)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over 
the world. One may rent a bike at any station and return it to any other stations in the city.

The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations. A station 
is said to be in perfect condition if it is exactly half-full. If a station is full or empty, PBMC will collect 
or send bikes to adjust the condition of that station to perfect. And more, all the stations on the way will be 
adjusted as well. 

When a problem station is reported, PBMC will always choose the shortest path to reach that station. If there are 
more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.
![Figure 1](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1018.jpg)
*Figure 1*

Figure 1 illustrates an example. The stations are represented by vertices and the roads correspond to the edges. 
The number on an edge is the time taken to reach one end station from another. The number written inside a vertex S 
is the current number of bikes stored at S. Given that the maximum capacity of each station is 10. To solve the 
problem at S3, we have 2 different shortest paths:

1. PBMC -> S1 -> S3. In this case, 4 bikes must be sent from PBMC, because we can collect 1 bike from S1 and then take 
   5 bikes to S3, so that both stations will be in perfect conditions.

2. PBMC -> S2 -> S3. This path requires the same time as path 1, but only 3 bikes sent from PBMC and hence is the one 
   that will be chosen.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 4 numbers: Cmax (<= 100), always an even 
number, is the maximum capacity of each station; N (<= 500), the total number of stations; Sp, the index of the problem 
station (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); and M, the number of roads. 
The second line contains N non-negative numbers Ci (i=1,...N) where each Ci is the current number of bikes at Si respectively. 
Then M lines follow, each contains 3 numbers: Si, Sj, and Tij which describe the time Tij taken to move betwen stations Si 
and Sj. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print your results in one line. First output the number of bikes that PBMC must send. Then after one 
space, output the path in the format: 0->S1->...->Sp. Finally after another space, output the number of bikes that we must 
take back to PBMC after the condition of Sp is adjusted to perfect.

Note that if such a path is not unique, output the one that requires minimum number of bikes that we must take back to PBMC. 
The judge's data guarantee that such a path is unique. 



## Sample Input:

10 3 3 5  
6 7 0  
0 1 1  
0 2 1  
0 3 3  
1 3 1  
2 3 1  

## Sample Output:

3 0->2->3 0  


## 题意：

N个车站，M条路。每个车站最多能容Cmax辆车，一个车站正好有Cmax/2辆则称为完美状态。当一个车站的车数为０或Cmax时，则
中心会派出车到达该出问题的车站，并将该车站和路上的车站均调整为完美状态。输入Cmax、N、Sp（问题车站的编号，车站编号
1~N，中心编号为0），以及M。之后输入每个车站的车数，以及M条路的起点编号、终点编号和通过这条路需要的时间。求从中心
到问题车站的时间最短的路径，若有多条，则输出从中心需要派出最少车的路径；若路径仍不唯一，则输出需要带回中心的车数
最少的路径

## 思路：

本题思路参考了 [柳婼 の blog 1018. Public Bike Management (30)-PAT甲级真题](https://www.liuchuo.net/archives/2373) 

dijkstra求最短路径时，从未收录的顶点中找到dist最小的顶点min，收录min后，遍历与min相邻且未收录的顶点时，对于通过min使
dist不变的顶点，将min记录到vector中。

dijkstra结束后DFS找出最优路径


## 参考：

[柳婼 の blog 1018. Public Bike Management (30)-PAT甲级真题](https://www.liuchuo.net/archives/2373)

## 代码：

[1018. Public Bike Management (30)_3.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1018.%20Public%20Bike%20Management%20(30)/1018.%20Public%20Bike%20Management%20(30)_3.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#define INF 50001

int minDist(int *dist, int *collected, int n)
{ /* 返回未收录顶点中dist值最小的 */
	int minV = -1, min = INF;
	for (int v = 0; v < n; v ++)
		if (!collected[v] && dist[v] < min) {
			min = dist[v];
			minV = v;
		}
	return minV;
}

int minRequire = INF, minBack = INF;
vector<int>best, tmp;
void dfs(int sp, vector<int>*path, int *weight)
{ /* DFS */
	tmp.push_back(sp);
	if (sp == 0) {
		int require = 0, back = 0;
		for (int i = tmp.size() - 2; i >= 0; i--) {
			int id = tmp[i];
			if (weight[id] < 0) //需要带回
				back -= weight[id];
			else {
				if (weight[id] - back < 0) back -= weight[id]; //需要带来的抵消不了需要带回的
				else { //需要带来的抵消掉了需要带回的
					require += weight[id] - back; //需要带来的
					back = 0; //不需要带回了
				}
			}
		}
		if (require < minRequire) {
			minRequire = require;
			minBack = back;
			best = tmp;
		}
		else if (require == minRequire && back < minBack) {
			minBack = back;
			best = tmp;
		}
		tmp.pop_back();
		return;
	}
	for (auto it = path[sp].begin(); it != path[sp].end(); it++)
		dfs(*it, path, weight);
	tmp.pop_back();
}

void printPath(vector<int>path, int sp)
{
	for (int i = path.size() - 1; i >= 0; i--) {
		if (i != path.size() - 1) cout << "->";
		printf("%d", path[i]);
	}
}

void dijkstra(int **graph, int *weight,int sp, int n)
{
	int s = 0;
	int *collected = new int[n];
	int *dist = new int[n];
	vector<int> *path = new vector<int>[n]; //记录多条最短路径
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		dist[i] = graph[s][i];
		if (dist[i] < INF) path[i].push_back(s);
	}
	collected[s] = 1;
	dist[s] = 0;
	path[s].push_back(s);
	while (1) {
		int min = minDist(dist, collected, n);
		if (min == -1) return;
		if (min == sp) break;
		collected[min] = 1;
		for (int v = 0; v < n; v ++) //遍历顶点
			if (!collected[v] && graph[min][v] < INF) { //若v未被收录 && min与v相邻
				if (dist[min] + graph[min][v] < dist[v]) { //若通过min能使源到v的距离减短
					dist[v] = dist[min] + graph[min][v];
					path[v].clear();
					path[v].push_back(min);
				}
				else if (dist[min] + graph[min][v] == dist[v]) //若通过min到v的距离相同
					path[v].push_back(min);
			}
	}
	dfs(sp, path, weight);
	cout << minRequire << " ";
	printPath(best, sp);
	cout << " " << minBack;
}

int main()
{
	int cmax, n, sp, m;
	cin >> cmax >> n >> sp >> m;
	int nVertexes = n + 1;
	int ** graph = new int *[nVertexes];
	for (int i = 0; i < nVertexes; i++) {
		graph[i] = new int[nVertexes];
		for (int j = 0; j < nVertexes; j++)
			graph[i][j] = INF;
	}
	int *nBikes = new int[nVertexes];
	for (int i = 1; i < nVertexes; i++) { cin >> nBikes[i]; nBikes[i] = cmax / 2 - nBikes[i]; }
	for (int i = 0; i < m; i++) {
		int s1,s2, time;
		cin >> s1 >> s2 >> time;
		graph[s1][s2] = graph[s2][s1] = time;
	}
	dijkstra(graph, nBikes, sp, nVertexes);
    return 0;
}
```
