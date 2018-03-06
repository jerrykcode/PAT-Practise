# 1059. Prime Factors (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1059)

* 时间限制 100 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 HE, Qinming



Given any positive integer N, you are supposed to find all of its prime factors, and write them in the 
format *N = p1^k1 * p2^k2 *…*pm^km.*

## Input Specification: 

Each input file contains one test case which gives a positive integer N in the range of long int.

## Output Specification: 

Factor N in the format N = p1^k1 * p2^k2 *…*pm^km, where pi's are prime factors of N in increasing order, 
and the exponent ki is the number of pi -- hence when there is only one pi, ki is 1 and must NOT be printed 
out.


## Sample Input:

97532468

## Sample Output:

97532468=2^2\*11\*17\*101\*1291

## 题意：

输入一个long int范围内的整数N，输出分解质因数的结果: N = p1^k1 \* p2^k2 \*…\*pm^km，ki为因数pi出现的次数，为
1则忽略


## 思路：

将质因数存储在vector中，排序，对每个因数求相同因数的个数


## 代码：
[1059. Prime Factors (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1059.%20Prime%20Factors%20(25)/1059.%20Prime%20Factors%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int main()
{
	long n;
	cin >> n;
	printf("%d=", n);
	vector<long> primeFactors;
	for (int i = 2; i <= n; i++) {
		while (n != i) {
			if (n %i == 0) {
				primeFactors.push_back(i);
				n /= i;
			}
			else break;
		}
	}
	primeFactors.push_back(n);
	sort(primeFactors.begin(), primeFactors.end());
	int count = 1;
	int flag = 0;
	for (int i = 0; i < primeFactors.size(); i++) {
		if (i + 1 < primeFactors.size() && primeFactors[i] == primeFactors[i + 1]) count++;
		else {
			if (flag)
				cout << "*";
			else flag = 1;
			cout << primeFactors[i];
			if (count > 1) printf("^%d", count);
			count = 1;
		}
	}
    return 0;
}
```