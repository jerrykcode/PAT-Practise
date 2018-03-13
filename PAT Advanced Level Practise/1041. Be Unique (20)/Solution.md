# 1041. Be Unique (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1041)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Being unique is so important to people on Mars that even their lottery is designed in a unique way. 
The rule of winning is simple: one bets on a number chosen from [1, 104]. The first one who bets on 
a unique number wins. For example, if there are 7 people betting on 5 31 5 88 67 88 17, then the second 
one who bets on 31 wins.



## Input Specification: 

Each input file contains one test case. Each case contains a line which begins with a positive integer 
N (<=10^5) and then followed by N bets. The numbers are separated by a space.



## Output Specification: 

For each test case, print the winning number in a line. If there is no winner, print "None" instead. 



## Sample Input 1:

7 5 31 5 88 67 88 17  

## Sample Output 1:

31  


## Sample Input 2:  

5 888 666 666 888 888  

## Sample Output 2:  

None  



## 题意：

求一个整数序列中第一个无重复的数字

## 思路：

用map存储数字与输入次序的对应，若多次出现则为-1，map中大于0的value最小的key即为第一个无重复整数


## 代码：
[1041. Be Unique (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1041.%20Be%20Unique%20(20)/1041.%20Be%20Unique%20(20).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <map>
#include <string>

int main()
{
	map<int, int> bets; //数字对应输入次序
	int n, number;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> number;
		if (bets[number] == 0)
			bets[number] = i + 1;//第i + 1个数字
		else
			bets[number] = -1; //重复
	}
	int min = 100001, win;
	for (auto it = bets.begin(); it != bets.end(); it++) {
		if (it->second > 0 && it->second < min) {
			min = it->second;
			win = it->first;
		}
	}
	if (min < 100001)
		cout << win;
	else
		cout << "None";
	return 0;
}
```