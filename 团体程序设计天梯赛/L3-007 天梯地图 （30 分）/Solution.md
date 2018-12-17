# L3-007 天梯地图 （30 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805051153825792)

* 题目作者: 陈越

* 单位: 浙江大学

* 时间限制: 300 ms

* 内存限制: 64 MB

* 代码长度限制: 16 KB


本题要求你实现一个天梯赛专属在线地图，队员输入自己学校所在地和赛场地

点后，该地图应该推荐两条路线：一条是最快到达路线；一条是最短距离的路

线。题目保证对任意的查询请求，地图上都至少存在一条可达路线。

## 输入格式：

输入在第一行给出两个正整数N（2 ≤ N ≤ 500）和M，分别为地图中所有标

记地点的个数和连接地点的道路条数。随后M行，每行按如下格式给出一条道

路的信息：

```
V1 V2 one-way length time
```


其中V1和V2是道路的两个端点的编号（从0到N-1）；如果该道路是从V1到V2的

单行线，则one-way为1，否则为0；length是道路的长度；time是通过该路所

需要的时间。最后给出一对起点和终点的编号。

## 输出格式：

首先按下列格式输出最快到达的时间T和用节点编号表示的路线：

```
Time = T: 起点 => 节点1 => ... => 终点
```


然后在下一行按下列格式输出最短距离D和用节点编号表示的路线：

```
Distance = D: 起点 => 节点1 => ... => 终点
```

如果最快到达路线不唯一，则输出几条最快路线中最短的那条，题目保证这条

路线是唯一的。而如果最短距离的路线不唯一，则输出途径节点数最少的那条

，题目保证这条路线是唯一的。

如果这两条路线是完全一样的，则按下列格式输出：

```
Time = T; Distance = D: 起点 => 节点1 => ... => 终点
```


## 输入样例1：

10 15  
0 1 0 1 1  
8 0 0 1 1  
4 8 1 1 1  
5 4 0 2 3  
5 9 1 1 4  
0 6 0 1 1  
7 3 1 1 2  
8 3 1 1 2  
2 5 0 2 2  
2 1 1 1 1  
1 5 0 1 3  
1 4 0 1 1  
9 7 1 1 3  
3 1 0 2 5  
6 3 1 2 1  
5 3  


## 输出样例1：

Time = 6: 5 => 4 => 8 => 3  
Distance = 3: 5 => 1 => 3  


## 输入样例2：

7 9  
0 4 1 1 1  
1 6 1 3 1  
2 6 1 1 1  
2 5 1 2 2  
3 0 0 1 1  
3 1 1 3 1  
3 2 1 2 1  
4 5 0 2 2  
6 5 1 2 1  
3 5  


## 输出样例2：

Time = 3; Distance = 4: 3 => 2 => 5  

## 思路：

Dijkstra

用两个二维数组分别表示两个邻接矩阵图，边分别表示两顶点之间的时间和距离。用两次dijkstra求时间最短和距离最短的路径。

在求`时间最短`时，每收录一个顶点minV后，遍历所有相邻且未收录顶点时，若通过minV到达该顶点使源到该顶点的时间减小，则该顶点更新为通过minV到达；若通过minV时间相同但可以使源到该顶点的距离减小，则也更新该顶点为通过minV到达的顶点。

在求`距离最短`时，每收录一个顶点minV后，遍历所有相邻且未收录顶点时，若通过minV到达该顶点使源到该顶点的距离减小，则该顶点更新为通过minV到达；若通过minV距离相同但可以使源到该顶点的经过的顶点数减小，则也更新该顶点为通过minV到达的顶点。


## 代码：

