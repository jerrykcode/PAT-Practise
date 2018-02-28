# 1028. List Sorting (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1028)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



Excel can sort records according to any column. Now you are supposed to imitate this function.




## Input

Each input file contains one test case. For each case, the first line contains two integers N 
(<=100000) and C, where N is the number of records and C is the column that you are supposed 
to sort the records with. Then N lines follow, each contains a record of a student. A student's 
record consists of his or her distinct ID (a 6-digit number), name (a string with no more than 
8 characters without space), and grade (an integer between 0 and 100, inclusive).



## Output

For each test case, output the sorting result in N lines. That is, if C = 1 then the records 
must be sorted in increasing order according to ID's; if C = 2 then the records must be sorted 
in non-decreasing order according to names; and if C = 3 then the records must be sorted in 
non-decreasing order according to grades. If there are several students who have the same name 
or grade, they must be sorted according to their ID's in increasing order.



## Sample Input 1

3 1  
000007 James 85  
000010 Amy 90  
000001 Zoe 60  

## Sample Output 1

000001 Zoe 60  
000007 James 85  
000010 Amy 90  


## Sample Input 2

4 2  
000007 James 85  
000010 Amy 90  
000001 Zoe 60  
000002 James 98  

## Sample Output 2

000010 Amy 90  
000002 James 98  
000007 James 85  
000001 Zoe 60  



## Sample Input 3

4 3  
000007 James 85  
000010 Amy 90  
000001 Zoe 60  
000002 James 90  

## Sample Output 3

000001 Zoe 60  
000007 James 85  
000002 James 90  
000010 Amy 90  



## 题意：

输入N与C，输入N个学生的id、姓名、分数，若C = 1则按id递增顺序输出；C = 2则按姓名非递减顺序输出；
C = 3则按分数非递减顺序输出，(若姓名或分数相同则按id的递增顺序排序)

## 思路：

用结构体数组存储N个像学生，在排序时按C分类

## 代码：


[1028. List Sorting (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1028.%20List%20Sorting%20(25)/1028.%20List%20Sorting%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <string.h>
#include <algorithm>

typedef struct node {
	int id;
	char name[9];
	int grade;
} student;

int flag;

bool compare(student a, student b)
{
	if (flag == 1)
		return a.id < b.id; //比较id
	else if (flag == 2)
		return strcmp(a.name, b.name) == 0 ? a.id < b.id : strcmp(a.name, b.name) < 0; //姓名相同则比较id，否则比较姓名
	else
		return a.grade == b.grade ? a.id < b.id : a.grade < b.grade; //分数相同则比较id，否则比较分数
}

int main()
{
	int n;
	cin >> n >> flag;
	student *records = new student[n];
	for (int i = 0; i < n; i++)
		scanf("%d %s %d", &records[i].id, records[i].name, &records[i].grade);
	sort(records, records + n, compare);
	for (int i = 0; i < n; i++)
		printf("%06d %s %d\n", records[i].id, records[i].name, records[i].grade);
    return 0;
}
```
