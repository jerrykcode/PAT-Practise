# 1089. Insert or Merge (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1089)

* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Merge sort works as follows: Divide the unsorted list into N sublists, each containing 1 element (a list of 1 element is considered sorted). Then repeatedly merge two adjacent sublists to produce new sorted sublists until there is only 1 sublist remaining.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100). Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, print in the first line either "Insertion Sort" or "Merge Sort" to indicate the method used to obtain the partial result. Then run this method for one more iteration and output in the second line the resulting sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.
## Sample Input 1:
10  
3 1 2 8 7 5 9 4 6 0  
1 2 3 7 8 5 9 4 6 0  

## Sample Output 1: 
Insertion Sort  
1 2 3 5 7 8 9 4 6 0  

## Sample Input 2:
10  
3 1 2 8 7 5 9 4 0 6  
1 3 2 8 5 7 4 9 0 6  

## Sample Output 2:
Merge Sort  
1 2 3 8 4 5 7 9 0 6  


#### 题意与思路参考:[数据结构-中国大学MOOC-第十二讲 综合习题选讲-Insert or Merge](http://www.icourse163.org/learn/ZJU-93001?tid=1002261004#/learn/content?type=detail&id=1003011875)

## 代码：

[1089. Insert or Merge (25).cpp ](https://github.com/jerrykcode/PAT-Advanced-Level-Practise/blob/master/PAT%20Advanced%20Level%20Practice/1089.%20Insert%20or%20Merge%20(25)/1089.%20Insert%20or%20Merge%20(25).cpp)

```cpp
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
```
