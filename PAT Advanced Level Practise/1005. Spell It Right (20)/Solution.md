# 1005. Spell It Right (20)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



Given a non-negative integer N, your task is to compute the sum of all the digits of N, 
and output every digit of the sum in English. 



## Input Specification: 

Each input file contains one test case. Each case occupies one line which contains an N (<= 10100). 



## Output Specification: 

For each test case, output in one line the digits of the sum in English words. 
There must be one space between two consecutive words, but no extra space at the end of a line. 



## Sample Input:
12345

## Sample Output:
one five



## 题意：
输入一个整数N，将N的每一个字符相加得到另一个整数M，输出M的每一个字符的英文，
如输入12345，则由于1+2+3+4+5=15，应输出one five

## 思路：
用数组hash存储数字的英文，如hash[0] = "zero", hash[1] = "one", ... , hash[9] = "nine"
用字符串格式输入N，每个字符-'0'后相加得到M的值，再将M转为字符串，将此字符串的
每个字符-'0'后输出对应的hash值

## 代码：

[1005. Spell It Right (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1005.%20Spell%20It%20Right%20(20)/1005.%20Spell%20It%20Right%20(20)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string input;
	cin >> input;
	int sum = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		sum += input[i] - '0';
	}
	string str = to_string(sum);
	string hash[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	cout << hash[str[0] - '0'];
	for (int i = 1; i <str.length(); i++) {
		cout << " " + hash[str[i] - '0'];
	}
	return 0;
}
```
