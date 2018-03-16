#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <algorithm>

bool compare(pair<int, int>a, pair<int, int> b)
{
	return a.first != b.first ? a.first < b.first : a.second < b.second;
}

int main()
{
	int n, m;
	cin >> n >> m;
	vector<int>  graph[10000];//邻接表
	int gender[10000];//性别
	for (int i = 0; i < m; i++) {
		string a, b;//输入id时一定要用string，否则无法区分`-0000`与`0000`的性别
		cin >> a >> b;
		int v1 = atoi(a.c_str()), v2 = atoi(b.c_str());
		gender[v1] = a[0] == '-' ? 0 : 1;
		if (v1 < 0) v1 = 0 - v1;
		gender[v2] = b[0] == '-' ? 0 : 1;
		if (v2 < 0) v2 = 0 - v2;
		graph[v1].push_back(v2); //v1、v2是朋友
		graph[v2].push_back(v1);
	}
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
		if (a < 0) a = 0 - a;
		if (b < 0) b = 0 - b;
		if (a == b) {
			cout << "0" << endl;
			continue;
		}
		vector<pair<int, int>> friends; //帮助a、b的朋友对
		vector<int> flag[10000]; //flag[id]存储id与a共同的朋友(除b外)
		for (auto it = graph[a].begin(); it != graph[a].end(); it++) //遍历a的朋友
			if (gender[*it] == gender[a] && *it != b) { //该朋友与a同性且不是b
				for (auto i = graph[*it].begin(); i != graph[*it].end(); i++) //遍历该朋友的朋友
					if (*i != b && *i != a) //不是a、b
						flag[*i].push_back(*it); //*it是a的朋友，*i是*it的朋友，*it是*i与a共同的朋友
			}
		for (auto it = graph[b].begin(); it != graph[b].end(); it++) //遍历b的朋友
			if (gender[*it] == gender[b] && *it != a && flag[*it].size() > 0) //性别相同且不是a且有与a共同的朋友(*it是a的某些朋友的朋友)
				for (auto i = flag[*it].begin(); i != flag[*it].end(); i++) //*i是*it与a共同的朋友
					friends.push_back({*i, *it});//*i，*it可与作为一个朋友对。*i是a的朋友，*it是*i的朋友，b是*it的朋友
		sort(friends.begin(), friends.end(), compare);
		cout << friends.size() << endl;
		for (auto it = friends.begin(); it != friends.end(); it++) {
			printf("%04d %04d\n", it->first, it->second);
		}
	}
}