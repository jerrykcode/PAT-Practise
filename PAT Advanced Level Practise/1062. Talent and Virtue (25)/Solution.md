# 1062. Talent and Virtue (25)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1062)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Li



About 900 years ago, a Chinese philosopher Sima Guang wrote a history book in which he talked 
about people's talent and virtue. According to his theory, a man being outstanding in both talent 
and virtue must be a "sage（圣人）"; being less excellent but with one's virtue outweighs talent 
can be called a "nobleman（君子）"; being good in neither is a "fool man（愚人）"; yet a fool man 
is better than a "small man（小人）" who prefers talent than virtue. 

Now given the grades of talent and virtue of a group of people, you are supposed to rank them 
according to Sima Guang's theory. 



## Input Specification: 

Each input file contains one test case. Each case first gives 3 positive integers in a line: N (<=105), 
the total number of people to be ranked; L (>=60), the lower bound of the qualified grades -- that is, 
only the ones whose grades of talent and virtue are both not below this line will be ranked; and H (<100), 
the higher line of qualification -- that is, those with both grades not below this line are considered 
as the "sages", and will be ranked in non-increasing order according to their total grades. Those with 
talent grades below H but virtue grades not are cosidered as the "noblemen", and are also ranked in 
non-increasing order according to their total grades, but they are listed after the "sages". Those with 
both grades below H, but with virtue not lower than talent are considered as the "fool men". They are 
ranked in the same way but after the "noblemen". The rest of people whose grades both pass the L line 
are ranked after the "fool men". 

Then N lines follow, each gives the information of a person in the format:

*ID_Number Virtue_Grade Talent_Grade*

where ID_Number is an 8-digit number, and both grades are integers in [0, 100]. All the numbers are 
separated by a space. 



## Output Specification: 

The first line of output must give M (<=N), the total number of people that are actually ranked. Then M lines 
follow, each gives the information of a person in the same format as the input, according to the ranking rules. 
If there is a tie of the total grade, they must be ranked with respect to their virtue grades in non-increasing 
order. If there is still a tie, then output in increasing order of their ID's. 



## Sample Input:

14 60 80  
10000001 64 90  
10000002 90 60  
10000011 85 80  
10000003 85 80  
10000004 80 85  
10000005 82 77  
10000006 83 76  
10000007 90 78  
10000008 75 79  
10000009 59 90  
10000010 88 45  
10000012 80 100  
10000013 90 99  
10000014 66 60  

## Sample Output:

12  
10000013 90 99  
10000012 80 100  
10000003 85 80  
10000011 85 80  
10000004 80 85  
10000007 90 78  
10000006 83 76  
10000005 82 77  
10000002 90 60  
10000014 66 60  
10000008 75 79  
10000001 64 90  


## 题意：

司马光曰: 
>>"夫聪察强毅之谓才，正直中和之谓德。才者，德之资也；德者，才之帅也... ...是故才德全尽
谓之圣人，才德兼亡谓之愚人，德胜才谓之君子，才胜德谓之小人"(《资治通鉴·周纪》)  

输入最低线与高分线，输入N个人的id、"德"分与"才"分，对他们中"德"分、"才"分均不低于最低线的进行排序，规则：圣人
(才德全尽，"德"分、"才"分均不低于高分线)排在最前，他们中按德与才的总分非递增排序，若总分相同则
按"德"分非递增排序，若仍相同则按id递增排序；圣人之后，对于君子(德胜才，"德"分不低于高分线，"才"
分低于高分线)排序，规则与圣人一样；再之后对愚人(德才兼亡，"德"分与"才"分均低于高分线，但"德"分
不低于"才"分)；最后剩余的"德"分低于高分线且低于"才"分的排在最后。输出排序的人数与排序结果


## 思路：

结构体存储id、"德"分、"才"分，对存储结构体的vector排序，对结构体通过"德"分、"才"分判断其是否为
圣人(0)、君子(1)、愚人(2)、小人(3)，若两个结构体不是一种人则小的排在前，若是同一种人则按总分非
递增，总分相同则按"德"分非递增，"德"分相同则按id递增排序，写出compare函数，调用sort


## 代码：

[1062. Talent and Virtue (25).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1062.%20Talent%20and%20Virtue%20(25)/1062.%20Talent%20and%20Virtue%20(25).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>

int low, high;

typedef struct node {
	int id, virtue, talent;
} person;

int judge(person p)
{
	if (p.virtue >= high && p.talent >= high) //sage
		return 0;
	if (p.virtue >= high && p.talent < high) //nobleman
		return 1;
	if (p.virtue < high && p.talent < high && p.virtue >= p.talent) //fool man
		return 2;
	return 3; //small man
}

bool compare(person a, person b)
{
	if (judge(a) != judge(b))
		return judge(a) < judge(b);
	if (a.virtue + a.talent != b.virtue + b.talent)
		return a.virtue + a.talent > b.virtue + b.talent;
	return a.virtue != b.virtue ? a.virtue > b.virtue : a.id < b.id;
}

int main()
{
	int n;
	cin >> n >> low >> high;
	vector <person> rank;
	int id, virtue, talent;
	for (int i = 0; i < n; i++) {
		cin >> id >> virtue >> talent;
		if (virtue >= low && talent >= low) 
			rank.push_back({id, virtue, talent});
	}
	sort(rank.begin(), rank.end(), compare);
	cout << rank.size() << endl;
	for (auto it = rank.begin(); it != rank.end(); it ++) {
		printf("%d %d %d\n",it->id, it->virtue, it->talent);
	}
    return 0;
}
```