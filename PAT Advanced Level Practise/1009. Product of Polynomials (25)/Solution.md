# 1009. Product of Polynomials (25)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


This time, you are supposed to find A*B where A and B are two polynomials.



## Input Specification: 

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of 
a polynomial: *K N1 aN1 N2 aN2 ... NK aNK*, where K is the number of nonzero terms in the polynomial, Ni and aNi 
(i=1, 2, ..., K) are the exponents and coefficients, respectively. 
It is given that 1 <= K <= 10, 0 <= NK < ... < N2 < N1 <=1000. 



## Output Specification: 

For each test case you should output the product of A and B in one line, with the same format as the input. 
Notice that there must be NO extra space at the end of each line. Please be accurate up to 1 decimal place.


 
## Sample Input
2 1 2.4 0 3.2  
2 2 1.5 1 0.5  

## Sample Output
3 3 3.6 2 6.0 1 1.6  


## 题意：

已知两个多项式，求积

## 思路：

本题思路参考 [柳婼 の blog  1009. Product of Polynomials(25)-PAT甲级真题](https://www.liuchuo.net/archives/2026)

用double类型的数组arr存储第一个多项式的值，arr[i]的值为指数为i的项的系数，用double数组product存储积多项式的值，
当输入第二个多项式的数据的时候，一边进行运算一边保存结果，最后按照指数递减的顺序输出所有不为0的项

## 参考：
[柳婼 の blog  1009. Product of Polynomials(25)-PAT甲级真题](https://www.liuchuo.net/archives/2026)


## 代码：

[1009. Product of Polynomials (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1009.%20Product%20of%20Polynomials%20(25)/1009.%20Product%20of%20Polynomials%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int k, k1, e;
	double c, arr[1001] = { 0.0 }, product[2001] = {0.0};
	cin >> k;
	for (int i = 0; i < k; i++) {
		scanf("%d %lf", &e, &c);
		arr[e] = c;
	}
	cin >> k1;
	for (int i = 0; i < k1; i++) {
		scanf("%d %lf", &e, &c);
		for (int j = 0; j < 1001; j++) {
			product[j + e] += arr[j] * c;
		}
	}
	int count = 0;
	for (int i = 0; i < 2001; i++)
		if (product[i] != 0.0)
			count++;
	cout << count ;
	for (int i = 2000; i >= 0; i--)
		if (product[i] != 0.0) 
			printf(" %d %.1f", i, product[i]);
    return 0;
}

```