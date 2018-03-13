# 1077. Kuchiguse (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1077)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 HOU, Qiming



The Japanese language is notorious for its sentence ending particles. Personal preference of such 
particles can be considered as a reflection of the speaker's personality. Such a preference is called 
"Kuchiguse" and is often exaggerated artistically in Anime and Manga. For example, the artificial 
sentence ending particle "nyan~" is often used as a stereotype for characters with a cat-like personality:

*Itai nyan~ (It hurts, nyan~)*
*Ninjin wa iyada nyan~ (I hate carrots, nyan~)*

Now given a few lines spoken by the same character, can you find her Kuchiguse?



## Input Specification: 

Each input file contains one test case. For each case, the first line is an integer N (2<=N<=100). Following 
are N file lines of 0~256 (inclusive) characters in length, each representing a character's spoken line. The 
spoken lines are case sensitive.



## Output Specification: 

For each test case, print in one line the kuchiguse of the character, i.e., the longest common suffix of all 
N lines. If there is no such suffix, write "nai".


## Sample Input 1:

3  
Itai nyan~  
Ninjin wa iyadanyan~  
uhhh nyan~  

## Sample Output 1:

nyan~  



## Sample Input 2:

3  
Itai!  
Ninjinnwaiyada T_T  
T_T  

## Sample Output 2:

nai  



## 题意：

输出N个字符串的相同后缀，没有则输出"nai"

## 思路：

最先输入的字符串设为s，int begin = 0设为第一个字符串中后缀开始的字符的位置。输入之后的N - 1个
字符串，从后往前遍历求最先与s不相同的字符从而确定begin

## 代码：

[1077. Kuchiguse (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1077.%20Kuchiguse%20(20)/1077.%20Kuchiguse%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	int n, begin = 0;
	scanf("%d", &n);
	string s, s1;
	cin.ignore();
	getline(cin, s);
	for (int i = 1; i < n; i++) {
		getline(cin, s1);
		int a = s.length() - 1, b = s1.length() - 1;
		while (a >= 0 && b >= 0) {
			if (s[a] == s1[b]) {
				a--;
				b--;
			}
			else break;
		}
		if (a + 1 > begin) begin = a + 1;
	}
	if (begin == s.length()) cout << "nai";
	else cout << s.substr(begin, s.length() - begin);
    return 0;
}
```