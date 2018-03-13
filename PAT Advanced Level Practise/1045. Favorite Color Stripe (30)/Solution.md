# 1045. Favorite Color Stripe (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1045)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Eva is trying to make her own color stripe out of a given one. She would like to keep only her favorite 
colors in her favorite order by cutting off those unwanted pieces and sewing the remaining parts together 
to form her favorite color stripe.

It is said that a normal human eye can distinguish about less than 200 different colors, so Eva's favorite 
colors are limited. However the original stripe could be very long, and Eva would like to have the remaining 
favorite stripe with the maximum length. So she needs your help to find her the best result.

Note that the solution might not be unique, but you only have to tell her the maximum length. For example, 
given a stripe of colors {2 2 4 1 5 5 6 3 1 1 5 6}. If Eva's favorite colors are given in her favorite order 
as {2 3 1 5 6}, then she has 4 possible best solutions {2 2 1 1 1 5 6}, {2 2 1 5 5 5 6}, {2 2 1 5 5 6 6}, 
and {2 2 3 1 1 5 6}.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (<=200) 
which is the total number of colors involved (and hence the colors are numbered from 1 to N). Then the next 
line starts with a positive integer M (<=200) followed by M Eva's favorite color numbers given in her favorite 
order. Finally the third line starts with a positive integer L (<=10000) which is the length of the given 
stripe, followed by L colors on the stripe. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, simply print in a line the maximum length of Eva's favorite stripe.



## Sample Input:

6  
5 2 3 1 5 6  
12 2 2 4 1 5 5 6 3 1 1 5 6  

## Sample Output:

7  



## 题意：

N种颜色，输入M种喜欢的颜色的顺序，给出一个有L个颜色的序列，在序列上删除掉一些颜色，使剩余序列按颜色的喜欢
程度排序，输出最长的序列长度

## 思路：

本题思路参考了 [1045. Favorite Color Stripe (30) (柳婼 の blog)](https://www.liuchuo.net/archives/2283)

用int数组r存储喜欢颜色的排名，r[i]表示颜色i的排名；用int数组stripe存储序列中的颜色，输入时喜欢的颜色中没有
颜色不存入stripe。

用int数组dp，dp[i]表示以序列中第i个颜色作为子序列的最后一个，可得到的最长子序列（按颜色喜欢程度排序）的长度。
遍历stripe数组，初始化dp[i] = 1，用j循环小于i的数，若r[stripe[i]] >= r[stripe[j]]，表示第i个颜色的排名后于第
j个颜色，则i排在j后面是符合要求的，故dp[i]更新为dp[i]与dp[j] + 1中较大的


## 参考：
 [1045. Favorite Color Stripe (30) (柳婼 の blog)](https://www.liuchuo.net/archives/2283)
 
 
 ## 代码：
[1045. Favorite Color Stripe (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1045.%20Favorite%20Color%20Stripe%20(30)/1045.%20Favorite%20Color%20Stripe%20(30).cpp)
 ```cpp
 #include "stdafx.h"
#include <iostream>
using namespace std;

int r[201], stripe[10001], dp[10001];

int main()
{
	fill(r, r + 201, -1);
	int n, m, l, color, count = 0, maxlen = 0;
	cin >> n;
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> color;
		r[color] = i;
	}
	cin >> l;
	for (int i = 0; i < l; i++) {
		cin >> color;
		if (r[color] >= 0) stripe[count++] = color;
	}
	for (int i = 0; i < count; i++) {
		dp[i] = 1;
		for (int j = 0; j < i; j++) {
			if (r[stripe[i]] >= r[stripe[j]]) 
				dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
		}
		maxlen = maxlen > dp[i] ? maxlen : dp[i];
	}
	cout << maxlen;
    return 0;
}
 ```
