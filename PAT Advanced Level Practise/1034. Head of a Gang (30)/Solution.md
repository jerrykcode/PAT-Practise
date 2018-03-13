# 1034. Head of a Gang (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1034)

* 时间限制 100 ms



* 内存限制 65536 kB



* 代码长度限制 16000 B



* 判题程序 Standard 

* 题目作者 CHEN, Yue



One way that the police finds the head of a gang is to check people's phone calls. If there is a phone call between A and B, we say that A and B is related. The weight of a relation is defined to be the total time length of all the phone calls made between the two persons. A "Gang" is a cluster of more than 2 persons who are related to each other with total relation weight being greater than a given threshold K. In each gang, the one with maximum total weight is the head. Now given a list of phone calls, you are supposed to find the gangs and the heads.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains two positive numbers N and K (both less than or equal to 1000), the number of phone calls and the weight threshold, respectively. Then N lines follow, each in the following format:

*Name1 Name2 Time*

where Name1 and Name2 are the names of people at the two ends of the call, and Time is the length of the call. A name is a string of three capital letters chosen from A-Z. A time length is a positive integer which is no more than 1000 minutes.

## Output Specification: 

For each test case, first print in a line the total number of gangs. Then for each gang, print in a line the name of the head and the total number of the members. It is guaranteed that the head is unique for each gang. The output must be sorted according to the alphabetical order of the names of the heads.

## Sample Input 1:  
8 59  
AAA BBB 10  
BBB AAA 20  
AAA CCC 40  
DDD EEE 5  
EEE DDD 70  
FFF GGG 30  
GGG HHH 20  
HHH FFF 10  

## Sample Output 1:  
2  
AAA 3  
GGG 3  

## Sample Input 2:  
8 70  
AAA BBB 10  
BBB AAA 20  
AAA CCC 40  
DDD EEE 5  
EEE DDD 70  
FFF GGG 30  
GGG HHH 20  
HHH FFF 10  

## Sample Output 2:  
0  

## 题意：

输入N（N <= 1000）条通话记录，每条记录包含通话的两个人的名字与通话时间。若一群因通话而关联在一起的人，人数超过2，且他们之间的总通话时间超过一个阈值K，则这一群人为一个团伙。权值（与他人通话总时间）最大的为团伙的头目。求所有团伙的数量，并输出每个团伙的头目的名字与人数。


## 思路：


BFS求连通分量

每输入一条记录，对通话的双方编号，并用map<string, int>及map<int, string>记录人的名字与id之间的关系。邻接矩阵存储图，BFS遍历求连通分量，记录连通分量中的总人数与总权值，及权值最大的顶点。注意点权是一个人与他人通话的总时间，输入一条通话记录时，通话双方的点权都增加，但连通分量的总权值是关联的人之间的通话时间，故遍历时收录一个顶点时，应将其点权的一半加到连通分量的总权值上。题目没有给出最大人数，但最大通话记录数为1000，故最大人数为2000。



## 代码：


[1034. Head of a Gang (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1034.%20Head%20of%20a%20Gang%20(30)/1034.%20Head%20of%20a%20Gang%20(30)_4.cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

int graph[2001][2001];
int weight[2001];
map<string, int> name_to_id;
map<int, string> id_to_name;
int id_count = 1;

struct node {
	int head, n_members;
};

int get_id(string name)
{
	if (name_to_id[name] == 0) {
		name_to_id[name] = id_count;
		id_to_name[id_count++] = name;
	}
	return name_to_id[name];
}

vector<node> bfs(int n, int threshold)
{
	vector<node> gangs;
	int *collected = new int[n];
	fill(collected, collected + n, 0);
	for (int i = 1; i < n; i++) {
		if (collected[i])continue;
		queue<int> q;
		q.push(i);
		collected[i] = 1;
		int n_members = 1, total_weight = weight[i]/2, head = i;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int w = 1; w < n; w ++)
				if (!collected[w] && graph[v][w] != 0) {
					q.push(w);
					collected[w] = 1;
					n_members++;
					total_weight += weight[w]/2;
					if (weight[w] > weight[head]) head = w;
				}
		}
		if (n_members > 2 && total_weight > threshold) 
			gangs.push_back({ head, n_members });
	}
	return gangs;
}

bool compare(node a, node b)
{
	return id_to_name[a.head] < id_to_name[b.head];
}

int main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		string name1, name2;
		int time;
		cin >> name1 >> name2 >> time;
		int id1 = get_id(name1), id2 = get_id(name2);
		graph[id1][id2] += time;
		graph[id2][id1] += time;
		weight[id1] += time;
		weight[id2] += time;
	}
	vector<node> gangs = bfs(id_count, k);
	cout << gangs.size() << endl;
	if (gangs.size() > 0) {
		sort(gangs.begin(), gangs.end(), compare);
		for (auto it = gangs.begin(); it != gangs.end(); it++) 
			cout << id_to_name[it->head] << " " << it->n_members << endl;
	}
    return 0;
}
```