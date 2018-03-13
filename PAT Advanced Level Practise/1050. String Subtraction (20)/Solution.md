# 1050. String Subtraction (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1050)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given two strings S1 and S2, S = S1 - S2 is defined to be the remaining string after taking all 
the characters in S2 from S1. Your task is simply to calculate S1 - S2 for any given strings. 
However, it might not be that simple to do it fast.


## Input Specification: 

Each input file contains one test case. Each case consists of two lines which gives S1 and S2, 
respectively. The string lengths of both strings are no more than 10^4. It is guaranteed that all 
the characters are visible ASCII codes and white space, and a new line character signals the end 
of a string.



## Output Specification: 

For each test case, print S1 - S2 in one line. 



## Sample Input:

They are students.  
aeiou  

## Sample Output:

Thy r stdnts.  



## 题意：

输入两个字符串，输出第一个字符串删除掉第二个字符串中的所有字符后的结果

## 思路：

本题参考了 [1050. String Subtraction (20) 柳婼 の blog](https://www.liuchuo.net/archives/2130) (以前这么简单的题自己都做不出~~~)

用int flag[256]数组，所有元素初始化为0，遍历并标记二个字符串的所有字符flag[s2[i]]为1，再遍历第一
个字符串的所有字符，只输出flag[s1[i]]为0的

## 参考：

[1050. String Subtraction (20) 柳婼 の blog](https://www.liuchuo.net/archives/2130)


## 代码：

[1050. String Subtraction (20)](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1050.%20String%20Subtraction%20(20)/1050.%20String%20Subtraction%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string.h>

int main()
{
	char s1[10001], s2[10001];
	cin.getline(s1, 10001);
	cin.getline(s2, 10001);
	int flag[256];
	fill(flag, flag + 256, 0);
	for (int i = 0; i < strlen(s2); i++)
		flag[s2[i]] = 1;
	for (int i = 0; i < strlen(s1); i++)
		if (!flag[s1[i]])
			cout << s1[i];
    return 0;
}
```
