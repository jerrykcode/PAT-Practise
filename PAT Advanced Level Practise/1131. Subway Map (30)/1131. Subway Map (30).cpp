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