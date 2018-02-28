# 1115. Counting Nodes in a BST (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1115)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B


* 判题程序 Standard 

* 作者 CHEN, Yue



A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

•The left subtree of a node contains only nodes with keys less than or equal to the node's key.   
•The right subtree of a node contains only nodes with keys greater than the node's key.   
•Both the left and right subtrees must also be binary search trees.   

Insert a sequence of numbers into an initially empty binary search tree. Then you are supposed to count the total number of nodes in the lowest 2 levels of the resulting tree.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=1000) which is the size of the input sequence. Then given in the next line are the N integers in [-1000 1000] which are supposed to be inserted into an initially empty binary search tree.

## Output Specification: 

For each case, print in one line the numbers of nodes in the lowest 2 levels of the resulting tree in the format:

*n1 + n2 = n* 

where n1 is the number of nodes in the lowest level, n2 is that of the level above, and n is the sum. 

## Sample Input:
9  
25 30 42 16 20 20 35 -5 28  

## Sample Output:  

2 + 4 = 6  

## 题意：


BST有N个结点，输入每个结点的值，按输入顺序插入BST。求BST最后两层的结点数之和。*n1 + n2 = n* 形式输出。n1为最后一层的结点数，n2为倒数第二层的结点数


## 思路：


元素插入BST：待插入的元素 <= 结点的值，递归插入左子树；> 结点的值，递归插入右子树。结点不存在则创建新结点，此新结点即插入的结点。用全局数组存储每一层的结点数，递归插入结点时记录从0开始递归到了第几层，插入元素（结点不存在，创建新结点）时该层的结点数增1。


## 代码：

[1115. Counting Nodes in a BST (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1115.%20Counting%20Nodes%20in%20a%20BST%20(30)/1115.%20Counting%20Nodes%20in%20a%20BST%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int *level;

typedef struct node { //Node of BST
	int data;
	node *left, *right;
} *BST;

BST insert(BST tree, int data, int l)
{	/* Inserts an element into the BST, l is the level of the tree on which the node insert */
	if (tree == NULL) {
		tree = new node;
		tree->data = data;
		tree->left = tree->right = NULL;
		level[l]++;
		return tree;
	}
	if (data <= tree->data)
		tree->left = insert(tree->left, data, l + 1); //Inserts on the left, next level
	if (data > tree->data)
		tree->right = insert(tree->right, data, l + 1); //Inserts on the right, next level
	return tree;
}

int main()
{
	int n;
	cin >> n;
	level = new int[n]; //Number of nodes on each level
	fill(level, level + n, 0);
	BST tree = NULL;
	for (int i = 0; i < n; i++) {
		int data;
		cin >> data;
		tree = insert(tree, data, 0);
	}
	int maxL = 0;
	for (int i = 0; i < n; i++) 
		if (level[i] == 0) {
			maxL = i;
			break;
		}
	if (maxL == 0)maxL = n;
	printf("%d + %d = %d", level[maxL - 1], level[maxL - 2], level[maxL - 1] + level[maxL - 2]);
    return 0;
}

```
