# L2-006 树的遍历 （25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805069361299456)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

给定一棵二叉树的后序遍历和中序遍历，请你输出其层序遍历的序列。这里假设键值都是互不相等的正整数。

## 输入格式：

输入第一行给出一个正整数N（≤30），是二叉树中结点的个数。第二行给出其后序遍历序列。第三行给出其中序遍历序列。数字间以空格分隔。

##　输出格式：

在一行中输出该树的层序遍历的序列。数字间以1个空格分隔，行首尾不得有多余空格。

## 输入样例：

> 7  
> 2 3 1 5 7 6 4  
> 1 2 3 4 5 6 7  


## 输出样例：

> 4 1 6 3 5 7 2  

## 思路

根据inorder和postorder建树，再bfs层序遍历

## 代码

```cpp
#include <iostream>
#include <queue>
using  namespace std;

typedef struct TNode {
	int val;
	struct TNode *left;
	struct TNode *right;
	TNode(int val) : val(val), left(NULL), right(NULL) {}
} *Tree;

Tree createTree(int *inorder, int inStart, int inEnd, int *postorder, int postStart, int postEnd) {
	if (inStart > inEnd) return NULL;	
	int root = postorder[postEnd];
	Tree t = new TNode(root);
	int root_idx;
	for (root_idx = inStart; root_idx < inEnd; root_idx++)
		if (inorder[root_idx] == root) break;
	int leftSize = root_idx - inStart;
	t->left = createTree(inorder, inStart, root_idx - 1, postorder, postStart, postStart + leftSize - 1);
	t->right = createTree(inorder, root_idx + 1, inEnd, postorder, postStart + leftSize, postEnd - 1);
	return t;
}

void bfs(Tree t) {
	if (t == NULL) return;
	queue<Tree> q;
	q.push(t);
	cout << t->val;
	while (!q.empty()) {
		Tree tree = q.front();
		q.pop();
		if (tree->left != NULL) {
			q.push(tree->left);
			cout << " " << tree->left->val;
		}	
		if (tree->right != NULL) {
			q.push(tree->right);
			cout << " " << tree->right->val;
		}
	}
	cout << endl;
}

int main()
{
	int n;
	cin >> n;
	int *inorder = new int[n];
	int *postorder = new int[n];
	for (int i = 0; i < n; i++)
		cin >> postorder[i];
	for (int i = 0; i < n; i++)
		cin >> inorder[i];
	Tree t = createTree(inorder, 0, n - 1, postorder, 0, n - 1);
	bfs(t);
	return 0;
}
```
