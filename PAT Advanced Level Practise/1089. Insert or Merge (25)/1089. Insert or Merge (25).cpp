// 1089. Insert or Merge (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

void merge(int *a, int *tmpa, int left, int right, int rend)
{
	int lend = right - 1;
	int i = left, j = right, k = left;
	while (i <= lend && j <= rend) {
		if (a[i] < a[j]) tmpa[k++] = a[i++];
		else tmpa[k++] = a[j++];
	}
	while (i <= lend)
		tmpa[k++] = a[i++];
	while (j <= rend)
		tmpa[k++] = a[j++];
}

void mSort(int *list, int n, int len)
{
	int i, *tmp = new int[n];
	for (i = 0; i <= n - 2 * len; i += 2 * len) 
		merge(list, tmp, i, i + len, i + 2 * len - 1);
	if (i + len < n)
		merge(list, tmp, i, i + len, n - 1);
	else
		for (int j = i; j < n; j++) tmp[j] = list[j];
	for (int i = 0; i < n; i++)
		list[i] = tmp[i];
}

void InsertionSort(int *list, int k)
{
	int i, tmp = list[k];
	for (i = k - 1; i >= 0; i--) 
		if (list[i] > tmp)
			list[i + 1] = list[i];
		else break;
	list[i + 1] = tmp;
}

int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	int *sorted = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];
	for (int i = 0; i < n; i++)
		cin >> sorted[i];
	int tmp = 0;
	for (int i = 0; i < n - 1; i++)
		if (sorted[i] > sorted[i + 1]) {
			tmp = i + 1;
			break;
		}
	for (int i = tmp; i < n; i++)
		if (list[i] != sorted[i]) {
			printf("Merge Sort\n");
			int len;
			for (len = 2; len <= n; len *= 2) {
				for (int k = len - 1; k < n - 1; k += 2 * len)
					if (sorted[k] > sorted[k + 1]) {
						mSort(sorted, n, len);
						goto PRINT;
					}
			}
			goto PRINT;
		}
	printf("Insertion Sort\n");
	InsertionSort(sorted, tmp);
PRINT: {
	for (int i = 0; i < n; i++) {
		if (i != 0) putchar(' ');
		cout << sorted[i];
	}
	}
	return 0;
}

