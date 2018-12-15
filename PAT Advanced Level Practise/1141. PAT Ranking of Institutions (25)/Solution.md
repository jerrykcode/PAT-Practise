# 1141. PAT Ranking of Institutions (25)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1141)

* 时间限制 500 ms/考试时是800ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue

After each PAT, the PAT Center will announce the ranking of institutions based on their students' performances. Now you are asked to generate the ranklist.

## Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (<=105), which is the number of testees. Then N lines follow, each gives the information of a testee in the following format:

*ID Score School*

where "ID" is a string of 6 characters with the first one representing the test level: "B" stands for the basic level, "A" the advanced level and "T" the top level; "Score" is an integer in [0, 100]; and "School" is the institution code which is a string of no more than 6 English letters (case insensitive). Note: it is guaranteed that "ID" is unique for each testee.

## Output Specification:

For each case, first print in a line the total number of institutions. Then output the ranklist of institutions in nondecreasing order of their ranks in the following format:

*Rank School TWS Ns*

where "Rank" is the rank (start from 1) of the institution; "School" is the institution code (all in lower case); "TWS" is the total weighted score which is defined to be the integer part of "ScoreB/1.5 + ScoreA + ScoreT*1.5", where "ScoreX" is the total score of the testees belong to this institution on level X; and "Ns" is the total number of testees who belong to this institution.

The institutions are ranked according to their TWS. If there is a tie, the institutions are supposed to have the same rank, and they shall be printed in ascending order of Ns. If there is still a tie, they shall be printed in alphabetical order of their codes.

## Sample Input:

10  
A57908 85 Au  
B57908 54 LanX  
A37487 60 au  
T28374 67 CMU  
T32486 24 hypu  
A66734 92 cmu  
B76378 71 AU  
A47780 45 lanx  
A72809 100 pku  
A03274 45 hypu  

## Sample Output:

5  
1 cmu 192 2  
1 au 192 3  
3 pku 100 1  
4 hypu 81 2  
4 lanx 81 2  


## 思路：

map存储学校名称(string)与学校结构体的对应，输入考生时，该考生的学校的人数++，相应等级的总分增加。然后遍历map，算出每个学校的TWS，并将学校存入vector中，对vector排序后输出。

## 代码：
[1141. PAT Ranking of Institutions (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1141.%20PAT%20Ranking%20of%20Institutions%20(25)/1141.%20PAT%20Ranking%20of%20Institutions%20(25).cpp)


```cpp
#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>
#include <algorithm>

struct node
{
	string name;
	int sa, sb, st, tws;
	int ns;
} ;

bool compare(node a, node b)
{
	if (a.tws != b.tws) return a.tws > b.tws;
	return a.ns != b.ns ? a.ns < b.ns : a.name < b.name;
}

int main()
{
	map<string, node> schools;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string id, school;
		int score;
		cin >> id >> score >> school;
		for (int j = 0; j < school.length(); j++)
			school[j] = tolower(school[j]);
		char level = id[0];
		schools[school].name = school;
		if (level == 'A')
			schools[school].sa += score;
		else if (level == 'B')
			schools[school].sb += score;
		else if (level == 'T')
			schools[school].st += score;
		schools[school].ns++;
	}
	vector<node> v;
	for (auto it = schools.begin(); it != schools.end(); it++)
	{
		it->second.tws = it->second.sb / 1.5 + it->second.sa + it->second.st*1.5;
		v.push_back(it->second);
	}
	sort(v.begin(), v.end(), compare);
	int rank = 1;
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++)
	{
		if (i != 0 && v[i].tws != v[i - 1].tws)
			rank = i + 1;
		printf("%d %s %d %d\n", rank, v[i].name.c_str(), v[i].tws, v[i].ns);
	}
	return 0;
}
```



