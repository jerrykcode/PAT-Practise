#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int bfs(vector<int> * graph, int s, int * components_index, int index, int n) {
    queue<int> q;
    bool *tmp_collected = new bool[n];
    fill(tmp_collected, tmp_collected + n, false);
    q.push(s);
    if (components_index[s] == -1)
        components_index[s] = index;
    tmp_collected[s] = true;
    int last = s, tail = s, level = 0;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int w : graph[v]) {
            if (!tmp_collected[w]) {
                q.push(w);
                if (components_index[w] == -1)
                    components_index[w] = index;
                tmp_collected[w] = true;
                last = w;
            }
        }
        if (v == tail) {
            level++;
            tail = last;
        }
    }
    free(tmp_collected);
    return level - 2;
}

int main ()
{
    int n;
    cin >> n;
    vector<int> * graph = new vector<int>[n];
    int k, p;
    for (int i = 0; i < n; i++) {
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> p;
            p--;
            graph[i].push_back(p);
            graph[p].push_back(i);
        }
    }
    int * components_index = new int[n];
    fill(components_index, components_index + n, -1);
    map<int, int> diameter;
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (components_index[i] == -1)
            index++;
        int level = bfs(graph, i, components_index, index, n);
        if (level > diameter[index])
            diameter[index] = level;
    }
    int max_dia = 0;
    for (auto it = diameter.begin(); it != diameter.end(); it++)
        if (it->second > max_dia)
            max_dia = it->second;
    cout << index + 1 << " " << max_dia;
    free(components_index);
    return 0;
}
