# 1043. Is It a Binary Search Tree (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1043)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

* The left subtree of a node contains only nodes with keys less than the node's key. 
* The right subtree of a node contains only nodes with keys greater than or equal to the node's key. 
* Both the left and right subtrees must also be binary search trees. 

If we swap the left and right subtrees of every node, then the resulting tree is called the Mirror Image 
of a BST.

Now given a sequence of integer keys, you are supposed to tell if it is the preorder traversal sequence 
of a BST or the mirror image of a BST.




## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<=1000). 
Then N integer keys are given in the next line. All the numbers in a line are separated by a space.




## Output Specification: 

For each test case, first print in a line "YES" if the sequence is the preorder traversal sequence of a 
BST or the mirror image of a BST, or "NO" if not. Then if the answer is "YES", print in the next line the 
postorder traversal sequence of that tree. All the numbers in a line must be separated by a space, and 
there must be no extra space at the end of the line. 



## Sample Input 1:

7  
8 6 5 7 10 8 11  

## Sample Output 1:  

YES  
5 7 6 8 11 10 8  



## Sample Input 2:  

7  
8 10 11 8 6 7 5  

## Sample Output 2:  

YES  
11 8 10 7 5 6 8  



## Sample Input 3:   

7  
8 6 8 5 10 9 11  

## Sample Output 3:  
NO  


## 题意：

输入二叉树的结点个数与前序遍历结果，若是二叉搜索树(BST)，或BST的镜像(镜像即每个非叶子结点的左、右
子树交换)，则输出"YES"以及后序遍历结果，否则输出"NO"

## 思路：

前序遍历的第一个值即根，若是BST，则前序遍历结果中第一个大于等于根的即为右子树的根，右子树的根往后，若有
小于根的值，则肯定不是BST，若没有则递归判断左、右子树是否为BST  

若不是BST，判断是否为BST的镜像，所谓镜像，就是左子树的所有结点大于等于根，右子树的所有结点小于根，与判断
是否为BST的方法类似，只不过前序遍历结果中第一个小于根的为右子树的根，判断条件相反。

判断是否为BST和是否为BST的镜像可写在一个函数内，用参数flag来判定判断条件

后序遍历也是根据flag(BST或BST的镜像)，先确定右子树的根，递归左、右子树，最后输出根


## 代码：
[1043. Is It a Binary Search Tree (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1043.%20Is%20It%20a%20Binary%20Search%20Tree%20(25)/1043.%20Is%20It%20a%20Binary%20Search%20Tree%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

bool isBST(int *tree, int start, int end, int flag)
{	/* flag == 1则判断是否为BST，flag == 0则判断是否为BST的镜像 */
	if (start >= end)
		return true;
	int root = tree[start];
	int left = start + 1, right = left;
	for (int i = start + 1; i <= end; i++)
		if (flag ? tree[i] < root : tree[i] >= root)
			right++;
	for (int i = right; i <= end; i++)
		if (flag ? tree[i] < root : tree[i] >= root)
			return false;
	return isBST(tree, left, right - 1, flag) && isBST(tree, right, end, flag);
}

int first = 1;
void postTraversal(int *tree, int start, int end, int flag)
{
	if (start == end) {
		if (!first) 
			putchar(' ');
		first = 0;
		printf("%d", tree[start]);
		return;
	}
	if (start > end)
		return;
	int root = tree[start];
	int left = start + 1, right = left;
	for (int i = start + 1; i <= end; i++)
		if (flag ? tree[i] < root : tree[i] >= root)
			right++;
	postTraversal(tree, left, right - 1, flag);
	postTraversal(tree, right, end, flag);
	if (!first)
		putchar(' ');
	first = 0;
	printf("%d", root);
}

int main()
{
	int n;
	cin >> n;
	int *tree = new int[n];
	for (int i = 0; i < n; i++)
		cin >> tree[i];
	if (isBST(tree, 0, n - 1, 1)) {
		cout << "YES" << endl;
		postTraversal(tree, 0, n - 1, 1);
	}
	else if (isBST(tree, 0, n - 1, 0)) {
		cout << "YES" << endl;
		postTraversal(tree, 0, n - 1, 0);
	}
	else
		cout << "NO" << endl;
    return 0;
}
```
