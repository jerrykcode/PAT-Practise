L3-005 垃圾箱分布 （30 分）

[原题地址](https://pintia.cn/problem-sets/994805046380707840/problems/994805052131098624)

> 作者: 陈越  
> 单位: 浙江大学  
> 时间限制: 200 ms  
> 内存限制: 64 MB  
> 代码长度限制: 16 KB  

大家倒垃圾的时候，都希望垃圾箱距离自己比较近，但是谁都不愿意守着垃圾箱住。所以垃圾箱的位置必须选在到所有居民点的最短距离最长的地方，同时还要保证每个居民点都在距离它一个不太远的范围内。

现给定一个居民区的地图，以及若干垃圾箱的候选地点，请你推荐最合适的地点。如果解不唯一，则输出到所有居民点的平均距离最短的那个解。如果这样的解还是不唯一，则输出编号最小的地点。

## 输入格式：

输入第一行给出4个正整数：N（≤10^?3??）是居民点的个数；M（≤10）是垃圾箱候选地点的个数；K（≤10^?4??）是居民点和垃圾箱候选地点之间的道路的条数；D?S
??是居民点与垃圾箱之间不能超过的最大距离。所有的居民点从1到N编号，所有的垃圾箱候选地点从G1到GM编号。

随后K行，每行按下列格式描述一条道路：

> P1 P2 Dist


其中P1和P2是道路两端点的编号，端点可以是居民点，也可以是垃圾箱候选点。Dist是道路的长度，是一个正整数。

## 输出格式：

首先在第一行输出最佳候选地点的编号。然后在第二行输出该地点到所有居民点的最小距离和平均距离。数字间以空格分隔，保留小数点后1位。如果解不存在，则输出No Solution。

## 输入样例1：

> 4 3 11 5  
> 1 2 2  
> 1 4 2  
> 1 G1 4  
> 1 G2 3  
> 2 3 2  
> 2 G2 1  
> 3 4 2  
> 3 G3 2  
> 4 G1 3  
> G2 G1 1  
> G3 G2 2  


## 输出样例1：

> G1  
> 2.0 3.3  


## 输入样例2：

> 2 1 2 10  
> 1 G1 9  
> 2 G1 20  


## 输出样例2：

> No Solution  

## 思路:

对每一个垃圾箱候选点，以它作为源进行dijkstra，求它与所有居民点之间的最短距离，并记录最短距离中的最大值，最小值，及所有最短距离之和。
若最大值超出DS，或者居民点不连通(dijkstra过程中收录的居民点数小于n)，则不考虑此候选点。最短距离中的最小值越大越好，最小值相同时，距
离之和越小越好，距离和仍然相同时，编号越小越好。

## 代码

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define INF 1000000

typedef short Vertex; 
typedef struct Edge { 
	Vertex v;
	Vertex w;
	double dist;
	Edge(Vertex v, Vertex w, double dist) : v(v), w(w), dist(dist) {}
} *PEdge;

typedef struct GNode { //Node of graph
	Vertex v;
	vector<PEdge> edges; //边的指针
	GNode(Vertex v) : v(v) {}
} *PGNode;
typedef PGNode *Graph; //图是一个存储指针的数组，指针指向图顶点信息

Graph graph;
int n, m, k, ds;

typedef int index_t; //图数组的下标
index_t stoidx(string name) { //返回一个输入的顶点在graph中的下标
	if (name[0] != 'G') //若顶点是居民点
		return stoi(name) - 1; //输入从1开始
	else //若顶点是候选垃圾箱
		return n + (int)name[1] - (int)'0' - 1;
}

void input_graph() {
	scanf("%d %d %d %d", &n, &m, &k, &ds);
	graph = new PGNode[n + m];
	for (int i = 0; i < n + m; i++)
		graph[i] = new GNode((Vertex)i); //初始化顶点
	for (int i = 0; i < k; i++) {
		string p1, p2;
		double dist;
		cin >> p1 >> p2 >> dist;
		index_t idx1 = stoidx(p1), idx2 = stoidx(p2);
		PEdge pEdge = new Edge((Vertex)idx1, (Vertex)idx2, dist);
		//插入边
		graph[idx1]->edges.push_back(pEdge);
		graph[idx2]->edges.push_back(pEdge);
	}
}

index_t findMin(double *dist, bool *collected) { //返回未收录的dist最小的顶点下标
	index_t min_idx = -1;
	double min_dist = INF;
	for (index_t i = 0; i < n + m; i++)
		if (!collected[i] && dist[i] < min_dist) {
			min_idx = i;
			min_dist = dist[i];
		}
	return min_idx;
}

void findBestPosition() {
	index_t best_idx = -1;
	double best_min_dist = 0;
	double best_total_dist = -1;
	double *dist = new double[n + m];
	bool *collected = new bool[n + m];
	for (index_t candidate_idx = n; candidate_idx < n + m; candidate_idx++) {
		//遍历每一个候选垃圾箱，以它为源进行dijkstra，计算它与所有居民点的最短距离
		double min_dist = INF, max_dist = 0, total_dist = 0;
		fill(dist, dist + n + m, INF);
		fill(collected, collected + n + m, false);
		dist[candidate_idx] = 0;
		int nv = 0;
		while (1) {
			index_t idx = findMin(dist, collected);
			if (idx == -1) break;
			if (idx < n) { //若idx是居民点
				if (dist[idx] < min_dist) min_dist = dist[idx];
				if (dist[idx] > max_dist) max_dist = dist[idx];
				if (max_dist > ds) break; //若距离超出ds
				total_dist += dist[idx];
				nv++;
			}
			collected[idx] = true;
			for (PEdge pEdge : graph[idx]->edges) {
				index_t neighbor = (index_t)pEdge->v == idx ? (index_t)pEdge->w : (index_t)pEdge->v;
				if (!collected[neighbor])
					if (dist[idx] + pEdge->dist < dist[neighbor]) dist[neighbor] = dist[idx] + pEdge->dist;
			}
		} //while
		if (max_dist > ds || nv < n) continue; //最大距离超出ds或者居民点不连通，则不考虑此候选点
		if (min_dist > best_min_dist) {
			best_min_dist = min_dist;
			best_total_dist = total_dist;
			best_idx = candidate_idx;
		}
		else if (min_dist == best_min_dist && total_dist < best_total_dist) {
			best_total_dist = total_dist;
			best_idx = candidate_idx;
		}
		else if (min_dist == best_min_dist && total_dist == best_total_dist && candidate_idx < best_idx) {
			best_idx = candidate_idx;
		}
	}
	free(dist);
	free(collected);	
	if (best_idx == -1) 
		printf("No Solution\n");
	else 
		printf("G%d\n%.1f %.1f", best_idx - n + 1, best_min_dist, best_total_dist/n);
}

void deleteMemory() { //释放内存
	map<PEdge, bool> hasDeleted; //记录边结点是否delete过
	for (index_t i = 0; i < n + m; i++) {
		if (graph[i] != NULL) {			
			for (auto it = graph[i]->edges.begin(); it != graph[i]->edges.end(); it++)
				if (*it != NULL && !hasDeleted[*it]) {
					delete *it;	
					hasDeleted[*it] = true; //记录该结点已被delete，避免重复删除
					*it = NULL;
				}
			graph[i]->edges.clear();
			vector<PEdge>().swap(graph[i]->edges);
			delete graph[i];
			graph[i] = NULL;
		}
	}
	free(graph);
	hasDeleted.clear(); //map<PEdge, bool>中PEdge指向的内存已被释放
	map<PEdge, bool>().swap(hasDeleted);
}

int main() {
	input_graph();
	findBestPosition();
	deleteMemory();
	return 0;
}

```

