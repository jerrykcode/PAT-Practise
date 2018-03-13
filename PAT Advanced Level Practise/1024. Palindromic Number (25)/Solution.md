# 1024. Palindromic Number (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1024)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



A number that will be the same when it is written forwards or backwards is known as a Palindromic 
Number. For example, 1234321 is a palindromic number. All single digit numbers are palindromic 
numbers. 



Non-palindromic numbers can be paired with palindromic ones via a series of operations. First, 
the non-palindromic number is reversed and the result is added to the original number. If the 
result is not a palindromic number, this is repeated until it gives a palindromic number. For 
example, if we start from 67, we can obtain a palindromic number in 2 steps: 67 + 76 = 143, 
and 143 + 341 = 484. 

Given any positive integer N, you are supposed to find its paired palindromic number and the 
number of steps taken to find it. 



## Input Specification: 

Each input file contains one test case. Each case consists of two positive numbers N and K, where 
N (<= 10^10) is the initial numer and K (<= 100) is the maximum number of steps. The numbers are 
separated by a space.



## Output Specification: 

For each test case, output two numbers, one in each line. The first number is the paired palindromic 
number of N, and the second number is the number of steps taken to find the palindromic number. If 
the palindromic number is not found after K steps, just output the number obtained at the Kth step 
and K instead.



## Sample Input 1:

67 3  

## Sample Output 1:

484  
2  

## Sample Input 2:

69 3  

## Sample Output 2:

1353  
3  



## 题意：

若一个整数从左到右读与从右到左读相同则为回文，输入整数N、K，若N不是回文，则N与其逆序相加，求N逆序相加多少
次后得到回文(若K次逆序相加尚未得到回文，则输出第K次逆序相加的结果与K，N < 10^10，K < 100)

## 思路：

用字符串输入N，若N不是回文则逆序相加直到得到回文或循环次数超过K

判断字符串number是否为回文：对于 0 <= i < number.length()/2，有number[i] == number[number.length() - 1 - i]，
则为回文

逆序相加：字符串result存储结果，number[i]与number[number.length() - i - 1]的数值(int)相加得到的数值转为字符串
加到result最后(注意进位)

## 代码：

[1024. Palindromic Number (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1024.%20Palindromic%20Number%20(25)/1024.%20Palindromic%20Number%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

bool isPalindromic(string number)
{	/* 判断一个数是否为palindromic */
	for (int i = 0; i < number.length() / 2; i++)
		if (number[i] != number[number.length() - i - 1])
			return 0;
	return 1;
}

string reverseAdd(string number)
{
	string result;
	int k = 0; //进位
	for (int i = 0; i < number.length(); i++) {
		int n = number[i] - '0' + number[number.length() - i - 1] - '0' + k;
		result = std::to_string(n % 10 ) + result;
		k = n / 10;
	}
	if (k > 0) result = std::to_string(k) + result;
	return result;
}

int main()
{
	string number;
	int k, i;
	cin >> number >> k;
	for (i = 0; i < k; i++) {
		if (isPalindromic(number))
			break;
		number = reverseAdd(number);
	}
	cout << number << "\n" << i;
    return 0;
}
```