
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

#define INF 100000

int findMin(int *arr, bool *collected, int n) {
	int min = INF, minV = -1;
	for (int i = 0; i < n; i++) {
		if (!collected[i] && arr[i] < min) {
			min = arr[i];
			minV = i;
		}
	}
	return minV;
}

void getPath(int *path, int src, int des, int n, vector<int>& vpath) {
	stack<int> s;
	while (des != src) {
		s.push(des);
		des = path[des];
	}
	vpath.push_back(src);
	while (!s.empty()) {
		vpath.push_back(s.top());
		s.pop();
	}
}

int timeDijkstra(int **timeGraph, int **distGraph, int n, int src, int des, vector<int>& vpath) {
	int *time = new int[n];
	int *dist = new int[n];
	int *path = new int[n];
	bool *collected = new bool[n];
	for (int i = 0; i < n; i++) {
		time[i] = timeGraph[src][i];
		dist[i] = distGraph[src][i];
		path[i] = time[i] < INF ? src : -1;
		collected[i] = false;
	}
	time[src] = dist[src] = 0;
	path[src] = -1;
	collected[src] = true;
	while (1) {
		int minV = findMin(time, collected, n);
		if (minV == -1) return -1;
		if (minV == des) break;
		collected[minV] = true;
		for (int v = 0; v < n; v++) {
			if (!collected[v] && timeGraph[minV][v] < INF) {
				if (time[minV] + timeGraph[minV][v] < time[v]) {
					time[v] = time[minV] + timeGraph[minV][v];
					dist[v] = dist[minV] + distGraph[minV][v];
					path[v] = minV;
				}
				else if (time[minV] + timeGraph[minV][v] == time[v] && dist[minV] + distGraph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + distGraph[minV][v];
					path[v] = minV;
				}
			}
		}
	} //while
	getPath(path, src, des, n, vpath);
	int result = time[des];
	free(time);
	free(dist);
	free(path);
	free(collected);
	return result;
}

int distDijkstra(int **distGraph, int n, int src, int des, vector<int>& vpath) {
	int *dist = new int[n];
	int *num = new int[n];
	int *path = new int[n];
	bool *collected = new bool[n];
	for (int i = 0; i < n; i++) {
		dist[i] = distGraph[src][i];
		num[i] = dist[i] < INF ? 2 : -1;
		path[i] = dist[i] < INF ? src : -1;
		collected[i] = false;
	}
	dist[src] = 0;
	num[src] = 1;
	path[src] = -1;
	collected[src] = true;
	while (1) {
		int minV = findMin(dist, collected, n);
		if (minV == -1) return -1;
		if (minV == des) break;
		collected[minV] = true;
		for (int v = 0; v < n; v++) {
			if (!collected[v] && distGraph[minV][v] < INF) {
				if (dist[minV] + distGraph[minV][v] < dist[v]) {
					dist[v] = dist[minV] + distGraph[minV][v];
					num[v] = num[minV] + 1;
					path[v] = minV;
				}
				else if (dist[minV] + distGraph[minV][v] == dist[v] && num[minV] + 1 < num[v]) {
					num[v] = num[minV] + 1;
					path[v] = minV;
				}
			}
		}
	} //while
	getPath(path, src, des, n, vpath);
	int result = dist[des];
	free(dist);
	free(num);
	free(path);
	free(collected);
	return result;
}

int main()
{
	int n, m;
	std::cin >> n >> m;
	int **timeGraph = new int*[n];
	int **distGraph = new int*[n];
	for (int i = 0; i < n; i++) {
		timeGraph[i] = new int[n];
		distGraph[i] = new int[n];
		for (int j = 0; j < n; j++)
			timeGraph[i][j] = distGraph[i][j] = INF;
	}
	for (int i = 0; i < m; i++) {
		int v1, v2, oneWay, len, time;
		std::cin >> v1 >> v2 >> oneWay >> len >> time;
		distGraph[v1][v2] = len;
		timeGraph[v1][v2] = time;
		if (oneWay == 0) {
			distGraph[v2][v1] = len;
			timeGraph[v2][v1] = time;
		}
	}
	int src, des;
	std::cin >> src >> des;
	vector<int> timePath;
	int t = timeDijkstra(timeGraph, distGraph, n, src, des, timePath);
	for (int i = 0; i < n; i++)
		free(timeGraph[i]);
	free(timeGraph);
	vector<int> distPath;
	int d = distDijkstra(distGraph, n, src, des, distPath);
	for (int i = 0; i < n; i++)
		free(distGraph[i]);
	free(distGraph);
	bool equal = true;
	if (timePath.size() != distPath.size())
		equal = false;
	else {
		for (int i = 0; i < timePath.size(); i++)
			if (timePath[i] != distPath[i]) {
				equal = false;
				break;
			}
	}
	if (equal) {
		printf("Time = %d; Distance = %d: ", t, d);
		for (auto it = timePath.begin(); it != timePath.end(); it++) {
			if (it != timePath.begin()) cout << " => ";
			cout << *it;
		}
	}
	else {
		printf("Time = %d: ", t);
		for (auto it = timePath.begin(); it != timePath.end(); it++) {
			if (it != timePath.begin()) cout << " => ";
			cout << *it;
		}
		cout << endl;
		printf("Distance = %d: ", d);
		for (auto it = distPath.begin(); it != distPath.end(); it++) {
			if (it != distPath.begin()) cout << " => ";
			cout << *it;
		}
	}
	return 0;
}
