#include <iostream>
using namespace std;
#include <vector>

typedef struct node
{
	int data;
	node *left, *right;
} *tree;

tree getTree(int *pre, int start, int end)
{
	if (start > end) return NULL;
	int root = pre[start];
	int left = start + 1;
	int right = left;
	for (int i = left; i <= end; i++)
	{
		if (pre[i] < root) right++;
	}
	tree T = new node;
	T->data = root;
	T->left = getTree(pre, left, right - 1);
	T->right = getTree(pre, right, end);
	return T;
}

vector<int>path;
void findPath(tree T, int v)
{
	if (T == NULL)
	{
		path.clear(); //empty vector means error
		return;
	}
	path.push_back(T->data);
	if (v == T->data)
		return;
	else if (v < T->data)
		findPath(T->left, v);
	else
		findPath(T->right, v);
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int m, n;
	cin >> m >> n;
	int *pre = new int[n];
	for (int i = 0; i < n; i++)
		cin >> pre[i];
	tree T = getTree(pre, 0, n - 1);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		vector<int> u_path, v_path;
		path.clear();
		findPath(T, u);
		u_path = path;
		path.clear();
		findPath(T, v);
		v_path = path;
		if (v_path.size() == 0 && u_path.size() == 0)
			printf("ERROR: %d and %d are not found.\n", u, v);
		else if (u_path.size() == 0)
			printf("ERROR: %d is not found.\n", u);
		else if (v_path.size() == 0)
			printf("ERROR: %d is not found.\n", v);
		else {
			int i;
			for (i = 0; i < min(u_path.size(), v_path.size()); i++)
				if (u_path[i] != v_path[i]) break;
			int lca = u_path[i - 1];
			if (lca == u)
			{
				printf("%d is an ancestor of %d.\n", u, v);
			}
			else if (lca == v)
			{
				printf("%d is an ancestor of %d.\n", v, u);
			}
			else
			{
				printf("LCA of %d and %d is %d.\n", u, v, lca);
			}
		}
	}
	return 0;
}