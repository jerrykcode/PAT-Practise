# 1048. Find Coins (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1048)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Eva loves to collect coins from all over the universe, including some other planets like Mars. 
One day she visited a universal shopping mall which could accept all kinds of coins as payments. 
However, there was a special requirement of the payment: for each bill, she could only use exactly 
two coins to pay the exact amount. Since she has as many as 105 coins with her, she definitely 
needs your help. You are supposed to tell her, for any given amount of money, whether or not she 
can find two coins to pay for it.


## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive numbers: 
N (<=10^5, the total number of coins) and M(<=10^3, the amount of money Eva has to pay). The second 
line contains N face values of the coins, which are all positive numbers no more than 500. All the 
numbers in a line are separated by a space.



## Output Specification: 

For each test case, print in one line the two face values V1 and V2 (separated by a space) such that 
V1 + V2 = M and V1 <= V2. If such a solution is not unique, output the one with the smallest V1. If 
there is no solution, output "No Solution" instead.



## Sample Input 1:

8 15  
1 2 8 7 2 4 11 15  

## Sample Output 1:  
  
4 11  


## Sample Input 2:

7 14  
1 8 7 2 4 11 15  

## Sample Output 2:
No Solution  


## 题意：

宇宙中的硬币...输入N个正整数与另一个正整数M，求这N个正整数中是否存在V1 <= V2使得V1 + V2 == M，若
不存在输出"No Solution"，若存在多对V1，V2，输出V1最小的

## 思路：

N个正整数存储在数组中，由于要输出V1最小的，故先对数组从小到大排序，对于数组中的每个元素，若此元素
就是V1，则V2 = M - V1，在数组V1之后的元素中二分查找V2，若存在V2，则输出V1、V2，不存在则试探数组中
下一个元素是否为V1


## 代码：


[1048. Find Coins (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1048.%20Find%20Coins%20(25)/1048.%20Find%20Coins%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

bool find(int *arr, int l, int r, int v)
{
	while (l <= r) {
		int m = (l + r) / 2;
		if (arr[m] == v)
			return true;
		else if (v < arr[m])
			r = m - 1;
		else
			l = m + 1;
	}
	return false;
}

int main()
{
	int n, m;
	cin >> n >> m;
	int *coins = new int[n];
	for (int i = 0; i < n; i++)
		cin >> coins[i];
	sort(coins, coins + n);
	int v1, v2;
	for (int i = 0; i < n; i++) {
		v1 = coins[i];
		v2 = m - v1;
		if (find(coins, i + 1, n - 1, v2)) {
			printf("%d %d", v1, v2);
			return 0;
		}
	}
	cout << "No Solution";
    return 0;
}
```
