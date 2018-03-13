# 1030. Travel Plan (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1030)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A traveler's map gives the distances between cities along the highways, together with the cost 
of each highway. Now you are supposed to write a program to help a traveler to decide the shortest 
path between his/her starting city and the destination. If such a shortest path is not unique, 
you are supposed to output the one with the minimum cost, which is guaranteed to be unique. 



## Input Specification: 

Each input file contains one test case. Each case starts with a line containing 4 positive integers 
N, M, S, and D, where N (<=500) is the number of cities (and hence the cities are numbered from 0 to 
N-1); M is the number of highways; S and D are the starting and the destination cities, respectively. 
Then M lines follow, each provides the information of a highway, in the format:

*City1 City2 Distance Cost*

where the numbers are all integers no more than 500, and are separated by a space. 




## Output Specification: 

For each test case, print in one line the cities along the shortest path from the starting point to 
the destination, followed by the total distance and the total cost of the path. The numbers must be 
separated by a space and there must be no extra space at the end of output. 



## Sample Input

4 5 0 3  
0 1 1 20  
1 3 2 30  
0 3 4 10  
0 2 2 20   
2 3 1 20  

## Sample Output

0 2 3 3 40  



## 题意：

N个城市，M条路，已知每条路连接的两个城市及路的长度和走这条路的费用，输入两个城市的下标(0~N - 1)，
求这两个城市之间的最短路径(长度最短，若有多条最短路径，则输出费用最小的一条)

## 思路：

用dijkstra求最短路径

两个二维数组分别存储任两个城市之间路的长度和费用，每次收录距离最小的顶点后，遍历每个与其相邻且未收录
过的顶点，若距离减小就更新，若距离不变但费用减小也要更新


## 代码：

[1030. Travel Plan (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1030.%20Travel%20Plan%20(30)/1030.%20Travel%20Plan%20(30).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#define INF 501

int minDist(int *dist, int *collected, int n)
{	/* 返回未收录的顶点中找到dist值最小的 */
	int minV, min = INF;
	for (int i = 0; i < n; i++)
		if (!collected[i] && dist[i] < min) {
			min = dist[i];
			minV = i;
		}
	if (min == INF)
		return -1;
	return minV;
}

void printPath(int *path, int s, int des)
{	/* 输出从s到des的路径 */
	if (path[des] == s)
		printf("%d %d ", s, des);
	else {
		printPath(path, s, path[des]); // 输出从s到path[des]的路径
		printf("%d ", des); //输出des
	}
}

void dijkstra(int **distance, int **cost, int s, int des, int n)
{
	int *collected = new int[n]; //顶点是否被收录过
	int *dist = new int[n]; //源到顶点的当前最短距离
	int *cst = new int[n]; //源到顶点的当前最短路径的费用
	int *path = new int[n]; //源到顶点的当前最短路径
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		dist[i] = distance[s][i];
		cst[i] = cost[s][i];
		path[i] = dist[i] < INF ? s : -1; //与源相邻则path[i] = s，否则path[i] = -1
	}
	collected[s] = 1; //收录源
	dist[s] = cst[s] = 0;
	path[s] = s;
	while (1) {
		int min = minDist(dist, collected, n);
		if (min == -1)
			break;
		if (min == des)
			break;
		collected[min] = 1; //收录min
		for (int v = 0; v < n; v ++)
			if (!collected[v] && distance[min][v] < INF) { //v未被收录&&v与min相邻
				if (dist[min] + distance[min][v] < dist[v]) { //若通过min到达v可以使距离更短
					dist[v] = dist[min] + distance[min][v];
					cst[v] = cst[min] + cost[min][v];
					path[v] = min;
				}
				else if (dist[min] + distance[min][v] == dist[v]) // 若通过min到达v的距离相同
					if (cst[min] + cost[min][v] < cst[v]) { // 若通过min到达v可以使费用更少
						cst[v] = cst[min] + cost[min][v];
						path[v] = min;
					}
			}
	}
	printPath(path, s, des);
	cout << dist[des] << " " << cst[des];
}

int main()
{
	int n, m, s, d;
	cin >> n >> m >> s >> d;
	int **distance = new int*[n]; //距离图
	int **cost = new int *[n]; //费用图
	for (int i = 0; i < n; i++) {//初始化
		distance[i] = new int[n];
		cost[i] = new int[n];
		for (int j = 0; j < n; j++)
			distance[i][j] = cost[i][j] = INF;
	}
	for (int i = 0; i < m; i++) {
		int c1, c2, dist, cst; //输入两城市之间的距离及费用
		scanf("%d %d %d %d", &c1, &c2, &dist, &cst);
		distance[c1][c2] = distance[c2][c1] = dist;
		cost[c1][c2] = cost[c2][c1] = cst;
	}
	dijkstra(distance, cost, s, d, n);
    return 0;
}
```