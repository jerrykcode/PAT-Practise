#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define INFINITE 100000000

int c; //Constant in the function f(C), 常量
int * shortest_edge; //Length of the shortest edge a vertex connected to. 与一顶点相连的最短边长度

/* Calculates the confidence. */
int calc_confidence(int max_weight, int nv_mst) {
    return max_weight + (int)(c/nv_mst + 0.5);
}

/* MST. */
void prim(int **graph, bool * collected, int nv, int s, vector<int>& mst) {
    int *dist = new int[nv]; //Distance between a vertex and the MST
    for (int v = 0; v < nv; v ++) {
        if (collected[v]) continue;
        dist[v] = graph[s][v];
    }   
    collected[s] = true;// Collects the source
    mst.push_back(s);
    dist[s] = 0;
    int max_weight = 0; //Maximum edge weight of the MST
    int nv_mst = 1;
    int confidence = calc_confidence(max_weight, nv_mst); //Calculates the confidence
    while (1) {
        int minV = -1, min = INFINITE;
        for (int v = 0; v < nv; v ++)
            if (!collected[v] && dist[v] < min) {
                min = dist[v];
                minV = v;
            }
        if (minV == -1) break; //无顶点，MST连通分量计算结束
        if (min <= confidence) {
            collected[minV] = true; //Collects minV
            mst.push_back(minV);
            nv_mst++;
            dist[minV] = 0; //Distance between minV and the MST is 0
            for (int v = 0; v < nv; v ++) {
                if (collected[v]) continue;
                if (graph[minV][v] < dist[v])
                    dist[v] = graph[minV][v];
            }
            if (min > max_weight) 
                max_weight = min; //Updates max_weight         
            confidence = calc_confidence(max_weight, nv_mst); //Updates confidence
        }
        else break; //min > confidence, MST连通分量计算结束
    }
    free(dist);
}

bool compare0(int a, int b) {
    return shortest_edge[a] < shortest_edge[b];
}

void mst_components (int **graph, int nv, vector<vector<int>>& msts) {
    bool * collected = new bool[nv];
    fill(collected, collected + nv, false);
    int * sequence = new int [nv]; //Sequence. 顶点调用prim的次序
    for (int i = 0; i < nv; i ++) sequence[i] = i;
    sort(sequence, sequence + nv, compare0); //Sorts according to the length of the minimum edge they connected to
    for (int i = 0; i < nv; i ++) {
        int v = sequence[i];
        if (collected[v]) continue;
        vector<int> mst;
        prim(graph, collected, nv, v, mst);
        sort(mst.begin(), mst.end());
        msts.push_back(mst);
    }
    free(collected);
    free(sequence);
}

bool compare1(vector<int>& a, vector<int>& b) {
    return *(a.begin()) < *(b.begin());
}

int main()
{
    int nv, ne;
    //Input
    cin >> nv >> ne >> c;
    int ** graph = new int *[nv];   
    for (int i = 0; i < nv; i ++) {
        graph[i] = new int[nv];
        fill(graph[i], graph[i] + nv, INFINITE);
    }
    shortest_edge = new int[nv];
    fill(shortest_edge, shortest_edge + nv, INFINITE);
    for (int i = 0; i < ne; i ++) {
        int v1, v2, weight;
        cin >> v1 >> v2 >> weight;
        graph[v1][v2] = graph[v2][v1] = weight;
        if (weight < shortest_edge[v1]) shortest_edge[v1] = weight;
        if (weight < shortest_edge[v2]) shortest_edge[v2] = weight;
    }
    //Calculate
    vector<vector<int>> msts;
    mst_components(graph, nv, msts);
    sort(msts.begin(), msts.end(), compare1);
    //Output
    for (auto i = msts.begin(); i != msts.end(); i ++) {
        for (auto j = i->begin(); j != i->end(); j ++) {
            if (j != i->begin()) putchar(' ');
            cout << *j;
        }
        cout << endl;
    }
    free(graph);
    free(shortest_edge);
    return 0;
}
