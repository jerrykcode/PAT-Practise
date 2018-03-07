# 1065. A+B and C (64bit) (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1065)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 HOU, Qiming



Given three integers A, B and C in [-2^63, 2^63], you are supposed to tell whether A+B > C.



## Input Specification: 

The first line of the input gives the positive number of test cases, T (<=10). Then T test cases follow, 
each consists of a single line containing three integers A, B and C, separated by single spaces.



## Output Specification: 

For each test case, output in one line "Case #X: true" if A+B>C, or "Case #X: false" otherwise, where X 
is the case number (starting from 1). 



## Sample Input:

3  
1 2 3  
2 3 4  
9223372036854775807 -9223372036854775808 0  

## Sample Output:

Case #1: false  
Case #2: true  
Case #3: false  


## 题意：

输入a、b、c，范围[-2^63~2^63]，问a + b是否大于c

## 思路：

本题思路参考了(柳婼 の blog) https://www.liuchuo.net/archives/2023

用long long 可以表示[-2^63~2^63]，但a + b有可能溢出，故作判断：

* 若 a > 0 && b > 0 && a + b <= 0 溢出，由于c在long long范围内，所以 a + b 一定大于c
* 若 a < 0 && b < 0 && a + b >= 0 溢出，由于c在long long范围内，所以 a + b 一定小于c

## 代码：

[1065. A+B and C (64bit) (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1065.%20A+B%20and%20C%20(64bit)%20(20)/1065.%20A+B%20and%20C%20(64bit)%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	long long a, b, c;
	for (int i = 0; i < t; i++) {
		scanf("%lld %lld %lld", &a, &b, &c);
		long long sum = a + b;
		if (a > 0 && b > 0 && sum <= 0)
			printf("Case #%d: true\n", i + 1);
		else if (a < 0 && b < 0 && sum >= 0)
			printf("Case #%d: false\n", i + 1);
		else if (sum > c)
			printf("Case #%d: true\n", i + 1);
		else
			printf("Case #%d: false\n", i + 1);
	}
    return 0;
}
```
