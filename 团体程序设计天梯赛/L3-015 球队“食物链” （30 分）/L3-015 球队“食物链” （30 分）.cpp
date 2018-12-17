#include <iostream>
using namespace std;
#include <vector>

#define WIN(Ti, Tj) (graph[Ti][Tj] == 'W' || graph[Tj][Ti] == 'L')

char **graph;

bool dfs(int start, vector<int>& chain, bool *collected, int n) {
	int size = (int)chain.size();
	int chainLastTeam = chain[size - 1]; //chain is never empty in this function
	if (size == n) {
		if (WIN(chainLastTeam, start)) return true;
	}
	bool flag = true;
	for (int team = 0; team < n; team++)
		if (!collected[team])
			if (WIN(team, start)) {
				flag = false;
				break;
			}
	if (flag) return false;
	for (int team = 0; team < n; team++) {
		if (!collected[team] && WIN(chainLastTeam, team)) {
			chain.push_back(team);
			collected[team] = true;
			if (dfs(start, chain, collected, n)) return true;
			chain.pop_back();
			collected[team] = false;
		}
	}
	return false;
}

int main()
{
	int n;
	cin >> n;
	graph = new char *[n];
	for (int i = 0; i < n; i++) {
		graph[i] = new char[n];
		for (int j = 0; j < n; j++)
			cin >> graph[i][j];
	}
	vector<int> chain;
	bool *collected = new bool[n];
	fill(collected, collected + n, false);
	for (int team = 0; team < n; team++) {
		chain.push_back(team);
		collected[team] = true;
		if (dfs(team, chain, collected, n)) break;
		chain.pop_back();
		collected[team] = false;
	}
	free(collected);
	for (int i = 0; i < n; i++) {
		free(graph[i]);
	}
	free(graph);
	if (chain.empty()) {
		cout << "No Solution" << endl;
	}
	else {
		for (auto it = chain.begin(); it != chain.end(); it++) {
			if (it != chain.begin()) putchar(' ');
			cout << (*it) + 1;
		}
		cout << endl;
	}
	return 0;
}