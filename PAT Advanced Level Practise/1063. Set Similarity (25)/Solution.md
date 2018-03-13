# 1063. Set Similarity (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1063)
* 时间限制 300 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given two sets of integers, the similarity of the sets is defined to be Nc/Nt*100%, where Nc is the 
number of distinct common numbers shared by the two sets, and Nt is the total number of distinct numbers 
in the two sets. Your job is to calculate the similarity of any given pair of sets.



## Input Specification: 

Each input file contains one test case. Each case first gives a positive integer N (<=50) which is the 
total number of sets. Then N lines follow, each gives a set with a positive M (<=104) and followed by 
M integers in the range [0, 109]. After the input of sets, a positive integer K (<=2000) is given, followed 
by K lines of queries. Each query gives a pair of set numbers (the sets are numbered from 1 to N). All 
the numbers in a line are separated by a space.



## Output Specification: 

For each query, print in one line the similarity of the sets, in the percentage form accurate up to 
1 decimal place.



## Sample Input:

3  
3 99 87 101  
4 87 101 5 87  
7 99 101 18 5 135 18 99  
2  
1 2  
1 3  

## Sample Output:

50.0%  
33.3%  


## 题意：

在N个整数序列中，求K对序列，每对序列的两个整数序列中不重复的相同元素个数除以不重复的所有元素个数的百分数

## 思路：

用set存储不重复元素

## 代码：

[1063. Set Similarity (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1063.%20Set%20Similarity%20(25)/1063.%20Set%20Similarity%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <set>

int main()
{
	int n, m, k, a, b;
	scanf("%d", &n);
	set<int> * sets = new set<int>[n];
	for (int i = 0; i < n; i++) {
		scanf("%d", &m);
		for (int j = 0; j < m; j++) {
			int item;
			scanf("%d", &item);
			sets[i].insert(item);
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		int total = sets[a].size(), common = 0;
		for (auto it = sets[b].begin(); it != sets[b].end(); it++) {
			if (sets[a].find(*it) != sets[a].end())
				common++;
			else total++;
		}
		printf("%.1f%%\n", (common*100.0)/(total*1.0));
	}
    return 0;
}
```