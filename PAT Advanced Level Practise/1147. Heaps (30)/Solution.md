# 1147. Heaps (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1147)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


In computer science, a heap is a specialized tree-based data structure that satisfies the heap property: if P is a parent node of C, then the key (the value) of P is either greater than or equal to (in a max heap) or less than or equal to (in a min heap) the key of C. A common implementation of a heap is the binary heap, in which the tree is a complete binary tree. (Quoted from Wikipedia at https://en.wikipedia.org/wiki/Heap_(data_structure)) 

Your job is to tell if a given complete binary tree is a heap. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives two positive integers: M (<= 100), the number of trees to be tested; and N (1 < N <= 1000), the number of keys in each tree, respectively. Then M lines follow, each contains N distinct integer keys (all in the range of int), which gives the level order traversal sequence of a complete binary tree. 

## Output Specification: 

For each given tree, print in a line "Max Heap" if it is a max heap, or "Min Heap" for a min heap, or "Not Heap" if it is not a heap at all. Then in the next line print the tree's postorder traversal sequence. All the numbers are separated by a space, and there must no extra space at the beginning or the end of the line.


## Sample Input:

3 8  
98 72 86 60 65 12 23 50  
8 38 25 58 52 82 70 60  
10 28 15 12 34 9 8 56  

## Sample Output:

Max Heap  
50 60 65 72 12 23 86 98  
Min Heap  
60 58 52 38 82 70 25 8  
Not Heap  
56 12 34 28 9 8 15 10  


## 题意：

给出M棵完全二叉树的层序遍历结果，判断是否为最大堆、最小堆，或者不是堆，并输出后序遍历。

## 思路：

判断根是否比左右孩子的值大(小)，然后递归判断左、右子树是否为最大、小堆。

## 代码：

[1147. Heaps (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1147.%20Heaps%20(30)/1147.%20Heaps%20(30).cpp)

```cpp
#include <iostream>
using namespace std;
typedef int h_type;
#define MAX 1
#define MIN 0

bool isHeap(int *tree, int root, int n, h_type flag)
{
	int left = root * 2 + 1, right = left + 1;
	if (left < n) {
		if (flag == MAX && tree[root] < tree[left]) return false;
		if (flag == MIN && tree[root] > tree[left]) return false;
		if (!isHeap(tree, left, n, flag))return false;
	}
	if (right < n) {
		if (flag == MAX && tree[root] < tree[right]) return false;
		if (flag == MIN && tree[root] > tree[right]) return false;
		if (!isHeap(tree, right, n, flag))return false;
	}
	return true;
}

void post(int *tree, int root, int n)
{
	int left = root * 2 + 1, right = left + 1;
	if (left < n) {
		post(tree, left, n);
		putchar(' ');
	}
	if (right < n) {
		post(tree, right, n);
		putchar(' ');
	}
	printf("%d", tree[root]);
}

int main()
{
	int m, n;
	cin >> m >> n;
	int *tree = new int[n];
	for (int i = 0; i < m; i++) {
		for (int i = 0; i < n; i++) cin >> tree[i];
		if (isHeap(tree, 0, n, MAX)) printf("Max Heap\n");
		else if (isHeap(tree, 0, n, MIN)) printf("Min Heap\n");
		else printf("Not Heap\n");
		post(tree, 0, n);
		cout << endl;
	}
    return 0;
}
```
