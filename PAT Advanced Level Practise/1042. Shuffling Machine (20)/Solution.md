# 1042. Shuffling Machine (20)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1042)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue


Shuffling is a procedure used to randomize a deck of playing cards. Because standard shuffling 
techniques are seen as weak, and in order to avoid "inside jobs" where employees collaborate with 
gamblers by performing inadequate shuffles, many casinos employ automatic shuffling machines. 
Your task is to simulate a shuffling machine.



The machine shuffles a deck of 54 cards according to a given random order and repeats for a given 
number of times. It is assumed that the initial status of a card deck is in the following order:

*S1, S2, ..., S13, H1, H2, ..., H13, C1, C2, ..., C13, D1, D2, ..., D13, J1, J2*

where "S" stands for "Spade", "H" for "Heart", "C" for "Club", "D" for "Diamond", and "J" for "Joker". 
A given order is a permutation of distinct integers in [1, 54]. If the number at the i-th position 
is j, it means to move the card from position i to position j. For example, suppose we only have 5 
cards: S3, H5, C1, D13 and J2. Given a shuffling order {4, 2, 5, 3, 1}, the result will be: J2, H5, 
D13, S3, C1. If we are to repeat the shuffling again, the result will be: C1, H5, S3, J2, D13.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive integer 
K (<= 20) which is the number of repeat times. Then the next line contains the given order. All the 
numbers in a line are separated by a space.



## Output Specification: 

For each test case, print the shuffling results in one line. All the cards are separated by a space, 
and there must be no extra space at the end of the line.



## Sample Input:


2  
36 52 37 38 3 39 40 53 54 41 11 12 13 42 43 44 2 4 23 24 25 26 27 6 7 8 48 49 50 51 9 10 14 15 16 5 17 18 19 1 20 21 22 28 29 30 31 32 33 34 35 45 46 47  


## Sample Output:

S7 C11 C10 C12 S1 H7 H8 H9 D8 D9 S11 S12 S13 D10 D11 D12 S3 S4 S6 S10 H1 H2 C13 D2 D3 D4 H6 H3 D13 J1 J2 C1 C2 C3 C4 D1 S5 H5 H11 H12 C6 C7 C8 C9 S2 S8 S9 H10 D5 D6 D7 H4 H13 C5  



## 题意：

模拟洗牌，开始牌的排序为{S1, S2, ..., S13, H1, H2, ..., H13, C1, C2, ..., C13, D1, D2, ..., D13, J1, J2}，
输入洗牌顺序，若第i个输入的元素为j，说明原来第i个位置的元素放到第j个位置，循环洗牌k次，输出洗牌后的结果

## 思路：

用数组start、end分别存储洗牌前、洗牌后的牌，(牌用数字0~53表示，最后再用除13及取余来得到牌的输出格式，
这一点参考了[1042. Shuffling Machine (20) (柳婼 の blog)](https://www.liuchuo.net/archives/2019 )，数组shuffle存储洗牌顺序，循环k次，
每次start中的值根据shuffle来确定在end中的位置


## 参考：

[1042. Shuffling Machine (20) (柳婼 の blog)](https://www.liuchuo.net/archives/2019 )


## 代码：

[1042. Shuffling Machine (20).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1042.%20Shuffling%20Machine%20(20)/1042.%20Shuffling%20Machine%20(20).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int start[54], end[54], shuffle[54], k;
	for (int i = 0; i < 54; i++)
		start[i] = i; //初始化
	cin >> k;
	for (int i = 0; i < 54; i++)
		cin >> shuffle[i];
	for (int i = 0; i < k; i++) { //k次
		for (int j = 0; j < 54; j++)
			end[shuffle[j] - 1] = start[j]; //根据shuffle确定start中的元素在end中的位置
		for (int j = 0; j < 54; j++)
			start[j] = end[j];
	}
	char deck[5] = {'S', 'H', 'C', 'D', 'J'};
	for (int i = 0; i < 54; i++) {
		printf("%c%d", deck[end[i]/13], end[i]%13 + 1);
		if (i != 53) putchar(' ');
	}
    return 0;
}
```
