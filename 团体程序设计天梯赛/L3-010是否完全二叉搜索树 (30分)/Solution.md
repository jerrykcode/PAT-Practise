# L3-010 是否完全二叉搜索树 （30 分）
[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805049870368768)

> 作者: 陈越

> 单位: 浙江大学

> 时间限制: 400 ms

> 内存限制: 64 MB

> 代码长度限制: 16 KB


将一系列给定数字顺序插入一个初始为空的二叉搜索树（定义为左子树键值大，右子树键值小），你需要判断最后的树是否一棵完全二叉树，并且给出其层序遍历的结果。

## 输入格式：

输入第一行给出一个不超过20的正整数N；第二行给出N个互不相同的正整数，其间以空格分隔。

## 输出格式：

将输入的N个正整数顺序插入一个初始为空的二叉搜索树。在第一行中输出结果树的层序遍历结果，数字间以1个空格分隔，行的首尾不得有多余空格。第二行输出YES，如果该树是完全二叉树；否则输出NO。

## 输入样例1：
9  
38 45 42 24 58 30 67 12 51  


## 输出样例1：
38 45 24 58 42 30 12 67 51  
YES  


## 输入样例2：
8  
38 24 12 45 58 67 42 51  


## 输出样例2：
38 45 24 58 42 12 67 51  
NO  


## 思路

插入元素，构建BST，BFS层序遍历，同时判断是否为完全二叉树。在树结点中使用成员id，表示若树为完全二叉树，则该结点在层序遍历数组中的下标(0~n - 1)，即
```
t->left->id = (t->id) * 2 + 1; 
t->right->id = (t->id) * 2 + 2;
```

不是完全二叉树等介于存在树结点的id  > n - 1，n为结点数。


## 代码code

[L3-010 是否完全二叉搜索树 （30 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-010%E6%98%AF%E5%90%A6%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%20(30%E5%88%86)/L3-010%20%E6%98%AF%E5%90%A6%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)

```cpp
#include <iostream>
#include <queue>
using namespace std;

typedef unsigned char BYTE;
typedef struct TNode {
	int val;
	BYTE id;
	struct TNode *left, *right;
	TNode (int val) : val(val), id(0), left(NULL), right(NULL) {}
} *Tree;
typedef Tree BST;

BST insert(BST tree, int val) {
	if (tree == NULL) {
		return new TNode(val);
	}
	if (val > tree->val)
		tree->left = insert(tree->left, val);
	else
		tree->right = insert(tree->right, val);
	return tree;
}

//用id表示若树为完全二叉树，则该结点在层序遍历数组中的下标，即
//t->left->id = (t->id) * 2 + 1; t->right->id = (t->id) * 2 + 2;
//存在 id  > n - 1 <=> 不是完全二叉树
void bfs(Tree tree, int n) {
	if (tree == NULL) return;
	bool isComplete = true;
	queue<Tree> q;
	q.push(tree);
	cout << tree->val;
	while (!q.empty()) {
		Tree t = q.front();
		q.pop();
		if (t->left != NULL) {
			q.push(t->left);
			cout << " " << t->left->val;			
			if (isComplete && (t->left->id = (t->id) * 2 + 1) > n - 1) isComplete = false;
		}
		if (t->right != NULL) {
			q.push(t->right);
			cout << " " << t->right->val;
			if (isComplete && (t->right->id = (t->id) * 2 + 2) > n - 1) isComplete = false;
		}
	}
	cout << endl;
	cout << (isComplete ? "YES" : "NO");
}

int main() {
	int n;
	cin >> n;
	BST tree = NULL;
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		tree = insert(tree, val);
	}
	bfs(tree, n);
	return 0;
}
```

