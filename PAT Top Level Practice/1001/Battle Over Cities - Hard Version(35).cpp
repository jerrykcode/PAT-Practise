//788ms通过，不稳定AC/TLE
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 10000000
#define NA -1

//邻接表表示图，边Edge
struct Edge {
	Edge (int nextCity, int cost, bool isInUse) : nextCity(nextCity), cost(cost), isInUse(isInUse) {}
	int nextCity;
	int cost;
	bool isInUse;
};

vector<Edge>* cityGraph; //图

/* BFS求连通分量 */
int getConnectedComponents(int lostCity, int *componentsID, int n) {
	int countID = 0;
	for (int city = 0; city < n; city++) {
		if (city == lostCity) continue;
		if (componentsID[city] != NA) continue;
		queue<int> q;
		q.push(city);
		componentsID[city] = countID;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (Edge e : cityGraph[v]) {
				if (e.nextCity == lostCity) continue;
				if (componentsID[e.nextCity] != NA) continue;
				if (!e.isInUse) continue;
				componentsID[e.nextCity] = countID;
				q.push(e.nextCity);
			}
		} //while
		countID++;
	}
	return countID;
}

/* 求图的最小生成树 */
int getMSTWeight(int **graph, int n) {
	int mstWeight = 0;
	int src = 0;
	int *dist = new int[n];
	for (int v = 0; v < n; v++) {
		dist[v] = graph[src][v];
	}
	dist[src] = 0;
	int count = 1;
	while (1) {
		int minV = -1, minDist = INF;
		for (int v = 0; v < n; v++)
			if (dist[v] != 0 && dist[v] < minDist) {
				minV = v;
				minDist = dist[v];
			}
		if (minV == -1) break;
		mstWeight += minDist;
		dist[minV] = 0;
		count++;
		for (int v = 0; v < n; v++)
			if (dist[v] != 0 && graph[minV][v] < INF) {
				if (graph[minV][v] < dist[v]) dist[v] = graph[minV][v];
			}
	}
	free(dist);
	return count == n ? mstWeight : INF;
}

int main () 
{
	int n, m;
	scanf("%d %d", &n, &m);
	cityGraph = new vector<Edge>[n];
	int c1, c2, cost, status;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &c1, &c2, &cost, &status);
		c1--;
		c2--;
		Edge e1(c2, cost, status == 1 ? true : false);
		cityGraph[c1].push_back(e1);
		Edge e2(c1, cost, status == 1 ? true : false);
		cityGraph[c2].push_back(e2);
	}
	int lostCity;
	int maxEffort = 0;
	vector<int> maxEffortCity;
	int *componentsID = new int[n];
	for (lostCity = 0; lostCity < n; lostCity++) { //假设lostCity被占领 If lostCity was conquered by the enemy
		fill(componentsID, componentsID + n, NA);
		int nComponents = getConnectedComponents(lostCity, componentsID, n); //求此时的连通分量 BFS: get the connected components(city clusters)
		int repairEffort;
		if (nComponents == 1) //只有1个连通分量，即剩下的城市仍然连通，不需要effort
		                      //If there is only one connected components,then the rest of the cities are connected
			repairEffort = 0;
		else {
		  //以连通分量作为顶点的图 A graph with its vertexes composed by the connected components
			int **graph = new int*[nComponents]; 
			for (int i = 0; i < nComponents; i++) {
				graph[i] = new int[nComponents];
				fill(graph[i], graph[i] + nComponents, INF);
			}
			for (int city = 0; city < n; city++) {
				if (city == lostCity) continue;
				for (Edge e : cityGraph[city]) { //遍历所有的边
					if (e.nextCity == lostCity) continue;
					//若一边的两个顶点位于不同的连通分量内（修复此边可以连接两个连通分量，是一条边）&& 比当前连接这两个连通分量的边短
					//If the two vertexes of an edge are in different connected components then repair this edge we can connected two city clusters
					//&& if the edge is shorter than the current edge between these connected components
					if (componentsID[city] != componentsID[e.nextCity] && e.cost < graph[componentsID[city]][componentsID[e.nextCity]])
						graph[componentsID[city]][componentsID[e.nextCity]] = e.cost;
				}
			}
			//求由连通分量构成的图的最小生成树，MST权重即为lostCity丢失后使剩余城市连通需要的最小修复代价
			//Calculates the MST of this graph. The weight of the MST is the minmum effort to let the cities connected again after lostCity is lost
			repairEffort = getMSTWeight(graph, nComponents); 
			if (repairEffort > maxEffort) {
				maxEffortCity.clear();
				maxEffortCity.push_back(lostCity);
				maxEffort = repairEffort;
			} else if (repairEffort == maxEffort) {
				maxEffortCity.push_back(lostCity);
			}
			for (int i = 0; i < nComponents; i++)
				free(graph[i]);
			free(graph);
		}
	}	
	free(componentsID);
	if (maxEffort == 0) //无需修复
		printf("0");
	else {
		sort(maxEffortCity.begin(), maxEffortCity.end());
		for (auto it = maxEffortCity.begin(); it != maxEffortCity.end(); it++) {
			if (it != maxEffortCity.begin()) putchar(' ');
			printf("%d", (*it) + 1);
		}
	}
	return 0;
}
