# 1113. Integer Set Partition (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1113)

* 时间限制 150 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



Given a set of N (> 1) positive integers, you are supposed to partition them into two disjoint sets A1 and A2 of n1 and n2 numbers, respectively. Let S1 and S2 denote the sums of all the numbers in A1 and A2, respectively. You are supposed to make the partition so that |n1 - n2| is minimized first, and then |S1 - S2| is maximized. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives an integer N (2 <= N <= 105), and then N positive integers follow in the next line, separated by spaces. It is guaranteed that all the integers and their sum are less than 231.

## Output Specification: 

For each case, print in a line two numbers: |n1 - n2| and |S1 - S2|, separated by exactly one space. 

## Sample Input 1:
10  
23 8 10 99 46 2333 46 1 666 555  

## Sample Output 1:  
0 3611  

## Sample Input 2:  
13  
110 79 218 69 3721 100 29 135 2 6 13 5188 85  

## Sample Output 2: 
1 9359


## 题意：

输入N个正整数，将它们存入两个集合A1、A2中，A1、A2的元素数量为n1、n2，元素之和为S1、S2，求使|n1 - n2|最小而|S1 - S2|最大的A1、A2，输出此|n1 - n2| 与 |S1 - S2|。

## 思路：

所有元素从小到大排序，[0 ~ N/2 - 1]元素加到S1上（存入A1），[N/2， N - 1]元素加到S2上（存入A2），若N是奇数则 |n1 - n2| = 1，否则为0，（即N%2），输出 S2 - S1。

## 代码：

[1113. Integer Set Partition (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1113.%20Integer%20Set%20Partition%20(25)/1113.%20Integer%20Set%20Partition%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

int main() 
{
	int n;
	cin >> n;
	int *list = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> list[i];
	}
	sort(list, list + n);
	int center = n / 2;
	int s1 = 0, s2 = 0;
	for (int i = 0; i < center; i++)
		s1 += list[i];
	for (int i = center; i < n; i++)
		s2 += list[i];
	cout << n % 2;
	printf(" %d", s2 - s1);
    return 0;
}
```
