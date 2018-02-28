# 1015. Reversible Primes (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1015)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



A reversible prime in any number system is a prime whose "reverse" in that number system is also a prime. 
For example in the decimal system 73 is a reversible prime because its reverse 37 is also a prime. 

Now given any two positive integers N (< 105) and D (1 < D <= 10), you are supposed to tell if N is a 
reversible prime with radix D. 



## Input Specification: 

The input file consists of several test cases. Each case occupies a line which contains two integers N and D. 
The input is finished by a negative N.



## Output Specification: 

For each test case, print in one line "Yes" if N is a reversible prime with radix D, or "No" if not.



## Sample Input:

73 10  
23 2  
23 10  
-2  

## Sample Output:

Yes  
Yes  
No  



## 题意：

输入正整数N与D，若N（10进制）是素数且N在D进制中的值的逆序也是素数（在10进制中判断是否为素数），则输出"Yes"，
否则输出"No"

## 代码：

[1015. Reversible Primes (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1015.%20Reversible%20Primes%20(20)/1015.%20Reversible%20Primes%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <stack>
#include <math.h>

bool isPrime(int n)
{
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (!(n % 2))return false;
	int i;
	for (i = sqrt(n); i > 2; i--)
		if (!(n % i)) break;
	return i == 2;
}

int main()
{
	int n, d, reverse;
	stack<int>s;
	while (1) {
		cin >> n;
		if (n < 0) break;
		cin >> d;
		if (!isPrime(n)) { cout << "No\n"; continue; }
		reverse = 0;
		int count = 0;
		do { 
			s.push(n%d);
			n /= d;
		} while (n != 0);
		while (!s.empty()) { reverse += s.top()*pow(d, count++); s.pop(); }
		if(isPrime(reverse)) cout << "Yes\n";
		else cout << "No\n";
	}
    return 0;
}
```

