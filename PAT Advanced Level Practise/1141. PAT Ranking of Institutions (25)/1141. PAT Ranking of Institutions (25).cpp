#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <vector>
#include <algorithm>

struct node
{
	string name;
	int sa, sb, st, tws;
	int ns;
} ;

bool compare(node a, node b)
{
	if (a.tws != b.tws) return a.tws > b.tws;
	return a.ns != b.ns ? a.ns < b.ns : a.name < b.name;
}

int main()
{
	map<string, node> schools;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string id, school;
		int score;
		cin >> id >> score >> school;
		for (int j = 0; j < school.length(); j++)
			school[j] = tolower(school[j]);
		char level = id[0];
		schools[school].name = school;
		if (level == 'A')
			schools[school].sa += score;
		else if (level == 'B')
			schools[school].sb += score;
		else if (level == 'T')
			schools[school].st += score;
		schools[school].ns++;
	}
	vector<node> v;
	for (auto it = schools.begin(); it != schools.end(); it++)
	{
		it->second.tws = it->second.sb / 1.5 + it->second.sa + it->second.st*1.5;
		v.push_back(it->second);
	}
	sort(v.begin(), v.end(), compare);
	int rank = 1;
	printf("%d\n", v.size());
	for (int i = 0; i < v.size(); i++)
	{
		if (i != 0 && v[i].tws != v[i - 1].tws)
			rank = i + 1;
		printf("%d %s %d %d\n", rank, v[i].name.c_str(), v[i].tws, v[i].ns);
	}
	return 0;
}