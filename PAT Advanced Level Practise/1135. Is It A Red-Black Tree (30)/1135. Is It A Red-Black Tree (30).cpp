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