# 1047. Student List for Course (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1047)
* 时间限制 400 ms

* 内存限制 64000 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Zhejiang University has 40000 students and provides 2500 courses. Now given the registered course 
list of each student, you are supposed to output the student name lists of all the courses.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 numbers: N (<=40000), 
the total number of students, and K (<=2500), the total number of courses. Then N lines follow, each 
contains a student's name (3 capital English letters plus a one-digit number), a positive number C (<=20) 
which is the number of courses that this student has registered, and then followed by C course numbers. 
For the sake of simplicity, the courses are numbered from 1 to K.



## Output Specification: 

For each test case, print the student name lists of all the courses in increasing order of the course 
numbers. For each course, first print in one line the course number and the number of registered students, 
separated by a space. Then output the students' names in alphabetical order. Each name occupies a line.



## Sample Input:

10 5  
ZOE1 2 4 5  
ANN0 3 5 2 1  
BOB5 5 3 4 2 1 5  
JOE4 1 2  
JAY9 4 1 2 5 4  
FRA8 3 4 2 5  
DON2 2 4 5  
AMY7 1 5  
KAT3 3 5 4 2  
LOR6 4 2 4 1 5  

## Sample Output:  

1 4  
ANN0  
BOB5  
JAY9  
LOR6  
2 7  
ANN0  
BOB5  
FRA8  
JAY9  
JOE4  
KAT3  
LOR6  
3 1  
BOB5  
4 7  
BOB5  
DON2  
FRA8  
JAY9  
KAT3  
LOR6  
ZOE1  
5 9  
AMY7  
ANN0  
BOB5  
DON2  
FRA8  
JAY9  
KAT3  
LOR6  
ZOE1  

## 题意：

N个学生K门课，输入每个学生的姓名与参加的每门课的序号(1~K)，输出每门课参与的学生姓名。

## 思路：

用vector<int>数组存储每门课参与的学生的序号(直接用string存储学生姓名会超时，输入的第i个学生的序号为i，
其姓名存储在字符串数组name中的name[i])，对数组中的每个vector排序，输出每个学生序号在name中对应的字符串
姓名。


## 代码：

[1047. Student List for Course (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1047.%20Student%20List%20for%20Course%20(25)/1047.%20Student%20List%20for%20Course%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string.h>
#include <vector>
#include <algorithm>

char name[40001][5];
bool compare(int a, int b)
{
	return strcmp(name[a], name[b]) < 0;
}

int main()
{
	int n, k;
	cin >> n >> k;
	vector<int> *courses = new vector<int>[k];
	int c, number;
	for (int i = 0; i < n; i++) {
		scanf("%s %d", name[i], &c);
		for (int j = 0; j < c; j++) {
			scanf("%d", &number);
			courses[number - 1].push_back(i);
		}
	}
	for (int i = 0; i < k; i++) {
		printf("%d %d\n", i + 1, courses[i].size());
		sort(courses[i].begin(), courses[i].end(), compare);
		for (int j = 0; j < courses[i].size(); j++)
			printf("%s\n", name[courses[i][j]]);
	}
    return 0;
}
```