# 1036. Boys vs Girls (25)
[ 原题地址](https://www.patest.cn/contests/pat-a-practise/1036)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

*  题目作者 CHEN, Yue



This time you are asked to tell the difference between the lowest grade of all the male students 
and the highest grade of all the female students.



## Input Specification: 

Each input file contains one test case. Each case contains a positive integer N, followed by N lines 
of student information. Each line contains a student's name, gender, ID and grade, separated by a space, 
where name and ID are strings of no more than 10 characters with no space, gender is either F (female) 
or M (male), and grade is an integer between 0 and 100. It is guaranteed that all the grades are distinct.


## Output Specification: 

For each test case, output in 3 lines. The first line gives the name and ID of the female student 
with the highest grade, and the second line gives that of the male student with the lowest grade. 
The third line gives the difference gradeF-gradeM. If one such kind of student is missing, output 
"Absent" in the corresponding line, and output "NA" in the third line instead.



## Sample Input 1:

3  
Joe M Math990112 89  
Mike M CS991301 100  
Mary F EE990830 95  

## Sample Output 1:  

Mary EE990830  
Joe Math990112  
6  


## Sample Input 2:  

1  
Jean M AA980920 60  

Sample Output 2:  

Absent  
Jean AA980920  
NA   



## 题意：

输入N个学生的姓名(string)、性别(string)、id(char)、分数(int)，第一行输出女生中分数最高的学生的姓名与
id，第二行输出男生中分数最低的学生的姓名与id，最后输出他们的分数差，若输入数据中没有女生或男生则在相
应位置输出"Absent"，最后分数差输出"NA"

## 思路：

女生最高分数初始化为-1(同时记录该学生的姓名与id，初始化可以不赋值)，男生最低分数初始化为101(同时记录
该学生的姓名与id，初始化可以不赋值)，边输入边比较，若有分数更高的女生或分数更低的男生则覆盖，输入结束
后可得女生最高分与男生最低分，若最高分为-1或最低分为101则相应输出"Absent"


##  代码：
[1036. Boys vs Girls (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1036.%20Boys%20vs%20Girls%20(25)/1036.%20Boys%20vs%20Girls%20(25).cpp)
```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>

int main()
{
	string maxFemaleName, maxFemaleId;
	int maxFemaleGrades = -1;
	string minMaleName, minMaleId;
	int minMaleGrades = 101;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string name, id;
		char gender;
		int grades;
		cin >> name >> gender >> id >> grades;
		if (gender == 'F') {
			if (grades > maxFemaleGrades) {
				maxFemaleName = name;
				maxFemaleId = id;
				maxFemaleGrades = grades;
			}
		}
		else {
			if (grades < minMaleGrades) {
				minMaleName = name;
				minMaleId = id;
				minMaleGrades = grades;
			}
		}
	}
	if (maxFemaleGrades == -1)
		cout << "Absent\n";
	else
		cout << maxFemaleName << " " << maxFemaleId << endl;
	if (minMaleGrades == 101)
		cout << "Absent\n";
	else
		cout << minMaleName << " " << minMaleId << endl;
	cout << (maxFemaleGrades == -1 || minMaleGrades == 101 ? "NA" : std::to_string(maxFemaleGrades - minMaleGrades)) << endl;
    return 0;
}
```
