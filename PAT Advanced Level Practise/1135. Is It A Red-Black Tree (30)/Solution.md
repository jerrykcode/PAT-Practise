# 1135. Is It A Red-Black Tree (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1135)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue

There is a kind of balanced binary search tree named red-black tree in the data structure. It has the following 5 properties:

(1) Every node is either red or black.
(2) The root is black.
(3) Every leaf (NULL) is black.
(4) If a node is red, then both its children are black.
(5) For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

For example, the tree in Figure 1 is a red-black tree, while the ones in Figure 2 and 3 are not.



![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1135_1.jpg)
*Figure 1*

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1135_2.jpg)
*Figure 2*

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1135_3.jpg)
*Figure 3*

For each given binary search tree, you are supposed to tell if it is a legal red-black tree.

## Input Specification:

Each input file contains several test cases. The first line gives a positive integer K (<=30) which is the total number of cases. For each case, the first line gives a positive integer N (<=30), the total number of nodes in the binary tree. The second line gives the preorder traversal sequence of the tree. While all the keys in a tree are positive integers, we use negative signs to represent red nodes. All the numbers in a line are separated by a space. The sample input cases correspond to the trees shown in Figure 1, 2 and 3.

## Output Specification:

For each test case, print in a line "Yes" if the given tree is a red-black tree, or "No" if not.

## Sample Input:

3  
9  
7 -2 1 5 -4 -11 8 14 -15  
9  
11 -2 1 -7 5 -4 8 14 -15  
8  
10 -7 5 -6 8 15 -11 17  

## Sample Output:

Yes  
No  
No  

## 题意：　

输入一颗二叉树的前序遍历结果，判断它是否可能为一颗红黑树。

## 思路： 

假设该树是一颗二叉搜索树BST，则可根据前序遍历数组pre建树：abs(pre[0])为根结点元素，pre(取绝对值)中第一个比根元素大的即为右子树的根，此时递归左、右子树，注意确定右子树的根后，若pre数组(取绝对值)在右子树的根之后有比原树的根小的，则此树不是BST。若不是BST，则一定不是红黑树，若是BST，则建树后，判断是否为红黑树：1、根应为黑，2、dfs遍历时遇到红结点，若它有左右孩子，则其左右孩子必须为黑，到根结点(NULL)时，其经过的黑结点数目应相同。具体算法见代码。

## 代码：

[1135. Is It A Red-Black Tree (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1135.%20Is%20It%20A%20Red-Black%20Tree%20(30)/1135.%20Is%20It%20A%20Red-Black%20Tree%20(30).cpp)

```cpp
#include <iostream>
using namespace std;
#include <queue>
#define RED 0
#define BLACK 1
#define ERROR -1
int n_black_nodes;

typedef struct node {
	int data, color;
	node *left, *right;
} *tree;

tree getTree(int *pre, int start, int end)
{
	if (start > end) return NULL;
	int root = abs(pre[start]);
	tree T = new node;
	T->data = root;
	T->color = pre[start] < 0 ? RED : BLACK;
	int left = start + 1;
	int right = left;
	for (int i = left; i <= end; i++) {
		if (abs(pre[i]) < root)
			right++;
		else break;
	}
	for (int i = right; i <= end; i++)
		if (abs(pre[i]) < root) {
			T->data = ERROR;
			return T;
		}
	T->left = getTree(pre, left, right - 1);
	if (T->left != NULL && T->left->data == ERROR) {
		T->data = ERROR;
		return T;
	}
	T->right = getTree(pre, right, end);
	if (T->right != NULL && T->right->data == ERROR) {
		T->data = ERROR;
		return T;
	}
	return T;
}

bool dfs(tree T, int count)
{
	if (T == NULL) {
		if (n_black_nodes == 0) {
			n_black_nodes = count;
			return true;
		}
		else if (n_black_nodes != count)
			return false;
		else return true;
	}
	if (T->color == BLACK)
		count++;
	else {
		if (T->left != NULL && T->left->color != BLACK) return false;
		if (T->right != NULL && T->right->color != BLACK) return false;
	}
	if (!dfs(T->left, count)) return false;
	if (!dfs(T->right, count)) return false;
	return true;
}

bool isRedBlackTree(tree T)
{
	if (T == NULL) return true;
	if (T->color != BLACK) return false;
	n_black_nodes = 0;
	if (!dfs(T, 0)) return false;
	else return true;
}

int main()
{
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int n;
		cin >> n;
		int *pre = new int[n];
		for (int j = 0; j < n; j++)
			cin >> pre[j];
		tree T = getTree(pre, 0, n - 1);
		if (T->data == ERROR) {
			cout << "No" << endl;
			continue;
		}
		cout << (isRedBlackTree(T) ? "Yes" : "No") << endl;
	}
	return 0;
}
```