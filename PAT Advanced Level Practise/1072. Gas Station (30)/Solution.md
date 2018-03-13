# 1072. Gas Station (30)
[原题地址](https://www.patest.cn/contests/pat-a-practise/1072)
* 时间限制 200 ms

* 内存限制 65536 kB

* 代码长度限制 16000 B

* 判题程序 Standard 

* 题目作者 CHEN, Yue



A gas station has to be built at such a location that the minimum distance between the station and 
any of the residential housing is as far away as possible. However it must guarantee that all the 
houses are in its service range.

Now given the map of the city and several candidate locations for the gas station, you are supposed 
to give the best recommendation. If there are more than one solution, output the one with the smallest 
average distance to all the houses. If such a solution is still not unique, output the one with the 
smallest index number.


## Input Specification: 

Each input file contains one test case. For each case, the first line contains 4 positive integers: N (<= 103), 
the total number of houses; M (<= 10), the total number of the candidate locations for the gas stations; K (<= 104), 
the number of roads connecting the houses and the gas stations; and DS, the maximum service range of the gas station. 
It is hence assumed that all the houses are numbered from 1 to N, and all the candidate locations are numbered from 
G1 to GM.

Then K lines follow, each describes a road in the format
*P1 P2 Dist*
where P1 and P2 are the two ends of a road which can be either house numbers or gas station numbers, and Dist is the 
integer length of the road.


## Output Specification: 

For each test case, print in the first line the index number of the best location. In the next line, print the minimum 
and the average distances between the solution and all the houses. The numbers in a line must be separated by a space 
and be accurate up to 1 decimal place. If the solution does not exist, simply output “No Solution”. 


## Sample Input 1:

4 3 11 5  
1 2 2  
1 4 2  
1 G1 4  
1 G2 3  
2 3 2  
2 G2 1  
3 4 2  
3 G3 2  
4 G1 3  
G2 G1 1  
G3 G2 2  

## Sample Output 1:

G1  
2.0 3.3  


## Sample Input 2:

2 1 2 10  
1 G1 9  
2 G1 20  

## Sample Output 2:

No Solution  



## 题意：

N个居住地，M个候选修建加油站的地点，K条路。输入N、M、K以及DS（加油站的最远服务距离），输入每条路的起点、终点
与长度，起点和终点可以是一个居住地或候选地点。求在哪个候选地点修建加油站，可以使与加油站距离最近的居住地的距
离最远，且每个居住地都在加油站的服务距离内。若有多个加油站符合条件，则输出与每个居住地距离的平均值最小的，若
仍不唯一，输出序号最小的。若不存在符合条件的加油站，输出"No Solution"

## 思路：

居住地与候选地一起作为图的顶点，设与加油站距离最近的居住地的距离为max_min，初始化为0。对于每个候选地，将其作
为源调用dijkstra算法，得到与除源自己外每个顶点的最短距离，对于居住地，若有距离大于DS，则此候选地被排除，居住
地与源的最短距离中的最小值若大于max_min则更新，若不大于max_min但源与各居住地的距离之和减小也更新，若其他不变，
序号减小也更新(候选地从小到大试探，则不用考虑序号大小)

## 代码：

[1072. Gas Station (30).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Advanced%20Level%20Practise/1072.%20Gas%20Station%20(30)/1072.%20Gas%20Station%20(30).cpp)

```cpp
#include "stdafx.h"
#include <iostream>
using namespace std;
#include <string>
#define INF 100000

int get_id(string s, int n)
{	/* 返回城市在图中的编号 */
	if (s[0] == 'G') {
		s.erase(s.begin());
		return atoi(s.c_str()) + n - 1;
	}
	return atoi(s.c_str()) - 1;
}

int findMin(int *dist, int *collected, int n)
{	/* 返回未受录的顶点中dist值最小的 */
	int min = INF, minV = -1;
	for (int v = 0; v < n; v++) 
		if (!collected[v] && dist[v] < min) {
			min = dist[v];
			minV = v;
		}
	return minV;
}

int * dijkstra(int **graph, int s, int n)
{	/* 最短路径 */
	int *collected = new int[n]; /* 是否被收录过 */
	int *dist = new int[n]; /* 当前最短距离 */
	for (int i = 0; i < n; i++) {
		collected[i] = 0;
		dist[i] = graph[s][i];
	}
	collected[s] = 1;
	dist[s] = 0;
	while (1) {
		int min = findMin(dist, collected, n);
		if (min == -1) break;
		collected[min] = 1;
		for (int v = 0; v < n; v ++) /* 遍历每个顶点 */
			if (!collected[v] && graph[min][v] < INF) /* 未收录&&与min相邻 */
				if (dist[min] + graph[min][v] < dist[v]) /* 若通过min使路径更短 */
					dist[v] = dist[min] + graph[min][v]; /* 更新 */
	}
	return dist;
}

int main()
{
	int n, m, k, d;
	cin >> n >> m >> k >> d;
	int nVertexes = n + m; //图的顶点数
	int **graph = new int *[nVertexes];
	for (int i = 0; i < nVertexes; i++) {
		graph[i] = new int[nVertexes];
		for (int j = 0; j < nVertexes; j++)
			graph[i][j] = INF;
	}
	for (int i = 0; i < k; i++) {
		string v, w;
		int len, v_id, w_id;
		cin >> v >> w >> len;
		v_id = get_id(v, n);
		w_id = get_id(w, n);
		graph[v_id][w_id] = graph[w_id][v_id] = len;
	}
	int max_min = 0; //max_min是最远的最短距离
	int min_sum = INF;
	int best = -1;
	for (int i = 0; i < m; i++) { /* G1 ~ Gm (n ~ n + m - 1) */
		int *dist = dijkstra(graph, n + i, nVertexes);
		int minDist = INF, sum = 0, flag = 0;
		for (int v = 0; v < n; v++) { //0 ~ n-1
			if (dist[v] > d) { flag = 1;  break; }
			if (dist[v] < minDist) minDist = dist[v];
			sum += dist[v];
		}
		if (flag == 1) continue;
		if (minDist > max_min) { //minDist更大
			max_min = minDist;
			min_sum = sum;
			best = i;
		}
		else if (minDist == max_min && sum < min_sum) { //minDist相同但sum更小，故平均值更小
			min_sum = sum;
			best = i;
		}
	}
	if (best == -1) {
		cout << "No Solution" << endl;
		return 0;
	}
	printf("G%d\n%.1f %.1f\n", best + 1, max_min*1.0, (min_sum*1.0)/n);
    return 0;
}
```