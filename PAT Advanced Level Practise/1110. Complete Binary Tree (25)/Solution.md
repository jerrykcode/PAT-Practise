# 1110. Complete Binary Tree (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1110)


* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a tree, you are supposed to tell if it is a complete binary tree.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=20) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N-1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

## Output Specification: 

For each case, print in one line "YES" and the index of the last node if the tree is a complete binary tree, or "NO" and the index of the root if not. There must be exactly one space separating the word and the number. 

## Sample Input 1:

9  
7 8  
\- \-  
\- \-  
\- \-  
0 1  
2 3  
4 5  
\- \-  
\- \-  

## Sample Output 1:

YES 8  

## Sample Input 2:

8  
\- \-  
4 5  
0 6  
\- \-  
2 3  
\- 7  
\- \-  
\- \-  

## Sample Output 2:

NO 1  

## 题意：

输入二叉树N个结点(序号0~N - 1)每个结点的左、右孩子的序号，判断这是否为一棵完全二叉树。

## 思路：

从未作为其他结点的孩子出现过的即为根。

BFS遍历二叉树，计算每个结点在完全二叉树BST中的编号，即根为0，左孩子为父结点编号\*2 + 1，右孩子为父结点编号\*2 + 2，若一个出队列的结点不是根，且其在BST中的编号 - 1不存在，即它在BST中应有的前一个结点不存在，则不是BST。

## 代码：

[1110. Complete Binary Tree (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1110.%20Complete%20Binary%20Tree%20(25)/1110.%20Complete%20Binary%20Tree%20(25).cpp)



```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <queue>

struct node {
	int index, left, right;
};

void bfs(node *tree, int root, int n)
{
	queue<int> q;
	int *flag = new int[2*n + 1];
	fill(flag, flag + 2*n + 1, 0);
	tree[root].index = 0;
	flag[0] = 1;
	q.push(root);
	int last = root;
	while (!q.empty()) {
		int t = q.front();
		q.pop();
		if (t != root && !flag[tree[t].index - 1]) {
			printf("NO %d\n", root);
			return;
		}
		int left = tree[t].left, right = tree[t].right;
		if (left != -1) {
			tree[left].index = tree[t].index * 2 + 1;
			flag[tree[left].index] = 1;
			q.push(left);
			last = left;
		}
		if (right != -1) {
			tree[right].index = tree[t].index * 2 + 2;
			flag[tree[right].index] = 1;
			q.push(right);
			last = right;
		}
	}
	printf("YES %d\n", last);
}

int main()
{
	int n;
	cin >> n;
	node *tree = new node[n];
	int *flag = new int[n];
	fill(flag, flag + n, 0);
	for (int i = 0; i < n; i++) {
		string left, right;
		cin >> left >> right;
		int l = left == "-" ? -1 : atoi(left.c_str());
		int r = right == "-" ? -1 : atoi(right.c_str());
		tree[i] = {-1, l, r};
		if (l != -1) flag[l] = 1;
		if (r != -1) flag[r] = 1;
	}
	int root;
	for (int i = 0; i < n; i++) 
		if (!flag[i]) {
			root = i;
			break;
		}
	bfs(tree, root, n);
    return 0;
}
```