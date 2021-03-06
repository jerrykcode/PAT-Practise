// 1107. Social Clusters (30).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int *S;

int findRoot(int x)
{
	if (S[x] < 0)
		return x;
	return S[x] = findRoot(S[x]);
}

void unionSets(int x1, int x2)
{
	int root1 = findRoot(x1);
	int root2 = findRoot(x2);
	if (root1 == root2) return;
	if (S[root1] > S[root2]) {
		S[root2] += S[root1];
		S[root1] = root2;
	}
	else {
		S[root1] += S[root2];
		S[root2] = root1;
	}
}

int main()
{
	int n;
	cin >> n;
	S = new int[n + 1];
	int hobbies[1001] = { 0 };
	fill(S, S + n + 1, -1);
	for (int i = 1; i <= n; i++) {
		int k, h;
		scanf("%d:", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &h);
			if (hobbies[h] > 0)
				unionSets(i, hobbies[h]);
			hobbies[h] = i;
		}
	}
	vector<int> clusters;
	for (int i = 1; i <= n; i++) 
		if (S[i] < 0) clusters.push_back(S[i]);
	sort(clusters.begin(), clusters.end());
	printf("%d\n", clusters.size());
	for (auto it = clusters.begin(); it != clusters.end(); it++) {
		if (it != clusters.begin()) putchar(' ');
		printf("%d", -1*(*it));
	}
    return 0;
}

