# 1102. Invert a Binary Tree (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1102)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



The following is from Max Howell @twitter:

> Google: 90% of our engineers use the software you wrote (Homebrew), but you can't invert a binary tree on a whiteboard so fuck off.

Now it's your turn to prove that `YOU CAN` invert a binary tree!

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N-1. Then N lines follow, each corresponds to a node from 0 to N-1, and gives the indices of the left and right children of the node. If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

## Output Specification: 

For each test case, print in the first line the level-order, and then in the second line the in-order traversal sequences of the inverted tree. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.
## Sample Input:8
1 \-  
\- \-  
0 \-  
2 7  
\- \-  
\- \-  
5 \-  
4 6  

## Sample Output:

3 7 2 6 4 0 5 1  
6 5 7 4 3 2 0 1  

## 题意：

二叉树有N个结点，编号0~N - 1。输入N行，第i行输入第i个结点的左、右孩子编号（*但按 sample Input 与 sample Output，应该是先输入右孩子，再输入左孩子，否则遍历结果是这颗树的镜像*），"-" 表示结点不存在。输出这颗树的层序遍历结果与中序遍历结果（结点编号即应输出的值）


## 思路：

用结构体数组存储树结点，下标即为结点编号。用int数组flag存储一个结点是否作为另一结点的孩子出现过，输入结点的孩子时，将这些孩子的编号作为下标的flag值赋为1，然后遍历flag，唯一不为1的就是不是任何结点的孩子的结点，也就是根。确定根后即可进行层序、中序遍历


## 代码：

[1102. Invert a Binary Tree (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1102.%20Invert%20a%20Binary%20Tree%20(25)/1102.%20Invert%20a%20Binary%20Tree%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <queue>

struct node {
	int index;
	int left, right;
};

void level(node *tree, int root)
{
	queue<int> q;
	q.push(root);
	int flag = 0;
	while (!q.empty()) {
		int n = q.front();
		q.pop();
		if (flag) putchar(' ');
		else flag = 1;
		cout << n;
		if (tree[n].left != -1) q.push(tree[n].left);
		if (tree[n].right != -1) q.push(tree[n].right);
	}
}

void inOrder(node *tree, int root)
{
	if (tree[root].left != -1) {
		inOrder(tree, tree[root].left);
		putchar(' ');
	}
	cout << root;
	if (tree[root].right != -1) {
		putchar(' ');
		inOrder(tree, tree[root].right);
	}
}

int main()
{
	int n;
	cin >> n;
	node *tree = new node[n];
	int *flag = new int[n];
	for (int i = 0; i < n; i++) {
		string l, r;
		int left, right;
		cin >> r >> l;
		left = l == "-" ? -1 : atoi(l.c_str());
		right = r == "-" ? -1 : atoi(r.c_str());
		tree[i] = {i, left, right};
		if (left != -1) flag[left] = 1;
		if (right != -1) flag[right] = 1;
	}
	int root;
	for (int i = 0; i < n; i ++)
		if (flag[i] != 1) {
			root = i; //The only node that had not appeared as a child of others is the root
			break;
		}
	level(tree, root);
	cout << endl;
	inOrder(tree, root);
    return 0;
}
```