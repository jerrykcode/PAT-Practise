# 1006. Sign In and Sign Out (25)



* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



At the beginning of every day, the first person who signs in the computer room will unlock the door, 
and the last one who signs out will lock the door. Given the records of signing in's and out's, you 
are supposed to find the ones who have unlocked and locked the door on that day. 




## Input Specification: 

Each input file contains one test case. Each case contains the records for one day. The case starts 
with a positive integer M, which is the total number of records, followed by M lines, each in the format:

*ID_number Sign_in_time Sign_out_time*

where times are given in the format HH:MM:SS, and ID number is a string with no more than 15 characters. 




## Output Specification: 

For each test case, output in one line the ID numbers of the persons who have unlocked and locked the door 
on that day. The two ID numbers must be separated by one space.

Note: It is guaranteed that the records are consistent. That is, the sign in time must be earlier than the 
sign out time for each person, and there are no two persons sign in or out at the same moment.




## Sample Input:
3
CS301111 15:30:28 17:00:10
SC3021234 08:00:00 11:25:25
CS301133 21:45:00 21:58:40

## Sample Output:
SC3021234 CS301133




## 题意：

每天第一个登录的用户会“开门”，最后一个登出的用户会“关门”，已知某天的M条记录，每条包含用户id号码、登录时间以及
登出时间（时间格式为HH:MM:SS），求这一天“开门”与“关门”的用户
注意：题目保证每个用户的登录时间早于登出时间，且没有两人的登录或登出时间相同


## 思路：

建立结构体，存储用户的id号码、登录时间以及登出时间（均为字符串），用结构体数组存储M个用户的信息，
定义全局变量flag，调用<algorithm>的sort函数对结构体数组排序，compare函数为：当flag为0时按登录时间递增，
flag非0时按登出时间递减。（由于字符'0'<'9'，故按HH:MM:SS格式，时间早的相应的字符串也小）
flag赋值为0，调用sort，排序后结构体数组下标为0的元素的登录时间最小，此用户为“开门”的用户，输出其id，再将flag赋值
为1，调用sort，排序后结构体数组下标为0的元素的登出时间最大，此用户为“关门”的用户，输出其id

## 代码：

[1006. Sign In and Sign Out(25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1006.%20Sign%20In%20and%20Sign%20Out(25)/1006.%20Sign%20In%20and%20Sign%20Out%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

typedef struct Node {
	string id;
	string sign_in_time;
	string sign_out_time;
} record;

int flag;

bool compare(record a, record b)
{
	return (flag == 0) ? a.sign_in_time < b.sign_in_time : a.sign_out_time > b.sign_out_time;
}

int main()
{
	int M;
	cin >> M;
	record * records = new record[M];
	for (int i = 0; i < M; i++) 
		cin >> records[i].id >> records[i].sign_in_time >> records[i].sign_out_time;
	flag = 0;
	sort(records, records + M, compare);
	cout << records[0].id;
	flag = 1;
	sort(records, records + M, compare);
	putchar(' ');
	cout << records[0].id;
	return 0;
}
```