[L3-007 天梯地图 （30 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-007%20%E5%A4%A9%E6%A2%AF%E5%9C%B0%E5%9B%BE%20%EF%BC%8830%20%E5%88%86%EF%BC%89/L3-007%20%E5%A4%A9%E6%A2%AF%E5%9C%B0%E5%9B%BE%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define INF 100000

int findMin(int *arr, bool *collected, int n) {
	int min = INF, minV = -1;
	for (int i = 0; i < n; i++) {
		if (!collected[i] && arr[i] < min) {
			min = arr[i];
			minV = i;
		}
	}
	return minV;
}

void getPath(int *path, int src, int des, int n, vector<int>& vpath) {
	stack<int> s;
	while (des != src) {
		s.push(des);
		des = path[des];
	}
	vpath.push_back(src);
	while (!s.empty()) {
		vpath.push_back(s.top());
		s.pop();
	}
}

int timeDijkstra(int **timeGraph, int **distGraph, int n, int src, int des, vector<int>& vpath) {
	int *time = new int[n];
	int *dist = new int[n];
	int *path = new int[n];
	bool *collected = new bool[n];
	for (int i = 0; i < n; i++) {
		time[i] = timeGraph[src][i];
		dist[i] = distGraph[src][i];
		path[i] = time[i] < INF ? src : -1;
		collected[i] = false;
	}
	time[src] = dist[src] = 0;
	path[src] = -1;
	collected[src] = true;
	while (1) {
		int minV = findMin(time, collected, n);
		if (minV == -1) return -1;
		if (minV == des) break;
		collected[minV] = true;
		for (int v = 0; v < n; v++) {
			if (!collected[v] && timeGraph[minV][v] < INF) {
				if (time[minV] + timeGraph[minV][v] < time[v]) {
					time[v] = time[minV] + timeGraph[minV][v];
					dist[v] = dist[minV] + distGraph[minV][v];
					path[v] = minV;
				}
				else if (time[minV] + timeGraph[minV][v] == time[v] && dist[minV] + distGraph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + distGraph[minV][v];
					path[v] = minV;
				}
			}
		}
	} //while
	getPath(path, src, des, n, vpath);
	int result = time[des];
	free(time);
	free(dist);
	free(path);
	free(collected);
	return result;
}

int distDijkstra(int **distGraph, int n, int src, int des, vector<int>& vpath) {
	int *dist = new int[n];
	int *num = new int[n];
	int *path = new int[n];
	bool *collected = new bool[n];
	for (int i = 0; i < n; i++) {
		dist[i] = distGraph[src][i];
		num[i] = dist[i] < INF ? 2 : -1;
		path[i] = dist[i] < INF ? src : -1;
		collected[i] = false;
	}
	dist[src] = 0;
	num[src] = 1;
	path[src] = -1;
	collected[src] = true;
	while (1) {
		int minV = findMin(dist, collected, n);
		if (minV == -1) return -1;
		if (minV == des) break;
		collected[minV] = true;
		for (int v = 0; v < n; v++) {
			if (!collected[v] && distGraph[minV][v] < INF) {
				if (dist[minV] + distGraph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + distGraph[minV][v];
					num[v] = num[minV] + 1;
					path[v] = minV;
				}
				else if (dist[minV] + distGraph[minV][v] == dist[v] && num[minV] + 1 < num[v]) {
					num[v] = num[minV] + 1;
					path[v] = minV;
				}
			}
		}
	} //while
	getPath(path, src, des, n, vpath);
	int result = dist[des];
	free(dist);
	free(num);
	free(path);
	free(collected);
	return result;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	int **timeGraph = new int*[n];
	int **distGraph = new int*[n];
	for (int i = 0; i < n; i++) {
		timeGraph[i] = new int[n];
		distGraph[i] = new int[n];
		for (int j = 0; j < n; j++)
			timeGraph[i][j] = distGraph[i][j] = INF;
	}
	for (int i = 0; i < m; i++) {
		int v1, v2, oneWay, len, time;
		std::cin >> v1 >> v2 >> oneWay >> len >> time;
		distGraph[v1][v2] = len;
		timeGraph[v1][v2] = time;
		if (oneWay == 0) {
			distGraph[v2][v1] = len;
			timeGraph[v2][v1] = time;
		}
	}
	int src, des;
	std::cin >> src >> des;
	vector<int> timePath;
	int t = timeDijkstra(timeGraph, distGraph, n, src, des, timePath);
	for (int i = 0; i < n; i++)
		free(timeGraph[i]);
	free(timeGraph);
	vector<int> distPath;
	int d = distDijkstra(distGraph, n, src, des, distPath);
	for (int i = 0; i < n; i++)
		free(distGraph[i]);
	free(distGraph);
	bool equal = true;
	if (timePath.size() != distPath.size())
		equal = false;
	else {
		for (int i = 0; i < timePath.size(); i++)
			if (timePath[i] != distPath[i]) {
				equal = false;
				break;
			}
	}
	if (equal) {
		printf("Time = %d; Distance = %d: ", t, d);
		for (auto it = timePath.begin(); it != timePath.end(); it++) {
			if (it != timePath.begin()) cout << " => ";
			cout << *it;
		}
	}
	else {
		printf("Time = %d: ", t);
		for (auto it = timePath.begin(); it != timePath.end(); it++) {
			if (it != timePath.begin()) cout << " => ";
			cout << *it;
		}
		cout << endl;
		printf("Distance = %d: ", d);
		for (auto it = distPath.begin(); it != distPath.end(); it++) {
			if (it != distPath.begin()) cout << " => ";
			cout << *it;
		}
	}
	return 0;
}


```




