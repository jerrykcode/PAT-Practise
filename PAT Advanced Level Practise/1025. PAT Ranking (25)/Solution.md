# 1025. PAT Ranking (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1025)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 作者 CHEN, Yue



Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of 
Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists 
will be merged immediately after the test. Now it is your job to write a program to correctly merge 
all the ranklists and generate the final rank.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains a positive number N (<=100), 
the number of test locations. Then N ranklists follow, each starts with a line containing a positive 
integer K (<=300), the number of testees, and then K lines containing the registration number (a 13-digit number) 
and the total score of each testee. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, first print in one line the total number of testees. Then print the final ranklist 
in the following format:

*registration_number final_rank location_number local_rank*

The locations are numbered from 1 to N. The output must be sorted in nondecreasing order of the final ranks. 
The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order 
of their registration numbers.



## Sample Input:

2  
5  
1234567890001 95  
1234567890005 100  
1234567890003 95  
1234567890002 77  
1234567890004 85  
4  
1234567890013 65  
1234567890011 25  
1234567890014 100  
1234567890012 85  



## Sample Output:

9  
1234567890005 1 1 1  
1234567890014 1 2 1  
1234567890001 3 1 2  
1234567890003 3 1 2  
1234567890004 5 1 4  
1234567890012 5 2 2  
1234567890002 7 1 5  
1234567890013 8 2 3  
1234567890011 9 2 4  


## 题意：

输入PAT的考场数N(<=100)，对每个考场输入考生数K(<=300)，及每个考生的注册号和分数，按照分数非递减排序(分数相同的
有相同的排名，并按注册号非递减排序)输出所有考场所有考生的注册号、总排名、考场号(按输入顺序从1到N编号)，及在其考
场的排名


## 思路：

用结构体存储考生的相关信息，定义长度为30001(100*300 + 1)的结构体数组testees，用int tag(初始化为0)表示已输入的考
生数，对每个考场，输入考生数K，其考生为testees[tag]~testees[tag + K - 1]，对testees[tag]~testees[tag + K - 1]元
素进行排序，排序后得到该考场每个考生在该考场中的排名，tag更新为tag + K，对下一个考场进行输入。最后在对testees整
个数组排序，得到每个考生的总排名，并输出。

## 代码：


[1025. PAT Ranking (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1025.%20PAT%20Ranking%20(25)/1025.%20PAT%20Ranking%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

struct node {
	string registration;
	int score;
	int final_rank;
	int local_number;
	int local_rank;
}testees[30001];

bool compare(struct node a, struct node b)
{
	return a.score == b.score ? a.registration < b.registration : a.score > b.score;
}

int main()
{
	int n, k = 0, tag = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		tag += k;
		cin >> k;
		for (int j = 0; j < k; j++) {
			testees[tag + j].local_number = i + 1; //第i+1个考场
			cin >> testees[tag + j].registration >> testees[tag + j].score;
		}
		sort(testees + tag, testees + tag + k, compare); //对testees[tag]~testees[tag + k]排序，即对第i+1个考场的考生排序
		for (int j = 0; j < k; j++) //第i+1个考场中的排名
			testees[tag + j].local_rank = (j > 0 && testees[tag + j - 1].score == testees[tag + j].score) ? testees[tag + j - 1].local_rank : j + 1;
	}
	cout << tag + k << "\n"; //总考生数
	sort(testees, testees + tag + k, compare);//对所有考场的所有考生排序
	for (int i = 0; i < tag + k; i++) {
		cout << testees[i].registration << " ";
		testees[i].final_rank = (i > 0 && testees[i].score == testees[i - 1].score) ? testees[i - 1].final_rank : i + 1;//总排名
		printf("%d %d %d\n", testees[i].final_rank, testees[i].local_number, testees[i].local_rank);
	}
    return 0;
}

```