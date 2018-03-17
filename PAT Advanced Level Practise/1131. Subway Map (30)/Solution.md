# 1131. Subway Map (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1131)

* 时间限制 400 ms

* 内存限制 65536 kB

*代码长度限制　16000 B

* 判题程序 Standard

* 题目作者 CHEN, Yue

In the big cities, the subway systems always look so complex to the visitors. To give you some sense, the following figure shows the map of Beijing subway. Now you are supposed to help people with your computer skills! Given the starting position of your user, your task is to find the quickest way to his/her destination.

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1131_1.jpg)

## Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (< =100), the number of subway lines. Then N lines follow, with the i-th (i = 1, ..., N) line describes the i-th subway line in the format:

*M S[1] S[2] ... S[M]*

where M (<= 100) is the number of stops, and S[i]'s (i = 1, ... M) are the indices of the stations (the indices are 4-digit numbers from 0000 to 9999) along the line. It is guaranteed that the stations are given in the correct order -- that is, the train travels between S[i] and S[i+1] (i = 1, ..., M-1) without any stop.

Note: It is possible to have loops, but not self-loop (no train starts from S and stops at S without passing through another station). Each station interval belongs to a unique subway line. Although the lines may cross each other at some stations (so called "transfer stations"), no station can be the conjunction of more than 5 lines.

After the description of the subway, another positive integer K (<= 10) is given. Then K lines follow, each gives a query from your user: the two indices as the starting station and the destination, respectively.

The following figure shows the sample map.

![](https://raw.githubusercontent.com/jerrykcode/PAT-Practise/master/images/1131_2.jpg)


Note: It is guaranteed that all the stations are reachable, and all the queries consist of legal station numbers.

## Output Specification:

For each query, first print in a line the minimum number of stops. Then you are supposed to show the optimal path in a friendly format as the following:

Take Line#X1 from S1 to S2.
Take Line#X2 from S2 to S3.
......
where Xi's are the line numbers and Si's are the station indices. Note: Besides the starting and ending stations, only the transfer stations shall be printed.

If the quickest path is not unique, output the one with the minimum number of transfers, which is guaranteed to be unique.

## Sample Input:

4  
7 1001 3212 1003 1204 1005 1306 7797  
9 9988 2333 1204 2006 2005 2004 2003 2302 2001  
13 3011 3812 3013 3001 1306 3003 2333 3066 3212 3008 2302 3010 3011  
4 6666 8432 4011 1306  
3  
3011 3013  
6666 2001  
2004 3001  


## Sample Output:

2  
Take Line#3 from 3011 to 3013.  
10  
Take Line#4 from 6666 to 1306.  
Take Line#3 from 1306 to 2302.  
Take Line#2 from 2302 to 2001.  
6  
Take Line#2 from 2004 to 1204.  
Take Line#1 from 1204 to 1306.  
Take Line#3 from 1306 to 3001.  


## 思路：

本题思路参考：[PAT 1131. Subway Map (30) (柳婼 の blog)](https://www.liuchuo.net/archives/3850)

dfs求最短路径

## 代码：

[1131. Subway Map (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1131.%20Subway%20Map%20(30)/1131.%20Subway%20Map%20(30).cpp)

```cpp
#include <iostream>
using namespace std;
#include <vector>

vector<int> graph[10000];
int visit[10000], start, des, minCount, minTransfer;
vector<int> path, best;
int line[10000][10000];

int n_transfer(vector<int> path)
{
	int count = 0;
	for (int i = 1; i < path.size() - 1; i++) {
		if (line[path[i - 1]][path[i]] != line[path[i]][path[i + 1]])
			count++;
	}
	return count;
}

void dfs(int station, int count)
{
	if (station == des) {
		if (count < minCount || count == minCount && n_transfer(path) < minTransfer) {
			best = path;
			minCount = count;
			minTransfer = n_transfer(path);
		}
		return;
	}
	for (auto it = graph[station].begin(); it != graph[station].end(); it++) {
		if (!visit[*it]) {
			visit[*it] = 1;
			path.push_back(*it);
			dfs(*it, count + 1);
			visit[*it] = 0;
			path.pop_back();
		}
	}
}

void printPath(vector<int> path)
{
	for (auto it = path.begin(); it != path.end(); it++) 
		if (*it == start || *it == des || line[*(it - 1)][*it] != line[*it][*(it + 1)]) {
			if (*it != start)
				printf("%04d.\n", *it);
			if (*it != des)
				printf("Take Line#%d from %04d to ", line[*it][*(it + 1)], *it);
		}
}

int main()
{
	int n, m, k;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int pre, station;
		cin >> m >> pre;
		for (int j = 0; j < m - 1; j++) {
			cin >> station;
			graph[pre].push_back(station);
			graph[station].push_back(pre);
			line[pre][station] = line[station][pre] = i + 1;
			pre = station;
		}
	}
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> start >> des;
		minCount = minTransfer = 10001;
		fill(visit, visit + 10000, 0);
		visit[start] = 1;
		path.clear();
		path.push_back(start);
		dfs(start, 0);
		cout << minCount << endl;
		printPath(best);
	}
	return 0;
}
```

