# 1016. Phone Bills (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1016)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue




A long-distance telephone company charges its customers by the following rules:

Making a long-distance call costs a certain amount per minute, depending on the time of day when the call is made. 
When a customer starts connecting a long-distance call, the time will be recorded, and so will be the time when 
the customer hangs up the phone. Every calendar month, a bill is sent to the customer for each minute called 
(at a rate determined by the time of day). Your job is to prepare the bills for each month, given a set of phone 
call records.




## Input Specification: 

Each input file contains one test case. Each case has two parts: the rate structure, and the phone call records.

The rate structure consists of a line with 24 non-negative integers denoting the toll (cents/minute) from 00:00 - 01:00, 
the toll from 01:00 - 02:00, and so on for each hour in the day. 

The next line contains a positive number N (<= 1000), followed by N lines of records. Each phone call record consists of 
the name of the customer (string of up to 20 characters without space), the time and date (mm:dd:hh:mm), and the word 
"on-line" or "off-line".

For each test case, all dates will be within a single month. Each "on-line" record is paired with the chronologically next 
record for the same customer provided it is an "off-line" record. Any "on-line" records that are not paired with an "off-line" 
record are ignored, as are "off-line" records not paired with an "on-line" record. It is guaranteed that at least one call is 
well paired in the input. You may assume that no two records for the same customer have the same time. Times are recorded using 
a 24-hour clock.




## Output Specification: 

For each test case, you must print a phone bill for each customer. 

Bills must be printed in alphabetical order of customers' names. For each customer, first print in a line the name of the customer 
and the month of the bill in the format shown by the sample. Then for each time period of a call, print in one line the beginning 
and ending time and date (dd:hh:mm), the lasting time (in minute) and the charge of the call. The calls must be listed in chronological 
order. Finally, print the total charge for the month in the format shown by the sample.




## Sample Input:
10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10  
10  
CYLL 01:01:06:01 on-line  
CYLL 01:28:16:05 off-line  
CYJJ 01:01:07:00 off-line  
CYLL 01:01:08:03 off-line  
CYJJ 01:01:05:59 on-line  
aaa 01:01:01:03 on-line  
aaa 01:02:00:01 on-line  
CYLL 01:28:15:41 on-line  
aaa 01:05:02:24 on-line  
aaa 01:04:23:59 off-line  

## Sample Output:
CYJJ 01  
01:05:59 01:07:00 61 $12.10  
Total amount: $12.10  
CYLL 01  
01:06:01 01:08:03 122 $24.40  
28:15:41 28:16:05 24 $3.85  
Total amount: $28.25  
aaa 01  
02:00:01 04:23:59 4318 $638.80  
Total amount: $638.80  



## 题意：

已知24小时每小时的电话费用（cents/min），输入N条记录，每条记录包含用户名、该记录的时间，及状态（on-line或off-line），求每个用户的总电话费

## 思路：

本题思路参考[柳婼 の blog 1016. Phone Bills (25)-PAT甲级真题](https://www.liuchuo.net/archives/2350)

用结构体存储记录信息，N条记录存在结构体数组中，对数组进行排序，记录的用户名不同就按用户名排序，否则按时间排序，然后遍历数组，对相邻的两个
记录，若其用户名相同且前面的状态为on-line，后面为off-line，则为合格数据

计算从on-line到off-line之间的电话费，用00:00:00到off-line之间的电话费减去00:00:00到on-line之间的电话费

## 参考：
[柳婼 の blog 1016. Phone Bills (25)-PAT甲级真题](https://www.liuchuo.net/archives/2350)

## 代码：

[1016. Phone Bills (25)_2.cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1016.%20Phone%20Bills%20(25)/1016.%20Phone%20Bills%20(25)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

/* 定义电话记录结点 */
typedef struct node {
	string customer; /* 用户 */
	int time; /* 从本月01日00:00到此记录的时间 */
	int month, day, hour, min; /* 此记录的日期 月、日、时、分 */
	int status; /* 此记录的状态：on-line 为1，off-line为0 */
} record;

bool compare(record a, record b)
{	/* 比较记录，若用户相同，则比较time，否则比较customer */
	return a.customer == b.customer ? a.time < b.time : a.customer < b.customer;
}

int billFromBegin(record r, int *rates)
{	/* 返回从本月01日00:00到此记录时刻之间的费用 */
	int bill = (r.day - 1)*rates[24] * 60 + r.min*rates[r.hour];
	for (int i = 0; i < r.hour; i++)
		bill += rates[i] * 60;
	return bill;
}

void printBill(record *records, int *rates, int N)
{	/* 输出账单 */
	map <string, vector<record>> bills;
	for (int i = 0; i < N - 1; i++) { //i 0 to N - 2
		if (records[i].customer == records[i + 1].customer && records[i].status && !records[i + 1].status) {
			/* i和i+1的用户相同&&i的状态为1(即on-line), i+1的状态为0(off-line) */
			bills[records[i].customer].push_back(records[i]);
			bills[records[i].customer].push_back(records[i + 1]);
		}
	}
	map<string, vector<record>>::iterator iter = bills.begin();
	while (iter != bills.end()) {
		cout << iter->first;
		vector<record> temp = iter->second;
		printf(" %02d\n", temp[0].month);
		float total = 0;
		for (int i = 0; i < temp.size(); i += 2) {
			float bill = billFromBegin(temp[i + 1], rates) - billFromBegin(temp[i], rates);
			total += bill;
			printf("%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", temp[i].day, temp[i].hour, temp[i].min, 
				temp[i + 1].day, temp[i+1].hour, temp[i+1].min,temp[i + 1].time - temp[i].time, bill/100);
		}
		printf("Total amount: $%.2f\n", total/100);
		iter++;
	}
}

int main()
{
	int rates[25] = {0};
	for (int i = 0; i < 24; i++) {
		cin >> rates[i]; //第i小时的话费(cents/min)
		rates[24] += rates[i];
	}
	int N;
	cin >> N;
	record *records = new record[N];
	for (int i = 0; i < N; i++) {//输入记录
		cin >> records[i].customer;
		scanf("%d:%d:%d:%d", &records[i].month, &records[i].day, &records[i].hour, &records[i].min);
		records[i].time = (records[i].day - 1) * 24 * 60 + records[i].hour * 60 + records[i].min; //month不计入
		string flag;
		cin >> flag;
		records[i].status = flag == "on-line" ? 1 : 0;
	}
	sort(records, records + N, compare); //排序
	printBill(records, rates, N);
    return 0;
}
```
