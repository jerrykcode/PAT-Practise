# 1003. Emergency (25)



* 时间限制 400 ms



* 内存限制      65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



As an emergency rescue team leader of a city, you are given a special map of your country. 
The map shows several scattered cities connected by some roads. Amount of rescue teams in 
each city and the length of each road between any pair of cities are marked on the map. 
When there is an emergency call to you from some other city, your job is to lead your men 
to the place as quickly as possible, and at the mean time, call up as many hands on the 
way as possible.



## Input

Each input file contains one test case. For each test case, the first line contains 4 
positive integers: N (<= 500) - the number of cities (and the cities are numbered from 0 to N-1),
M - the number of roads, C1 and C2 - the cities that you are currently in and that you must save, 
respectively. The next line contains N integers, where the i-th integer is the number of rescue 
teams in the i-th city. Then M lines follow, each describes a road with three integers c1, c2 and L, 
which are the pair of cities connected by a road and the length of that road, respectively. 
It is guaranteed that there exists at least one path from C1 to C2. 




## Output

For each test case, print in one line two numbers: the number of different shortest paths between C1 and C2,
and the maximum amount of rescue teams you can possibly gather.
All the numbers in a line must be separated by exactly one space, and there is no extra space 
allowed at the end of a line.

 
 
 
## Sample Input
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1

## Sample Output
2 4




## 题意：
N个城市M条路，已知每个城市的救援小组的数量，每条路的起点城市与终点城市及该路的长度，
问两个城市之间所有最短路径（长度小即为短）的数量，
以及最短路径上能够集合到的最多小组数量（即所有最短路径中点权之和最大的）


## 思路：
本题思路参考了 [柳婼 の blog 1003. Emergency (25)-PAT甲级真题（Dijkstra算法）](https://www.liuchuo.net/archives/2359)

用dijkstra，
设源为s，目的地为des
数组int dist[] 为每个顶点（城市）与源s的当前最短距离，
int num[] 为每个顶点与源s的当前最短路径数量，
int weight[] 为每个顶点与源s的最短路径中能得到的最大的小组数量

从未收录的顶点中找dist值最小的顶点收录（设为min），遍历每个与min相邻且未收录的顶点v，
若dist[min] + graph[min][v] < dist[v]，此时不仅要更新dist[v]为dist[min] + graph[min][v]，还要
更新num[v]为num[min]，weight[v]为weight[min] + v的点权（即城市v的小组数量），

若dist[min] + graph[min][v] == dist[v]，此时dist[v]不用改变，但num[v] += num[min]，
如果weight[min] + v的点权 > weight[v]，则更新weight[v]为weight[min] + v的点权

再次从未收录的顶点中找dist值最小的顶点收录，
直到所有连通的顶点均收录，或收录目的地des，
此时跳出循环输出num[des]与weight[des]
 
 
 ## 参考：
 
 [柳婼 の blog 1003. Emergency (25)-PAT甲级真题（Dijkstra算法）](https://www.liuchuo.net/archives/2359)



## 代码：

 [1003. Emergency (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1003.%20Emergency%20(25)/1003.%20Emergency%20(25)_3.cpp)

```cpp
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
```
