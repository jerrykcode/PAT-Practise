# 1136. A Delayed Palindrome (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1136)
* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Consider a positive integer N written in standard notation with k+1 digits ai as ak...a1a0 with 0 <= ai < 10 for all i and ak > 0. Then N is palindromic if and only if ai = ak-i for all i. Zero is written 0 and is also palindromic by definition. 

Non-palindromic numbers can be paired with palindromic ones via a series of operations. First, the non-palindromic number is reversed and the result is added to the original number. If the result is not a palindromic number, this is repeated until it gives a palindromic number. Such number is called a delayed palindrome. (Quoted from https://en.wikipedia.org/wiki/Palindromic_number) 

Given any positive integer, you are supposed to find its paired palindromic number. 

## Input Specification: 

Each input file contains one test case which gives a positive integer no more than 1000 digits.

## Output Specification: 

For each test case, print line by line the process of finding the palindromic number. The format of each line is the following:
*A + B = C*


where A is the original number, B is the reversed A, and C is their sum. A starts being the input number, and this process ends until C becomes a palindromic number -- in this case we print in the last line "C is a palindromic number."; or if a palindromic number cannot be found in 10 iterations, print "Not found in 10 iterations." instead. 
## Sample Input 1:

97152  

## Sample Output 1:

97152 + 25179 = 122331  
122331 + 133221 = 255552  
255552 is a palindromic number.  

## Sample Input 2:  

196  

## Sample Output 2:

196 + 691 = 887  
887 + 788 = 1675  
1675 + 5761 = 7436  
7436 + 6347 = 13783  
13783 + 38731 = 52514  
52514 + 41525 = 94039  
94039 + 93049 = 187088  
187088 + 880781 = 1067869  
1067869 + 9687601 = 10755470  
10755470 + 07455701 = 18211171  
Not found in 10 iterations.  

## 题意：

输入一个不超过1000字符的正整数，若它不是回文就将它更新为与它的字符逆组成的数相加之和，直到它成为回文，输出这个过程，若10次相加的结果仍不是回文，则输出"Not found in 10 iterations."。

## 思路：

while (不是回文) 更新为与逆相加的结果 //超过10次要跳出

用字符串输入正整数，主要实现三个函数：

* 1、判断一个字符串是否为回文

* 2、求一个字符串的逆

* 3、求两个字符串表示的数值之和

## 代码：


[1136. A Delayed Palindrome (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1137.%20Final%20Grading%20(25)/1137.%20Final%20Grading%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

bool isPalindrome(string s)
{
	for (int i = 0; i < s.length() / 2; i++) 
		if (s[i] != s[s.length() - i - 1]) return false;
	return true;
}

string reverse(string s)
{
	string result = "";
	for (int i = s.length() - 1; i >= 0; i--)
		result += s[i];
	return result;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

string add(string a, string b)
{
	string result = "";
	int len = max(a.length(), b.length());
	while (a.length() < len) a = "0" + a;
	while (b.length() < len) b = "0" + b;
	int k = 0;
	for (int i = len - 1; i >= 0; i--) {
		int n = (int)a[i] - (int)'0' + (int)b[i] - (int)'0' + k;
		result = to_string(n % 10) + result;
		k = n / 10;
	}
	if (k != 0) result = to_string(k) + result;
	return result;
}

int main()
{
	string a;
	cin >> a;
	int time = 0;
	while (!isPalindrome(a)) {
		if (time >= 10) {
			cout<<"Not found in 10 iterations.";
			return 0;
		}
		string b = reverse(a);
		string sum = add(a, b);
		cout << a << " + " << b << " = " << sum << endl;
		a = sum;
		time++;
	}
	cout << a << " is a palindromic number.";
    return 0;
}
```


