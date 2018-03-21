# 1094. The Largest Generation (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1094)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A family hierarchy is usually presented by a pedigree tree where all the nodes on the same level 
belong to the same generation. Your task is to find the generation with the largest population.



## Input Specification: 

Each input file contains one test case. Each case starts with two positive integers N (<100) which 
is the total number of family members in the tree (and hence assume that all the members are numbered 
from 01 to N), and M (<N) which is the number of family members who have children. Then M lines follow, 
each contains the information of a family member in the following format:

*ID K ID[1] ID[2] ... ID[K]*

where ID is a two-digit number representing a family member, K (>0) is the number of his/her children, 
followed by a sequence of two-digit ID's of his/her children. For the sake of simplicity, let us fix 
the root ID to be 01. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print in one line the largest population number and the level of the corresponding 
generation. It is assumed that such a generation is unique, and the root level is defined to be 1. 



## Sample Input:

23 13  
21 1 23  
01 4 03 02 04 05  
03 3 06 07 08  
06 2 12 13  
13 1 21  
08 2 15 16  
02 2 09 10  
11 2 19 20  
17 1 22  
05 1 11  
07 1 14  
09 1 17  
10 1 18  

## Sample Output:

9 4  



## 题意：

输入家族人数（树结点数）N，有孩子的人数（非叶结点数）M，及每个有孩子的人的孩子数量和所有孩子的id。
根结点id为1。求结点树最多的一层的结点数（根这一层为第1层）


## 思路：

结构体存储结点的id、孩子数量和存储孩子id的数组。结构体数组存储所有结点。

BFS分层遍历树，找出结点最多的一层


## 代码：

[1094. The Largest Generation (25)](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1094.%20The%20Largest%20Generation%20(25)/1094.%20The%20Largest%20Generation%20(25).cpp)

```cpp
#include <iostream>
using namespace std;
#include <queue>

struct node {
	int id, k, *children;
};

void bfs(node *tree)
{
	queue<int> q;
	int root = 0, last = root, tail = root, max = 1, count = 0, level = 1, maxLevel = 1;
	q.push(root);
	while (!q.empty()) {
		int n = q.front();
		q.pop();
		for (int i = 0; i < tree[n].k; i++) {
			q.push(tree[n].children[i]);
			last = tree[n].children[i]; //last是最后一个进队列的
		}
		count += tree[n].k; 
		if (n == tail) { //n是一层的最后一个，若有下一层则进入下一层
			if (!q.empty()) level++;
			if (count > max) {
				max = count;
				maxLevel = level;
			}
			count = 0;
			tail = last;
		}
	}
	cout << max << " " << maxLevel;
}

int main()
{
	int n, m;
	cin >> n >> m;
	node *tree = new node[n];
	for (int i = 0; i < n; i++)
		tree[i] = {i, 0, NULL};
	int id, k;
	for (int i = 0; i < m; i++) {
		cin >> id >> k;
		id--; //题目中id 1~N，这里id 0~N - 1
		tree[id].k = k;
		tree[id].children = new int[k];
		for (int j = 0; j < k; j++) {
			cin >> tree[id].children[j];
			tree[id].children[j]--;
		}
	}
	bfs(tree);
    return 0;
}
```