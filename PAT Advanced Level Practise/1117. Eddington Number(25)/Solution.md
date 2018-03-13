# 1117. Eddington Number(25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1117)


* 时间限制 250 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



British astronomer Eddington liked to ride a bike. It is said that in order to show off his skill, he has even defined an "Eddington number", E -- that is, the maximum integer E such that it is for E days that one rides more than E miles. Eddington's own E was 87.

Now given everyday's distances that one rides for N days, you are supposed to find the corresponding E (<=N). 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N(<=10^5), the days of continuous riding. Then N non-negative integers are given in the next line, being the riding distances of everyday.

## Output Specification: 

For each case, print in a line the Eddington number for these N days. 
## Sample Input:  
10  
6 7 6 9 3 10 8 2 7 8  

## Sample Output:  
6  


## 题意：


输入N个非负整数，求最大的E，使大于E的数超过或等于E个。


## 思路：

E直接从1开始试，遍历，看大于E的数有没有E个，会超时。  
先将N个数（存数组list中）从大到小（非递增）排序，E最大不能超过N，也不能超过给出数据中的最大值。故E初始化为min{N, list[0]}。用count记录大于E的个数。遍历list，若list[i] > E，则count++，若list[i] <= E，此时list[i]之后的值不会有比E大的了，若count >= E，则最大E求出；否则E--，i不增加，再判断`list[i] > E`或`count >= E`是否成立。


## 代码：

[1117. Eddington Number(25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1117.%20Eddington%20Number(25)/1117.%20Eddington%20Number(25)_2.cpp)


```cpp
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
```