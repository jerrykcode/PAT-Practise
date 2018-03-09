# 1076. Forwards on Weibo (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1076)
* 时间限制 3000 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue


Weibo is known as the Chinese version of Twitter. One user on Weibo may have many followers, and 
may follow many other users as well. Hence a social network is formed with followers relations. 
When a user makes a post on Weibo, all his/her followers can view and forward his/her post, which 
can then be forwarded again by their followers. Now given a social network, you are supposed to 
calculate the maximum potential amount of forwards for any specific user, assuming that only L levels 
of indirect followers are counted.

## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive integers: N (<=1000), 
the number of users; and L (<=6), the number of levels of indirect followers that are counted. Hence it is 
assumed that all the users are numbered from 1 to N. Then N lines follow, each in the format:

*M[i] user_list[i]*

where M[i] (<=100) is the total number of people that user[i] follows; and user_list[i] is a list of the M[i] users 
that are followed by user[i]. It is guaranteed that no one can follow oneself. All the numbers are separated by a space.

Then finally a positive K is given, followed by K UserID's for query. 


## Output Specification: 

For each UserID, you are supposed to print in one line the maximum potential amount of forwards this user can triger, 
assuming that everyone who can view the initial post will forward it once, and that only L levels of indirect followers 
are counted. 


## Sample Input:

7 3  
3 2 3 4  
0  
2 5 6  
2 3 1  
2 3 4  
1 4  
1 5  
2 2 6  

## Sample Output:

4  
5  

## 题意：

N个用户（用户编号1~N），假设一个用户发了一条微博，他/她的粉丝就会看到并有可能转发，若一个粉丝转发了，那么这个
粉丝的粉丝也会看到并有可能转发，若考虑L层粉丝关系，输入N个用户每人关注的用户，输入K个用户，对他们中的每一个，
求若此用户发了一条微博，最多可能有几人转发（只考虑L层粉丝）

## 思路：

用户作为图的顶点，用户到粉丝有边，但到他关注的人之间没有边（即某人发了微博他的粉丝会看到但他的关注不会看到）。
用BFS遍历L层内相邻的顶点，计数，具体算法实现见代码

## 代码：

[1076. Forwards on Weibo (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1076.%20Forwards%20on%20Weibo%20(30)/1076.%20Forwards%20on%20Weibo%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <queue>

int bfs(int **graph, int s, int n, int l)
{	/* 返回连通分量中与源相距L层内的元素个数 */
	int *collected = new int[n];
	fill(collected, collected + n, 0);
	int count = 0, tail = s, last = s, level = 0; //tail是一层中的最后一个，last是当前最后一个进队列的
	queue<int>q;
	q.push(s);
	collected[s] = 1;
	while (!q.empty() && level < l) { //在L层内
		int v = q.front();
		q.pop();
		for (int w = 0; w < n; w ++)
			if (!collected[w] && graph[v][w]) {
				q.push(w);
				collected[w] = 1;
				count++;
				last = w; //last是当前最后一个进队列的
			}
		if (v == tail) { //出队列的是上一层的最后一个，last变为这一层最后一个，进入下一层
			level++;
			tail = last;
		}
	}
	return count;
}

int main()
{
	int n, l;
	cin >> n >> l;
	int **graph = new int *[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
		for (int j = 0; j < n; j++)
			graph[i][j] = 0;
	}
	for (int i = 0; i < n; i++) {
		int n_followed;
		cin >> n_followed;
		for (int j = 0; j < n_followed; j++) {
			int followed;
			cin >> followed;
			followed--;
			graph[followed][i] = 1; //用户到粉丝之间有边
		}
	}
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int query;
		cin >> query;
		cout << bfs(graph, query - 1, n, l) << endl;
	}
    return 0;
}
```