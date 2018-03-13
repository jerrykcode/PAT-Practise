# 1098. Insertion or Heap Sort (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1098)

* 时间限制 100 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



According to Wikipedia:

Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.

Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100). Then in the next line, N integers are given as the initial sequence. The last line contains the partially sorted sequence of the N numbers. It is assumed that the target sequence is always ascending. All the numbers in a line are separated by a space.

## Output Specification: 

For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result. Then run this method for one more iteration and output in the second line the resuling sequence. It is guaranteed that the answer is unique for each test case. All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.
## Sample Input 1:
10  
3 1 2 8 7 5 9 4 6 0  
1 2 3 7 8 5 9 4 6 0  

## Sample Output 1:
Insertion Sort  
1 2 3 5 7 8 9 4 6 0  

## Sample Input 2:
10  
3 1 2 8 7 5 9 4 6 0  
6 4 5 1 0 3 2 7 8 9  

## Sample Output 2:
Heap Sort  
5 4 3 1 0 2 6 7 8 9  


## 题意：


输入N个整数，作为一个序列未排序时的初始状态。用插入排序或者堆排序对这个序列非递减排序，输入在排序中的某一步时的序列。判断这是那一种排序，并用这种排序再排序一步并输出结果。


## 思路：


数组list存储未排序的序列，sorted存储部分排序的序列。对排序好的一部分，有sorted[i] <= sorted[i + 1]，i从0开始，找到第一个sorted[i] > sorted[i + 1]，此后的i若有sorted[i] == list[i]则它们都未参加排序，则一定是插入排序；若有不满足sorted[i] == list[i]的则一定不是插入排序，也就是堆排序。插入排序再插入一个元素然后输出即可，若是堆排序，则sorted[0]是堆顶，即未排好的元素中最大的，i从n - 1开始递减，找到满足sorted[0] > sorted[i]的最大i，sorted[i]即未排好的堆中的最后一个元素，交换sorted[0]与sorted[i]，下滤

## 代码：


[1098. Insertion or Heap Sort (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1098.%20Insertion%20or%20Heap%20Sort%20(25)/1098.%20Insertion%20or%20Heap%20Sort%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

void Insert_Element(int *list, int k)
{
	int tmp = list[k], i;
	for (i = k - 1; i >= 0; i--) {
		if (list[i] > tmp)
			list[i + 1] = list[i];
		else break;
	}
	list[i + 1] = tmp;
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void percDown(int *list, int n)
{
	int parent, child, x = list[0];
	for (parent = 0; parent < n; parent = child) {
		child = parent * 2 + 1;
		if (child >= n) break;
		if (child + 1 < n && list[child + 1] > list[child])
			child++;
		if (x >= list[child]) break;
		list[parent] = list[child];
	}
	list[parent] = x;
}

int main()
{
	int n;
	cin >> n;
	int *list = new int[n];
	int *sorted = new int[n];
	for (int i = 0; i < n; i++) cin >> list[i];
	for (int i = 0; i < n; i++) cin >> sorted[i];
	int k = 0;
	for (int i = 0; i < n - 1; i++)
		if (sorted[i] > sorted[i + 1]) {
			k = i + 1;
			break;
		}
	for (int i = k; i < n; i ++)
		if (sorted[i] != list[i]) {
			printf("Heap Sort\n");
			for (int i = n - 1; i >= 0; i--)
				if (sorted[i] < sorted[0]) {
					swap(sorted + i, sorted);
					percDown(sorted, i);
					break;
				}
			goto PRINT;
		}
	printf("Insertion Sort\n");
	Insert_Element(sorted, k);
PRINT: {
	for (int i = 0; i < n; i++) {
		if (i != 0) putchar(' ');
		cout << sorted[i];
	}
	}
	return 0;
}

```