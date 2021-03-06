// 1101. Quick Sort (25)_2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];
	int *max = new int[n]; //max[i] is the max number in [list[0], list[i]]
	max[0] = list[0];
	for (int i = 1; i < n; i++)
		max[i] = list[i] > max[i - 1] ? list[i] : max[i - 1];
	int *min = new int[n];
	min[n - 1] = list[n - 1]; //min[i] is the minmum number in [list[i], list[n - 1]]
	for (int i = n - 2; i >= 0; i--)
		min[i] = list[i] < min[i + 1] ? list[i] : min[i + 1];
	vector<int> pivots;
	for (int i = 0; i < n; i++) {
		if (i == 0 || list[i] > max[i - 1]) {
			if ( i == n - 1 || list[i] < min[i + 1])
				pivots.push_back(list[i]);
		}
	}
	cout << pivots.size() << endl;
	for (auto it = pivots.begin(); it != pivots.end(); it++) {
		if (it != pivots.begin()) putchar(' ');
		printf("%d", *it);
	}
	cout << endl;
    return 0;
}

