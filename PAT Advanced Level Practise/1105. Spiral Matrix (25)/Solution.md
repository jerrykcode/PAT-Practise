# 1105. Spiral Matrix (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1105)

* 时间限制 150 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



This time your job is to fill a sequence of N positive integers into a spiral matrix in non-increasing order. A spiral matrix is filled in from the first element at the upper-left corner, then move in a clockwise spiral. The matrix has m rows and n columns, where m and n satisfy the following: m*n must be equal to N; m>=n; and m-n is the minimum of all the possible values.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N. Then the next line contains N positive integers to be filled into the spiral matrix. All the numbers are no more than 104. The numbers in a line are separated by spaces.

## Output Specification: 

For each test case, output the resulting matrix in m lines, each contains n numbers. There must be exactly 1 space between two adjacent numbers, and no extra space at the end of each line. 

## Sample Input:
12  
37 76 20 98 76 42 53 95 60 81 58 93  

## Sample Output:
98 95 93  
42 37 81  
53 20 76  
58 60 76  

## 题意：


输入正整数N，分解成m\*n形式，要求 m >= n && m - n 最小。输入N个正整数，将它们从大到小“旋转”插入m\*n矩阵中。“旋转”即从矩阵(0, 0)开始，先向右插入元素至最右端，然后向下，然后向左，最后向上，接着再次向右插入元素。输出这个矩阵中的元素。


## 思路：

0、首先求m、n。
```cpp
    for (n = 1; n <= m; n++)
		if (N % n == 0 && n <= N / n) m = N / n;
	n = N / m;
```
n从1开始++递增，若N%n为0，且n <= N/n，则更新m为N/n。


1、对N个正整数从大到小排序。

2、旋转插入矩阵

建立int二维数组matrix[m][n]，元素初始化为-1，i，j从0开始，matrix[i][j]插入元素后，若右边可以插入元素（j + 1 < n &&  matrix[i][j + 1] == -1）则j\+\+向右，否则若向下可以插入元素则i\+\+向下，否则若可以向左则j\-\-向左，若向右、下、左都不行，则i\-\-向上，但在向上的时候不管右边可不可以插入元素都只能向上，故用flag = 1标记这种情况，一直向上到顶，然后flag标记回到0，此时就右可以向右了
```cpp
int i = 0, j = 0, flag = 0;
for (int k = 0; k < m*n; k++) {
	matrix[i][j] = numbers[k]; //numbers存储N个非递增的正整数
	if (flag) { //现在是向上
		if (i - 1 >= 0 && matrix[i - 1][j] == -1) {
			i--; //一直向上
			continue;
		}
		else flag = 0; //已到顶端，flag = 0，可以向右了
	}
	if (j + 1 < n && matrix[i][j + 1] == -1)
		j++; //向右
	else if (i + 1 < m && matrix[i + 1][j] == -1)
		i++; //向下
	else if (j - 1 >= 0 && matrix[i][j - 1] == -1)
		j--; //向左
	else {
		i--; //向上
		flag = 1; //标记
	}
}
```


## 代码：


[1105. Spiral Matrix (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1105.%20Spiral%20Matrix%20(25)/1105.%20Spiral%20Matrix%20(25).cpp)


```cpp
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
```