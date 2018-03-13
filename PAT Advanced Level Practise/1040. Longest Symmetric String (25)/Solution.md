# 1040. Longest Symmetric String (25)
[原题地址] ((https://www.patest.cn/contests/pat-a-practise/1040))
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a string, you are supposed to output the length of the longest symmetric sub-string. 
For example, given "Is PAT&TAP symmetric?", the longest symmetric sub-string is "s PAT&TAP s", 
hence you must output 11.



## Input Specification: 

Each input file contains one test case which gives a non-empty string of length no more than 1000.



## Output Specification: 

For each test case, simply print the maximum length in a line.



## Sample Input:

Is PAT&TAP symmetric?  

## Sample Output:

11  


## 题意：

求字符串str中最长的回文长度

## 思路：

本题思路参考了[1040. Longest Symmetric String (25) (柳婼 の blog)](https://www.liuchuo.net/archives/2104)

用二维数组：dp[i][j]表示str[i]到str[j]之间是否为回文，为1则是，为0则不是，有：
	
*	若　j - i >= 2：
	
	*	若str[i] == str[j]，则dp[i][j] = dp[i + 1][j - 1]
				
	*	若str[i] != str[j]，则dp[i][j] = 0
		
*	若　i == j，dp[i][j] = 1
	
*	若　j == i + 1，dp[i][j] = str[i] == str[j] ? 1 : 0
	
初始化dp[i][i] = 1，dp[i][i + 1] = str[i] == str[i + 1]? 1 : 0，(0 <= i < i + 1 < str.length())，
此时dp[i][j]对于 i == j || j == i + 1的i、j均已确定

l从3开始直到l <= str.length()，根据递推求dp[i][i + l - 1]		

在判断dp的同时记录当前最大的回文长度，最后输出


## 参考：

[1040. Longest Symmetric String (25) (柳婼 の blog)](https://www.liuchuo.net/archives/2104)


## 代码：
[1040. Longest Symmetric String (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1040.%20Longest%20Symmetric%20String%20(25)/1040.%20Longest%20Symmetric%20String%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	string str;
	getline(cin, str);
	int len = str.length(), result = 1;
	int **dp = new int*[len];
	for (int i = 0; i < len; i++) {
		dp[i] = new int[len];
	}
	for (int i = 0; i < len; i++) {
		dp[i][i] = 1; //str[i]到str[i]一定是回文
		if (i < len - 1 && str[i] == str[i + 1]) {
			dp[i][i + 1] = 1;
			result = 2;
		}
	}
	int l;
	for (l = 3; l <= len; l++) {
		for (int i = 0; i + l - 1 < len; i++) {
			int j = i + l - 1;
			if (str[i] == str[j] && dp[i + 1][j - 1]) {
				dp[i][j] = 1;
				result = l;
			}
		}
	}
	cout << result;
    return 0;
}

```
