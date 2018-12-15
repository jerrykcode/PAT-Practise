#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int root_idx;
	int left_start, left_end;
	int right_start, right_end;
	node *left;
	node *right;
} *Tree;

int *in;
int *pre;

Tree getTree(int in_start, int in_end, int pre_start) {
	if (in_start > in_end) return NULL;
	Tree t = new node;
	int root = pre[pre_start];
	for (int i = in_start; i <= in_end; i++)
		if (in[i] == root) {
			t->root_idx = i;
			t->left_start = in_start;
			t->left_end = i - 1;
			t->right_start = i + 1;
			t->right_end = in_end;
			break;
		}
	int left_len = t->left_end - t->left_start + 1;
	t->left = getTree(t->left_start, t->left_end, pre_start + 1);
	t->right = getTree(t->right_start, t->right_end, pre_start + left_len + 1);
	return t;
}

int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	in = new int[n];
	pre = new int[n];
	for (int i = 0; i < n; i++)
		scanf("%d", in + i);
	for (int i = 0; i < n; i++)
		scanf("%d", pre + i);
	Tree t = getTree(0, n - 1, 0);
	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		int u_idx  = -1, v_idx = -1;
		for (int j = 0; j < n; j++) {
			if (in[j] == u) u_idx = j;
			if (in[j] == v) v_idx = j;
		}
		if (u_idx == -1 && v_idx == -1) {
			printf("ERROR: %d and %d are not found.\n", u, v);
		} else if (u_idx == -1) {
			printf("ERROR: %d is not found.\n", u);
		} else if (v_idx == -1) {
			printf("ERROR: %d is not found.\n", v);
		} else {
			Tree tmp = t;
			while (tmp != NULL) {
				int root = in[tmp->root_idx];
				if (root == u) {
					printf("%d is an ancestor of %d.\n", u, v);
					break;
				}
				else if (root == v) {
					printf("%d is an ancestor of %d.\n", v, u);
					break;
				}
				else {
					bool u_in_left = u_idx >= tmp->left_start && u_idx <= tmp->left_end;
					bool v_in_left = v_idx >= tmp->left_start && v_idx <= tmp->left_end;
					if ((u_in_left && !v_in_left) || (!u_in_left && v_in_left)) {
						printf("LCA of %d and %d is %d.\n", u, v, root);
						break; //while
					} else if (u_in_left && v_in_left) {
						tmp = tmp->left;
					} else {
						tmp = tmp->right;
					}
				}
			}
		}
	}
	free(in);
	free(pre);
	return 0;
}
