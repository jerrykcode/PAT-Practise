# 1108. Finding Average (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1108)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



The basic task is simple: given N real numbers, you are supposed to calculate their average. But what makes it complicated is that some of the input numbers might not be legal. A "legal" input is a real number in [-1000, 1000] and is accurate up to no more than 2 decimal places. When you calculate the average, those illegal numbers must not be counted in.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=100). Then N numbers are given in the next line, separated by one space. 

## Output Specification: 

For each illegal input number, print in a line "ERROR: X is not a legal number" where X is the input. Then finally print in a line the result: "The average of K numbers is Y" where K is the number of legal inputs and Y is their average, accurate to 2 decimal places. In case the average cannot be calculated, output "Undefined" instead of Y. In case K is only 1, output "The average of 1 number is Y" instead. 
## Sample Input 1:  
7  
5 -3.2 aaa 9999 2.3.4 7.123 2.35  

## Sample Output 1:  
ERROR: aaa is not a legal number  
ERROR: 9999 is not a legal number  
ERROR: 2.3.4 is not a legal number  
ERROR: 7.123 is not a legal number  
The average of 3 numbers is 1.38  

## Sample Input 2:  
2  
aaa -9999  

## Sample Output 2:  
ERROR: aaa is not a legal number  
ERROR: -9999 is not a legal number  
The average of 0 numbers is Undefined  

## 代码：


[1108. Finding Average (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1108.%20Finding%20Average%20(20)/1108.%20Finding%20Average%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	int n;
	cin >> n;
	int k = 0;
	double total = 0.0;
	for (int i = 0; i < n; i++) {
		string number;
		cin >> number;
		int flag = 0, count = 0;
		double n;
		for (int j = 0; j < number.length(); j++) {
			if (flag) count++;
			if (isdigit(number[j])) continue;
			if (number[j] == '-' && j == 0) continue;
			if (number[j] == '.' && j != 0 && flag == 0) {
				flag = 1;
				continue;
			}
			goto ERROR;
		}
		if (count > 2) goto ERROR;
		n = atof(number.c_str());
		if (n < -1000 || n > 1000) goto ERROR;
		k++;
		total += n;
		continue;
	ERROR: {
		cout << "ERROR: " << number << " is not a legal number" << endl;
		}
	}
	if (k == 1) printf("The average of %d number is ", k);
	else printf("The average of %d numbers is ", k);
	if (k) printf("%.2f\n", total/k);
	else printf("Undefined\n");
    return 0;
}

```