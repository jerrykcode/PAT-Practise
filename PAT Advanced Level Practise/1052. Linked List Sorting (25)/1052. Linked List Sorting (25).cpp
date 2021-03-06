// 1052. Linked List Sorting (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

struct node {
	int ad, key, next;
};

bool compare(node a, node b)
{
	return a.key < b.key;
}

int main()
{
	node memory[100000];
	int n, head_ad, flag = 0;
	cin >> n >> head_ad;
	vector<node> list;
	for (int i = 0; i < n; i++) {
		int ad, key, next;
		cin >> ad >> key >> next;
		if (ad == head_ad) flag = 1;
		memory[ad] = { ad, key, next };
	}
	if (flag == 0) {
		printf("0 -1\n");
		return 0;
	}
	int ad = head_ad;
	while (ad != -1) {
		list.push_back(memory[ad]);
		ad = memory[ad].next;
	}
	sort(list.begin(), list.end(), compare);
	printf("%d %05d\n", list.size(), list[0].ad);
	for (int i = 0; i < list.size(); i++) {
		printf("%05d %d ", list[i].ad, list[i].key);
		if (i + 1 < list.size()) printf("%05d\n", list[i + 1].ad);
		else printf("-1\n");
	}
    return 0;
}

