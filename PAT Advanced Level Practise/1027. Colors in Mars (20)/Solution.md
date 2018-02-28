# 1027. Colors in Mars (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1027)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



People in Mars represent the colors in their computers in a similar way as the Earth people. 
That is, a color is represented by a 6-digit number, where the first 2 digits are for Red, 
the middle 2 digits for Green, and the last 2 digits for Blue. The only difference is that 
they use radix 13 (0-9 and A-C) instead of 16. Now given a color in three decimal numbers 
(each between 0 and 168), you are supposed to output their Mars RGB values.



## Input

Each input file contains one test case which occupies a line containing the three decimal 
color values. 



## Output

For each test case you should output the Mars RGB value in the following format: first output 
"#", then followed by a 6-digit number where all the English characters must be upper-cased. 
If a single color is only 1-digit long, you must print a "0" to the left. 



## Sample Input

15 43 71  

## Sample Output

\#123456



## 题意：

火星人用6个13进制字符表示颜色(0~9 & A~C)，(rrggbb)，前两个字符表示红，中间两个表示绿，最后两个
表示蓝，输入三个10进制数表示的红、绿、蓝，输出火星人的颜色字符

## 思路：

输入的三个数字改为13进制后按要求格式输出

## 代码：

[1027. Colors in Mars (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1027.%20Colors%20in%20Mars%20(20)/1027.%20Colors%20in%20Mars%20(20).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

string toRadix13(int n)
{
	string result = ""; //13进制的结果
	char hash[3] = { 'A', 'B', 'C' };
	while (n != 0) {
		char digit = n % 13 >= 10 ? hash[n % 13 - 10] :(n % 13) + '0';
		result = digit + result;
		n /= 13;
	}
	while (result.length() < 2)
		result = "0" + result;
	return result;
}

int main()
{
	int r, g, b;
	cin >> r >> g >> b;
	cout<<"#"<<toRadix13(r)<<toRadix13(g)<<toRadix13(b);
    return 0;
}

```