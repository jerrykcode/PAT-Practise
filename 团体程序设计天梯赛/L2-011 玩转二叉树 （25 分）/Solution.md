# L2-011 玩转二叉树 （25 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805065406070784)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 400 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  


给定一棵二叉树的中序遍历和前序遍历，请你先将树做个镜面反转，再输出反转后的层序遍历的序列。所谓镜面反转，是指将所有非叶结点的左右孩子对换。这里假设键值都是互不相等的正整数。

## 输入格式：

输入第一行给出一个正整数N（≤30），是二叉树中结点的个数。第二行给出其中序遍历序列。第三行给出其前序遍历序列。数字间以空格分隔。

## 输出格式：

在一行中输出该树反转后的层序遍历的序列。数字间以1个空格分隔，行首尾不得有多余空格。

## 输入样例：

> 7  
> 1 2 3 4 5 6 7  
> 4 1 3 2 6 5 7  


##输出样例：

> 4 6 1 7 5 3 2

## 思路

首先根据preorder和inorder建树，再BFS层序遍历。镜像即左右子树对换，故BFS时，对出队列的元素，先将其右子树进队，再将其左子树进队即可。

## 代码

[L2-011 玩转二叉树 （25 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L2-011%20%E7%8E%A9%E8%BD%AC%E4%BA%8C%E5%8F%89%E6%A0%91%20%EF%BC%8825%20%E5%88%86%EF%BC%89/L2-011%20%E7%8E%A9%E8%BD%AC%E4%BA%8C%E5%8F%89%E6%A0%91%20%EF%BC%8825%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <queue>
using namespace std;

typedef struct TNode {
	int val;
	struct TNode *left;
	struct TNode *right;
	TNode(int val) : val(val), left(NULL), right(NULL) {}
} *Tree;

Tree createTree(int *preorder, int preStart, int preEnd, int *inorder, int inStart, int inEnd) {
	if (preStart > preEnd) return NULL;
	int root = preorder[preStart];
	Tree t = new TNode(root);
	int inorderIndex;
	for (inorderIndex = inStart; inorderIndex <= inEnd; inorderIndex++) 
		if (inorder[inorderIndex] == root) break;
	int leftSize = inorderIndex - inStart;
	t->left = createTree(preorder, preStart + 1, preStart + leftSize, inorder, inStart, inorderIndex - 1);
	t->right = createTree(preorder, preStart + leftSize + 1, preEnd, inorder, inorderIndex + 1, inEnd);
	return t;
}

void mirrorImageBFS(Tree t) {
	if (t == NULL) return;
	queue<Tree> q;
	cout << t->val;
	q.push(t);
	while (!q.empty()) {
		Tree tree = q.front();
		q.pop();
		if (tree->right != NULL) {
			cout << " " << tree->right->val;
			q.push(tree->right);
		}
		if (tree->left != NULL) {
			cout << " " << tree->left->val;
			q.push(tree->left);
		}
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	int *inorder = new int[n];
	int *preorder = new int[n];
	for (int i = 0; i < n; i++) cin >> inorder[i];
	for (int i = 0; i < n; i++) cin >> preorder[i];
	Tree t = createTree(preorder, 0, n - 1, inorder, 0, n - 1);
	mirrorImageBFS(t);
	return 0;
}

```
