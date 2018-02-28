# 1031. Hello World for U (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1031)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given any string of N (>=5) characters, you are asked to form the characters into the shape of U. 
For example, "helloworld" can be printed as:

h  d  
e  l  
l  r  
lowo  

That is, the characters must be printed in the original order, starting top-down from the left vertical 
line with n1 characters, then left to right along the bottom line with n2 characters, and finally bottom-up 
along the vertical line with n3 characters. And more, we would like U to be as squared as possible -- that 
is, it must be satisfied that n1 = n3 = max { k| k <= n2 for all 3 <= n2 <= N } with n1 + n2 + n3 - 2 = N.



## Input Specification: 

Each input file contains one test case. Each case contains one string with no less than 5 and no more than 80 
characters in a line. The string contains no white space.



## Output Specification: 

For each test case, print the input string in the shape of U as specified in the description.

## Sample Input:

helloworld!  

## Sample Output:

h   !  
e   d  
l   l  
lowor  



## 题意：

输入一个字符串(n个字符)，将字符按"U"("|_|")形输出。输出从左上到底部有n1个字符，底部有n2个字符，从
底部到右上有n3个字符。满足n1 == n3，n1 <= n2，3 <= n2 <= n，n1 + n2 + n3 - 2 = n ，n1尽量大

## 思路：

for (int i = 3; i <= n; i++) 若n2 = i，则n1 = n3 = (n + 2 - i) / 2，若此时(n + 2 - i) / 2 <= n2，且
以(n + 2 - i) / 2作为n1使n1更大，则更新n1 = (n + 2 - i) / 2，循环结束后通过n1算出n2，按U形输出


## 代码：

[1031. Hello World for U (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1031.%20Hello%20World%20for%20U%20(20)/1031.%20Hello%20World%20for%20U%20(20)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	string str;
	cin >> str;
	int n1 = 0, n2, n = str.length();
	for (int i = 3; i <= n; i++) { //若n2 = i
		if ((n + 2 - i) / 2 <= i && (n + 2 - i) / 2 > n1)
			n1 = (n + 2 - i) / 2;
	}
	n2 = n + 2 - 2 * n1;
	for (int i = 0; i < n1; i++) {
		cout << str[i];
		for (int j = 0; j < n2 - 2; j++)
			cout << (i == n1 - 1 ? str[n1 + j] : ' ');
		cout << str[n - i - 1] << endl;
	}
	
    return 0;
}
```
