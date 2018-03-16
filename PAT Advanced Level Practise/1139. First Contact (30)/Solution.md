# 1139. First Contact (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1139)

* 时间限制 400 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue

Unlike in nowadays, the way that boys and girls expressing their feelings of love was quite subtle in the early years. When a boy A had a crush on a girl B, he would usually not contact her directly in the first place. Instead, he might ask another boy C, one of his close friends, to ask another girl D, who was a friend of both B and C, to send a message to B -- quite a long shot, isn't it? Girls would do analogously.

Here given a network of friendship relations, you are supposed to help a boy or a girl to list all their friends who can possibly help them making the first contact.

## Input Specification:

Each input file contains one test case. For each case, the first line gives two positive integers N (1 < N <= 300) and M, being the total number of people and the number of friendship relations, respectively. Then M lines follow, each gives a pair of friends. Here a person is represented by a 4-digit ID. To tell their genders, we use a negative sign to represent girls.

After the relations, a positive integer K (<= 100) is given, which is the number of queries. Then K lines of queries follow, each gives a pair of lovers, separated by a space. It is assumed that the first one is having a crush on the second one.

## Output Specification:

For each query, first print in a line the number of different pairs of friends they can find to help them, then in each line print the IDs of a pair of friends.

If the lovers A and B are of opposite genders, you must first print the friend of A who is of the same gender of A, then the friend of B, who is of the same gender of B. If they are of the same gender, then both friends must be in the same gender as theirs. It is guaranteed that each person has only one gender.

The friends must be printed in non-decreasing order of the first IDs, and for the same first ones, in increasing order of the seconds ones.

## Sample Input:  

10 18  
-2001 1001  
-2002 -2001  
1004 1001  
-2004 -2001  
-2003 1005  
1005 -2001  
1001 -2003  
1002 1001  
1002 -2004  
-2004 1001  
1003 -2002  
-2003 1003  
1004 -2002  
-2001 -2003  
1001 1003  
1003 -2001  
1002 -2001  
-2002 -2003  
5  
1001 -2001  
-2003 1001  
1005 -2001  
-2002 -2004  
1111 -2003  


## Sample Output:

4  
1002 2004  
1003 2002  
1003 2003  
1004 2002  
4  
2001 1002  
2001 1003  
2002 1003  
2002 1004  
0  
1  
2003 2001  
0  


## 思路：

见代码注释

## 代码：

[1139. First Contact (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1139.%20First%20Contact%20(30)/1139.%20First%20Contact%20(30).cpp) 

```cpp
#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <algorithm>

bool compare(pair<int, int>a, pair<int, int> b)
{
	return a.first != b.first ? a.first < b.first : a.second < b.second;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int>  graph[10000];//邻接表
	int gender[10000];//性别
	for (int i = 0; i < m; i++) {
		string a, b;//输入id时一定要用string，否则无法区分`-0000`与`0000`的性别
		cin >> a >> b;
		int v1 = atoi(a.c_str()), v2 = atoi(b.c_str());
		gender[v1] = a[0] == '-' ? 0 : 1;
		if (v1 < 0) v1 = 0 - v1;
		gender[v2] = b[0] == '-' ? 0 : 1;
		if (v2 < 0) v2 = 0 - v2;
		graph[v1].push_back(v2); //v1、v2是朋友
		graph[v2].push_back(v1);
	}
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		if (a < 0) a = 0 - a;
		if (b < 0) b = 0 - b;
		if (a == b) {
			cout << "0" << endl;
			continue;
		}
		vector<pair<int, int>> friends; //帮助a、b的朋友对
		vector<int> flag[10000]; //flag[id]存储id与a共同的朋友(除b外)
		for (auto it = graph[a].begin(); it != graph[a].end(); it++) //遍历a的朋友
			if (gender[*it] == gender[a] && *it != b) { //该朋友与a同性且不是b
				for (auto i = graph[*it].begin(); i != graph[*it].end(); i++) //遍历该朋友的朋友
					if (*i != b && *i != a) //不是a、b
						flag[*i].push_back(*it); //*it是a的朋友，*i是*it的朋友，*it是*i与a共同的朋友
			}
		for (auto it = graph[b].begin(); it != graph[b].end(); it++) //遍历b的朋友
			if (gender[*it] == gender[b] && *it != a && flag[*it].size() > 0) //性别相同且不是a且有与a共同的朋友(*it是a的某些朋友的朋友)
				for (auto i = flag[*it].begin(); i != flag[*it].end(); i++) //*i是*it与a共同的朋友
					friends.push_back({*i, *it});//*i，*it可与作为一个朋友对。*i是a的朋友，*it是*i的朋友，b是*it的朋友
		sort(friends.begin(), friends.end(), compare);
		cout << friends.size() << endl;
		for (auto it = friends.begin(); it != friends.end(); it++) {
			printf("%04d %04d\n", it->first, it->second);
		}
	}
}
```