#1064. Complete Binary Search Tree (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1064)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

•The left subtree of a node contains only nodes with keys less than the node's key. 
•The right subtree of a node contains only nodes with keys greater than or equal to the node's key. 
•Both the left and right subtrees must also be binary search trees. 

A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom 
level, which is filled from left to right.

Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required 
that the tree must also be a CBT. You are supposed to output the level order traversal sequence of this BST.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<=1000). 
Then N distinct non-negative integer keys are given in the next line. All the numbers in a line are separated 
by a space and are no greater than 2000.



## Output Specification: 

For each test case, print in one line the level order traversal sequence of the corresponding complete binary 
search tree. All the numbers in a line must be separated by a space, and there must be no extra space at the 
end of the line. 



## Sample Input:

10  
1 2 3 4 5 6 7 8 9 0  

## Sample Output:

6 3 8 1 5 7 9 0 2 4  


## 题意：

输入一个整数序列，这是一颗既是完全二叉树，亦是二叉搜索树的树的结点，求此二叉树的层序遍历

## 思路：

首先对序列非递减排序，只要知道左子树有多少结点，就可确定根结点的在序列中的位置，再对左、右递归求解

设二叉树最后一层的结点数为x，层数为h + 1，总结点数(已知)为n，则h = [log2(n + 1)]，x = min{n + 1 - 2^h，2^(h - 1)}，
左子树的结点数为2^(h - 1) - 1 + x

## 代码：

[Complete Binary Search Tree (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1064.%20Complete%20Binary%20Search%20Tree%20(30)/1064.%20Complete%20Binary%20Search%20Tree%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

int *input;
int *tree;

void getTree(int left, int right, int root)
{
	int n = right - left + 1;
	if (n == 0) return;
	int h = log(n + 1)/log(2);
	int x = n + 1 - pow(2, h);
	x = x < pow(2, h - 1) ? x : pow(2, h - 1);
	int leftNumber = pow(2, h - 1) - 1 + x;
	tree[root] = input[left + leftNumber];
	getTree(left, left + leftNumber - 1, root * 2 + 1);
	getTree(left + leftNumber + 1, right, root * 2 + 2);
}

int main()
{
	int n;
	cin >> n;
	input = new int[n];
	tree = new int[n];
	for (int i = 0; i < n; i++)
		cin >> input[i];
	sort(input, input + n);
	getTree(0, n - 1, 0);
	for (int i = 0; i < n; i++) {
		if (i != 0) putchar(' ');
		cout << tree[i];
	}
	return 0;
}
```