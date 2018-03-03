# 1032. Sharing (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1032)
* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



To store English words, one method is to use linked lists and store a word letter by letter. 
To save some space, we may let the words share the same sublist if they share the same suffix. 
For example, "loading" and "being" are stored as showed in Figure 1.

![Figure1:](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1032.jpg)
*Figure 1*

You are supposed to find the starting position of the common suffix (e.g. the position of "i" 
in Figure 1).




## Input Specification: 

Each input file contains one test case. For each case, the first line contains two addresses of 
nodes and a positive N (<= 10^5), where the two addresses are the addresses of the first nodes of 
the two words, and N is the total number of nodes. The address of a node is a 5-digit positive 
integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

*Address Data Next*

where Address is the position of the node, Data is the letter contained by this node which is an 
English letter chosen from {a-z, A-Z}, and Next is the position of the next node.




## Output Specification: 

For each case, simply output the 5-digit starting position of the common suffix. If the two words 
have no common suffix, output "-1" instead. 




## Sample Input 1:

11111 22222 9  
67890 i 00002  
00010 a 12345  
00003 g -1  
12345 D 67890  
00002 n 00003  
22222 B 23456  
11111 L 00001  
23456 e 67890  
00001 o 00010  

## Sample Output 1:  

67890  

## Sample Input 2:  

00001 00002 4  
00001 a 10001  
10001 s -1  
00002 a 10002  
10002 t -1  

## Sample Output 2:

-1  



## 题意：

英文单词的字母存储在5位地址中，不同单词的相同字母(后缀)可用相同的地址存储，给出两个单词的链表，
求它们第一个共同地址

## 思路：

本题参考 [柳婼 の blog 1032. Sharing (25)-PAT甲级真题](https://www.liuchuo.net/archives/2113)

用结构体数组list存储，list[ad]表示地址为ad的结点，data表示结点存储的字母，next表示下一个结点的
地址，flag表示第一个链表中是否存在此结点(初始化为0)，遍历第一个链表，其中所有结点的flag记为1，
遍历第二个链表，若遇到了flag为1的结点就输出并结束程序，没有遇到就输出-1


## 参考：

[柳婼 の blog 1032. Sharing (25)-PAT甲级真题](https://www.liuchuo.net/archives/2113)

## 代码：

[1032. Sharing (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1032.%20Sharing%20(25)/1032.%20Sharing%20(25)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

typedef struct node {
	char data;
	int next;
	int flag;
} letter;

int main()
{
	int ad1, ad2, n, ad, next;
	cin >> ad1 >> ad2 >> n;
	letter *list = new letter[100000];
	char data;
	for (int i = 0; i < n; i++) {//输入结点
		scanf("%d %c %d", &ad, &data, &next);
		list[ad] = {data, next, 0};
	}
	while (ad1 != -1) {//遍历第一个链表
		list[ad1].flag = 1;//标记为1
		ad1 = list[ad1].next;
	}
	while (ad2 != -1) {//遍历第二个链表
		if (list[ad2].flag) {
			printf("%05d", ad2);
			return 0;
		}
		ad2 = list[ad2].next;
	}
	cout << -1;
    return 0;
}
```