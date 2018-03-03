# 1123. Is It a Complete AVL Tree (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1123)


* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Figures 1-4 illustrate the rotation rules.

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1123_1.jpg)

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1123_2.jpg)

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1123_3.jpg)

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1123_4.jpg)
    

Now given a sequence of insertions, you are supposed to output the level-order traversal sequence of the resulting AVL tree, and to tell if it is a complete binary tree.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<= 20). Then N distinct integer keys are given in the next line. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, insert the keys one by one into an initially empty AVL tree. Then first print in a line the level-order traversal sequence of the resulting AVL tree. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line. Then in the next line, print "YES" if the tree is complete, or "NO" if not. 
## Sample Input 1:  
5  
88 70 61 63 65  

## Sample Output 1:  
70 63 88 61 65  
YES  

## Sample Input 2:  
8  
88 70 61 96 120 90 65 68  

## Sample Output 2:  
88 65 96 61 70 90 120 68  
NO  

## 题意：

输入N个互不相同的整数，作为树结点插入一颗初始为空的AVL树中，求AVL树的层序遍历结果，并判断该AVL树是否为一颗完全二叉树。


## 思路：

按[AVL树的插入操作](https://github.com/jerrykcode/Data-Structure/blob/master/Tree/AVL_Tree.cpp)插入结点。在树结点的结构体中增加一个成员int index用于存储该结点在完全二叉树中的下标（根为0，左孩子为\*2 + 1，右孩子为\*2 + 2），用于在BFS时判断是否为完全二叉树。

## 代码：

[1123. Is It a Complete AVL Tree (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1123.%20Is%20It%20a%20Complete%20AVL%20Tree%20(30)/1123.%20Is%20It%20a%20Complete%20AVL%20Tree%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>

typedef struct node {
	int data;
	int index;
	node * left, * right;
}* AVLT;

int max(int a, int b)
{
	return a > b ? a : b;
}

int getHeight(AVLT tree)
{
	if (tree == NULL)
		return 0;
	return max(getHeight(tree->left),getHeight(tree->right)) + 1;
}

AVLT LL(AVLT tree)
{
	AVLT b = tree->left;
	tree->left = b->right;
	b->right = tree;
	return b;
}

AVLT RR(AVLT tree)
{
	AVLT b = tree->right;
	tree->right = b->left;
	b->left = tree;
	return b;
}

AVLT LR(AVLT tree)
{
	tree->left = RR(tree->left);
	return LL(tree);
}

AVLT RL(AVLT tree)
{
	tree->right = LL(tree->right);
	return RR(tree);
}

AVLT insert(AVLT tree, int data)
{
	if (tree == NULL) {
		tree = new node;
		tree->data = data;
		tree->index = -1;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	if (data < tree->data) { //Inserts on left
		tree->left = insert(tree->left, data);
		if (getHeight(tree->left) - getHeight(tree->right) >= 2) {
			if (data < tree->left->data)
				tree = LL(tree);
			else tree = LR(tree);
		}
	}
	else { //Inserts on right
		tree->right = insert(tree->right, data);
		if (getHeight(tree->right) - getHeight(tree->left) >= 2) {
			if (data > tree->right->data)
				tree = RR(tree);
			else
				tree = RL(tree);
		}
	}
	return tree;
}

void bfs(AVLT tree)
{
	queue<AVLT> q;
	q.push(tree);
	tree->index = 0;
	int flag[20];
	fill(flag, flag + 20, -1);
	flag[0] = 1;
	int tag = 0;
	while (!q.empty()) {
		AVLT t = q.front();
		q.pop();
		if (t != tree) putchar(' ');
		cout << t->data;
		if (t->index - 1 >= 0 && flag[t->index - 1] == -1)
			tag = 1;
		if (t->left != NULL) {
			t->left->index = t->index * 2 + 1;
			flag[t->left->index] = 1;
			q.push(t->left);
		}
		if (t->right != NULL) {
			t->right->index = t->index * 2 + 2;
			flag[t->right->index] = 1;
			q.push(t->right);
		}
	}
	cout << endl << (tag == 1 ? "NO" : "YES") << endl;
}

int main()
{
	int n;
	cin >> n;
	AVLT tree = NULL;
	for (int i = 0; i < n; i++) {
		int data;
		cin >> data;
		tree = insert(tree, data);
	}
	bfs(tree);
    return 0;
}
```
