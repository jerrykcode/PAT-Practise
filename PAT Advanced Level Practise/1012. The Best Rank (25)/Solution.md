# 1012. The Best Rank (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1012)
* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue


To evaluate the performance of our first year CS majored students, we consider their grades of three courses only: 
C - C Programming Language, M - Mathematics (Calculus or Linear Algebra), and E - English. At the mean time, we 
encourage students by emphasizing on their best ranks -- that is, among the four ranks with respect to the three 
courses and the average grade, we print the best rank for each student.

For example, The grades of C, M, E and A - Average of 4 students are given as the following:
StudentID  C  M  E  A  
310101     98 85 88 90  
310102     70 95 88 84  
310103     82 87 94 88  
310104     91 91 91 91  


Then the best ranks for all the students are No.1 since the 1st one has done the best in C Programming Language, 
while the 2nd one in Mathematics, the 3rd one in English, and the last one in average.




## Input

Each input file contains one test case. Each case starts with a line containing 2 numbers N and M (<=2000), 
which are the total number of students, and the number of students who would check their ranks, respectively. 
Then N lines follow, each contains a student ID which is a string of 6 digits, followed by the three integer 
grades (in the range of [0, 100]) of that student in the order of C, M and E. Then there are M lines, each 
containing a student ID.




## Output

For each of the M students, print in one line the best rank for him/her, and the symbol of the corresponding rank, 
separated by a space.

The priorities of the ranking methods are ordered as A > C > M > E. Hence if there are two or more ways for a student 
to obtain the same best rank, output the one with the highest priority.

If a student is not on the grading list, simply output "N/A".




## Sample Input
5 6  
310101 98 85 88  
310102 70 95 88  
310103 82 87 94  
310104 91 91 91  
310105 85 90 90  
310101  
310102  
310103  
310104  
310105  
999999  

## Sample Output
1 C  
1 M  
1 E  
1 A  
3 A  
N/A  



## 题意：

已知N个学生的id，及A（平均分）、C（C语言）、M（数学）、E（英语）（平均分不给出，在程序内计算）的分数，输入M个id，
对每个id求该id对应学生的排名最靠前的科目，输出此排名及科目。科目的优先级为A > C > M > E，如某学生的A、C的排名均为1，
M的排名为6，E的排名为4，则输出 1 A

## 思路：

用结构体存储学生的信息：用int id存储id，用数组int score[4]存储4科目的分数（0，1，2，3分别为A、C、M、E），用数组
int rank[4]存储4科目的排名（0，1，2，3分别为A、C、M、E），建立结构体数组，通过输入的每个学生的C、M、E的分数计算
平均分，此时每个学生的score数组的值已确定，用<algorithm>的sort函数对结构体数组分别按A、C、M、E的分数大小进行4次
排序，可得每个学生每科目的排名，至此rank数组的值亦确定，用hash数组建立id与结构体数组下标的对应，对M个id，通过hash
数组找到结构体数组中对应的学生，循环其rank数组，得其排名最小（靠前）的科目

## 代码：

[1012. The Best Rank (25)_2.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1012.%20The%20Best%20Rank%20(25)/1012.%20The%20Best%20Rank%20(25)_2.cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>

typedef struct node {
	int id;
	int score[4], rank[4];//4门考试的分数及排名, 0, 1, 2, 3分别对应A, C, M, E
} student;

int flag;

bool compare(student a, student b)
{
	return a.score[flag] > b.score[flag]; //按第flag门考试的分数排序
}

int main()
{
	int n, m;
	cin >> n >> m;
	student* students = new student[n];
	for (int i = 0; i < n; i++) {
		cin >> students[i].id >> students[i].score[1] >> students[i].score[2] >> students[i].score[3];
		students[i].score[0] = (int)((students[i].score[1] + students[i].score[2] + students[i].score[3]) / 3.0 + 0.5);//平均分, +0.5是四舍五入
	}
	for (flag = 0; flag < 4; flag++) {
		sort(students, students + n, compare); //按不同的分数排序
		for (int i = 0; i < n; i++) {
			students[i].rank[flag] = i + 1; //按第flag门分数排序，第i名学生的第flag门考试的排名为i + 1
			if (i != 0 && students[i].score[flag] == students[i - 1].score[flag])
				students[i].rank[flag] = students[i - 1].rank[flag];
		}
	}
	char subject[4] = { 'A', 'C', 'M', 'E' }; //科目
	int hash[1000000];
	for (int i = 0; i < n; i++)
		hash[students[i].id] = i + 1; //hash[students[0].id] = 1，则hash值为0的id不存在
	for (int i = 0; i < m; i++) {
		int id;
		cin >> id;
		if (hash[id] > 0) {
			int best = 0;
			student * s = students + hash[id] - 1; //&students[hash[id] - 1]
			for (int j = 0; j < 4; j++) //寻找该学生的最好排名
				if (s->rank[j] < s->rank[best]) 
					best = j;
			cout << s->rank[best] << " " << subject[best];
		}
		else
			cout << "N/A";
		printf("\n");
	}
    return 0;
}
```
