#include <iostream>
using namespace std;
#include <vector>
#include <math.h>

int max_height = 0, n_max = 0;

void dfs(vector<int> *tree, int t, int count)
{
	if (tree[t].size() == 0) {
		if (count > max_height) {
			max_height = count;
			n_max = 1;
		}
		else if (count == max_height)
			n_max++;
		return;
	}
	for (auto it = tree[t].begin(); it != tree[t].end(); it++)
		dfs(tree, *it, count + 1);
}

int  main()
{
	int n, root;
	double p, r;
	cin >> n >> p >> r;
	vector<int> * tree = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		if (t == -1) root = i;
		else tree[t].push_back(i);
	}
	dfs(tree, root, 0);
	printf("%.2f %d\n", p * pow((1 + r/100), max_height), n_max);
	return 0;
}