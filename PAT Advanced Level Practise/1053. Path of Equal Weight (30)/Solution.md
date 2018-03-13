# 1053. Path of Equal Weight (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1053)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a non-empty tree with root R, and with weight Wi assigned to each tree node Ti. The weight 
of a path from R to L is defined to be the sum of the weights of all the nodes along the path from 
R to any leaf node L.

Now given any weighted tree, you are supposed to find all the paths with their weights equal to a 
given number. For example, let's consider the tree showed in Figure 1: for each node, the upper 
number is the node ID which is a two-digit number, and the lower number is the weight of that node. 
Suppose that the given number is 24, then there exists 4 different paths which have the same given 
weight: {10 5 2 7}, {10 4 10}, {10 3 3 6 2} and {10 3 3 6 2}, which correspond to the red edges in 
Figure 1. 

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1053.jpg)
*Figure 1*			



## Input Specification: 

Each input file contains one test case. Each case starts with a line containing 0 < N <= 100, the 
number of nodes in a tree, M (< N), the number of non-leaf nodes, and 0 < S < 2^30, the given weight 
number. The next line contains N positive numbers where Wi (<1000) corresponds to the tree node Ti. 
Then M lines follow, each in the format:

*ID K ID[1] ID[2] ... ID[K]*


where ID is a two-digit number representing a given non-leaf node, K is the number of its children, 
followed by a sequence of two-digit ID's of its children. For the sake of simplicity, let us fix the 
root ID to be 00.



## Output Specification: 

For each test case, print all the paths with weight S in non-increasing order. Each path occupies a line 
with printed weights from the root to the leaf in order. All the numbers must be separated by a space with 
no extra space at the end of the line. 

Note: sequence {A1, A2, ..., An} is said to be greater than sequence {B1, B2, ..., Bm} if there exists 
1 <= k < min{n, m} such that Ai = Bi for i=1, ... k, and Ak+1 > Bk+1.



## Sample Input:

20 9 24  
10 2 4 3 5 10 2 18 9 7 2 2 1 3 12 1 8 6 2 2  
00 4 01 02 03 04  
02 1 05  
04 2 06 07  
03 3 11 12 13  
06 1 09  
07 2 08 10  
16 1 15  
13 3 14 16 17  
17 2 18 19  

## Sample Output:

10 5 2 7  
10 4 10  
10 3 3 6 2  
10 3 3 6 2  



## 题意：

一棵树有N个结点，M个非叶结点，定义从根结点到某叶结点的路径上经过的所有结点的权值之和为这条路径的权
重。若0 <= N <= 100，每个结点的编号为一个两位数，根的编号为00。输入每个结点的权，以及每个非叶结点的
孩子个数与每个孩子的编号。给定一个整数，求所有权重为这个整数的路径。输出每条路径从根到叶子的所有结
点的权重。路径中，相同层的结点中权大的排在前面。

## 思路：

DFS

建立结构体数组存储树，结构体存储一个树结点的编号、权、孩子个数及孩子结点编号数组。输入数据。DFS遍历
树，递归遍历过程中记录当前的路径vector与路径总权重，遇到叶子结点时判断，若总权重与给定整数相同，则将
此路径存入vector（存vector的vector）中。最后排序并输出所有路径。

## 代码：

[1053. Path of Equal Weight (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1053.%20Path%20of%20Equal%20Weight%20(30)/1053.%20Path%20of%20Equal%20Weight%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

typedef struct node { //树结点
	int id, weight, nChildren, *children;
} tnode;
tnode tree[101]; //树
int s;
vector<vector<int>> paths; //所有路径

void dfs(int n, vector<int>path, int total)
{
	path.push_back(n);
	total += tree[n].weight;
	if (tree[n].nChildren == 0) { //叶结点
		if (total == s) {
			vector<int> tmp = path;
			paths.push_back(tmp); 
		}
		path.pop_back();
		return;
	}
	for (int i = 0; i < tree[n].nChildren; i++) {
		dfs(tree[n].children[i], path, total);
	}
}

int Min(int a, int b)
{
	return a < b ? a : b;
}

bool compare(vector<int>a, vector<int>b)
{
	for (int i = 0; i < Min(a.size(), b.size()); i++)
		if (a[i] != b[i]) return tree[a[i]].weight > tree[b[i]].weight;
	return false;
}

int main()
{
	int n, m;
	cin >> n >> m >> s;
	for (int i = 0; i < n; i++) {
		int weight;
		cin >> weight;
		tree[i] = {i, weight, 0, NULL};
	}
	for (int i = 0; i < m; i++) {
		int id, k;
		cin >> id >> k;
		tree[id].nChildren = k;
		tree[id].children = new int[k];
		for (int j = 0; j < k; j++) 
			cin >> tree[id].children[j];
	}
	vector<int>path;
	dfs(0, path, 0);
	sort(paths.begin(), paths.end(), compare);
	for (auto it = paths.begin(); it != paths.end(); it++) {
		for (auto i = it->begin(); i != it->end(); i++) {
			if (i != it->begin()) putchar(' ');
			cout << tree[*i].weight;
		}
		cout << endl;
	}
    return 0;
}
```

