# 1091. Acute Stroke (30)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


One important factor to identify acute stroke (急性脑卒中) is the volume of the stroke core. Given 
the results of image analysis in which the core regions are identified in each MRI slice, your job 
is to calculate the volume of the stroke core.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 4 positive integers: M, 
N, L and T, where M and N are the sizes of each slice (i.e. pixels of a slice are in an M by N matrix, 
and the maximum resolution is 1286 by 128); L (<=60) is the number of slices of a brain; and T is the 
integer threshold (i.e. if the volume of a connected core is less than T, then that core must not be counted).

Then L slices are given. Each slice is represented by an M by N matrix of 0's and 1's, where 1 represents 
a pixel of stroke, and 0 means normal. Since the thickness of a slice is a constant, we only have to count 
the number of 1's to obtain the volume. However, there might be several separated core regions in a brain, 
and only those with their volumes no less than T are counted. Two pixels are "connected" and hence belong 
to the same region if they share a common side, as shown by Figure 1 where all the 6 red pixels are connected 
to the blue one. 

![Figure 1](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1091.jpg)
				



## Output Specification: 


For each case, output in a line the total volume of the stroke core. 



## Sample Input:

3 4 5 2
1 1 1 1
1 1 1 1
1 1 1 1
0 0 1 1
0 0 1 1
0 0 1 1
1 0 1 1
0 1 0 0
0 0 0 0
1 0 1 1
0 0 0 0
0 0 0 0
0 0 0 1
0 0 0 1
1 0 0 0

## Sample Output:

26



## 题意：

L层切片，每层是一个M*N矩阵，矩阵中的元素若为0表示正常，1表示不正常。上下左右连接在一起的1为一个
核心。若一个核心中的1的数量大于阈值T，则记录此核心。求所有记录的核心的1的数量和


## 思路：

三维数组表示L层M*N矩阵，元素相当于图中的顶点，上下左右连接在一起的1（核心）组成一个连通分量。BFS
求连通分量中的顶点（为1的元素）数量。


## 代码：

[BFS-1091. Acute Stroke (30) ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1091.%20Acute%20Stroke%20(30)/1091.%20Acute%20Stroke%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>
#include <vector>

int m, n, l, t;

struct node {
	int i, j, k;
	int value;
	int flag;
};

vector<node> nodesAround(node ***graph, node v)
{	/* 返回与v相邻的顶点*/
	vector<node>nodes;
	int i = v.i, j = v.j, k = v.k;
	if (i - 1 >= 0 && graph[i - 1][j][k].value == 1 && !graph[i - 1][j][k].flag) 
		nodes.push_back(graph[i - 1][j][k]);
	if (i + 1 < l && graph[i + 1][j][k].value == 1 && !graph[i + 1][j][k].flag)
		nodes.push_back(graph[i + 1][j][k]);
	if (j - 1 >= 0 && graph[i][j - 1][k].value == 1 && !graph[i][j - 1][k].flag)
		nodes.push_back(graph[i][j - 1][k]);
	if (j + 1 < m && graph[i][j + 1][k].value == 1 && !graph[i][j + 1][k].flag)
		nodes.push_back(graph[i][j + 1][k]);
	if (k - 1 >= 0 && graph[i][j][k - 1].value == 1 && !graph[i][j][k - 1].flag)
		nodes.push_back(graph[i][j][k - 1]);
	if (k + 1 < n && graph[i][j][k + 1].value == 1 && !graph[i][j][k + 1].flag)
		nodes.push_back(graph[i][j][k + 1]);
	return nodes;
}

int bfs(node ***graph, node s)
{
	if (s.flag || !s.value) return 0;
	int count = 0;
	queue<node> q;
	q.push(s);
	graph[s.i][s.j][s.k].flag = 1;
	count++;
	while (!q.empty()) {
		node v = q.front();
		q.pop();
		vector<node> nodes = nodesAround(graph, v);
		for (auto it = nodes.begin(); it != nodes.end(); it++) {
			q.push(*it);
			graph[it->i][it->j][it->k].flag = 1;
			count++;
		}
	}
	return count;
}

int main()
{
	cin >> m >> n >> l >> t;
	node ***graph = new node**[l]; //三维数组表示L层M*N矩阵
	for (int i = 0; i < l; i++) {
		graph[i] = new node*[m];
		for (int j = 0; j < m; j++) {
			graph[i][j] = new node[n];
			int value;
			for (int k = 0; k < n; k++) {
				cin >> value;
				graph[i][j][k] = {i, j, k, value, 0};
			}
		}
	}
	int total = 0;
	for (int i = 0; i < l; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < n; k++) {
				int count = bfs(graph, graph[i][j][k]); //BFS求连通分量中的元素数量
				if (count >= t) total += count;
			}
	cout << total;
    return 0;
}
```