# 1002. A+B for Polynomials (25)



* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



This time, you are supposed to find A+B where A and B are two polynomials.



## Input

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information 
of a polynomial: K N1 aN1 N2 aN2 ... NK aNK, where K is the number of nonzero terms in the polynomial, 
Ni and aNi (i=1, 2, ..., K) are the exponents and coefficients, respectively. 
It is given that 1 <= K <= 10，0 <= NK < ... < N2 < N1 <=1000. 



## Output

For each test case you should output the sum of A and B in one line, with the same format as the input. 
Notice that there must be NO extra space at the end of each line. Please be accurate to 1 decimal place. 


## Sample Input
2 1 2.4 0 3.2
2 2 1.5 1 0.5



## Sample Output
3 2 1.5 1 2.9 0 3.2



## 题意：

输入2个多项式(格式：K N1 aN1 N2 aN2 ... NK aNK，K为非0项数，Ni为指数， aNi为系数, 1 <= i <= k ), 按同样格式输出２个多项式的和


## 思路：

用数组Ae, Ac存储多项式A(长度为AL)的指数和系数，数组Be, Bc存储多项式B(长度为BL)的指数和系数，
数组Me,Mc(长度定义为AL+BL)存储和的指数和系数

## 代码：

[1002. A+B for Polynomials (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1002.%20A%2BB%20for%20Polynomials%20(25)/1002.%20A%2BB%20for%20Polynomials%20(25).cpp)



```cpp
#include "stdafx.h"
#include <iostream>

using namespace std;

void Merge(float *Ae, float *Ac, int AL, float *Be, float *Bc, int BL)
{	/* Merge 2 polynomial */
	float *Me = new float[AL + BL];
	float *Mc = new float[AL + BL];
	int i = 0, j = 0, flag = 0, count = 0;
	while (i < AL && j < BL) {
		if (Ae[i] > Be[j]) {
			Me[count] = Ae[i];
			Mc[count++] = Ac[i++];
		}
		else if (Ae[i] < Be[j]) {
			Me[count] = Be[j];
			Mc[count++] = Bc[j++];
		}
		else {
			if (Ac[i] + Bc[j] != 0) {
				Me[count] = Ae[i];
				Mc[count++] = Ac[i] + Bc[j];
			}
			i++;
			j++;
		}
	}//while
	while (i < AL) {
		Me[count] = Ae[i];
		Mc[count++] = Ac[i++];
	}
	while (j < BL) {
		Me[count] = Be[j];
		Mc[count++] = Bc[j++];
	}
	printf("%d", count);
	for (i = 0; i < count; i++)
		printf(" %.0f %.1f", Me[i], Mc[i]);
}

int main()
{
	int i;
	/* 输入多项式Ａ：*/
	int AL;
	cin >> AL;
	float *Ae = new float[AL];
	float *Ac = new float[AL];
	for (i = 0; i < AL; i++)
		cin >> Ae[i] >> Ac[i];
	/* Input polynomial B: */
	int BL;
	cin >> BL;
	float *Be = new float[BL];
	float *Bc = new float[BL];
	for (i = 0; i < BL; i++)
		cin >> Be[i] >> Bc[i];
	Merge(Ae, Ac, AL, Be, Bc, BL);
	return 0;
}
```