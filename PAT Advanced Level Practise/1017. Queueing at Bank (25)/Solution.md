# 1017. Queueing at Bank (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1017)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



Suppose a bank has K windows open for service. There is a yellow line in front of the windows which devides 
the waiting area into two parts. All the customers have to wait in line behind the yellow line, until it is
his/her turn to be served and there is a window available. It is assumed that no window can be occupied by 
a single customer for more than 1 hour.

Now given the arriving time T and the processing time P of each customer, you are supposed to tell the average 
waiting time of all the customers.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 numbers: N (<=10000) - the 
total number of customers, and K (<=100) - the number of windows. Then N lines follow, each contains 2 times: 
HH:MM:SS - the arriving time, and P - the processing time in minutes of a customer. Here HH is in the range [00, 23], 
MM and SS are both in [00, 59]. It is assumed that no two customers arrives at the same time.

Notice that the bank opens from 08:00 to 17:00. Anyone arrives early will have to wait in line till 08:00, and 
anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.



## Output Specification: 

For each test case, print in one line the average waiting time of all the customers, in minutes and accurate 
up to 1 decimal place.



## Sample Input:
7 3  
07:55:00 16  
17:00:01 2  
07:59:59 15  
08:01:00 60  
08:00:00 30  
08:00:02 2  
08:03:00 10  

## Sample Output:
8.2  



## 题意：

K个窗口，N个客户，每个客户到达时，若不到08:00，则需等待到08:00，若到达时所有窗口均有客户，则在黄线外等待，直到
轮到此客户且有一个窗口空出，输入N个客户到达时间(HH:MM:SS，精确到秒)及处理需要的时间，求客户等待的平均时间(分钟)

所有到达时间大于等于17:00:01的都不记录在平均分内


## 思路：

用从00:00:00到HH:MM:SS的秒数表示HH:MM:SS的时间

用结构体数组存储N个客户的到达时间及处理所需时间，对数组按到达时间进行排序(到达时间小的排在前面)

用数组last存储K个窗口当前客户的离开时间，初始化为8*60*60(08:00:00)

total表示所有客户等待时间总和，count表示到达时间小于17:00:01的客户数量

遍历结构体数组，对每个客户，若到达时间大于等于17:00:01，则break，否则遍历last找到最先空出的窗口(设为w)，则等待时间
为: last[w] - 客户到达时间，
若等待时间 < 0，说明该客户到达时该窗口已空出，等待时间为0秒，total不用增加，last[w]更新为该客户到达时间 + 客户处理
时间
若等待时间 > 0，则客户需要等待，total增加，last[w]更新为last[w] + 客户处理时间

## 代码：


[1017. Queueing at Bank (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1017.%20Queueing%20at%20Bank%20(25)/1017.%20Queueing%20at%20Bank%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

typedef struct node {
	int arrive_time; //到达时间，用从00:00:00到当前时刻的秒钟数表示
	int processing_time; //处理时间（秒）
} customer;

bool compare(customer a, customer b)
{
	return a.arrive_time < b.arrive_time;
}

int main()
{
	int n, k;
	cin >> n >> k;
	int *last = new int[k]; //窗口当前客户的离开时间
	for (int i = 0; i < k; i++) last[i] = 8*60*60; //08:00:00
	customer *customers = new customer[n];
	for (int i = 0; i < n; i++) {
		int hour, min, sec;
		scanf("%d:%d:%d", &hour, &min, &sec);
		customers[i].arrive_time = hour * 3600 + min * 60 + sec;
		cin >> customers[i].processing_time;
		customers[i].processing_time *= 60; //单位改为秒
	}
	sort(customers, customers + n, compare);
	int total = 0;
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (customers[i].arrive_time >= 17 * 3600 + 01) //到达时间>=17:00:01
			break;
		int min = 0; //需要等待时间最小的窗口
		for (int j = 0; j < k; j++)
			if (last[j] < last[min])
				min = j;
		int wait = last[min] - customers[i].arrive_time; //等待时间 
		if (wait > 0) { //等待时间 > 0
			total += wait;
			last[min] += customers[i].processing_time;
		}
		else  //不需等待
			last[min] = customers[i].arrive_time + customers[i].processing_time;
		count++;
	}
	printf("%.1f", (total/count)/60.0);
    return 0;
}
```