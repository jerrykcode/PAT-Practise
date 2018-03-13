# 1075. PAT Judge (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1075)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



The ranklist of PAT is generated from the status list, which shows the scores of the submittions. This time 
you are supposed to generate the ranklist for PAT. 



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 3 positive integers, N (<=10^4), 
the total number of users, K (<=5), the total number of problems, and M (<=10^5), the total number of submittions. 
It is then assumed that the user id's are 5-digit numbers from 00001 to N, and the problem id's are from 1 to K. 
The next line contains K positive integers p[i] (i=1, ..., K), where p[i] corresponds to the full mark of the i-th 
problem. Then M lines follow, each gives the information of a submittion in the following format:

*user_id problem_id partial_score_obtained*

where partial_score_obtained is either -1 if the submittion cannot even pass the compiler, or is an integer in the 
range [0, p[problem_id]]. All the numbers in a line are separated by a space.



## Output Specification: 

For each test case, you are supposed to output the ranklist in the following format:

*rank user_id total_score s[1] ... s[K]*

where rank is calculated according to the total_score, and all the users with the same total_score obtain the same rank; 
and s[i] is the partial score obtained for the i-th problem. If a user has never submitted a solution for a problem, then 
"-" must be printed at the corresponding position. If a user has submitted several solutions to solve one problem, then 
the highest score will be counted. 

The ranklist must be printed in non-decreasing order of the ranks. For those who have the same rank, users must be sorted in 
nonincreasing order according to the number of perfectly solved problems. And if there is still a tie, then they must be printed 
in increasing order of their id's. For those who has never submitted any solution that can pass the compiler, or has never 
submitted any solution, they must NOT be shown on the ranklist. It is guaranteed that at least one user can be shown on the ranklist.



## Sample Input:

7 4 20  
20 25 25 30  
00002 2 12  
00007 4 17  
00005 1 19  
00007 2 25  
00005 1 20  
00002 2 2  
00005 1 15  
00001 1 18  
00004 3 25  
00002 2 25  
00005 3 22  
00006 4 -1  
00001 2 18  
00002 1 20  
00004 1 15  
00002 4 18  
00001 3 4  
00001 4 2  
00005 2 -1  
00004 2 0  

## Sample Output:

1 00002 63 20 25 - 18  
2 00005 42 20 0 22 -  
2 00007 42 - 25 - 17  
2 00001 42 18 18 4 2  
5 00004 40 15 0 25 -  



## 题意：

Ｎ个用户，Ｋ道题，以及Ｍ个提交，输入Ｎ、Ｋ、Ｍ，Ｋ道题的总分，Ｍ次提交的用户、题目编号、得分，每个用户的每道
题的得分是此用户提交的此题得分中最高的，求用户的排名。按总分非递增排序，若总分相同就按得满分的题目数量非递增
排序，若仍相同则按id递增排序。从未提交过能通过编译的答案的用户不会显示在排名上

## 思路：

结构体存储用户的id，总分，每道题的得分数组，以及flag(是否提交过能通过编译的答案)。对结构体数组排序


## 代码：


[1075. PAT Judge (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1075.%20PAT%20Judge%20(25)/1075.%20PAT%20Judge%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>

typedef struct node {
	int id, total_score, perfect;
	int *score;
	int flag;
} user;

bool compare(user a, user b)
{
	if (!a.flag || !b.flag)
		return a.flag > b.flag;
	if (a.total_score != b.total_score) return a.total_score > b.total_score;
	return a.perfect != b.perfect ? a.perfect > b.perfect : a.id < b.id;
}

int main()
{
	int n, k, m;
	cin >> n >> k >> m;
	int *full_mark = new int[k];
	for (int i = 0; i < k; i++)
		cin >> full_mark[i];
	user *users = new user[n];
	for (int i = 0; i < n; i++) {
		int *score = new int[k];
		for (int j = 0; j < k; j++) score[j] = -1;
		users[i] = {i, 0, 0, score, 0};
	}
	for (int i = 0; i < m; i++) {
		int user_id, problem_id, partial_score;
		cin >> user_id >> problem_id >> partial_score;
		user_id--; //用户id从0~N - 1，输入id从1~N
		problem_id--;
		if (users[user_id].score[problem_id] == -1) users[user_id].score[problem_id] = 0; //若此题之前从未提交过
		if (partial_score == -1) continue; //没通过编译
		users[user_id].flag = 1; //此用户提交了能通过编译的答案
		if (partial_score > users[user_id].score[problem_id]) { //此次得分大于原来得分
			users[user_id].total_score += partial_score - users[user_id].score[problem_id];
			users[user_id].score[problem_id] = partial_score;
			if (partial_score == full_mark[problem_id]) users[user_id].perfect++; //满分
		}
	}
	sort(users, users + n, compare);
	int rank = 1;
	for (int i = 0; i < n; i++) {
		if (!users[i].flag) break;
		if (i > 0 && users[i].total_score == users[i - 1].total_score)
			cout << rank;
		else { cout << i + 1; rank = i + 1; }
		printf(" %05d %d", users[i].id + 1, users[i].total_score);
		for (int j = 0; j < k; j++)
			cout << " " << (users[i].score[j] == -1 ? "-" : std::to_string(users[i].score[j]));
		cout << endl;
	}
    return 0;
}
```