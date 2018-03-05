# 1055. The World's Richest (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1055)
* 时间限制 400 ms

* 内存限制 128000 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue


Forbes magazine publishes every year its list of billionaires based on the annual ranking of the world's 
wealthiest people. Now you are supposed to simulate this job, but concentrate only on the people in a certain 
range of ages. That is, given the net worths of N people, you must find the M richest people in a given range 
of their ages.



## Input Specification:

Each input file contains one test case. For each case, the first line contains 2 positive integers: N (<=10^5) 
- the total number of people, and K (<=10^3) - the number of queries. Then N lines follow, each contains the 
name (string of no more than 8 characters without space), age (integer in (0, 200]), and the net worth (integer 
in [-10^6, 10^6]) of a person. Finally there are K lines of queries, each contains three positive integers: M (<= 
100) - the maximum number of outputs, and [Amin, Amax] which are the range of ages. All the numbers in a line 
are separated by a space.



## Output Specification:

For each query, first print in a line "Case #X:" where X is the query number starting from 1. Then output the M 
richest people with their ages in the range [Amin, Amax]. Each person's information occupies a line, in the format

*Name Age Net_Worth*
					
The outputs must be in non-increasing order of the net worths. In case there are equal worths, it must be in 
non-decreasing order of the ages. If both worths and ages are the same, then the output must be in non-decreasing 
alphabetical order of the names. It is guaranteed that there is no two persons share all the same of the three 
pieces of information. In case no one is found, output "None".



## Sample Input:

12 4  
Zoe_Bill 35 2333  
Bob_Volk 24 5888  
Anny_Cin 95 999999  
Williams 30 -22  
Cindy 76 76000  
Alice 18 88888  
Joe_Mike 32 3222  
Michael 5 300000  
Rosemary 40 5888  
Dobby 24 5888  
Billy 24 5888  
Nobody 5 0  
4 15 45  
4 30 35  
4 5 95  
1 45 50  


## Sample Output:

Case #1:  
Alice 18 88888  
Billy 24 5888  
Bob_Volk 24 5888  
Dobby 24 5888  
Case #2:  
Joe_Mike 32 3222  
Zoe_Bill 35 2333  
Williams 30 -22  
Case #3:  
Anny_Cin 95 999999  
Michael 5 300000  
Alice 18 88888  
Cindy 76 76000  
Case #4:  
None  



题意：

输入N个人的姓名、年龄与财富，输出在M个给定年龄段内的人，对每个年龄段，顺序按财富非递增排序，若财富相同则按
年龄非递减排序，仍有相同则按姓名字符串非递减排序。每个年龄段最多输出给定人数M（M <= 100）人


思路：

本题思路参考了 [1055. The World's Richest (25)(柳婼 の blog)](https://www.liuchuo.net/archives/2255)

结构体数组存储所有人，按财富非递增、年龄非递减、姓名非递减对结构体数组排序。由于每个年龄段最多输出的M <= 100，故
每个岁数的人也不可能输出超过100个人，故将每个岁数的前100个人存储到一个vector中。然后对于每个年龄段，遍历其vector，
输出其中在年龄段内的人


## 参考：

[1055. The World's Richest (25)(柳婼 の blog)](https://www.liuchuo.net/archives/2255)

## 代码：

[1055. The World's Richest (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1055.%20The%20World's%20Richest%20(25)/1055.%20The%20World's%20Richest%20(25).cpp)


```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <algorithm>
#include <string>
#include <vector>

struct node {
	string name;
	int age, worth;
};

bool compare(node a, node b)
{
	if (a.worth != b.worth) return a.worth > b.worth;
	return a.age != b.age ? a.age < b.age : a.name < b.name;
}

int main()
{
	int n, k;
	cin >> n >> k;
	node *rank = new node[n];
	vector<node> rank0;
	for (int i = 0; i < n; i++) 
		cin >> rank[i].name >> rank[i].age >> rank[i].worth;
	int nAge[205];
	fill(nAge, nAge + 205, 0);
	sort(rank, rank + n, compare);
	for (int i = 0; i < n; i++) 
		if (nAge[rank[i].age] < 100) {
			rank0.push_back(rank[i]);
			nAge[rank[i].age] ++;
		}
	for (int i = 0; i < k; i++) {
		int m, amin, amax;
		cin >> m >> amin >> amax;
		printf("Case #%d:\n", i + 1);
		int count = 0;
		for (int j = 0; j < rank0.size(); j++)
			if (rank0[j].age >= amin && rank0[j].age <= amax) {
				cout << rank0[j].name;
				printf(" %d %d\n", rank0[j].age, rank0[j].worth);
				if (++count >= m) break;
			}
		if (count == 0) printf("None\n");
	}
	return 0;
}
```