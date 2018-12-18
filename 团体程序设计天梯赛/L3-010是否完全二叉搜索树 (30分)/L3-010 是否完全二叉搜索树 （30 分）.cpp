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
