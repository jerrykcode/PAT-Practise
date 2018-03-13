# 1114. Family Property (25)



* 时间限制 150 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B


* 判题程序 Standard 

* 作者 CHEN, Yue



This time, you are supposed to help us collect the data for family-owned property. Given each person's family members, and the estate（房产）info under his/her own name, we need to know the size of each family, and the average area and number of sets of their real estate.

## Input Specification: 

Each input file contains one test case. For each case, the first line gives a positive integer N (<=1000). Then N lines follow, each gives the infomation of a person who owns estate in the format:

*ID Father Mother k Child1 ... Childk M_estate Area*

where ID is a unique 4-digit identification number for each person; Father and Mother are the ID's of this person's parents (if a parent has passed away, -1 will be given instead); k (0<=k<=5) is the number of children of this person; Childi's are the ID's of his/her children; M_estate is the total number of sets of the real estate under his/her name; and Area is the total area of his/her estate. 

## Output Specification: 

For each case, first print in a line the number of families (all the people that are related directly or indirectly are considered in the same family). Then output the family info in the format: 

*ID M AVG_sets AVG_area*

where ID is the smallest ID in the family; M is the total number of family members; AVG_sets is the average number of sets of their real estate; and AVG_area is the average area. The average numbers must be accurate up to 3 decimal places. The families must be given in descending order of their average areas, and in ascending order of the ID's if there is a tie. 




## Sample Input:

10
6666 5551 5552 1 7777 1 100  
1234 5678 9012 1 0002 2 300  
8888 -1 -1 0 1 1000  
2468 0001 0004 1 2222 1 500  
7777 6666 -1 0 2 300  
3721 -1 -1 1 2333 2 150  
9012 -1 -1 3 1236 1235 1234 1 100  
1235 5678 9012 0 1 50  
2222 1236 2468 2 6661 6662 1 300  
2333 -1 3721 3 6661 6662 6663 1 100  

## Sample Output:

3
8888 1 1.000 1000.000  
0001 15 0.600 100.000  
5551 4 0.750 100.000  


## 题意：

N个人，输入每个人的id、父母id及所有子女的id，以及此人的房产数量和房产总面积。有亲属关系的人组成一个家庭，每个家庭的id为其成员中id最小的人的id。家庭的相关信息有：id、成员数量、成员人均房产数量和人均面积。输出家庭数量。家庭按成员人均面积递减排序，有相同则按id递增排序。输出所有家庭。所有id不超过4个数字，所有人的id均不相同

## 思路：


*BFS求连通分量*

长度10000的结构体数组存储N个人。数组的下标为该人的id。结构体中用vector存储此人的直接亲属（父母及子女）。这些直接亲属即是与该人直接相邻的顶点（看作图）。BFS求连通分量。一个连通分量即一个家庭。对每个连通分量求出其中最小的id，所有顶点的总房产数量、总面积，从而得到这个家庭的信息。家庭用另一个结构体存储。所有家庭存储在一个vector中，排序后输出


## 代码：

[1114. Family Property (25).cpp ](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1114.%20Family%20Property%20(25)/1114.%20Family%20Property%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>
#include <vector>
#include <algorithm>

typedef struct pnode { 
	int id;
	double  m_estate, area;
	int flag;
	vector<int> direct_relative; /* person的father、mother及children */
} person;

typedef struct fnode { /* family*/
	int id, m;
	double avg_sets, avg_area;
} family;

bool compare(family a, family b)
{
	return a.avg_area != b.avg_area ? a.avg_area > b.avg_area:a.id < b.id;
}

void bfs(person *persons, int * person_id, int n)
{	/* BFS求连通分量 */
	vector<family> families; /* 一个family为一个连通分量，存储在vector中 */
	for (int i = 0; i < n; i++) {
		int id = person_id[i];
		if (persons[id].flag == 1) continue; /* 已记录过 */
		queue<int>q;
		vector<int> family_members; /* 连通分量中的顶点，即家庭成员 */
		q.push(id);
		family_members.push_back(id);
		persons[id].flag = 1;
		while (!q.empty()) { //BFS
			int p = q.front();
			q.pop();
			for (auto it = persons[p].direct_relative.begin(); it != persons[p].direct_relative.end(); it++) //parents或chidren
				if (persons[*it].flag == 0) {
					q.push(*it);
					family_members.push_back(*it);
					persons[*it].flag = 1;
				}
		}
		double total_sets = 0, total_area = 0;
		int min_id = 9999;
		for (auto it = family_members.begin(); it != family_members.end(); it++) {
			total_sets += persons[*it].m_estate;
			total_area += persons[*it].area;
			if (*it < min_id)
				min_id = *it;
		}
		double avg_sets = total_sets  / family_members.size();
		double avg_area = total_area / family_members.size();
		int m = family_members.size();
		families.push_back({ min_id, m, avg_sets, avg_area});
	}
	sort(families.begin(), families.end(), compare);
	cout << families.size() << endl;
	for (auto it = families.begin(); it != families.end(); it++) 
		printf("%04d %d %.3f %.3f\n", it->id, it->m, it->avg_sets, it->avg_area);
}

int main()
{
	int n;
	cin >> n;
	person persons[10000];
	for (int i = 0; i < 10000; i++) persons[i] = {i, 0.0, 0.0, 0};
	int id, father, mother, child, k;
	double m_estate, area;
	int *person_id = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> id >> father >> mother >> k;
		vector<int> direct_relative;
		if (father != -1) {
			direct_relative.push_back(father);
			persons[father].direct_relative.push_back(id); //关系是相互的
		}
		if (mother != -1) {
			direct_relative.push_back(mother);
			persons[mother].direct_relative.push_back(id);
		}
		for (int j = 0; j < k; j++) {
			cin >> child;
			if (child != -1) {
				direct_relative.push_back(child);
				persons[child].direct_relative.push_back(id);
			}
		}
		cin >> m_estate >> area;
		persons[id] = {id, m_estate, area, 0, direct_relative};
		person_id[i] = id;
	}
	bfs(persons, person_id, n);
	return 0;
}
```
