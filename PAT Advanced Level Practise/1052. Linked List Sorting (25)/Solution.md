# 1052. Linked List Sorting (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1052)

* 时间限制 400 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



A linked list consists of a series of structures, which are not necessarily adjacent in memory. We assume that each structure contains an integer key and a Next pointer to the next structure. Now given a linked list, you are supposed to sort the structures according to their key values in increasing order.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive N (< 10^5) and an address of the head node, where N is the total number of nodes in memory and the address of a node is a 5-digit positive integer. NULL is represented by -1.

Then N lines follow, each describes a node in the format:

*Address Key Next*

where Address is the address of the node in memory, Key is an integer in [-10^5, 10^5], and Next is the address of the next node. It is guaranteed that all the keys are distinct and there is no cycle in the linked list starting from the head node.

## Output Specification: 

For each test case, the output format is the same as that of the input, where N is the total number of nodes in the list and all the nodes must be sorted order.

## Sample Input:  
5 00001  
11111 100 -1  
00001 0 22222  
33333 100000 11111  
12345 -1 33333  
22222 1000 12345  

## Sample Output:  
5 12345  
12345 -1 00001  
00001 0 11111  
11111 100 22222  
22222 1000 33333  
33333 100000 -1  

## 题意：

结构体含有地址(5位数字)、值key与下一个结构体的地址next，-1表示NULL，输入静态链表的头地址，与每个结构体的地址、key、next(每个结构体不一定都在链表上)，输出按key排序后的链表。

## 思路：

结构体数组下标表示地址存储静态链表，从头地址开始，将链表上的结点存入vector，对vector的元素排序，输出。输出时结构体的next要变为排序后的next，即vector中下一个结构体的地址。注意链表上无结点时要输出"0 -1\n"。

## 代码：

[1052. Linked List Sorting (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1052.%20Linked%20List%20Sorting%20(25)/1052.%20Linked%20List%20Sorting%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

struct node {
	int ad, key, next;
};

bool compare(node a, node b)
{
	return a.key < b.key;
}

int main()
{
	node memory[100000];
	int n, head_ad, flag = 0;
	cin >> n >> head_ad;
	vector<node> list;
	for (int i = 0; i < n; i++) {
		int ad, key, next;
		cin >> ad >> key >> next;
		if (ad == head_ad) flag = 1;
		memory[ad] = { ad, key, next };
	}
	if (flag == 0) {
		printf("0 -1\n");
		return 0;
	}
	int ad = head_ad;
	while (ad != -1) {
		list.push_back(memory[ad]);
		ad = memory[ad].next;
	}
	sort(list.begin(), list.end(), compare);
	printf("%d %05d\n", list.size(), list[0].ad);
	for (int i = 0; i < list.size(); i++) {
		printf("%05d %d ", list[i].ad, list[i].key);
		if (i + 1 < list.size()) printf("%05d\n", list[i + 1].ad);
		else printf("-1\n");
	}
    return 0;
}
```