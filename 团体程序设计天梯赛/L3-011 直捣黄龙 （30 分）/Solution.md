# L3-011 直捣黄龙 （30 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805049455132672)

>作者: 陈越
单位: 浙江大学
时间限制: 150 ms
内存限制: 64 MB
代码长度限制: 16 KB


本题是一部战争大片 —— 你需要从己方大本营出发，一路攻城略地杀到敌方大本营。首先时间就是生命，所以你必须选择合适的路径，以最快的速度占领敌方大本营。当这样的路径不唯一时，要求选择可以沿途解放最多城镇的路径。若这样的路径也不唯一，则选择可以有效杀伤最多敌军的路径。

## 输入格式：

输入第一行给出 2 个正整数 N（2 ≤ N ≤ 200，城镇总数）和 K（城镇间道路条数），以及己方大本营和敌方大本营的代号。随后 N-1 行，每行给出除了己方大本营外的一个城镇的代号和驻守的敌军数量，其间以空格分隔。再后面有 K 行，每行按格式城镇1 城镇2 距离给出两个城镇之间道路的长度。这里设每个城镇（包括双方大本营）的代号是由 3 个大写英文字母组成的字符串。

## 输出格式：

按照题目要求找到最合适的进攻路径（题目保证速度最快、解放最多、杀伤最强的路径是唯一的），并在第一行按照格式己方大本营->城镇1->...->敌方大本营输出。第二行顺序输出最快进攻路径的条数、最短进攻距离、歼敌总数，其间以 1 个空格分隔，行首尾不得有多余空格。

## 输入样例：
10 12 PAT DBY  
DBY 100  
PTA 20  
PDS 90  
PMS 40  
TAP 50  
ATP 200  
LNN 80  
LAO 30  
LON 70  
PAT PTA 10  
PAT PMS 10  
PAT ATP 20  
PAT LNN 10  
LNN LAO 10  
LAO LON 10  
LON DBY 10  
PMS TAP 10  
TAP DBY 10  
DBY PDS 10  
PDS PTA 10  
DBY ATP 10  


## 输出样例：
PAT->PTA->PDS->DBY  
3 30 210  


## 思路

Dijkstra + DFS

Dijkstra求最优路径。收录与源距离最近的顶点minV，遍历与其相邻并未被收录的顶点，若通过minV可以使源到一顶点的距离减小，则更新该顶点的路径通过minV到达。若距离不变但使路径上经过的顶点数增加则也更新；若路径上经过的顶点数也不变，但路径上经过的顶点的权重和增加，则也更新。用vector数组paths存储所有距离相同的路径，即paths[i]表示所有从源到i的距离相同的路径上i的前一个顶点的集合。dijkstra中通过minV距离减小时，```paths[v].clear(); paths[v].push_back(minV)```(更新v的路径)；距离不变时```paths[v].push_back(minV)```(minV为一条距离相同的路径)。dijkstra结束后用DFS回溯paths，求出所有距离相同的路径数。

## 代码

[L3-011 直捣黄龙 （30 分）.cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/%E5%9B%A2%E4%BD%93%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1%E5%A4%A9%E6%A2%AF%E8%B5%9B/L3-011%20%E7%9B%B4%E6%8D%A3%E9%BB%84%E9%BE%99%20%EF%BC%8830%20%E5%88%86%EF%BC%89/L3-011%20%E7%9B%B4%E6%8D%A3%E9%BB%84%E9%BE%99%20%EF%BC%8830%20%E5%88%86%EF%BC%89.cpp)


