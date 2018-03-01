# 1121. Damn Single (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1121)


* 时间限制 300 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



"Damn Single (单身狗)" is the Chinese nickname for someone who is being single. You are supposed to find those who are alone in a big party, so they can be taken care of.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=50000), the total number of couples. Then N lines of the couples follow, each gives a couple of ID's which are 5-digit numbers (i.e. from 00000 to 99999). After the list of couples, there is a positive integer M (<=10000) followed by M ID's of the party guests. The numbers are separated by spaces. It is guaranteed that nobody is having bigamous marriage (重婚) or dangling with more than one companion.

## Output Specification: 

First print in a line the total number of lonely guests. Then in the next line, print their ID's in increasing order. The numbers must be separated by exactly 1 space, and there must be no extra space at the end of the line. 

## Sample Input:  
3  
11111 22222  
33333 44444  
55555 66666  
7  
55555 44444 10000 88888 22222 11111 23333  

## Sample Output:  
5  
10000 23333 44444 55555 88888  

## 题意：

输入N对对象双方的ID(5位00000~99999)，然后输入一次聚会中参加的M个人的ID，在聚会中没有对象的称为单身（*狗*），求单身的数量并递增输出所有单身的ID。


## 思路：

int couple[100000]，数组下标表示某人的ID，值存储该人的对象的ID，没有则为-1。int flag[100000]，数组下标表示某人的ID，值表示该人是否参加了聚会。int guests[M]数组存储参加聚会的人的ID，长度为人数M，couple和flag以及guests的值边输入边确定。最后遍历guests，若一个人（ID为guests[i]）没有对象（couple[guests[i]] == -1）或有对象但对象没来（flag[couple[guests[i]]] == 0），则此人为单身，将其ID（guests[i]）存入vector。对vector排序并输出。


## 代码：

[1121. Damn Single (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1121.%20Damn%20Single%20(25)/1121.%20Damn%20Single%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	int couple[100000];
	int flag[100000];
	fill(couple, couple + 100000, -1);
	fill(flag, flag + 100000, 0);
	int n, m;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int c1, c2;
		cin >> c1 >> c2;
		couple[c1] = c2;
		couple[c2] = c1;
	}
	cin >> m;
	int * guests = new int[m];
	for (int i = 0; i < m; i++) {
		cin >> guests[i];
		flag[guests[i]] = 1;
	}
	vector<int> single;
	for (int i = 0; i < m; i++) {
		if (couple[guests[i]] == -1 || flag[couple[guests[i]]] == 0)
			single.push_back(guests[i]);
	}
	cout << single.size() << endl;
	sort(single.begin(), single.end());
	for (auto it = single.begin(); it != single.end(); it++) {
		if (it != single.begin()) putchar(' ');
		printf("%05d", *it);
	}
    return 0;
}
```
