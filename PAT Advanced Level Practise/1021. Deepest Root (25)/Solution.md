# 1021. Deepest Root (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1021)
* 时间限制 1500 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



A graph which is connected and acyclic can be considered a tree. The height of the tree depends on the selected root. 
Now you are supposed to find the root that results in a highest tree. Such a root is called the deepest root.


## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<=10000) which is 
the number of nodes, and hence the nodes are numbered from 1 to N. Then N-1 lines follow, each describes an edge by 
given the two adjacent nodes' numbers.


## Output Specification: 

For each test case, print each of the deepest roots in a line. If such a root is not unique, print them in increasing 
order of their numbers. In case that the given graph is not a tree, print "Error: K components" where K is the number 
of connected components in the graph.



## Sample Input 1:

5  
1 2  
1 3  
1 4  
2 5  

## Sample Output 1:

3  
4  
5  


## Sample Input 2:

5  
1 3  
1 4  
2 5  
3 4  

## Sample Output 2:

Error: 2 components  



## 题意：

图有N（N <= 10000）个顶点，给出N-1条边的两个顶点。若此图不连通，求连通分量的个数，若图连通，求用顶点作为树的结点，哪个
顶点作为根能使树的高度最大


## 思路：

用vector数组存储每个顶点的邻接点，顶点的邻接表中的顶点相当于树结点的孩子与父结点。对于每个顶点，用它作为根，BFS遍历求最
高层，遍历的同时收录结点，遍历后若图的所有顶点均被收录则图连通，继续用其他顶点作为根，可找出最高层的根；若遍历后图的顶点
有未被收录的，则图不连通，继续用其他顶点作为源开始遍历，求连通分量个数


## 代码：

[1021. Deepest Root (25)_2.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1021.%20Deepest%20Root%20(25)/1021.%20Deepest%20Root%20(25)_2.cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <queue>
#include <algorithm>

int main()
{
	int n;
	cin >> n;
	vector<int>* adjlists = new vector<int>[n]; //邻接表，图顶点的邻接点，或树结点的孩子与父结点
	for (int i = 0; i < n - 1; i++) {
		int n1, n2;
		cin >> n1 >> n2;
		n1--;
		n2--;
		adjlists[n1].push_back(n2);
		adjlists[n2].push_back(n1);
	}
	queue<int>q;
	int *collected = new int[n];
	int deepest = 0;
	vector<int>roots;
	int flag = 1; //1表示图连通，初始设为1
	int components = 0; //连通分量个数
	for (int i = 0; i < n; i++) { //顶点作为树的根
		if(flag)fill(collected, collected + n, 0); //图连通，计算deepest root
		else { //不连通，求连通分量个数
			if (collected[i]) continue;
			else components++;
		}
		collected[i] = 1; //BFS遍历
		q.push(i);
		int tail = i, last = i, level = 0;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (auto it = adjlists[v].begin(); it != adjlists[v].end(); it++) 
				if (!collected[*it]) {
					collected[*it] = 1;
					q.push(*it);
					last = *it; //当前最后进队列的元素
				}
			if (v == tail) { //出队列的是这一层最后一个，进入下一层
				tail = last;
				level ++;
			}
		}
		if (i == 0) { //第0次遍历
			for (int v = 0; v < n; v++)
				if (!collected[v]) { //不连通
					flag = 0;
					components++;
					break;
				}
		}
		if (!flag) continue;
		if (level > deepest) {
			deepest = level;
			roots.clear();
			roots.push_back(i);
		}
		else if (level == deepest) 
			roots.push_back(i);
	}
	if (flag) { //连通
		sort(roots.begin(), roots.end());
		for (auto it = roots.begin(); it != roots.end(); it++) 
			cout << (*it) + 1 << endl;
	}
	else printf("Error: %d components\n", components);
    return 0;
}
```