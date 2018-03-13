# 1125. Chain the Ropes (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1125)

* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given some segments of rope, you are supposed to chain them into one rope. Each time you may only fold two segments into loops and chain them into one piece, as shown by the figure. The resulting chain will be treated as another segment of rope and can be folded again. After each chaining, the lengths of the original two segments will be halved. 

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1125.jpg)


Your job is to make the longest possible rope out of N given segments. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (2 <= N <= 10^4). Then N positive integer lengths of the segments are given in the next line, separated by spaces. All the integers are no more than 104. 

## Output Specification: 

For each case, print in a line the length of the longest possible rope that can be made by the given segments. The result must be rounded to the nearest integer that is no greater than the maximum length. 
## Sample Input:  
8  
10 15 12 3 4 13 1 15  

## Sample Output:  
14  

## 题意：

将两根绳子连接在一起后的长度为 (两根绳子长度之和)/2，给出N根绳子的长度，求将它们全部连接在一起，最长能有多长。

## 思路：

由于每次连接会使一根绳子长度减半，故应让最短的连接次数最多；最长的连接次数最少。用数组存储每根绳子的长度，非递减排序，总长度sum初始化为第0根绳子即最短的绳子的长度，然后从1开始遍历数组，将绳子连接，即把从下标1开始数组的每个元素加到sum上，然后sum减半。


## 代码：
[1125. Chain the Ropes (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1125.%20Chain%20the%20Ropes%20(25)/1125.%20Chain%20the%20Ropes%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

int main()
{
	int n;
	cin >> n;
	int *rope = new int[n];
	for (int i = 0; i < n; i++) cin >> rope[i];
	sort(rope, rope + n);
	int sum = rope[0];
	for (int i = 1; i < n; i++)
		sum = (sum + rope[i]) / 2;
	cout << sum << endl;
    return 0;
}
```
