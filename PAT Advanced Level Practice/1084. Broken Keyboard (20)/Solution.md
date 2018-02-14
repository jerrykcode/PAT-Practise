# 1084. Broken Keyboard (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1084)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



On a broken keyboard, some of the keys are worn out. So when you type some sentences, the characters 
corresponding to those keys will not appear on screen.

Now given a string that you are supposed to type, and the string that you actually type out, please 
list those keys which are for sure worn out. 



## Input Specification: 

Each input file contains one test case. For each case, the 1st line contains the original string, and 
the 2nd line contains the typed-out string. Each string contains no more than 80 characters which are 
either English letters [A-Z] (case insensitive), digital numbers [0-9], or "_" (representing the space). 
It is guaranteed that both strings are non-empty. 



## Output Specification: 

For each test case, print in one line the keys that are worn out, in the order of being detected. The 
English letters must be capitalized. Each worn out key must be printed once only. It is guaranteed that 
there is at least one worn out key. 



## Sample Input:

7_This_is_a_test  
_hs_s_a_es  

## Sample Output:

7TI  


## 题意：

输入两个字符串，求第一个字符串中出现过而第二个字符串中没有出现过的字符，字母不分大小写，输出的字母按
大写

## 思路：

先把两个字符串中所有字母字符转为大写。用map<char, int>存储一个字符是否出现过。遍历第二个字符串，将其
所有字符在map中对应的值赋为1。遍历第一个字符串，若字符在map中对应的值为0，则输出此字符，并将此字符在
map中对应的值赋为1（防止重复输出）


##  代码：

[1084. Broken Keyboard (20)_2.cpp ](https://github.com/jerrykcode/PAT-Advanced-Level-Practise/blob/master/1084.%20Broken%20Keyboard%20(20)/1084.%20Broken%20Keyboard%20(20)_2.cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>

int main()
{
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	map<char, int> flags;
	for (int i = 0; i < s1.length(); i++) {
		if (isalpha(s1[i])) s1[i] = toupper(s1[i]);
		if (i < s2.length() && isalpha(s2[i])) s2[i] = toupper(s2[i]);
	}
	for (int i = 0; i < s2.length(); i++)
		flags[s2[i]] = 1;
	for (int i = 0; i < s1.length(); i++) 
		if (flags[s1[i]] == 0) {
			cout << s1[i];
			flags[s1[i]] = 1;
		}
    return 0;
}
```
