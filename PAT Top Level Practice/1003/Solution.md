# 1003 Universal Travel Sites (35)

[原题地址](https://pintia.cn/problem-sets/994805148990160896/problems/994805155688464384)

* Author: CHEN, Yue
* Organization: PAT联盟
* Time Limit: 200ms
* Memory Limit: 64MB
* Code Size Limit: 16KB

After finishing her tour around the Earth, CYLL is now planning a universal travel sites development project. After a careful investigation, she has a list of capacities of all the satellite transportation stations in hand. To estimate a budget, she must know the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

## Input Specification:

Each input file contains one test case. For each case, the first line contains the names of the source and the destination planets, and a positive integer N (<=500). Then N lines follow, each in the format:

source~i~ destination~i~ capacity~i~

where source~i~ and destination~i~ are the names of the satellites and the two involved planets, and capacity~i~ > 0 is the maximum number of passengers that can be transported at one pass from source~i~ to destination~i~. Each name is a string of 3 uppercase characters chosen from {A-Z}, e.g., ZJU.

Note that the satellite transportation stations have no accommodation facilities for the passengers. Therefore none of the passengers can stay. Such a station will not allow arrivals of space vessels that contain more than its own capacity. It is guaranteed that the list contains neither the routes to the source planet nor that from the destination planet.

## Output Specification:

For each test case, just print in one line the minimum capacity that a planet station must have to guarantee that every space vessel can dock and download its passengers on arrival.

## Sample Input:

EAR MAR 11  
EAR AAA 300  
EAR BBB 400  
AAA BBB 100  
AAA CCC 400  
AAA MAR 300  
BBB DDD 400  
AAA DDD 400  
DDD AAA 100  
CCC MAR 400  
DDD CCC 200  
DDD MAR 300  
## Sample Output:

700  

## 题意与思路

最大网络流问题。

对顶点从0开始编号，邻接矩阵存储图，求最大网络流 ：

(0) bfs 求从源到汇的一条增广路径，不存在则结束循环。
(1) 求增广路径中最小权重的边，该最小权重即路径中的最小容量，亦即该增广路径可以增加的流量，设为k。
(2) 增广路径中的每条边的容量减k，对应反向边容量增k。
(3) 重复(0)。

## 代码

[Universal Travel Sites (35).cpp](https://github.com/jerrykcode/PAT-Practise/blob/master/PAT%20Top%20Level%20Practice/1003/Universal%20Travel%20Sites%20(35).cpp)

```cpp
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
```
