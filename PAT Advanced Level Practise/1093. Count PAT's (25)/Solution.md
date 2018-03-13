# 1093. Count PAT's (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1093)

* 时间限制 120 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CAO, Peng



The string APPAPT contains two PAT's as substrings. The first one is formed by the 2nd, the 4th, and the 6th characters, and the second one is formed by the 3rd, the 4th, and the 6th characters. 

Now given any string, you are supposed to tell the number of PAT's contained in the string.

## Input Specification: 

Each input file contains one test case. For each case, there is only one line giving a string of no more than 105 characters containing only P, A, or T. 

## Output Specification: 

For each test case, print in one line the number of PAT's contained in the string. Since the result may be a huge number, you only have to output the result moded by 1000000007. 
## Sample Input:  
APPAPT  

## Sample Output:  
2  

## 题意

输入一个只含有字符'P'、'A'、'T'的字符串，求能够组成多少个"PAT"

## 思路：

遍历字符串，用countP存储当前有多少个"P"，countPA存储当前有多少个"PA"，用countPAT存储当前有多少个"PAT"。若一个字符是'P'，则countP++，若一个字符是'A'，由于在此字符之前有countP个"P"，故此字符可以组成countP个"PA"，所以countPA += countP，若一个字符是'T'，由于在此之前有countPA个"PA"，所以此字符可以组成countPA个"PAT"，所以countPAT += countPA。

## 代码：

[1093. Count PAT's (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1093.%20Count%20PAT's%20(25)/1093.%20Count%20PAT's%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	string pats;
	cin >> pats;
	long long countP = 0, countPA = 0, countPAT = 0;
	for (int i = 0; i < pats.length(); i++) {
		switch (pats[i]) {
		case 'P': { countP++; break; }
		case 'A': {countPA += countP; break; }
		case 'T': {countPAT += countPA; break; }
		}
	}
	countPAT %= 1000000007;
	cout << countPAT << endl;
    return 0;
}
```