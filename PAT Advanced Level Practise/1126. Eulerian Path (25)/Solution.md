# 1126. Eulerian Path (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1126)


* 时间限制 300 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



In graph theory, an *Eulerian path* is a path in a graph which visits every edge exactly once. Similarly, an *Eulerian circuit* is an Eulerian path which starts and ends on the same vertex. They were first discussed by Leonhard Euler while solving the famous Seven Bridges of Konigsberg problem in 1736. It has been proven that connected graphs with all vertices of even degree have an Eulerian circuit, and such graphs are called *Eulerian*. If there are exactly two vertices of odd degree, all Eulerian paths start at one of them and end at the other. A graph that has an Eulerian path but not an Eulerian circuit is called *semi-Eulerian*. (Cited from https://en.wikipedia.org/wiki/Eulerian_path) 

Given an undirected graph, you are supposed to tell if it is Eulerian, semi-Eulerian, or non-Eulerian. 

## Input Specification:

Each input file contains one test case. Each case starts with a line containing 2 numbers N (<= 500), and M, which are the total number of vertices, and the number of edges, respectively. Then M lines follow, each describes an edge by giving the two ends of the edge (the vertices are numbered from 1 to N).

## Output Specification:

For each test case, first print in a line the degrees of the vertices in ascending order of their indices. Then in the next line print your conclusion about the graph -- either "Eulerian", "Semi-Eulerian", or "Non-Eulerian". Note that all the numbers in the first line must be separated by exactly 1 space, and there must be no extra space at the beginning or the end of the line. 

## Sample Input 1:  
7 12  
5 7  
1 2  
1 3  
2 3  
2 4  
3 4  
5 2  
7 6  
6 3  
4 5  
6 4  
5 6  

## Sample Output 1:  
2 4 4 4 4 4 2  
Eulerian  

## Sample Input 2:  
6 10  
1 2  
1 3  
2 3  
2 4  
3 4  
5 2  
6 3  
4 5  
6 4  
5 6  

## Sample Output 2:  
2 4 4 4 3 3  
Semi-Eulerian  

## Sample Input 3:  
5 8  
1 2  
2 5  
5 4  
4 1  
1 3  
3 2  
3 4  
5 3  

## Sample Output 3:  
3 3 4 3 3  
Non-Eulerian  


## 题意与思路：

本题虽然说了很多 *Eulerian* ，但程序并不需要判断一个图是否有 Eulerian Path，因为题目已说明连通图中，顶点的度全部为偶数的为 "Eulerian"，有两个顶点为奇数的为"Semi-Eulerian"，其他都是"Non-Eulerian"。只需要遍历一遍判断图是否连通，并记录顶点的度的奇偶即可。

## 代码：

[1126. Eulerian Path (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1126.%20Eulerian%20Path%20(25)/1126.%20Eulerian%20Path%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>

bool bfs(int **graph, int n)
{
	queue<int> q;
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	q.push(0);
	collected[0] = 1;
	int count = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int w = 0; w < n; w ++)
			if (graph[v][w] == 1 && !collected[w]) {
				q.push(w);
				collected[w] = 1;
				count++;
			}
	}
	return count == n;
}

int main()
{
	int n, m;
	cin >> n >> m;
	int **graph = new int *[n];
	for (int i = 0; i < n; i++)
		graph[i] = new int[n];
	int *degree = new int[n];
	fill(degree, degree + n, 0);
	for (int i = 0; i < m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--;
		v2--;
		graph[v1][v2] = graph[v2][v1] = 1;
		degree[v1] ++;
		degree[v2] ++;
	}
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (i != 0) putchar(' ');
		cout << degree[i];
		if (degree[i] % 2 == 1) count++;
	}
	cout << endl;
	if (bfs(graph, n)) {
		if (count == 0) cout << "Eulerian";
		else if (count == 2) cout << "Semi-Eulerian";
		else cout << "Non-Eulerian";
	}
	else
		cout << "Non-Eulerian";
	cout << endl;
    return 0;
}
```

