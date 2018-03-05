# 1088. Rational Arithmetic (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1088)


* 时间限制 200 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



For two rational numbers, your task is to implement the basic arithmetics, that is, to calculate their sum, difference, product and quotient.

## Input Specification: 

Each input file contains one test case, which gives in one line the two rational numbers in the format "a1/b1 a2/b2". The numerators and the denominators are all in the range of long int. If there is a negative sign, it must appear only in front of the numerator. The denominators are guaranteed to be non-zero numbers.

## Output Specification: 

For each test case, print in 4 lines the sum, difference, product and quotient of the two rational numbers, respectively. The format of each line is "number1 operator number2 = result". Notice that all the rational numbers must be in their simplest form "k a/b", where k is the integer part, and a/b is the simplest fraction part. If the number is negative, it must be included in a pair of parentheses. If the denominator in the division is zero, output "Inf" as the result. It is guaranteed that all the output integers are in the range of long int.

## Sample Input 1:  
2/3 -4/2  

## Sample Output 1:  

2/3 + (-2) = (-1 1/3)  
2/3 - (-2) = 2 2/3  
2/3 * (-2) = (-1 1/3)  
2/3 / (-2) = (-1/3)  

## Sample Input 2:  

5/3 0/6  

## Sample Output 2:  

1 2/3 + 0 = 1 2/3  
1 2/3 - 0 = 1 2/3  
1 2/3 * 0 = 0  
1 2/3 / 0 = Inf  

## 代码：

[1088. Rational Arithmetic (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1088.%20Rational%20Arithmetic%20(20)/1088.%20Rational%20Arithmetic%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

long long int gcd(long long int a, long long int b)
{
	return a == 0 ? abs(b) : gcd(b%a, a);
}

string fraction(long long int a, long long int b)
{
	if (b == 0) return "Inf";
	if (a == 0) return "0";
	string result = "";
	if (a < 0)result += "(";
	long long int integer = a / b;
	if (integer != 0) {
		result += to_string(integer);
		a -= b * integer;
		if (a != 0) result += " ";
		if (integer < 0 && a < 0) a *= -1;
	}
	if (a != 0) {
		result += to_string(a);
		if (b != 1)result += "/" + to_string(b);
	}
	if (a < 0 || integer < 0) result += ")";
	return result;
}

int main()
{
	long long int a1, b1, a2, b2;
	scanf("%lld/%lld %lld/%lld", &a1, &b1, &a2, &b2);
	long long int g = gcd(a1, b1);
	a1 /= g;
	b1 /= g;
	g = gcd(a2, b2);
	a2 /= g;
	b2 /= g;
	long long int a = a1 * b2 + a2 * b1;
	long long int b = b1 * b2;
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " + " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
	a = a1 * b2 - a2 * b1;
	b = b1 * b2;
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " - " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
	a = a1 * a2;
	b = b1 * b2;
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " * " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
	a = a1 * b2 ;
	b = b1 * a2;
	if (b < 0) {
		b *= -1;
		a *= -1;
	}
	g = gcd(a, b);
	a /= g;
	b /= g;
	cout << fraction(a1, b1) << " / " << fraction(a2, b2) << " = " << fraction(a, b) << endl;
    return 0;
}
```