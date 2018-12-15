# 1137. Final Grading (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1137)

* 时间限制 100 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



For a student taking the online course "Data Structures" on China University MOOC (http://www.icourse163.org/), to be qualified for a certificate, he/she must first obtain no less than 200 points from the online programming assignments, and then receive a final grade no less than 60 out of 100. The final grade is calculated by G = (Gmid-termx 40% + Gfinalx 60%) if Gmid-term > Gfinal, or Gfinal will be taken as the final grade G. Here Gmid-term and Gfinal are the student's scores of the mid-term and the final exams, respectively.

The problem is that different exams have different grading sheets. Your job is to write a program to merge all the grading sheets into one. 

## Input Specification: 

Each input file contains one test case. For each case, the first line gives three positive integers: P , the number of students having done the online programming assignments; M, the number of students on the mid-term list; and N, the number of students on the final exam list. All the numbers are no more than 10,000.

Then three blocks follow. The first block contains P online programming scores Gp's; the second one contains M mid-term scores Gmid-term's; and the last one contains N final exam scores Gfinal's. Each score occupies a line with the format: StudentID Score, where StudentID is a string of no more than 20 English letters and digits, and Score is a nonnegative integer (the maximum score of the online programming is 900, and that of the mid-term and final exams is 100).

## Output Specification: 

For each case, print the list of students who are qualified for certificates. Each student occupies a line with the format: 

*StudentID Gp Gmid-term Gfinal G*

If some score does not exist, output "-1" instead. The output must be sorted in descending order of their final grades (G must be rounded up to an integer). If there is a tie, output in ascending order of their StudentID's. It is guaranteed that the StudentID's are all distinct, and there is at least one qualified student.

## Sample Input:

6 6 7  
01234 880  
a1903 199  
ydjh2 200  
wehu8 300  
dx86w 220  
missing 400  
ydhfu77 99  
wehu8 55  
ydjh2 98  
dx86w 88  
a1903 86  
01234 39  
ydhfu77 88  
a1903 66  
01234 58  
wehu8 84  
ydjh2 82  
missing 99  
dx86w 81  

## Sample Output:

missing 400 -1 99 99  
ydjh2 200 98 82 88  
dx86w 220 88 81 84  
wehu8 300 55 84 84  

## 题意：

学《数据结构》要在[PTA](https://pintia.cn/problem-sets)上的编程题得到200分，总评分得60分，可以合格。总评分为若期末成绩大于期中成绩，则为期末成绩，否则为期末成绩\*0.6 + 期中成绩\*0.4，四舍五入。输入P个学生的id与PTA成绩、M个学生的id与期中成绩、N个学生的id与期末成绩，对合格的学生按总评分非递增排序，若有相同则按id递增排序，输出排序结果。


## 思路：

用结构体存储学生的id与各种分数，map<string, int>存储学生id与结构体的对应，输入学生，对合格的排序即可。

## 代码：

[1137. Final Grading (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1137.%20Final%20Grading%20(25)/1137.%20Final%20Grading%20(25).cpp)

```cpp
#include "stdafx.h"
# include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>
#include <algorithm>

struct node {
	string id;
	int gp, gm, gf, g;
};

bool compare(node a, node b)
{
	return a.g != b.g ? a.g > b.g:a.id < b.id;
}

int main() {
	int p, m, n;
	cin >> p >> m >> n;
	map<string, node> students;
	string id;
	for (int i = 0; i < p; i++) {
		int gp;
		cin >> id >> gp;
		if (students.find(id) == students.end()) {
			students[id] = { id, -1, -1, -1, -1 };
		}
		students[id].gp = gp;
	}
	for (int i = 0; i < m; i++) {
		int gm;
		cin >> id >> gm;
		if (students.find(id) == students.end()) {
			students[id] = { id, -1, -1, -1, -1 };
		}
		students[id].gm = gm;
	}
	for (int i = 0; i < n; i++) {
		int gf;
		cin >> id >> gf;
		if (students.find(id) == students.end()) {
			students[id] = { id, -1, -1, -1, -1 };
		}
		students[id].gf = gf;
		students[id].g = gf > students[id].gm ? gf : round(students[id].gm*0.4 + gf * 0.6);
	}
	vector<node> s;
	for (auto it = students.begin(); it != students.end(); it++) {
		if (it->second.g < 60)continue;
		if (it->second.gp < 200) continue;
		s.push_back(it->second);
	}
	sort(s.begin(), s.end(), compare);
	for (auto it = s.begin(); it != s.end(); it++) {
		cout << it->id;
		printf(" %d %d %d %d\n", it->gp, it->gm, it->gf, it->g);
	}
	return 0;
}
```

