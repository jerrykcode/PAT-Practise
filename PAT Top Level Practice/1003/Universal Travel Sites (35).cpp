#include <iostream>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <queue>
using namespace std;

#define INF 1000000

map<string, int> name_to_index;
int n_v = 0; //number of vertexes
int src_idx, des_idx; //index of the source and the destination

struct Edge {
    int v, w; //Edge v -> w
    int c;
    Edge(int v, int w, int c) : v(v), w(w), c(c) {} 
};

int getIndexFromName(string name) {
    if (name_to_index[name] == 0) {
        name_to_index[name] = n_v + 1;
        n_v++;
    }
    return name_to_index[name] - 1; //index start from 0
}

bool bfs(int **graph, int *path) {
    bool *collected = new bool[n_v];
    memset(collected, false, n_v);
    queue <int> q;
    q.push(src_idx);
    collected[src_idx] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int w = 0; w < n_v; w++)
            if (!collected[w] && graph[v][w] != 0) {
                path[w] = v;
                q.push(w);
                collected[w] = true;
                if (w == des_idx) {
                    free(collected);
                    return true;
                }
            }
    }
    free(collected);
    return false;
}

int main()
{
    string src, des;
    cin >> src >> des;
    src_idx = getIndexFromName(src);
    des_idx = getIndexFromName(des);
    int n_edges;
    cin >> n_edges;
    vector<Edge> edges;
    for (int i = 0; i < n_edges; i++) {
        string v, w;
        int v_idx, w_idx, c;
        cin >> v >> w >> c;
        v_idx = getIndexFromName(v);
        w_idx = getIndexFromName(w);
        Edge e(v_idx, w_idx, c);
        edges.push_back(e);
    }
    int **graph = new int*[n_v];
    for (int i = 0; i < n_v; i++) {
        graph[i] = new int[n_v];
        fill(graph[i], graph[i] + n_v, 0);
    }
    for (Edge e : edges) {
        graph[e.v][e.w] = e.c;
    }
    int *path = new int[n_v];
    memset(path, -1, n_v);
    int flow = 0;
    while (bfs(graph, path)) {
        int min_c = INF;
        for (int v = des_idx; v != src_idx; v = path[v]) {
            if (graph[path[v]][v] < min_c)
                min_c = graph[path[v]][v];
        }
        flow += min_c;
        for (int v = des_idx; v != src_idx; v = path[v]) {
            graph[path[v]][v] -= min_c;
            graph[v][path[v]] += min_c;
        }
    }
    cout << flow << endl;
    free(path);
    free(graph);
    return 0;
}
