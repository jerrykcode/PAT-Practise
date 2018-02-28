# 1109. Group Photo (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1109)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



Formation is very important when taking a group photo. Given the rules of forming K rows with N people as the following:
• The number of people in each row must be N/K (round down to the nearest integer), with all the extra people (if any) standing in the last row; 
• All the people in the rear row must be no shorter than anyone standing in the front rows; 
• In each row, the tallest one stands at the central position (which is defined to be the position (m/2+1), where m is the total number of people in that row, and the division result must be rounded down to the nearest integer); 
• In each row, other people must enter the row in non-increasing order of their heights, alternately taking their positions first to the right and then to the left of the tallest one (For example, given five people with their heights 190, 188, 186, 175, and 170, the final formation would be 175, 188, 190, 186, and 170. Here we assume that you are facing the group so your left-hand side is the right-hand side of the one at the central position.); 
• When there are many people having the same height, they must be ordered in alphabetical (increasing) order of their names, and it is guaranteed that there is no duplication of names. 

Now given the information of a group of people, you are supposed to write a program to output their formation.

## Input Specification: 

Each input file contains one test case. For each test case, the first line contains two positive integers N (<=10000), the total number of people, and K (<=10), the total number of rows. Then N lines follow, each gives the name of a person (no more than 8 English letters without space) and his/her height (an integer in [30, 300]).

## Output Specification: 

For each case, print the formation -- that is, print the names of people in K lines. The names must be separated by exactly one space, but there must be no extra space at the end of each line. Note: since you are facing the group, people in the rear rows must be printed above the people in the front rows. 
## Sample Input:  
10 3  
Tom 188  
Mike 170  
Eva 168  
Tim 160  
Joe 190  
Ann 168  
Bob 175  
Nick 186  
Amy 160  
John 159  

## Sample Output:  
Bob Tom Joe Nick  
Ann Mike Eva  
Tim Amy John  


## 题意：


N个人排成K排照相，每排n/k(取整数部分)人，若有多出的人则站到最后一排。后排的所有人比前排的所有人高，每排中最高的站在中间，第二高的人站在最高的人的左边，第三高的站右边，然后第四高的又站在最高的左边的左边...输入每个人的名字与身高，输出照相的队形状态。同样高的人，名字按string更小的认为更高。

## 思路：

结构体数组formation存储所有人，对所有人排序，然后对每一排处理。first为这一排中最高的在formation中的下标(初始化为0，处理完一排后first += len，len为这一排的人数)。用长度为len的结构体数组row存储这一排的序列，center = len/2，row[center] = formation[first]，(最高的在中间)，然后对这一排中剩下的按奇偶确定排在center的左边还是右边。输出row中的人的名字，处理下一排。


## 代码：

[1109. Group Photo (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1109.%20Group%20Photo%20(25)/1109.%20Group%20Photo%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <string>

struct node {
	string name;
	int height;
};

bool compare(node a, node b)
{
	return a.height != b.height ? a.height > b.height:a.name < b.name;
}

int main()
{
	int n, k;
	cin >> n >> k;
	node *formation = new node[n];
	for (int i = 0; i < n; i++) 
		cin >> formation[i].name >> formation[i].height;
	sort(formation, formation + n, compare);
	int m = n / k;
	int extra = n - m * k;
	int first = 0;
	for (int i = 0; i < k; i++) {
		int len = i ? m : m + extra;
		node *row = new node[len];
		int  center = len / 2;
		row[center] = formation[first];
		int left = 1, right = 1;
		for (int j = 1; j < len; j++) {
			if (j % 2) row[center - left++] = formation[first + j];
			else row[center + right++] = formation[first + j];
		}
		for (int j = 0; j < len; j++) {
			if (j != 0) putchar(' ');
			cout << row[j].name;
		}
		printf("\n");
		first += len;
	}
    return 0;
}
```




