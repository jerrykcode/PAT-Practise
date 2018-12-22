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
