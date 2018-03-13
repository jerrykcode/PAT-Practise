# 1081. Rational Sum (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1081)


* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given N rational numbers in the form "*numerator/denominator*", you are supposed to calculate their sum.

## Input Specification: 

Each input file contains one test case. Each case starts with a positive integer N (<=100), followed in the next line N rational numbers "a1/b1 a2/b2 ..." where all the numerators and denominators are in the range of "long int". If there is a negative number, then the sign must appear in front of the numerator.

## Output Specification: 

For each test case, output the sum in the simplest form "integer numerator/denominator" where "integer" is the integer part of the sum, "numerator" < "denominator", and the numerator and the denominator have no common factor. You must output only the fractional part if the integer part is 0.
## Sample Input 1:  
5  
2/5 4/15 1/30 -2/60 8/3  

## Sample Output 1:  
3 1/3  

## Sample Input 2:  
2  
4/3 2/3  

## Sample Output 2:  
2  

## Sample Input 3:  
3  
1/3 -1/6 1/8  

## Sample Output 3:    
7/24  


## 题意：

输入N个分数求和


## 思路：
本题思路参考：[1081. Rational Sum (20) (柳婼 の blog)](https://www.liuchuo.net/archives/2108)  
对输入的每一个分数的分子与分母，求最大公约数，约分，与分数和（初始化为0/1）相加，相加之后再约分。

## 参考：
[1081. Rational Sum (20) (柳婼 の blog)](https://www.liuchuo.net/archives/2108)

## 代码：


[1081. Rational Sum (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1081.%20Rational%20Sum%20(20)/1081.%20Rational%20Sum%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	return a == 0 ? abs(b) : gcd(b%a, a);
}

int main()
{
	int n;
	cin >> n;
	int nsum = 0, dsum = 1; // 0/1
	for (int i = 0; i < n; i++) {
		int numerator, denominator;
		scanf("%d/%d", &numerator, &denominator);
		int com = gcd(numerator, denominator);
		numerator /= com;
		denominator /= com;
		nsum = nsum * denominator + dsum * numerator;
		dsum = denominator * dsum;
		com = gcd(nsum, dsum);
		nsum /= com;
		dsum /= com;
	}
	int integer = nsum / dsum;
	nsum -= dsum * integer;
	if (integer != 0) {
		cout << integer;
		if (nsum != 0) cout << " ";
	}
	if(nsum != 0) printf("%d/%d", nsum, dsum);
	if (integer == 0 && nsum == 0) cout << 0;
    return 0;
}
```