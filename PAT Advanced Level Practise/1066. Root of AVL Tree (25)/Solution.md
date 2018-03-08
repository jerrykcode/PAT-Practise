# 1066. Root of AVL Tree (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1066)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



An AVL tree is a self-balancing binary search tree. In an AVL tree, the heights of the two child 
subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing 
is done to restore this property. Figures 1-4 illustrate the rotation rules.

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1066_1.jpg)
*Figure 1*

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1066_2.jpg)
*Figure 2*
		
![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1066_3.jpg)
*Figure 3*
		
![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1066_4.jpg)
*Figure 4*

Now given a sequence of insertions, you are supposed to tell the root of the resulting AVL tree.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<=20) 
which is the total number of keys to be inserted. Then N distinct integer keys are given in the next line. 
All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, print the root of the resulting AVL tree in one line.



## Sample Input 1:

5  
88 70 61 96 120  

## Sample Output 1:

70  


## Sample Input 2:

7  
88 70 61 96 120 90 65  
 
## Sample Output 2:

88  


## 题意：

输入N个结点的值，求他们构成的AVL树的根结点的值

## 思路：

[AVL树的插入操作](https://github.com/jerrykcode/Data-Structure/blob/master/Tree/AVL_Tree.cpp)

## 代码：

[1066. Root of AVL Tree (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1066.%20Root%20of%20AVL%20Tree%20(25)/1066.%20Root%20of%20AVL%20Tree%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

typedef struct AvlNode {
	int data;
	struct AvlNode * left, * right;
	int height;
} *AvlTree;

int max(int a, int b)
{
	return a > b ? a : b;
}

int getHeight(AvlTree avlt)
{
	if (!avlt)
		return 0;
	return max(getHeight(avlt->left), getHeight(avlt->right)) + 1;
}

AvlTree ll(AvlTree avlt)
{	/* 左单旋 */
	AvlTree b = avlt->left;
	avlt->left = b->right;
	b->right = avlt;
	avlt->height = getHeight(avlt);
	b->height = getHeight(b);
	return b;
}

AvlTree rr(AvlTree avlt)
{	/* 右单旋 */
	AvlTree b = avlt->right;
	avlt->right = b->left;
	b->left = avlt;
	avlt->height = getHeight(avlt);
	b->height = getHeight(b);
	return b;
}

AvlTree lr(AvlTree avlt)
{	/* 左右双旋 */
	avlt->left = rr(avlt->left);
	return ll(avlt);
}

AvlTree rl(AvlTree avlt)
{	/* 右左双旋 */
	avlt->right = ll(avlt->right);
	return rr(avlt);
}

AvlTree insert(AvlTree avlt, int element)
{	/* 插入结点 */
	if (!avlt) { //不存在，创建并返回结点
		avlt = new struct AvlNode;
		avlt->data = element;
		avlt->height = 0;
		avlt->left = avlt->right = NULL;
		return avlt;
	}
	if (element < avlt->data) { //插在左子树上
		avlt->left = insert(avlt->left, element);
		if (getHeight(avlt->left) - getHeight(avlt->right) >= 2) { //不平衡
			if (element < avlt->left->data) //不平衡发生在左子树的左子树上
				avlt = ll(avlt); //左单旋
			else //不平衡发生在左子树的右子树上
				avlt = lr(avlt); //左右双旋
		}
	}
	else if (element > avlt->data) { //插在右子树上
		avlt->right = insert(avlt->right, element);
		if (getHeight(avlt->left) - getHeight(avlt->right) <= -2) { //不平衡
			if (element < avlt->right->data) //不平衡发生在右子树的左子树上
				avlt = rl(avlt); //右左双旋
			else //不平衡发生在右子树的右子树上
				avlt = rr(avlt);
		}
	}
	avlt->height = getHeight(avlt);
	return avlt;
}

int main()
{
	int n;
	cin >> n;
	AvlTree avlt = NULL;
	for (int i = 0; i < n; i++) {
		int element;
		cin >> element;
		avlt = insert(avlt, element);
	}
	cout << avlt->data;
    return 0;
}
```

