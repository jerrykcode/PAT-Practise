# 1099. Build A Binary Search Tree (30)

* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:
•The left subtree of a node contains only nodes with keys less than the node's key. 
•The right subtree of a node contains only nodes with keys greater than or equal to the node's key. 
•Both the left and right subtrees must also be binary search trees. 
Given the structure of a binary tree and a sequence of distinct integer keys, there is only one way to fill 
these keys into the tree so that the resulting tree satisfies the definition of a BST. You are supposed to 
output the level order traversal sequence of that tree. The sample is illustrated by Figure 1 and 2. 

![Figure1 & Figure2](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1099.jpg)




## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100) which 
is the total number of nodes in the tree. The next N lines each contains the left and the right children of a 
node in the format "left_index right_index", provided that the nodes are numbered from 0 to N-1, and 0 is always 
the root. If one child is missing, then -1 will represent the NULL child pointer. Finally N distinct integer keys 
are given in the last line.



## Output Specification: 

For each test case, print in one line the level order traversal sequence of that tree. All the numbers must be 
separated by a space, with no extra space at the end of the line. 



## Sample Input:

9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42


## Sample Output:

58 25 82 11 38 67 45 73 42


## 题意：

BST有N个结点，序号0~N - 1，输入N行，第i行输入第i个结点的左、右结点的序号，-1表示不存在结点。输入N个结点
的值，求BST的层序遍历


## 思路：

对N个结点的值递增排序，对于任一个结点，只要知道比它小的结点个数即可确定该结点的值。先写一个递归函数求每
一个结点的所有子孙结点的个数。再递归求每个结点左子树上的结点数，从而求结点的值

## 代码：

[1099. Build A Binary Search Tree (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1099.%20Build%20A%20Binary%20Search%20Tree%20(30)/1099.%20Build%20A%20Binary%20Search%20Tree%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <queue>

struct node {
	int value; //值
	int id, left, right; //自己的序号与左、右孩子的序号
	int nDescendants; //子孙结点的个数
};

int countDescendant(node *tree, int root)
{	/* 计算结点的子孙个数 */
	if (tree[root].left == -1 && tree[root].right == -1) return 0; //无左、右孩子
	if (tree[root].left != -1) tree[root].nDescendants += (countDescendant(tree, tree[root].left) + 1); //左孩子的子孙个数+1（加上左孩子本身）
	if (tree[root].right != -1) tree[root].nDescendants += (countDescendant(tree, tree[root].right) + 1); //右孩子的子孙个数+1（加上右孩子本身）
	return tree[root].nDescendants;
}

void findValue(node *tree, int *keys, int root)
{	/* 通过求结点的左子树上的结点个数确定结点在keys数组中的位置从而求结点的值 */
	int left = tree[root].left;
	int leftDescendant = left == -1 ? 0 : tree[left].nDescendants + 1; //root左子树上的结点个数
	tree[root].value = *(keys + leftDescendant); //root的值
	if (left != -1) findValue(tree, keys, left); //递归求左孩子的值
	if (tree[root].right != -1) findValue(tree, keys + leftDescendant + 1, tree[root].right);//递归求右孩子的值，注意从 keys + leftDescendant + 1 开始
}

void bfs(node *tree, int root)
{
	queue<node>q;
	q.push(tree[root]);
	while (!q.empty()) {
		node n = q.front();
		q.pop();
		if (n.id != root) putchar(' ');
		cout << n.value;
		if (n.left != -1) q.push(tree[n.left]);
		if (n.right != -1) q.push(tree[n.right]);
	}
}

int main()
{
	int n;
	cin >> n;
	node *tree = new node[n];
	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;
		tree[i] = {0, i, l, r, 0}; //值与子孙结点个数初始化为0
	}
	int * keys = new int[n];
	for (int i = 0; i < n; i++) cin >> keys[i];
	sort(keys, keys + n);
	countDescendant(tree, 0); //求结点的子孙结点个数
	findValue(tree, keys, 0); //通过求结点的左子树上的结点个数确定结点在keys数组中的位置从而求结点的值
	bfs(tree, 0); //BFS输出
    return 0;
}
```