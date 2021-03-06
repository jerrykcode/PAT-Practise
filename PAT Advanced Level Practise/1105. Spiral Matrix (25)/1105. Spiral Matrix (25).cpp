// 1105. Spiral Matrix (25).cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

bool compare(int a, int b)
{
	return a > b;
}

int **fill_matrix(int *numbers, int m, int n)
{
	int **matrix = new int*[m];
	for (int i = 0; i < m; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++)
			matrix[i][j] = -1;
	}
	int i = 0, j = 0, flag = 0;
	for (int k = 0; k < m*n; k++) {
		matrix[i][j] = numbers[k];
		if (flag) {
			if (i - 1 >= 0 && matrix[i - 1][j] == -1) {
				i--;
				continue;
			}
			else flag = 0;
		}
		if (j + 1 < n && matrix[i][j + 1] == -1)
			j++;
		else if (i + 1 < m && matrix[i + 1][j] == -1)
			i++;
		else if (j - 1 >= 0 && matrix[i][j - 1] == -1)
			j--;
		else {
			i--;
			flag = 1;
		}
	}
	return matrix;
}

int main()
{
	int N, n, m;
	cin >> N;
	m = N;
	for (n = 1; n <= m; n++)
		if (N % n == 0 && n <= N / n) m = N / n;
	n = N / m;
	int *numbers = new int[N];
	for (int i = 0; i < N; i++) 
		cin >> numbers[i];
	sort(numbers, numbers + N, compare);
	int **matrix = fill_matrix(numbers, m, n);
	for (int i = 0; i < m; i++) 
		for (int j = 0; j < n; j++) {
			if (j != 0)putchar(' ');
			cout << matrix[i][j];
			if (j == n - 1)cout << endl;
		}
    return 0;
}

