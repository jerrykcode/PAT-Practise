# 1083. List Grades (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1083)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Given a list of N student records with name, ID and grade. You are supposed to sort the records with respect to 
the grade in non-increasing order, and output those student records of which the grades are in a given interval.



## Input Specification: 

Each input file contains one test case. Each case is given in the following format:
*N*
*name[1] ID[1] grade[1]*
*name[2] ID[2] grade[2]*
*... ...*
*name[N] ID[N] grade[N]*
*grade1 grade2*


where name[i] and ID[i] are strings of no more than 10 characters with no space, grade[i] is an integer in [0, 100], 
grade1 and grade2 are the boundaries of the grade's interval. It is guaranteed that all the grades are distinct.



## Output Specification: 

For each test case you should output the student records of which the grades are in the given interval [grade1, grade2] 
and are in non-increasing order. Each student record occupies a line with the student's name and ID, separated by one 
space. If there is no student's grade in that interval, output "NONE" instead.


## Sample Input 1:

4  
Tom CS000001 59  
Joe Math990112 89  
Mike CS991301 100  
Mary EE990830 95  
60 100  

## Sample Output 1:

Mike CS991301  
Mary EE990830  
Joe Math990112  


## Sample Input 2:

2  
Jean AA980920 60  
Ann CS01 80  
90 95  

## Sample Output 2: 

NONE  



## 题意：

输入N个学生的姓名、id与分数。按分数非递增排序。输入分数范围的下线与上线，求在此范围内的学生的姓名与id（分数
各不相同，按非递增排序）。

## 思路：

结构体存储学生的姓名、id与分数，结构体数组存储所有学生，排序。遍历数组，输出在范围内的学生

## 代码：

[1083. List Grades (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1083.%20List%20Grades%20(25)/1083.%20List%20Grades%20(25).cpp)

```cpp
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

typedef struct node {
	string name, id;
	int grade;
}record;

bool compare(record a, record b)
{
	return a.grade > b.grade;
}

int main()
{
	int n;
	cin >> n;
	record *records = new record[n];
	for (int i = 0; i < n; i++) {
		string name, id;
		int grade;
		cin >> name >> id >> grade;
		records[i] = {name, id, grade};
	}
	int g1, g2;
	cin >> g1 >> g2;
	sort(records, records + n, compare);
	int flag = 1;
	for (int i = 0; i < n; i++) {
		if (records[i].grade > g2) continue;
		if (records[i].grade < g1) break;
		flag = 0;
		cout << records[i].name << " " << records[i].id << endl;
	}
	if (flag) cout << "NONE";
    return 0;
}
```

 
