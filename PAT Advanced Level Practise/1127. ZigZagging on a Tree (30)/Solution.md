# 1127. ZigZagging on a Tree (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1127)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Suppose that all the keys in a binary tree are distinct positive integers. A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences. And it is a simple standard routine to print the numbers in level-order. However, if you think the problem is too simple, then you are too naive. This time you are supposed to print the numbers in *"zigzagging order"* -- that is, starting from the root, print the numbers level-by-level, alternating between left to right and right to left. For example, for the following tree you must output: 1 11 5 8 17 12 20 15.

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1127.jpg)

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<= 30), the total number of nodes in the binary tree. The second line gives the inorder sequence and the third line gives the postorder sequence. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, print the zigzagging sequence of the tree in a line. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.
## Sample Input:  
8  
12 11 20 17 1 15 8 5  
12 20 17 11 15 8 5 1  

## Sample Output:  
1 11 5 8 17 12 20 15  

## 题意：

输入一颗二叉树的结点数，中序遍历结果与后序遍历结果，求 *"zigzagging order"* 遍历，即第1层结点从左到右输出，第2层结点从右到左输出（根在第0层），交替地从左到右、从右到左输出每一层结点。

## 思路：


* 通过中序、后序建树：后序遍历的最后一个元素是根结点，根据根在中序遍历中的位置分割出右子树与左子树，递归求解。

* 对树 *"zigzagging order"* 遍历：BFS分层遍历（用last记录最后进队列的结点，tail记录一层的最后一个结点，初始化为根；当一个出队列的结点是tail时，则上一层的所有结点都已出队列，说明一层已结束，tail更新为last，是本层最后一个结点，进入下一层），每一层的结点存储在一个vector中，一层结束后根据层数的奇偶，确定是从左到右还是从右到左输出这一层的结点（vector中的元素）。


## 代码：

[1127. ZigZagging on a Tree (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1127.%20ZigZagging%20on%20a%20Tree%20(30)/1127.%20ZigZagging%20on%20a%20Tree%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>
#include <vector>

int *inOrder;
int *postOrder;
int rootIndex;

typedef struct node {
	int data;
	node *left, *right;
} *tree;

tree getTree(int l, int r)
{
	if (l > r) return NULL;
	int rootData = postOrder[rootIndex--];
	int index = -1;
	for (int i = l; i <= r; i ++)
		if (inOrder[i] == rootData) {
			index = i;
			break;
		}
	tree T = new node;
	T->data = rootData;
	T->right = getTree(index + 1, r);
	T->left = getTree(l, index - 1);
	return T;
}

void bfs(tree T)
{
	queue<tree> q;
	tree tail, last;
	q.push(T);
	tail = T;
	last = T;
	vector<tree> level;
	int count = 0;
	while (!q.empty()) {
		tree t = q.front();
		q.pop();
		level.push_back(t);
		if (t->left != NULL) {
			q.push(t->left);
			last = t->left;
		}
		if (t->right != NULL) {
			q.push(t->right);
			last = t->right;
		}
		if (t == tail) {
			if (t == T) 
				cout << t->data;
			else if (count % 2 == 0) {
				for (int i = level.size() - 1; i >= 0; i--)
					printf(" %d", level[i]->data);
			}
			else {
				for (int i = 0; i < level.size(); i++)
					printf(" %d", level[i]->data);
			}
			level.clear();
			count++;
			tail = last;
		}
	}
}

int main()
{
	int n;
	cin >> n;
	inOrder = new int[n];
	postOrder = new int[n];
	for (int i = 0; i < n; i++) cin >> inOrder[i];
	for (int i = 0; i < n; i++) cin >> postOrder[i];
	rootIndex = n - 1;
	tree T = getTree(0, n - 1);
	bfs(T);
    return 0;
}
```