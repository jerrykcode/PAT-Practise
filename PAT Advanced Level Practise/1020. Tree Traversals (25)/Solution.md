# 1020. Tree Traversals (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1020)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal 
sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.



## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=30), the total 
number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder 
sequence. All the numbers in a line are separated by a space.


## Output Specification: 

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the 
numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.



## Sample Input:
7  
2 3 1 5 7 6 4  
1 2 3 4 5 6 7  

## Sample Output:
4 1 6 3 5 7 2  



## 题意：

若一颗树的结点都是不相同的正整数，已知树的结点个数N，输入树的后序遍历与中序遍历结果，求树的层序遍历

## 思路：

用数组post存储后序遍历结果，in存储中序遍历结果，post数组的最后一个值即为根结点的值，根据根结点在in中
的位置分割出左、右子序列，进行递归(先递归右子树)

post设为全局变量，定义全局变量postSize = N，每次递归时post[--postSize]即为根的值，分割后左边的值存储
在数组left中，右边存储在数组right中，若left或right的长度为0，则相应的左子树或右子树为NULL，

注意一定要先递归right!

## 代码：

[1020. Tree Traversals (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1020.%20Tree%20Traversals%20(25)/1020.%20Tree%20Traversals%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>

int *post, postSize;

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} * tree;

tree getTree(int *in, int inSize)
{
	int root = post[--postSize];
	int rootIndex;
	for (int i = 0; i < inSize; i ++)
		if (in[i] == root) {
			rootIndex = i;
			break;
		}
	tree T = (tree)malloc(sizeof(struct node));
	T->data = root;
	int *left, *right;
	//right
	if (inSize - rootIndex - 1 == 0)
		T->right = NULL;
	else {
		right = new int[inSize - rootIndex - 1];
		int count = 0;
		for (int i = rootIndex + 1; i < inSize; i++)
			right[count++] = in[i];
		T->right = getTree(right, inSize - rootIndex - 1);
	}
	//left
	if (rootIndex == 0)
		T->left = NULL;
	else {
		left = new int[rootIndex];
		for (int i = 0; i < rootIndex; i++)
			left[i] = in[i];
		T->left = getTree(left, rootIndex);
	}
	return T;
}

void levelOrder(tree T)
{
	queue<tree> nodes;
	nodes.push(T);
	int flag = 0;
	while (!nodes.empty()) {
		if (flag)
			putchar(' ');
		else flag = 1;
		T = nodes.front();
		cout << T->data;
		nodes.pop();
		if (T->left)
			nodes.push(T->left);
		if (T->right)
			nodes.push(T->right);
	}
}

int main()
{
	int n;
	cin >> n;
	post = new int[n];
	postSize = n;
	int *in = new int[n];
	for (int i = 0; i < n; i++) { cin >> post[i]; }
	for (int i = 0; i < n; i++) { cin >> in[i]; }
	tree T = getTree(in, n);
	levelOrder(T);
	return 0;
}
```
