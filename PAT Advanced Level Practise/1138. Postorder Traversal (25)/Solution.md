# 1138. Postorder Traversal (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1138)
* 时间限制 600 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue

Suppose that all the keys in a binary tree are distinct positive integers. Given the preorder and inorder traversal sequences, you are supposed to output the first number of the postorder traversal sequence of the corresponding binary tree. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=50000), the total number of nodes in the binary tree. The second line gives the preorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, print in one line the first number of the postorder traversal sequence of the corresponding binary tree. 

## Sample Input:

7
1 2 3 4 5 6 7  
2 3 1 5 4 7 6  

## Sample Output:

3

## 题意与思路：

二叉树前序、中序转后序

## 代码：

[1138. Postorder Traversal (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1138.%20Postorder%20Traversal%20(25)/1138.%20Postorder%20Traversal%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

typedef struct node {
	int data;
	node * left, *right;
} *tree;

int *pre, *in, index = 0;
tree getTree(int l, int r, int root)
{
	int rootIndex;
	for (int i = l; i <= r; i ++)
		if (in[i] == root) {
			rootIndex = i;
			break;
		}
	tree T = new node;
	T->data = root;
	if (l <= rootIndex - 1)
		T->left = getTree(l, rootIndex - 1, pre[++index]);
	else T->left = NULL;
	if (rootIndex + 1 <= r)
		T->right = getTree(rootIndex + 1, r, pre[++index]);
	else T->right = NULL;
	return T;
}

int flag = 0;
void post(tree T)
{
	if (T->left != NULL)
		post(T->left);
	if (T->right != NULL)
		post(T->right);
	if (flag == 0) {
		printf("%d\n", T->data);
		flag = 1;
	}
	else return;
}

int main()
{
	int n;
	cin >> n;
	pre = new int[n];
	int data;
	for (int i = 0; i < n; i++)
		cin >> pre[i];
	in = new int[n];
	for (int i = 0; i < n; i++)
		cin >> in[i];
	tree T = getTree(0, n - 1, pre[0]);
	post(T);
    return 0;
}
```