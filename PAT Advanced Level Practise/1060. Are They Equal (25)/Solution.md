# 1060. Are They Equal (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1060)


* 时间限制 100 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



If a machine can save only 3 significant digits, the float numbers 12300 and 12358.9 are considered equal since they are both saved as 0.123*105 with simple chopping. Now given the number of significant digits on a machine and two float numbers, you are supposed to tell if they are treated equal in that machine. 

## Input Specification: 

Each input file contains one test case which gives three numbers N, A and B, where N (<100) is the number of significant digits, and A and B are the two float numbers to be compared. Each float number is non-negative, no greater than 10^100, and that its total digit number is less than 100.

## Output Specification: 

For each test case, print in a line "YES" if the two numbers are treated equal, and then the number in the standard form "0.d1...dN*10^k" (d1>0 unless the number is 0); or "NO" if they are not treated equal, and then the two numbers in their standard form. All the terms must be separated by a space, with no extra space at the end of a line.

Note: Simple chopping is assumed without rounding.
## Sample Input 1:  

3 12300 12358.9  

## Sample Output 1:  
YES 0.123*10^5  

## Sample Input 2:  
3 120 128  

## Sample Output 2:  
NO 0.120*10^3 0.128*10^3  


## 注意：

`00000...000xyz...`(开头是0)、`00...00.0000xyz...`(整数部分是0，小数点后是0)、`000...000.000..000`(全部是0)的情况。

## 代码：

[1060. Are They Equal (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1060.%20Are%20They%20Equal%20(25)/1060.%20Are%20They%20Equal%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

string standard(string a, int n)
{
	string result = "";
	int flag = 0, count = 0, k = 0;
	while (a[0] == '0') // case : a = "00000000...000xyz..." remove "0"s
		a = a.substr(1);
	if (a[0] == '.') { 
		while (a.length() > 1 && a[1] == '0') {// case : a = "0.000...000xyz..." remove "0"s after the point"."
			a = "." + a.substr(2);
			k--;
		}
		if (a == ".") k = 0; //case "000...000.0000...000"
	}
	for (int i = 0; i < a.length(); i++) {
		if (flag == 0 && a[i] != '.') 
			k++;
		if (a[i] == '.') {
			flag = 1;
			continue;
		}
		if (count++ < n) result += a[i];
	}
	while (result.length() < n)
		result = result + "0";
	return "0." + result + "*10^" + std::to_string(k);
}

int main()
{
	int n;
	string a, b;
	cin >> n >> a >> b;
	a = standard(a, n);
	b = standard(b, n);
	if (a == b) 
		cout << "YES " << a;
	else cout << "NO " << a << " " << b;
    return 0;
}
```

