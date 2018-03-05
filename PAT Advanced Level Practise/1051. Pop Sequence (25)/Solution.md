# 1051. Pop Sequence (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1051)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N 
and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop 
sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from 
the stack, but not 3, 2, 1, 7, 5, 6, 4.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 3 numbers (all 
no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and 
K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence 
of N numbers. All the numbers in a line are separated by a space.



## Output Specification: 

For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the 
stack, or "NO" if not.



## Sample Input:

5 7 5  
1 2 3 4 5 6 7  
3 2 1 7 5 6 4  
7 6 5 4 3 2 1  
5 6 4 3 7 2 1  
1 7 6 5 4 3 2  

## Sample Output:

YES  
NO  
NO  
YES  
NO  



## 题意：

输入栈的最大容量M，整数N，按1~N次序进栈，进栈过程中可以出栈，输入K个出栈序列，问是否是可能的序列

## 思路：

初始化空栈，若出栈序列中的元素：

* 1、 小于栈顶元素，肯定不可能
	
* 2、 大于栈顶元素，进栈直到与栈顶元素相等，若进栈过程中栈的size超过了M，则此序列不可能
	
* 3、 等于栈顶元素，或经过数次进栈后等于栈顶元素，栈顶元素出栈
	
遍历完出栈序列后，若没有判定为不可能，则为可能的序列

## 代码：

[1051. Pop Sequence (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1051.%20Pop%20Sequence%20(25)/1051.%20Pop%20Sequence%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <stack>

int main()
{
	int m, n, k;
	cin >> m >> n >> k;
	for (int i = 0; i < k; i++) {
		stack<int>s;
		int pushNumber = 1, sequence;
		int flag = 0;
		for (int j = 0; j < n; j++) {
			cin >> sequence;
			if (flag) continue;
			if (!s.empty() && sequence < s.top())  flag = 1;
			while (s.empty() || sequence > s.top()) {
				if (flag) break;
				if (s.size() < m)
					s.push(pushNumber++);
				else flag = 1;
			}
			if (flag) continue;
			s.pop();
		}
		cout << (flag ? "NO" : "YES") << endl;
	}
    return 0;
}
```

