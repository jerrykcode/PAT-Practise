# 1122. Hamiltonian Cycle (25)


[原题地址](https://www.patest.cn/contests/pat-a-practise/1122)

* 时间限制 300 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



The "Hamilton cycle problem" is to find a simple cycle that contains every vertex in a graph. Such a cycle is called a "Hamiltonian cycle". 

In this problem, you are supposed to tell if a given cycle is a Hamiltonian cycle. 

## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive integers N (2< N <= 200), the number of vertices, and M, the number of edges in an undirected graph. Then M lines follow, each describes an edge in the format "Vertex1 Vertex2", where the vertices are numbered from 1 to N. The next line gives a positive integer K which is the number of queries, followed by K lines of queries, each in the format:

*n V1 V2 ... Vn*  

where n is the number of vertices in the list, and Vi's are the vertices on a path. 

## Output Specification: 

For each query, print in a line "YES" if the path does form a Hamiltonian cycle, or "NO" if not. 
## Sample Input:  
6 10  
6 2  
3 4  
1 5  
2 5  
3 1  
4 1  
1 6  
6 3  
1 2  
4 5  
6  
7 5 1 4 3 6 2 5  
6 5 1 4 3 6 2  
9 6 2 1 6 3 4 5 2 6  
4 1 2 5 1  
7 6 1 3 4 5 2 6  
7 6 1 2 5 4 3 1  

## Sample Output:  
YES  
NO  
NO  
NO  
YES  
NO  


## 题意：

在图中，若一条路径的起点顶点等于终点顶点，路径经过了图中的每个顶点，且除起点、终点外的每个顶点都只经过一次，则称此路径为`“Hamiltonian cycle”`。输入一个图的顶点数与边，然后输入k条路径，对每一条路径，判断它是不是“Hamiltonian cycle”。


## 思路：

用邻接矩阵二维数组graph存储图。对输入的每条路径*V1 V2 ... Vn*，用collected数组记录每个顶点是否收录过，对每一个`Vi -> V(i + 1)`，若V(i + 1)是路径上最后一个顶点，但它却不等于起点，此路径一定不是；若graph[Vi][V(i + 1)] ！= 1，则`Vi -> V(i + 1)`没有直接相连的边，则此路径一定不是。若顶点V(i + 1)不是终点却已收录过，则也不是(*若没收录过则收录顶点V(i + 1)，且计数器sum++*)。以上情况对每一个`Vi -> V(i + 1)`都没有出现，则此路径是连通的，且顶点无重复，且起点等于终点。此时若sum==N，即每个顶点都收录了，则该路径为`“Hamiltonian cycle”`。


## 代码：

[1122. Hamiltonian Cycle (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1122.%20Hamiltonian%20Cycle%20(25)/1122.%20Hamiltonian%20Cycle%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int N, M, k;
	cin >> N >> M;
	int **graph = new int*[N];
	for (int i = 0; i < N; i++)
		graph[i] = new int[N];
	for (int i = 0; i < M; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		v1--;
		v2--;
		graph[v1][v2] = graph[v2][v1] = 1;
	}
	cin >> k;
	int *collected = new int[N];
	for (int i = 0; i < k; i++) {
		fill(collected, collected + N, 0);
		int n, v, w;
		cin >> n >> v;
		v--;
		int start = v;
		collected[v] = 1;
		int sum = 1, flag = 0;
		for (int j = 1; j < n; j++) {
			cin >> w;
			w--;
			if (flag) continue;
			if (j == n - 1 && w != start) {
				flag = 1;
				continue;
			}
			if (graph[v][w] != 1) {
				flag = 1;
				continue;
			}
			if (!collected[w]) {
				collected[w] = 1;
				sum ++;
			}
			else if (j != n - 1) flag = 1;
			v = w;
		}
		if (flag) printf("NO\n");
		else if (sum != N) printf("NO\n");
		else printf("YES\n");
	}
    return 0;
}
```
