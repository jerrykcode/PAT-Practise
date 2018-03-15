# 1134. Vertex Cover (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1134)

* 时间限制 600 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue

A vertex cover of a graph is a set of vertices such that each edge of the graph is incident to at least one vertex of the set. Now given a graph with several vertex sets, you are supposed to tell if each of them is a vertex cover or not.

## Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers N and M (both no more than 10^4), being the total numbers of vertices and the edges, respectively. Then M lines follow, each describes an edge by giving the indices (from 0 to N-1) of the two ends of the edge.

After the graph, a positive integer K (<= 100) is given, which is the number of queries. Then K lines of queries follow, each in the format:

*Nv v[1] v[2] ... v[Nv]*

where Nv is the number of vertices in the set, and v[i]'s are the indices of the vertices.


## Output Specification:

For each query, print in a line "Yes" if the set is a vertex cover, or "No" if not.

## Sample Input:

10 11  
8 7  
6 8  
4 5  
8 4  
8 1  
1 2  
1 4  
9 8  
9 1  
1 0  
2 4  
5  
4 0 3 8 4  
6 6 1 7 5 4 9  
3 1 8 4  
2 2 8  
7 9 8 7 6 5 4 2  

## Sample Output:

No  
Yes  
Yes  
No  
No  

## 题意: 

对于一个图,若一个顶点集使所有边的两个顶点中至少有一个在集合内,则此顶点集合为一个"Vertex Cover"。输入一个图，以及K个顶点集合，判断它们是否为"Vertex Cover"。

## 思路：

用vector<pair<int, int>>存储每条边，对于每一个顶点集合，用int * collected = new int[n]数组，元素初始化为0，对于顶点集合中的每一个顶点，将其collected值标记为1，然后遍历所有的边，若有边的两个顶点的collected值都为0，则此边的两个顶点都不在顶点集合中，则不是"Vertex Cover"。


## 代码：

[1134. Vertex Cover (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1134.%20Vertex%20Cover%20(25)/1134.%20Vertex%20Cover%20(25).cpp)

```cpp
#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n, m, k;
	cin >> n >> m;
	vector<pair<int, int>> edges;
	for (int i = 0; i < m; i++) {
		int v1, v2;
		cin >> v1 >> v2;
		edges.push_back({v1, v2});
	}
	cin >> k;
	int *collected = new int[n];
	for (int i = 0; i < k; i++) {
		fill(collected, collected + n, 0);
		int nv, v, flag = 0;
		cin >> nv;
		for (int j = 0; j < nv; j++) {
			cin >> v;
			collected[v] = 1;
		}
		for (auto it = edges.begin(); it != edges.end(); it++) 
			if (!collected[it->first] && !collected[it->second]) {
				cout << "No" << endl;
				flag = 1;
				break;
			}
		if (flag == 0)
			cout << "Yes" << endl;
	}
	return 0;
}
```