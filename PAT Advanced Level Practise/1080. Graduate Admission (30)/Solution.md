# 1080. Graduate Admission (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1080)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue


It is said that in 2013, there were about 100 graduate schools ready to proceed over 40,000 applications in Zhejiang Province. 
It would help a lot if you could write a program to automate the admission procedure.

Each applicant will have to provide two grades: the national entrance exam grade GE, and the interview grade GI. The final grade 
of an applicant is (GE + GI) / 2. The admission rules are:

• The applicants are ranked according to their final grades, and will be admitted one by one from the top of the rank list. 
• If there is a tied final grade, the applicants will be ranked according to their national entrance exam grade GE. If still tied, 
  their ranks must be the same. 
• Each applicant may have K choices and the admission will be done according to his/her choices: if according to the rank list, it 
  is one's turn to be admitted; and if the quota of one's most preferred shcool is not exceeded, then one will be admitted to this 
  school, or one's other choices will be considered one by one in order. If one gets rejected by all of preferred schools, then this 
  unfortunate applicant will be rejected. 
• If there is a tied rank, and if the corresponding applicants are applying to the same school, then that school must admit all the 
  applicants with the same rank, even if its quota will be exceeded. 



## Input Specification: 

Each input file contains one test case. Each case starts with a line containing three positive integers: N (<=40,000), the total number 
of applicants; M (<=100), the total number of graduate schools; and K (<=5), the number of choices an applicant may have.

In the next line, separated by a space, there are M positive integers. The i-th integer is the quota of the i-th graduate school respectively.

Then N lines follow, each contains 2+K integers separated by a space. The first 2 integers are the applicant's GE and GI, respectively. 
The next K integers represent the preferred schools. For the sake of simplicity, we assume that the schools are numbered from 0 to M-1, 
and the applicants are numbered from 0 to N-1.



## Output Specification: 

For each test case you should output the admission results for all the graduate schools. The results of each school must occupy a line, 
which contains the applicants' numbers that school admits. The numbers must be in increasing order and be separated by a space. There 
must be no extra space at the end of each line. If no applicant is admitted by a school, you must output an empty line correspondingly.



## Sample Input:

11 6 3  
2 1 2 2 2 3  
100 100 0 1 2  
60 60 2 3 5  
100 90 0 3 4  
90 100 1 2 0  
90 90 5 1 3  
80 90 1 0 2  
80 80 0 1 2  
80 80 0 1 2  
80 70 1 3 2  
70 80 1 2 3  
100 100 0 2 4  

## Sample Output:

0 10  
3  
5 6 7  
2 8  

1 4  



## 题意：

N个申请人，M所学校，每个申请人可选择申请K所学校。已知每所学校的录取人数限额。输入每个申请人的GE成绩、GI成绩与她/他申请的学校的id（学校id 0～M - 1，
申请人id 0～N - 1）。申请人的排名按总分非递增排序，若有相同的总分则GE成绩分数大的排前面。每所学校在申请这所学校的人中择优录取限额人数，但若有多人
有相同的排名（即有相同的总分与GE成绩），且录取他们之前已录取的人数没有超出限额，则不管录取后是否超出限额，全部录取。求每所学校录取的所有人的id，每
个学校的录取人按id递增排序输出

## 思路：

建立结构体applicant存储申请人（成员：id、GE、GI、总分、存储申请学校的id的数组），以及结构体school存储学校（成员：限额人数、已录取人数、存储已录取的人
的名次的vector ，注意不是存储录取人的id）。

用applicants数组存储所有申请人，schools数组存储所有学校。对applicants数组排序，排序前数组下标等于id，排序后数组下标等于名次。

遍历applicants数组，对于每一个申请人，判断是否能被申请学校录取：

* 1、若申请学校的已录取人数小于限额，则被录取，该申请人的名次（即applicants数组下标）存进该学校的vector
	
* 2、若申请学校的已录取人数大于等于限额，则通过该学校的vector中的最后一个元素（即最后录取的人的名次）作为下标，在applicants数组中找到最后录取的人，若此人的总分与GE成绩都与申请人一样，则也要录取申请人。

遍历schools数组，对于每个学校的vector中的元素排序（按以元素作为下标，在applicants数组中的申请人的id递增排序）。输出以vector的元素作为下标在applicants数组中的申请人的id。




## 代码：


[1080. Graduate Admission (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1080.%20Graduate%20Admission%20(30)/1080.%20Graduate%20Admission%20(30).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

typedef struct ANode {
	int id, ge, gi, total, *choices;//申请人id， ge成绩， gi成绩，总分, 选择的学校的id
} applicant;

typedef struct SNode {
	int quota, n_students; //限额与已录取人数
	vector<int> students; //录取的人在数组applicants中的下标存储在vector中
}school;

applicant * applicants; 

bool compare1(applicant a, applicant b)
{
	return a.total != b.total ? a.total > b.total : a.ge > b.ge;
}

bool compare2(int a, int b)
{
	return applicants[a].id < applicants[b].id;
}

int main()
{
	int n, m, k;
	cin >> n >> m >> k;
	applicants = new applicant[n];
	school *schools = new school[m];
	for (int i = 0; i < m; i++) {
		int quota;
		vector<int> students;
		cin >> quota; //输入每个学校的限额
		schools[i] = {quota, 0, students};
	}
	for (int i = 0; i < n; i++) {
		int ge, gi;
		cin >> ge >> gi;
		int *choices = new int[k];
		for (int j = 0; j < k; j++) 
			cin >> choices[j];
		applicants[i] = { i, ge, gi, ge + gi, choices };
	}
	sort(applicants, applicants + n, compare1);
	for (int i = 0; i < n; i++) { //遍历申请人
		for (int j = 0; j < k; j++) { //该申请人选择的学校
			int school_id = applicants[i].choices[j];
			if (schools[school_id].n_students < schools[school_id].quota) { //该学校已录取的人数少于限额
				schools[school_id].students.push_back(i);
				schools[school_id].n_students++;
				break;
			}
			else if (schools[school_id].n_students >= schools[school_id].quota) //该学校已录取的人数超出限额
				if (applicants[schools[school_id].students.back()].total == applicants[i].total //该申请人与该学校最后录取的一个人总分及ge成绩
					&& applicants[schools[school_id].students.back()].ge == applicants[i].ge) { //相同，也录取
					schools[school_id].students.push_back(i);
					schools[school_id].n_students++;
					break;
				}
		}//for j 学校
	}//for i 申请人
	for (int i = 0; i < m; i++) { //遍历学校
		sort(schools[i].students.begin(), schools[i].students.end(), compare2);
		for (auto it = schools[i].students.begin(); it != schools[i].students.end(); it++) {
			if (it != schools[i].students.begin()) putchar(' ');
			cout << applicants[*it].id;
		}
		cout << endl;
	}
    return 0;
}
```
