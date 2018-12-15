# 1092. To Buy or Not to Buy (20)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1092)

* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Eva would like to make a string of beads with her favorite colors so she went to a small shop to buy some beads. 
There were many colorful strings of beads. However the owner of the shop would only sell the strings in whole pieces. 
Hence Eva must check whether a string in the shop contains all the beads she needs. She now comes to you for help: 
if the answer is "Yes", please tell her the number of extra beads she has to buy; or if the answer is "No", please 
tell her the number of beads missing from the string.

For the sake of simplicity, let's use the characters in the ranges [0-9], [a-z], and [A-Z] to represent the colors. 
For example, the 3rd string in Figure 1 is the one that Eva would like to make. Then the 1st string is okay since 
it contains all the necessary beads with 8 extra ones; yet the 2nd one is not since there is no black bead and one 
less red bead.

![Figure 1](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1092.jpg)
*Figure 1*



## Input Specification: 

Each input file contains one test case. Each case gives in two lines the strings of no more than 1000 beads which 
belong to the shop owner and Eva, respectively.



## Output Specification: 

For each test case, print your answer in one line. If the answer is "Yes", then also output the number of extra beads 
Eva has to buy; or if the answer is "No", then also output the number of beads missing from the string. There must be 
exactly 1 space between the answer and the number.



## Sample Input 1:

ppRYYGrrYBR2258  
YrR8RrY  

## Sample Output 1:

Yes 8  



## Sample Input 2:

ppRYYGrrYB225  
YrR8RrY  

## Sample Output 2:

No 2  



## 题意：

输入两个字符串（字符为'0'~'9'、'a'~'z'、'A'~'Z'，表示珠子的颜色）。若第二个字符串（Eva想要的所有珠子的颜色）的所
有字符在第一个字符串（出售的所有珠子的颜色）均出现（第二个字符串中重复出现的字符在第一个字符串中也要重复出现），
则出售的珠子符合条件，输出"Yes"，并输出第一个字符串中多余的字符个数；否则不符合条件，输出"No"，并输出第二个字符串
中缺失的字符个数


## 思路：

第一个字符串设为shop; 第二个字符串设为eva

'0'~'9'、'a'~'z'、'A'~'Z'共61个字符，故用 int fre[61] 数组存储每个字符在eva中出现的次数。shop多余的字符数量extra初始
化为0，缺失的字符个数missing初始化为eva的长度。遍历shop字符串，对每个字符shop[i]，若 fre[getIndex(shop[i])] == 0，则
这是一个多余字符，extra++，若 fre[getIndex(shop[i])] > 0，则fre[getIndex(shop[i])]--，missing-- 。getIndex是字符转为
在fre中的下标的函数。最后若 missing == 0 则符合条件，否则不符合


## 代码：

[1092. To Buy or Not to Buy (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1092.%20To%20Buy%20or%20Not%20to%20Buy%20(20)/1092.%20To%20Buy%20or%20Not%20to%20Buy%20(20).cpp)

```cpp
#include <iostream>
using namespace std;
#include <string>

int getIndex(char c)
{
	if (c >= '0' && c <= '9') return (int)c - (int)'0';
	else if (islower(c)) return (int)c - (int)'a' + 10;
	else return (int)c - (int)'A' + 36;
}

int main()
{
	int fre[61];
	fill(fre, fre + 61, 0);
	string shop, eva;
	cin >> shop >> eva;
	for (int i = 0; i < eva.length(); i++)
		fre[getIndex(eva[i])] ++; //出现次数++
	int missing = eva.length(); //缺失的珠子数量
	int extra = 0; //多余的珠子数量
	for (int i = 0; i < shop.length(); i++) {
		if (fre[getIndex(shop[i])] == 0) extra++; //多余
		else {
			fre[getIndex(shop[i])]--;
			missing--;
		}
	}
	if (missing == 0) printf("Yes %d\n", extra); //无缺失
	else printf("No %d\n", missing);
    return 0;
}
```