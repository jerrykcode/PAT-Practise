# 1067. Sort with Swap(0,*) (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1067)
* 时间限制 150 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given any permutation of the numbers {0, 1, 2,..., N-1}, it is easy to sort them in increasing order. 
But what if Swap(0, *) is the ONLY operation that is allowed to use? For example, to sort {4, 0, 2, 1, 3} 
we may apply the swap operations in the following way:

```
Swap(0, 1) => {4, 1, 2, 0, 3}
Swap(0, 3) => {4, 1, 2, 3, 0}
Swap(0, 4) => {0, 1, 2, 3, 4} 
```

Now you are asked to find the minimum number of swaps need to sort the given permutation of the first N 
nonnegative integers. 



## Input Specification: 

Each input file contains one test case, which gives a positive N (<=10^5) followed by a permutation 
sequence of {0, 1, ..., N-1}. All the numbers in a line are separated by a space.



## Output Specification: 

For each case, simply print in a line the minimum number of swaps need to sort the given permutation.



## Sample Input:

10 3 5 7 2 6 4 9 0 8 1

## Sample Output:

9


## 题意：

输入正整数N，对于{0~N - 1}的枚举序列排序，但只能使用交换0与另一个整数的swap函数

## 思路：

用index数组存储每个整数在序列中的位置

## 代码：

[1067. Sort with Swap(0,*) (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1067.%20Sort%20with%20Swap(0,*)%20(25)/1067.%20Sort%20with%20Swap(0,*)%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main()
{
	int n, m;
	scanf("%d", &n);
	if (n == 0) { printf("0"); return 0; }
	int *index = new int[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &m);
		index[m] = i; //m在位置i
	}
	int count = 0;
	while (1)
	{
		if (index[0] != 0) //0不在位置0
			swap(index, index + index[0]); //交换index[0]与index[index[0]]
		else {
			int i;
			while (index[i] == i) i++;//用for (i = 0; index[i] == i; i++);会超时！！！
			if (i == n) break;
			swap(index, index + i); //交换index[0]与index[i]
		}
		count++;
	}
	printf("%d", count);
    return 0;
}
```