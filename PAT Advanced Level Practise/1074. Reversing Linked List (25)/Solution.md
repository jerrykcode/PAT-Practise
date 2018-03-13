# 1074. Reversing Linked List (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1074)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a constant K and a singly linked list L, you are supposed to reverse the links of every K 
elements on L. For example, given L being 1→2→3→4→5→6, if K = 3, then you must output 3→2→1→6→5→4; 
if K = 4, you must output 4→3→2→1→5→6.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains the address of the first node, 
a positive N (<= 105) which is the total number of nodes, and a positive K (<=N) which is the length of the 
sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

*Address Data Next*

where Address is the position of the node, Data is an integer, and Next is the position of the next node.


## Output Specification: 

For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the 
same format as in the input. 



## Sample Input:

00100 6 4  
00000 4 99999  
00100 1 12309  
68237 6 -1  
33218 3 00000   
99999 5 68237  
12309 2 33218  

## Sample Output:

00000 4 33218  
33218 3 12309  
12309 2 00100  
00100 1 99999  
99999 5 68237  
68237 6 -1  



## 题意：

输入N个结点的地址、数据、下一个结点的地址，求对每K个结点进行反转的结果
eg：
*1->2->3->4->5->6，K = 4    4->3->2->1->5->6*
*1->2->3->4->5->6, K = 3    3->2->1->6->5->4*
		
## 思路：

数组下标作为地址存储结点结构体，注意N个结点不一定都在链表上

## 代码：
[1074. Reversing Linked List (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1074.%20Reversing%20Linked%20List%20(25)/1074.%20Reversing%20Linked%20List%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

typedef struct node {
	int ad, data, next;
} lnode;

int main()
{
	int head, n, k;
	cin >> head >> n >> k;
	lnode * list = new lnode[100000];
	for (int i = 0; i < n; i++) { //输入链表
		int ad;
		cin >> ad;
		cin >> list[ad].data >> list[ad].next;
	}
	int sum = 0, ad = head;
	while (ad != -1) { //记录链表中的结点的个数
		ad = list[ad].next;
		sum++;
	}
	ad = head;
	int next = list[ad].next, tmphead = head, tmphead1, tmpnext;
	for (int i = 0; i < sum / k; i++) { //反转sum/k次
		tmphead1 = ad;
		for (int j = 0; j < k - 1; j++) {
			tmpnext = list[next].next;
			list[next].next = ad;
			ad = next;
			next = tmpnext;
		}
		if (i == 0)
			head = ad;
		else { list[tmphead].next = ad; tmphead = tmphead1; }
		ad = next;
		next = ad == -1 ? -1 : list[ad].next;
	}
	list[tmphead].next = ad;
	ad = head;
	while (ad != -1) { //输出
		printf("%05d %d ", ad, list[ad].data);
		if (list[ad].next == -1)  
			cout << -1 << endl;
		else printf("%05d\n", list[ad].next);
		ad = list[ad].next;
	}
    return 0;
}
```