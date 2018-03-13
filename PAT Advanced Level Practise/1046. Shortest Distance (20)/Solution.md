# 1046. Shortest Distance (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1046)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



The task is really simple: given N exits on a highway which forms a simple cycle, you are supposed to tell 
the shortest distance between any pair of exits.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains an integer N (in [3, 10^5]), 
followed by N integer distances D1 D2 ... DN, where Di is the distance between the i-th and the (i+1)-st exits, 
and DN is between the N-th and the 1st exits. All the numbers in a line are separated by a space. The second 
line gives a positive integer M (<=10^4), with M lines follow, each contains a pair of exit numbers, provided 
that the exits are numbered from 1 to N. It is guaranteed that the total round trip distance is no more than 10^7.



## Output Specification: 

For each test case, print your results in M lines, each contains the shortest distance between the corresponding 
given pair of exits.



## Sample Input:

5 1 2 4 14 9  
3  
1 3  
2 5  
4 1  

## Sample Output:

3  
10  
7  



## 题意：

一个环形公路上N个出口，对于i >= 1 && i < N，输入Di(第i个出口与第i + 1个出口之间的距离)，然后输入第N个出口与
第1个出口之间的距离DN。输入M对出口，求一对出口之间的最短距离

## 思路：

int数组dist[N + 1]存储第1个出口与第i个出口之间的距离，dist[1] = 0，dist[i] = dist[i - 1] + D(i - 1)，(i >= 2 
&& i <= N)，输入的同时将Di加到int的total上。然后输入DN，(设为dist[0])，total += DN。

对于M对出口的每一对，设为a、b，若a > b则swap(a，b)。int d1 = dist[b] - dist[a]即为a到b的距离，int d2 = total - d1
即为从b环形走到a的距离，输出d1、d2中较小的


## 代码：

[1046. Shortest Distance (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1046.%20Shortest%20Distance%20(20)/1046.%20Shortest%20Distance%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int n, m, a, b, d1, d2, total = 0;
	cin >> n;
	int * dist = new int[n + 1];
	dist[1] = 1;
	for (int i = 2; i <= n; i++) {
		cin >> a;
		dist[i] = dist[i - 1] + a;  
		total += a;
	}
	cin >> dist[0] >> m;
	total += dist[0];
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		if (a > b) swap(a, b);
		d1 = dist[b] - dist[a];
		d2 = total - d1;
		cout << (d1 < d2 ? d1 : d2) << endl;
	}
    return 0;
}
```