# 1104. Sum of Number Segments (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1104)

* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CAO, Peng



Given a sequence of positive numbers, a segment is defined to be a consecutive subsequence. For example, given the sequence {0.1, 0.2, 0.3, 0.4}, we have 10 segments: (0.1) (0.1, 0.2) (0.1, 0.2, 0.3) (0.1, 0.2, 0.3, 0.4) (0.2) (0.2, 0.3) (0.2, 0.3, 0.4) (0.3) (0.3, 0.4) (0.4). 

Now given a sequence, you are supposed to find the sum of all the numbers in all the segments. For the previous example, the sum of all the 10 segments is 0.1 + 0.3 + 0.6 + 1.0 + 0.2 + 0.5 + 0.9 + 0.3 + 0.7 + 0.4 = 5.0. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N, the size of the sequence which is no more than 10^5. The next line contains N positive numbers in the sequence, each no more than 1.0, separated by a space.

## Output Specification: 

For each test case, print in one line the sum of all the numbers in all the segments, accurate up to 2 decimal places.

## Sample Input:  
4   
0.1 0.2 0.3 0.4   

## Sample Output:  
5.00  

## 代码：

[1104. Sum of Number Segments (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1104.%20Sum%20of%20Number%20Segments%20(20)/1104.%20Sum%20of%20Number%20Segments%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	double *list = new double[n];
	double total = 0.0;
	for (int i = 0; i < n; i++) {
		cin >> list[i];
		total += list[i] * (i + 1)*(n - i);
	}
	printf("%.2f\n", total);
    return 0;
}
```