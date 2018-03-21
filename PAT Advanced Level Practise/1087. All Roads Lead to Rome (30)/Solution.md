# 1087. All Roads Lead to Rome (30)

[原题地址](https://www.patest.cn/contests/pat-a-practise/1087)

* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



Indeed there are many different tourist routes from our city to Rome. You are supposed to find your 
clients the route with the least cost while gaining the most happiness.



## Input Specification: 

Each input file contains one test case. For each case, the first line contains 2 positive integers N 
(2<=N<=200), the number of cities, and K, the total number of routes between pairs of cities; followed 
by the name of the starting city. The next N-1 lines each gives the name of a city and an integer that 
represents the happiness one can gain from that city, except the starting city. Then K lines follow, 
each describes a route between two cities in the format "City1 City2 Cost". Here the name of a city is 
a string of 3 capital English letters, and the destination is always ROM which represents Rome. 



## Output Specification: 

For each test case, we are supposed to find the route with the least cost. If such a route is not unique, 
the one with the maximum happiness will be recommended. If such a route is still not unique, then we output 
the one with the maximum average happiness -- it is guaranteed by the judge that such a solution exists and 
is unique.

Hence in the first line of output, you must print 4 numbers: the number of different routes with the least 
cost, the cost, the happiness, and the average happiness (take the integer part only) of the recommended route. 
Then in the next line, you are supposed to print the route in the format "City1->City2->...->ROM". 



## Sample Input:

6 7 HZH  
ROM 100  
PKN 40  
GDN 55  
PRS 95  
BLN 80  
ROM GDN 1  
BLN ROM 1  
HZH PKN 1  
PRS ROM 2  
BLN HZH 2  
PKN GDN 1  
HZH PRS 1  

## Sample Output:

3 3 195 97  
HZH->PRS->ROM  


## 题意：

N个城市，K条路，输入起点城市的名字，及其他城市的名字与在该城市游玩的乐趣(点权，起点乐趣为0)，输入K
条路的起点与终点，及路费，求从起点到城市"ROM"的最短路径。费用最小为最短，若有多条费用最小的路径，则
输出路径上乐趣最大的，若仍有多条路径则输出路径上平均乐趣最大的，即路径上经过城市最少的。输出费用最小
的路径条数、最小费用、最大乐趣、最大平均乐趣，然后输出最短路径


## 思路：

对Dijkstra改造

在dijkstra中，每次在未收录的顶点中找到dist(费用)最小的顶点minV收录，对于每个与minV相邻且未收录的顶点，
若经过minV使dist(费用)更小，则更新，若dist(费用)相同但乐趣增多也要更新，若乐趣也不变但经过的城市能减少
也更新。

用int的数组nRoutes存储从起点到每个顶点的费用最小的路径数，在收录minV后，若dist减小则更新nRoutes[v]为
nRoutes[minV]，若dist不变则nRoutes[v] += nRoutes[minV]



## 代码: 

[1087. All Roads Lead to Rome (30)](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1087.%20All%20Roads%20Lead%20to%20Rome%20(30)/1087.%20All%20Roads%20Lead%20to%20Rome%20(30).cpp)

```cpp
#include <iostream>
using namespace std;
#include <string>
#include <map>

#define INF 10000
map<string, int> city_id; //城市名字对应编号
map<int, string> city_name; //城市编号对应名字
int id_count = 0;

int get_id(string city)
{	/* 返回城市的编号 */
	if (city_id[city] == 0) {
		city_id[city] = id_count;
		city_name[id_count++] = city;
	}
	return city_id[city];
}

int minDist(int *dist, int*collected, int n)
{	/* 返回未收录顶点中dist值最小的 */
	int minV = -1, min = INF;
	for (int v = 0; v < n; v++) 
		if (!collected[v] && dist[v] < min) {
			min = dist[v];
			minV = v;
		}
	return minV;
}

void printPath(int s, int des, int *path)
{
	if (path[des] == s)
		cout << city_name[s] << "->" << city_name[des];
	else {
		printPath(s, path[des], path);
		cout << "->" << city_name[des];
	}
}

void dijkstra(int **graph, int *weight, int s, int des, int n)
{	/* dijkstra */
	int *collected = new int[n];
	int *path = new int[n]; //顶点v的路径的上一个顶点为path[v]
	int *dist = new int[n]; //从源s到顶点的当前最短路径长度
	int *happiness = new int[n]; //s到顶点的路径上的总权重
	int *num = new int[n]; //s到顶点路径上经过的顶点个数
	int *nRoutes = new int[n]; //s到顶点的最小dist相同的路径数
	for (int v = 0; v < n; v++) {
		collected[v] = 0;
		dist[v] = graph[s][v];
		path[v] = dist[v] == INF ? -1 : s;
		happiness[v] = weight[v];
		num[v] = dist[v] == INF ? 0 : 1;
		nRoutes[v] = dist[v] == INF ? 0 : 1;
	}
	collected[s] = 1;
	path[s] = s;
	dist[s] = 0;
	happiness[s] = 0;
	num[s] = 1;
	nRoutes[s] = 1;
	while (1) {
		int minV = minDist(dist, collected, n);
		if (minV == des) {
			printf("%d %d %d %d\n", nRoutes[des], dist[des], happiness[des], happiness[des]/num[des]);
			printPath(s, des, path);
			return;
		}
		if (minV == -1)
			break;
		collected[minV] = 1;
		for (int v = 0; v < n; v ++) //遍历每个顶点
			if (!collected[v] && graph[minV][v] < INF) { //v未收录&&minV与v相邻
				if (dist[minV] + graph[minV][v] < dist[v]) { //经过minV使v的路径更短
					dist[v] = dist[minV] + graph[minV][v]; //更新
					path[v] = minV;
					happiness[v] = happiness[minV] + weight[v];
					num[v] = num[minV] + 1;
					nRoutes[v] = nRoutes[minV];
				}
				else if (dist[minV] + graph[minV][v] == dist[v]) { //经过minV使v的路径不变
					nRoutes[v] += nRoutes[minV];
					if (happiness[minV] + weight[v] > happiness[v]) { //经过minV使v的路径乐趣增多
						path[v] = minV;
						happiness[v] = happiness[minV] + weight[v];
						num[v] = num[minV] + 1;
					}
					else if (happiness[minV] + weight[v] == happiness[v] && num[minV] + 1 < num[v]) {//经过minV使v的路径不变、
						path[v] = minV;																	//乐趣不变但经过的城市减少
						num[v] = num[minV] + 1;
					}
				}
			}//for
	}//while
	printf("%d %d %d %d\n", nRoutes[des], dist[des], happiness[des], happiness[des] / num[des]);
	printPath(s, des, path);
}

int main()
{
	int nCities, nRoutes;
	cin >> nCities >> nRoutes;
	int **graph = new int*[nCities]; //图，城市为顶点，路为边
	for (int i = 0; i < nCities; i++) {
		graph[i] = new int[nCities];
		for (int j = 0; j < nCities; j++)
			graph[i][j] = INF;
	}
	string start;
	cin >> start;
	int *happiness = new int[nCities]; //点权
	for (int i = 0; i < nCities - 1; i++) {
		string city;
		cin >> city;
		cin >> happiness[get_id(city)];
	}
	get_id(start);
	for (int i = 0; i < nRoutes; i++) { //插入边
		string city1, city2;
		int cost;
		cin >> city1 >> city2 >> cost;
		int c1 = city_id[city1];
		int c2 = city_id[city2];
		graph[c1][c2] = graph[c2][c1] = cost;
	}
	dijkstra(graph, happiness, get_id(start), city_id["ROM"], nCities);
    return 0;
}
```