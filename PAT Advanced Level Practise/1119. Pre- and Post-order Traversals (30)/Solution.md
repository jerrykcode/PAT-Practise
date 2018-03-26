# 1119. Pre- and Post-order Traversals (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1119)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Special 

* 作者 CHEN, Yue



Suppose that all the keys in a binary tree are distinct positive integers. A unique binary tree can be determined by a given pair of postorder and inorder traversal sequences, or preorder and inorder traversal sequences. However, if only the postorder and preorder traversal sequences are given, the corresponding tree may no longer be unique.

Now given a pair of postorder and preorder traversal sequences, you are supposed to output the corresponding inorder traversal sequence of the tree. If the tree is not unique, simply output any one of them.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=30), the total number of nodes in the binary tree. The second line gives the preorder sequence and the third line gives the postorder sequence. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, first printf in a line "Yes" if the tree is unique, or "No" if not. Then print in the next line the inorder traversal sequence of the corresponding binary tree. If the solution is not unique, any answer would do. It is guaranteed that at least one solution exists. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

## Sample Input 1:

7  
1 2 3 4 6 7 5  
2 6 7 4 5 3 1  

## Sample Output 1:

Yes  
2 1 6 4 7 3 5  

## Sample Input 2:

4  
1 2 3 4  
2 4 3 1  

## Sample Output 2:

No  
2 1 3 4  

## 题意：

给出树的前序遍历与后序遍历结果，判断是否可以确定唯一的树，若可以则输出"Yes"以及中序遍历结果，否则输出"No"与不确定的树中任意一颗的中序遍历。

## 思路：

本题中前序后序转中序参考了[1119. Pre- and Post-order Traversals (柳婼 の blog)](https://www.liuchuo.net/archives/2484)。

前序的第0个元素与后序的最后一个应该是相同的，是树的根，而后序的最后一个的前面一个，是右子树的根，或者是在右子树不存在的情况下，左子树的根。找到后序最后一个前面的一个在前序中的位置，若在根的后面一个位置，则有可能是无右子树的情况下，左子树的根，也可能是无左子树情况下右子树的根。这时无法确定唯一的树，但只需输出任何一种，所以这里假设是右子树的根。若后序最后一个前面的一个在前序中的位置与根之间还有其他很多元素，则可以确定是右子树的根，划分左、右子树后递归求解。

## 参考：

[1119. Pre- and Post-order Traversals (柳婼 の blog)](https://www.liuchuo.net/archives/2484)


## 代码：

[1119. Pre- and Post-order Traversals(30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1119.%20Pre-%20and%20Post-order%20Traversals%20(30)/1119.%20Pre-%20and%20Post-order%20Traversals%20(30).cpp)

```cpp
#include <iostream>
using namespace std;

int *pre, *post, unique = 1;

typedef struct node {
	int data;
	node *left, *right;
} *tree;

tree getTree(int preLeft, int preRight, int postLeft,int postRight)
{
	if (preLeft > preRight)
		return NULL;
	tree T = new node;
	T->data = pre[preLeft];
	int left = preLeft + 1, right = left;
	for (int i = left; i <= preRight && pre[i] != post[postRight - 1]; i++)
		right++;
	if (right == left && preLeft != preRight)
		unique = 0;
	T->left = getTree(left, right - 1, postLeft, postLeft + right - left - 1);
	T->right = getTree(right, preRight, postRight - (preRight - right + 1), postRight - 1);
	return T;
}

void in(tree T)
{
	if (T->left) {
		in(T->left);
		putchar(' ');
	}
	printf("%d", T->data);
	if (T->right) {
		putchar(' ');
		in(T->right);
	}
}

int main()
{
	int n;
	cin >> n;
	pre = new int[n], post = new int[n];
	for (int i = 0; i < n; i++)cin >> pre[i];
	for (int i = 0; i < n; i++)cin >> post[i];
	tree T = getTree(0, n - 1, 0, n - 1);
	cout << (unique?"Yes":"No") << endl;
	in(T);
	cout << endl;
    return 0;
}
```