# 1061. Dating (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1061)
* 时间限制 150 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Sherlock Holmes received a note with some strange strings: "Let's date! 3485djDkxh4hhGE 2984akDfkkkkggEdsb s&hgsfdk d&Hyscvnm". 
It took him only a minute to figure out that those strange strings are actually referring to the coded time "Thursday 14:04" -- 
since the first common capital English letter (case sensitive) shared by the first two strings is the 4th capital letter 'D', 
representing the 4th day in a week; the second common character is the 5th capital letter 'E', representing the 14th hour (hence 
the hours from 0 to 23 in a day are represented by the numbers from 0 to 9 and the capital letters from A to N, respectively); 
and the English letter shared by the last two strings is 's' at the 4th position, representing the 4th minute. Now given two pairs 
of strings, you are supposed to help Sherlock decode the dating time.


## Input Specification: 

Each input file contains one test case. Each case gives 4 non-empty strings of no more than 60 characters without white space in 
4 lines.



## Output Specification: 

For each test case, print the decoded time in one line, in the format "DAY HH:MM", where "DAY" is a 3-character abbreviation for the 
days in a week -- that is, "MON" for Monday, "TUE" for Tuesday, "WED" for Wednesday, "THU" for Thursday, "FRI" for Friday, "SAT" for 
Saturday, and "SUN" for Sunday. It is guaranteed that the result is unique for each case.



## Sample Input:

3485djDkxh4hhGE  
2984akDfkkkkggEdsb  
s&hgsfdk  
d&Hyscvnm  

Sample Output:

THU 14:04  


## 题意：

两个字符串中第一个相同的大写字母A~G表示星期一到星期天，在确定星期之后，第一个相同的数字或大写字母A~N，表示小时0~9，10~23，此时
再输入两个字符串，他们第一个相同的字母(大写、小写均可)在字符串中的位置表示分钟，输入4个字符串输出日期时间

## 代码：

[1061. Dating (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1061.%20Dating%20(20)/1061.%20Dating%20(20).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	string day[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
	int flag = 0;
	for (int i = 0; i < s1.length() && i < s2.length(); i++) {
		if (s1[i] == s2[i]) {
			if (!flag) { //没有确定星期
				if (s1[i] >= 'A' && s1[i] <= 'G') {
					cout << day[s1[i] - 'A'] << " ";
					flag = 1; //已确定星期
				}
				else continue;
			}
			else {//已确定星期
				if (isdigit(s1[i])) printf("%02d:", (s1[i] - '0')); //数字或'A'~'N'则确定小时
				else if (s1[i] >= 'A' && s1[i] <= 'N') printf("%02d:", (s1[i] - 'A' + 10));
				else continue;
				break;
			}
		}
	}
	cin >> s1 >> s2;
	for (int i = 0; i < s1.length() && i < s2.length(); i++) //确定分钟
		if (s1[i] == s2[i] && (islower(s1[i]) || isupper(s1[i])))
			printf("%02d", i);
    return 0;
}
```
