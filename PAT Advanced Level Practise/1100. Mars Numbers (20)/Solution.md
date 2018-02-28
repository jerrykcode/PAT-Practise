# 1100. Mars Numbers (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1100)

* 时间限制 400 ms


* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 作者 CHEN, Yue



People on Mars count their numbers with base 13:
*  `Zero` on Earth is called *`"tret"`* on Mars. 
* The numbers `1 to 12` on Earch is called *`"jan, feb, mar, apr, may, jun, jly, aug, sep, oct, nov, dec"`* on Mars, respectively. 
* For the `next higher digit`, Mars people name the 12 numbers as *`"tam, hel, maa, huh, tou, kes, hei, elo, syy, lok, mer, jou"`*, respectively. 

For examples, the number 29 on Earth is called "hel mar" on Mars; and "elo nov" on Mars corresponds to 115 on Earth. In order to help communication between people from these two planets, you are supposed to write a program for mutual translation between Earth and Mars number systems. 

## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer N (< 100). Then N lines follow, each contains a number in [0, 169), given either in the form of an Earth number, or that of Mars.

## Output Specification: 

For each number, print in a line the corresponding number in the other language.
## Sample Input:
4  
29  
5  
elo nov  
tam  

## Sample Output:
hel mar  
may  
115  
13  

## 题意：

火星人使用的数字：
* `0` 为 *`“tret”`*
* `1 ~ 12` 为 *`"jan, feb, mar, apr, may, jun, jly, aug, sep, oct, nov, dec"`*
* 高位的数字 *`"tam, hel, maa, huh, tou, kes, hei, elo, syy, lok, mer, jou"`*

#### eg:
*`29`* 为 *`hel mar`*  
*`5`* 为 *`may`*  
*`115`* 为 *`elo nov`*  
*`13`* 为 *`tam`*  
*`26`* 为 *`hel`*  


输入N行，每行一个火星或地球数字，翻译成对应语言数字


## 代码：

[1100. Mars Numbers (20).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1100.%20Mars%20Numbers%20(20)/1100.%20Mars%20Numbers%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>

int main()
{
	string n1[12] = { "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec" };
	string n2[12] = { "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou" };
	map<string, int> string_to_int;
	for (int i = 0; i < 12; i++) {
		string_to_int[n1[i]] = i + 1;
		string_to_int[n2[i]] = (i + 1) * 13;
	}
	int n;
	cin >> n;
	cin.ignore();
	string number;
	for (int i = 0; i < n; i++) {
		getline(cin, number);
		if (isalpha(number[0])) { //Mars to Earth
			if (number == "tret") {
				printf("0\n");
				continue;
			}
			string a = "", b = "";
			int flag = 1;
			for (int i = 0; i < number.length(); i++) {
				if (flag) {
					if (number[i] != ' ') a += number[i];
					else flag = 0;
				}
				else b += number[i];
			}
			printf("%d\n", string_to_int[a] + string_to_int[b]);
		}
		else { //Earth to Mars
			int n = atoi(number.c_str());
			if (n == 0) {
				printf("tret\n");
				continue;
			}
			string result = "";
			if (n % 13 != 0)
				result = n1[n % 13 - 1];
			if (n / 13 != 0) {
				if (n % 13 != 0) result = " " + result;
				result = n2[n / 13 - 1] + result;
			}
			cout << result << endl;
		}
	}
    return 0;
}
```