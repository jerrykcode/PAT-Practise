# 1120. Friend Numbers (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1120)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Two integers are called "friend numbers" if they share the same sum of their digits, and the sum is their "friend ID". For example, 123 and 51 are friend numbers since 1+2+3 = 5+1 = 6, and 6 is their friend ID. Given some numbers, you are supposed to count the number of different friend ID's among them. Note: a number is considered a friend of itself.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N. Then N positive integers are given in the next line, separated by spaces. All the numbers are less than 10^4.

## Output Specification: 

For each case, print in the first line the number of different frind ID's among the given integers. Then in the second line, output the friend ID's in increasing order. The numbers must be separated by exactly one space and there must be no extra space at the end of the line. 
## Sample Input:  
8  
123 899 51 998 27 33 36 12  

## Sample Output:  
4  
3 6 9 26  

## 题意：

若两个整数的字符的数值之和相等，则这两个整数互为"friend numbers"，字符数值和为"friend ID"。如123和51： 1 + 2 + 3 = 5 + 1，friend ID 为6。一个数的friend number包括它自己。输入N个正整数，求其中的friend number个数，并递增输出所有的friend number。

## 思路：

用string形式输入正整数，将每个正整数的字符和插入set中，set不重复，且自动排序，故输入完后直接输出set中的元素即可。


## 代码：


[1120. Friend Numbers (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1120.%20Friend%20Numbers%20(20)/1120.%20Friend%20Numbers%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
# include <string>
#include <set>
#include <algorithm>

int main()
{
	int n, sum;
	cin >> n;
	set<int> id;
	string number;
	for (int i = 0; i < n; i++) {
		cin >> number;
		sum = 0;
		for (int j = 0; j < number.length(); j++) 
			sum += (int)number[j] - (int)'0';
		id.insert(sum);
	}
	cout << id.size() << endl;
	for (auto it = id.begin(); it != id.end(); it++) {
		if (it != id.begin()) putchar(' ');
		cout << *it;
	}
    return 0;
}
```