#include <iostream>
using namespace std;
#include <vector>

int main()
{
	int nv, ne;
	cin >> nv >> ne;
	int **graph = new int *[nv];
	for (int i = 0; i < nv; i++)
		graph[i] = new int[nv];
	for (int i = 0; i < ne; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		v1--;
		v2--;
		graph[v1][v2] = graph[v2][v1] = 1;
	}
	int m, k, v, flag;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> k;
		vector<int> sets;
		int *collected = new int[nv];
		for (int j = 0; j < k; j++)
		{
			cin >> v;
			sets.push_back(v - 1);
			collected[v - 1] = 1;
		}
		flag = 0;
		for (int v = 0; v < sets.size(); v++)
		{
			for (int w = 0; w < sets.size(); w ++)
				if (sets[v] != sets[w] && graph[sets[v]][sets[w]] != 1)
				{
					printf("Not a Clique\n");
					flag = 1;
					break;
				}
			if (flag) break;
		}
		if (flag) continue;
		else
		{
			for (int v = 0; v < nv; v++)
			{
				flag = 0;
				if (collected[v] == 1) continue;
				for (int w = 0; w < sets.size(); w++)
					if (graph[v][sets[w]] != 1)
					{
						flag = 1;
						break;
					}
				if (flag == 1) continue;
				else
				{
					printf("Not Maximal\n");
					flag = 2;
					break;
				}
			}
		}
		if (flag != 2)
			printf("Yes\n");
	}

	return 0;
}