```cpp
#include <iostream>
using namespace std;
#include <map>
#include <string>
#include <vector>
#include <stack>

#define INF 1000000

map<string, int> nameToIndex;
map<int, string> indexToName;
string srcName, desName;
int n, src, des;
int indexCount = 1;

int **graph;
int *weight;

int getIndex(string name) {
	if (name == srcName) return 0;
	if (nameToIndex[name] == 0) {
		nameToIndex[name] = indexCount;
		indexToName[indexCount] = name;
		indexCount++;
	}
	return nameToIndex[name];
}

int findMin(int *dist, bool *collected, int n) {
	int minV = -1, min = INF;
	for (int v = 0; v < n; v++)
		if (!collected[v] && dist[v] < min) {
			minV = v;
			min = dist[v];
		}
	return minV;
}

void dijkstra(int *bestPath, vector<int> *paths, int *minDist, int *maxW) {
	int *dist = new int[n];
	int *num = new int[n];
	int *w = new int[n];
	bool *collected = new bool[n];
	for (int v = 0; v < n; v++) {
		dist[v] = graph[src][v];
		num[v] = dist[v] < INF ? 2 : 0;
		w[v] = dist[v] < INF ? weight[src] + weight[v] : 0;
		collected[v] = false;
		bestPath[v] = dist[v] < INF ? src : -1;
		if (bestPath[v] == src) paths[v].push_back(src);
	}
	dist[src] = 0;
	num[src] = 1;
	w[src] = weight[src];
	collected[src] = true;
	while (true) {
		int minV = findMin(dist, collected, n);
		if (minV == des) break;
		collected[minV] = true;
		for (int v = 0; v < n; v++) {
			if (!collected[v] && graph[minV][v] < INF) {
				if (dist[minV] + graph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + graph[minV][v];
					num[v] = num[minV] + 1;
					w[v] = w[minV] + weight[v];
					bestPath[v] = minV;
					paths[v].clear();
					paths[v].push_back(minV);
				}
				else if (dist[minV] + graph[minV][v] == dist[v]) {
					paths[v].push_back(minV);
					if (num[minV] + 1 > num[v]) {
						num[v] = num[minV] + 1;
						w[v] = w[minV] + weight[v];
						bestPath[v] = minV;
					}
					else if (num[minV] + 1 == num[v] && w[minV] + weight[v] > w[v]) {
						w[v] = w[minV] + weight[v];
						bestPath[v] = minV;
					}
				}
			}
		} //for
	} //while
	*minDist = dist[des];
	*maxW = w[des];
	free(dist);
	free(num);
	free(w);
	free(collected);
}

void printPath(int *path) {
	stack<int> s;
	int v = des;
	while (v != src) {
		s.push(v);
		v = path[v];
	}
	cout << indexToName[src];
	while (!s.empty()) {
		cout << "->";
		cout << (indexToName[s.top()]);
		s.pop();
	}
}

int nPaths = 0;
void dfs(vector<int> *paths, int v) {
	if (v == src)
		nPaths++;
	else {
		for (int w : paths[v]) {
			dfs(paths, w);
		}
	}
}

int main() {
	int k;
	cin >> n >> k;
	graph = new int *[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new int[n];
		fill(graph[i], graph[i] + n, INF);
	}
	weight = new int[n];
	fill(weight, weight + n, 0);
	cin >> srcName >> desName;
	src = 0;
	nameToIndex[srcName] = src;
	indexToName[src] = srcName;
	src = getIndex(srcName);
	des = getIndex(desName);
	for (int i = 0; i < n - 1; i++) {
		string cityName;
		int nEnemies;
		cin >> cityName >> nEnemies;
		int cityIndex = getIndex(cityName);
		weight[cityIndex] = nEnemies;
	}
	for (int i = 0; i < k; i++) {
		string cityName1, cityName2;
		int dist;
		cin >> cityName1 >> cityName2 >> dist;
		int cityIndex1 = getIndex(cityName1), cityIndex2 = getIndex(cityName2);
		graph[cityIndex1][cityIndex2] = graph[cityIndex2][cityIndex1] = dist;
	}
	int *bestPath = new int[n];
	vector<int> *paths = new vector<int>[n];
	int minDist, maxW;
	dijkstra(bestPath, paths, &minDist, &maxW);
	printPath(bestPath);
	cout << endl;
	dfs(paths, des);
	cout << nPaths << " " << minDist << " " << maxW;
	free(bestPath);
	for (int i = 0; i < n; i++)
		free(graph[i]);
	free(graph);
	free(weight);
	return 0;
}

```
