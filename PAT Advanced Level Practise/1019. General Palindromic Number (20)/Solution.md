# 1019. General Palindromic Number (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1019)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



A number that will be the same when it is written forwards or backwards is known as a Palindromic Number. 
For example, 1234321 is a palindromic number. All single digit numbers are palindromic numbers. 

Although palindromic numbers are most often considered in the decimal system, the concept of palindromicity 
can be applied to the natural numbers in any numeral system. Consider a number N > 0 in base b >= 2, where 
it is written in standard notation with k+1 digits ai as the sum of (aibi) for i from 0 to k. Here, as usual, 
0 <= ai < b for all i and ak is non-zero. Then N is palindromic if and only if ai = ak-i for all i. Zero is 
written 0 in any base and is also palindromic by definition. 

Given any non-negative decimal integer N and a base b, you are supposed to tell if N is a palindromic number 
in base b. 



## Input Specification: 

Each input file contains one test case. Each case consists of two non-negative numbers N and b, where 0 <= N <= 10^9 
is the decimal number and 2 <= b <= 10^9 is the base. The numbers are separated by a space. 



## Output Specification: 

For each test case, first print in one line "Yes" if N is a palindromic number in base b, or "No" if not. Then in 
the next line, print N as the number in base b in the form "ak ak-1 ... a0". Notice that there must be no extra 
space at the end of output. 




## Sample Input 1:

27 2  

## Sample Output 1:

Yes  
1 1 0 1 1  


## Sample Input 2:

121 5  

## Sample Output 2:

No  
4 4 1  



## 题意：

若一个非负整数从左到右和从右到左写一样，则称为回文，输入一个10进制的非负整数N，判断在b进制下是否为回文(0在任何进制下
均为回文)，并输出N在b进制下的字符

## 思路:

b最大可以为10^9，字母无法表示，所以每个字符用其10进制的数值表示

N%b存储到vector <int>中，N更新为N/b，循环直到N==0，vector中存储了N在b进制下每个字符的10进制数值，若vector中每个i与对应
的size() - i - 1相同则为回文，最后逆序输出vector中的值

## 代码：

[1019. General Palindromic Number (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1019.%20General%20Palindromic%20Number%20(20)/1019.%20General%20Palindromic%20Number%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int n, b;
	cin >> n >> b;
	vector<int> nbase;
	if (n == 0) {
		cout << "Yes\n";
		cout << "0";
		return 0;
	}
	while (n != 0) {
		nbase.push_back(n%b);
		n /= b;
	}
	int flag = 0;
	for (int i = 0; i < nbase.size()/2; i++)
		if (nbase.at(i) != nbase.at(nbase.size() - i - 1)) {
			cout << "No\n";
			flag = 1;
			break;
		}
	if (!flag)
		cout << "Yes\n";
	cout << nbase.at(nbase.size() - 1);
	for (int i = 1; i < nbase.size(); i++)
		cout << " " << nbase.at(nbase.size() - i - 1);
    return 0;
}

```