# 1097. Deduplication on a Linked List (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1097)

* 时间限制   300 ms



* 内存限制   65536 kB



* 代码长度限制   16000 B



* 判题程序   Standard 

* 题目作者   CHEN, Yue



Given a singly linked list L with integer keys, you are supposed to remove the nodes with duplicated absolute values of the keys. That is, for each value K, only the first node of which the value or absolute value of its key equals K will be kept. At the mean time, all the removed nodes must be kept in a separate list. For example, given L being 21→-15→-15→-7→15, you must output 21→-15→-7, and the removed list -15→15.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains the address of the first node, and a positive N (<= 10^5) which is the total number of nodes. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

*Address Key Next*

where Address is the position of the node, Key is an integer of which absolute value is no more than 10^4, and Next is the position of the next node.

## Output Specification: 

For each case, output the resulting linked list first, then the removed list. Each node occupies a line, and is printed in the same format as in the input. 
## Sample Input:
00100 5  
99999 -7 87654  
23854 -15 00000  
87654 15 -1  
00000 -15 99999  
00100 21 23854  

## Sample Output:
00100 21 23854  
23854 -15 99999  
99999 -7 -1  
00000 -15 87654  
87654 15 -1  

## 题意：

输入一个静态链表的头地址与结点数，结点输入格式为*Address Key Next*，其中`Address`和`Next`是5位地址，Key是结点元素，不超过10000。若链表中只保留元素绝对值第一次出现的结点，其他结点（元素的绝对值已在之前的结点中出现过的结点）删除，并链在另一链表上，输出删除结点后的链表，以及删除结点组成的链表

## 思路：


结构体数组存储链表，下标表示结点地址。int数组flag[10001]表示一个元素的绝对值是否出现过。边遍历链表边处理，若结点元素的绝对值没出现过则输出其地址与元素值，Next不要输出，因为下一个结点是否要被删除还未确定，删除后的链表中该结点的下一个是谁还没有确定。若这个结点不是链表的头结点，那么在输出前还要先输出它的地址并换行（此时确定了上一个保留的结点的下一个）。更新该结点的元素的绝对值为已出现过。如果结点的元素的绝对值已出现过则将该结点插入到另一链表上。遍历并处理完链表后，再遍历输出删除结点组成的链表

## 代码：

[1097. Deduplication on a Linked List (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1097.%20Deduplication%20on%20a%20Linked%20List%20(25)/1097.%20Deduplication%20on%20a%20Linked%20List%20(25)_2.cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;

struct node {
	int key, next;
};

int abs(int a)
{
	return a >= 0 ? a : -a;
}

int main()
{
	node list[100000];
	int flag[10001];
	int n, head, ad, key, next;
	cin >> head >> n;
	for (int i = 0; i < n; i++) {
		cin >> ad >> key >> next;
		list[ad] = {key, next};
	}
	ad = head;
	int removed_list_head = -1, removed_list_tail = removed_list_head;
	while (ad != -1) {
		if (flag[abs(list[ad].key)] == 1) {
			if (removed_list_head == -1) {
				removed_list_head = ad;
				removed_list_tail = ad;
			}
			else {
				list[removed_list_tail].next = ad;
				removed_list_tail = ad;
			}
		}
		else {
			flag[abs(list[ad].key)] = 1;
			if (ad != head)printf(" %05d\n", ad);
			printf("%05d %d", ad, list[ad].key);
		}
		ad = list[ad].next;
	}
	printf(" -1\n");
	ad = removed_list_head;
	while (ad != removed_list_tail) {
		printf("%05d %d %05d\n", ad, list[ad].key, list[ad].next);
		ad = list[ad].next;
	}
	if (ad != -1) printf("%05d %d -1\n", ad, list[ad].key);
    return 0;
}
```
