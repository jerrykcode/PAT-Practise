// 1117. Eddington Number(25)_2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

bool compare(int a, int b)
{
	return a > b;
}

int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];
	sort(list, list + n, compare);
	int e = (n < list[0] - 1) ? n : list[0] - 1;
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (list[i] > e)
			count++;
		else {
			if (count >= e) {
				printf("%d\n", e);
				return 0;
			}
			else {
				e--;
				i--;
			}
		}
	}
	printf("%d\n", e);
    return 0;
}

